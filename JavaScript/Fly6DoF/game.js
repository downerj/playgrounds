import { loadAllResourcesAsync, modelAssets, RuntimeObject } from "./resources.js";
import { AnimationTimer } from "./timer.js";

/**
 * @import { ModelAsset } from './resources.js'
 */

/**
 * @param {HTMLCanvasElement} canvas
 * @throws An error if unable to initialize a WebGL 2 context
 */
const initializeGL = (canvas) => {
  const gl = canvas.getContext('webgl2');
  if (gl == null) {
    throw new Error('Failed to initialize WebGL 2 context');
  }
  return gl;
};

export class Game {
  /**
   * @type {WebGL2RenderingContext}
   */
  #gl;
  /**
   * @type {AnimationTimer}
   */
  #timer;
  /**
   * @type {{ [name: string]: WebGLProgram }}
   */
  #programs = {
    main: undefined
  };
  /**
   * @type {{ [name: string]: RuntimeObject }}
   */
  #dataObjects = {
    shape: undefined
  }

  /**
   * @param {HTMLCanvasElement} canvas
   */
  constructor(canvas) {
    this.#gl = initializeGL(canvas);
    console.log('WebGL 2 context initialized');
    this.#timer = new AnimationTimer(timestamp => this.#onTick(timestamp), 1000/60);
  }

  /**
   *
   */
  async initializeGraphicsAsync() {
    const gl = this.#gl;
    try {
      const resources = await loadAllResourcesAsync();
      const mainVertexShader = this.#initializeShader(resources.mainVertexSource, gl.VERTEX_SHADER);
      const mainFragmentShader = this.#initializeShader(resources.mainFragmentSource, gl.FRAGMENT_SHADER);
      const mainProgram = (() => {
        try {
          return this.#initializeProgram(mainVertexShader, mainFragmentShader);
        } catch (ex) {
          throw ex;
        } finally {
          gl.deleteShader(mainVertexShader);
          gl.deleteShader(mainFragmentShader);
        }
      })();
      const shape = this.#initializeVertexArray(modelAssets.triangle, mainProgram);
      this.#dataObjects.shape = shape;
      this.#programs.main = mainProgram;
      return true;
    } catch (ex) {
      console.error(ex);
      return false;
    }
  }

  /**
   * @param {string} source
   * @param {GLenum} type
   * @returns {WebGLShader}
   */
  #initializeShader(source, type) {
    const gl = this.#gl;
    const shader = gl.createShader(type);
    gl.shaderSource(shader, source);
    gl.compileShader(shader);
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
      const typeString = type === gl.VERTEX_SHADER ? 'vertex' : 'fragment'
      const log = gl.getShaderInfoLog(shader);
      throw new Error(`Unable to compile ${typeString} shader: ${log}`);
    }
    return shader;
  }

  /**
   * @param {WebGLShader} vertexShader
   * @param {WebGLShader} fragmentShader
   * @return {WebGLProgram}
   */
  #initializeProgram(vertexShader, fragmentShader) {
    const gl = this.#gl;
    const program = gl.createProgram();
    gl.attachShader(program, vertexShader);
    gl.attachShader(program, fragmentShader);
    gl.linkProgram(program);
    gl.detachShader(program, vertexShader);
    gl.detachShader(program, fragmentShader);
    if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
      const log = gl.getProgramInfoLog(program);
      throw new Error(`Unable to link program: ${log}`);
    }
    return program;
  }

  /**
   * @param {GLenum} target
   * @param {AllowSharedBufferSource} data
   * @param {GLenum} usage
   * @returns {WebGLBuffer}
   */
  #initializeBuffer(target, data, usage) {
    const gl = this.#gl;
    const buffer = gl.createBuffer();
    gl.bindBuffer(target, buffer);
    gl.bufferData(target, data, usage);
    gl.bindBuffer(target, null);
    return buffer;
  }

  /**
   * @param {ModelAsset} asset
   * @param {WebGLProgram} program
   * @returns {RuntimeObject}
   */
  #initializeVertexArray(asset, program) {
    const gl = this.#gl;

    gl.useProgram(program);
    const vao = gl.createVertexArray();
    gl.bindVertexArray(vao);

    const positionLocation = gl.getAttribLocation(program, 'position');
    const colorLocation = gl.getAttribLocation(program, 'color');

    const vbo = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
    gl.bufferData(gl.ARRAY_BUFFER, asset.vertices, gl.STATIC_DRAW);
    gl.enableVertexAttribArray(positionLocation);
    gl.vertexAttribPointer(positionLocation, 3, gl.FLOAT, false, 0, 0);

    const colorBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, asset.colors, gl.STATIC_DRAW);
    gl.enableVertexAttribArray(colorLocation);
    gl.vertexAttribPointer(colorLocation, 4, gl.FLOAT, false, 0, 0);

    const ibo = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, ibo);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, asset.indices, gl.STATIC_DRAW);

    gl.bindVertexArray(null);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
    gl.useProgram(null);

    return new RuntimeObject(vao, vbo, ibo, colorBuffer, asset.indexCount);
  }

  /**
   *
   */
  run() {
    this.#timer.resume();
    console.log('Animation timer started');
  }

  /**
   *
   */
  updateCanvasSize() {
    const gl = this.#gl;
    gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);
  }

  /**
   *
   */
  #render() {
    const gl = this.#gl;

    gl.useProgram(this.#programs.main);
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);
    gl.enable(gl.CULL_FACE);
    gl.frontFace(gl.CCW);
    gl.cullFace(gl.BACK);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    gl.useProgram(this.#programs.main);
    const shape = this.#dataObjects.shape;
    gl.bindVertexArray(shape.vao);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, shape.ibo);
    gl.drawElements(gl.TRIANGLES, shape.indexCount, gl.UNSIGNED_SHORT, 0);

    gl.bindVertexArray(null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
  }

  /**
   * @param {DOMHighResTimeStamp} _timestamp
   */
  #onTick(_timestamp) {
    this.#render();
  }

  /**
   *
   */
  #cleanUpAll() {
    const gl = this.#gl;

    gl.bindVertexArray(null);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
    for (const dataObject of Object.values(this.#dataObjects)) {
      gl.deleteVertexArray(dataObject.vao);
      gl.deleteBuffer(dataObject.vbo);
      gl.deleteBuffer(dataObject.ibo);
      gl.deleteBuffer(dataObject.colorBuffer);
    }

    gl.useProgram(null);
    for (const program of Object.values(this.#programs)) {
      gl.deleteProgram(program);
    }
  }
}
