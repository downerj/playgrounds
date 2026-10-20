import { AnimationTimer } from "./timer.js";

class ModelAsset {
  /**
   * @type {Float32Array}
   */
  vertices;
  /**
   * @type {Uint16Array}
   */
  indices;
  /**
   * @type {Float32Array}
   */
  colors;
  /**
   * @type {number}
   */
  indexCount;

  /**
   * @param {Iterable<number>} vertexData
   * @param {Iterable<number>} indexData
   * @param {Iterable<number>} colorData
   */
  constructor(vertexData, indexData, colorData) {
    this.vertices = new Float32Array(vertexData);
    this.indices = new Uint16Array(indexData);
    this.colors = new Float32Array(colorData);
    this.indexCount = indexData.length;
  }
}

class RuntimeObject {
  /**
   * @type {WebGLVertexArrayObject}
   */
  vao;
  /**
   * @type {WebGLBuffer}
   */
  vbo;
  /**
   * @type {WebGLBuffer}
   */
  ibo;
  /**
   * @type {WebGLBuffer}
   */
  colorBuffer;
  /**
   * @type {number}
   */
  indexCount;

  /**
   * @param {WebGLVertexArrayObject} vao
   * @param {WebGLBuffer} vbo
   * @param {WebGLBuffer} ibo
   * @param {WebGLBuffer} colorBuffer
   * @param {number} indexCount
   */
  constructor(vao, vbo, ibo, colorBuffer, indexCount) {
    this.vao = vao;
    this.vbo = vbo;
    this.ibo = ibo;
    this.colorBuffer = colorBuffer;
    this.indexCount = indexCount;
  }
}

const modelDefintions = {
  rectangle: {
    vertices: [
      // Bottom left
      -1.0, -1.0, 0.0,
      // Bottom right
      1.0, -1.0, 0.0,
      // Top right
      1.0, 1.0, 0.0,
      // Top left
      -1.0, 1.0, 0.0
    ],
    indices: [
      0, 1, 2,
      0, 2, 3
    ],
    colors: [
      // Bottom left
      1.0, 0.0, 0.0, 1.0,
      // Bottom right
      0.0, 1.0, 0.0, 1.0,
      // Top right
      0.0, 0.0, 1.0, 1.0,
      // Top left
      1.0, 1.0, 1.0, 1.0
    ]
  }
};

const modelAssets = {
  rectangle: new ModelAsset(
    modelDefintions.rectangle.vertices,
    modelDefintions.rectangle.indices,
    modelDefintions.rectangle.colors
  )
};

class ResourcePack {
  /**
   * @type {string}
   */
  mainVertexSource = '';
  /**
   * @type {string}
   */
  mainFragmentSource = '';
}

/**
 * @param {URL} url
 * @returns {string}
 */
const loadResourceAsync = (async url => {
  const response = await fetch(url, { cache: 'no-store' });
  if (!response.ok) {
    throw new Error(`Unable to load resource from ${url}: ${response.status}`);
  }
  return await response.text();
});

/**
 * @returns {ResourcePack}
 */
const loadAllResourcesAsync = (async () => {
  const resources = new ResourcePack();
  resources.mainVertexSource = await loadResourceAsync('./main.vert');
  resources.mainFragmentSource = await loadResourceAsync('./main.frag');
  return resources;
});

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
   * @type {HTMLCanvasElement}
   */
  #canvas;
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
  #prorgams = {
    main: undefined
  };
  /**
   * @type {{ [name: string]: RuntimeObject }}
   */
  #dataObjects = {
    rectangle: undefined
  }

  /**
   * @param {HTMLCanvasElement} canvas
   * @param {}
   */
  constructor(canvas) {
    this.#canvas = canvas;
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
      const rectangle = this.#initializeVertexArray(
        modelAssets.rectangle,
        gl.getAttribLocation(mainProgram, 'position'),
        gl.getAttribLocation(mainProgram, 'color')
      );
      this.#dataObjects.rectangle = rectangle;
      this.#prorgams.main = mainProgram;
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

  // /**
  //  * @param {GLenum} target
  //  * @param {AllowSharedBufferSource} data
  //  * @param {GLenum} usage
  //  * @returns {WebGLBuffer}
  //  */
  // #initializeBuffer(target, data, usage) {
  //   const gl = this.#gl;
  //   const buffer = gl.createBuffer();
  //   gl.bindBuffer(target, buffer);
  //   gl.bufferData(target, data, usage);
  //   gl.bindBuffer(target, null);
  //   return buffer;
  // }

  /**
   * @param {ModelAsset} asset
   * @param {GLuint} positionLocation
   * @param {GLuint} colorLocation
   * @returns {RuntimeObject}
   */
  #initializeVertexArray(asset, positionLocation, colorLocation) {
    const gl = this.#gl;

    const vao = gl.createVertexArray();
    gl.bindVertexArray(vao);

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

    gl.useProgram(this.#prorgams.main);
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);
    gl.enable(gl.CULL_FACE);
    gl.frontFace(gl.CCW);
    gl.cullFace(gl.BACK);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    gl.useProgram(this.#prorgams.main);
    const rectangle = this.#dataObjects.rectangle;
    gl.bindVertexArray(rectangle.vao);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, rectangle.ibo);
    gl.drawElements(gl.TRIANGLES, rectangle.indexCount, gl.UNSIGNED_SHORT, 0);

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
  cleanUpAll() {
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
    for (const program of Object.values(this.#prorgams)) {
      gl.deleteProgram(program);
    }
  }
}
