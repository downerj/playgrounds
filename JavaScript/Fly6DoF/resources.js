export class ModelAsset {
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

export class RuntimeObject {
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

export const modelDefinitions = {
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

export const modelAssets = {
  rectangle: new ModelAsset(
    modelDefinitions.rectangle.vertices,
    modelDefinitions.rectangle.indices,
    modelDefinitions.rectangle.colors
  )
};

export class ResourcePack {
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
export const loadResourceAsync = (async url => {
  const response = await fetch(url, { cache: 'no-store' });
  if (!response.ok) {
    throw new Error(`Unable to load resource from ${url}: ${response.status}`);
  }
  return await response.text();
});

/**
 * @returns {ResourcePack}
 */
export const loadAllResourcesAsync = (async () => {
  const resources = new ResourcePack();
  resources.mainVertexSource = await loadResourceAsync('./main.vert');
  resources.mainFragmentSource = await loadResourceAsync('./main.frag');
  return resources;
});
