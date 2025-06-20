import { Geometry } from "./geometry.js";

class ProgramInfo {
  /**
   * @param {WebGL2RenderingContext} gl
   * @param {string} vertexSource
   * @param {string} fragmentSource
   */
  constructor(gl, vertexSource, fragmentSource) {
    this.#gl = gl;
    const vertexShader = this.#createShader(gl.VERTEX_SHADER, vertexSource);
    const fragmentShader = this.#createShader(gl.FRAGMENT_SHADER, fragmentSource);
    const program = gl.createProgram();
    gl.attachShader(program, vertexShader);
    gl.attachShader(program, fragmentShader);
    gl.linkProgram(program);
    const status = gl.getProgramParameter(program, gl.LINK_STATUS);
    if (!status) {
      const programLog = gl.getProgramInfoLog(program);
      console.error(`Program log: ${programLog}`);
      const vertexLog = gl.getShaderInfoLog(vertexShader);
      if (vertexLog != null) {
        console.error(`Vertex log: ${vertexLog}`);
      }
      const fragmentLog = gl.getShaderInfoLog(fragmentShader);
      if (fragmentLog != null) {
        console.error(`Fragment log: ${fragmentLog}`);
      }
    }
    gl.detachShader(program, vertexShader);
    gl.deleteShader(vertexShader);
    gl.detachShader(program, fragmentShader);
    gl.deleteShader(fragmentShader);
    if (!status) {
      gl.deleteProgram(program);
      throw 'Failed to create WebGL2 program';
    }
    this.#program = program;
  };

  get program() {
    return this.#program;
  }

  useProgram() {
    const gl = this.#gl;
    gl.useProgram(this.#program);
  }

  /**
   * @type {WebGL2RenderingContext}
   */
  #gl;
  /**
   * @type {WebGLProgram}
   */
  #program;

  /**
   * @param {GLenum} type
   * @param {string} source
   * @returns {WebGLShader}
   */
  #createShader(type, source) {
    const gl = this.#gl;
    const shader = gl.createShader(type);
    gl.shaderSource(shader, source);
    gl.compileShader(shader);
    return shader;
  }
}

class VertexArrayInfo {
  /**
   *
   * @param {WebGLVertexArrayObject} vertexArray
   * @param {GLenum} drawMode
   * @param {number} indexCount
   */
  constructor(vertexArray, drawMode, indexCount) {
    this.#vertexArray = vertexArray;
    this.#drawMode = drawMode;
    this.#indexCount = indexCount;
  }

  get vertexArray() {
    return this.#vertexArray;
  }

  get drawMode() {
    return this.#drawMode;
  }

  get indexCount() {
    return this.#indexCount;
  }

  /**
   * @type {WebGLVertexArrayObject}
   */
  #vertexArray;
  /**
   * @type {GLenum}
   */
  #drawMode;
  /**
   * @type {number}
   */
  #indexCount;
}

export class Graphics3D {
  /**
   * @param {HTMLCanvasElement} canvas
   */
  constructor(canvas) {
    this.#gl = canvas.getContext('webgl2');
    if (!this.#gl) {
      throw 'Failed to get WebGL2 context';
    }
    this.#programInfo = new ProgramInfo(
      this.#gl,
      this.#mainVertexSource,
      this.#mainFragmentSource
    );
  }

  /**
   * @param {Geometry} geometry
   */
  addObject(geometry) {
    const gl = this.#gl;
    const { program } = this.#programInfo;
    const { vertices, colors, indices } = geometry;
    const vao = gl.createVertexArray();
    gl.bindVertexArray(vao);

    const vertexBuffer = this.#initBuffer(gl.ARRAY_BUFFER, vertices);
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    const vertexLocation = gl.getAttribLocation(program, 'aVertex');
    gl.vertexAttribPointer(vertexLocation, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vertexLocation);

    const colorBuffer = this.#initBuffer(gl.ARRAY_BUFFER, colors);
    gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
    const colorLocation = gl.getAttribLocation(program, 'aColor');
    gl.vertexAttribPointer(colorLocation, 4, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(colorLocation);

    const indexBuffer = this.#initBuffer(gl.ELEMENT_ARRAY_BUFFER, indices);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);

    gl.bindVertexArray(null);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
    this.#buffers.push(vertexBuffer, colorBuffer, indexBuffer);

    const vaoInfo = new VertexArrayInfo(vao, gl.TRIANGLES, indices.length);
    this.#vertexArrayInfos.push(vaoInfo);
  }

  /**
   *
   */
  render() {
    const gl = this.#gl;
    gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);
    gl.enable(gl.DEPTH_TEST);
    gl.clearColor(0., .7, 1., 1.);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    this.#programInfo.useProgram();
    gl.enable(gl.CULL_FACE);
    gl.cullFace(gl.BACK);
    gl.frontFace(gl.CCW);
    for (const vaoInfo of this.#vertexArrayInfos) {
      gl.bindVertexArray(vaoInfo.vertexArray);
      gl.drawElements(
        vaoInfo.drawMode,
        vaoInfo.indexCount,
        gl.UNSIGNED_SHORT,
        0
      );
    }
    gl.bindVertexArray(null);
  }

  /**
   * @param {GLenum} target
   * @param {ArrayBufferView} data
   * @param {GLenum?} usage
   * @returns {WebGLBuffer}
   */
  #initBuffer(target, data, usage) {
    const gl = this.#gl;
    const buffer = gl.createBuffer();
    gl.bindBuffer(target, buffer);
    gl.bufferData(target, data, usage ?? gl.STATIC_DRAW);
    gl.bindBuffer(target, null);
    return buffer;
  };

  /**
   * @type {WebGL2RenderingContext}
   */
  #gl;

  /**
   * @type {ProgramInfo}
   */
  #programInfo;

  /**
   * @type {WebGLBuffer[]}
   */
  #buffers = [];

  /**
   * @type {VertexArrayInfo[]}
   */
  #vertexArrayInfos = [];

  #mainVertexSource = `#version 300 es
in vec3 aVertex;
in vec4 aColor;
out vec4 vColor;

void main(void) {
  gl_Position = vec4(aVertex, 1.);
  vColor = aColor;
}
`;

  #mainFragmentSource = `#version 300 es
#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif // GL_FRAGMENT_PRECISION_HIGH

in vec4 vColor;
out vec4 fragColor;

void main(void) {
  fragColor = vColor;
}
`;

}
