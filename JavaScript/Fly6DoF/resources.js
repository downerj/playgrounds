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

class Colors {
  static black = [0.0, 0.0, 0.0];
  static red = [1.0, 0.0, 0.0];
  static yellow = [1.0, 1.0, 0.0];
  static green = [0.0, 1.0, 0.0];
  static cyan = [0.0, 1.0, 1.0];
  static blue = [0.0, 0.0, 1.0];
  static magenta = [1.0, 0.0, 1.0];
  static white = [1.0, 1.0, 1.0];
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
      ...Colors.red, 1.0,
      // Bottom right
      ...Colors.green, 1.0,
      // Top right
      ...Colors.blue, 1.0,
      // Top left
      ...Colors.white, 1.0
    ]
  },
  triangle: {
    vertices: [
      // Bottom left
      -1.0, -1.0, 0.0,
      // Bottom right
      1.0, -1.0, 0.0,
      // Top middle
      0.0, 1.0, 0.0
    ],
    indices: [
      0, 1, 2
    ],
    colors: [
      // Bottom left
      ...Colors.red, 1.0,
      // Bottom right
      ...Colors.green, 1.0,
      // Top middle
      ...Colors.blue, 1.0
    ]
  },
  cube: {
    vertices: [
      // Front
      -1.0, -1.0, -1.0,
      1.0, -1.0, -1.0,
      1.0, 1.0, -1.0,
      -1.0, 1.0, -1.0,
      // Back
      -1.0, -1.0, 1.0,
      1.0, -1.0, 1.0,
      1.0, 1.0, 1.0,
      -1.0, 1.0, 1.0
    ],
    indices: [
      // Front
      0, 1, 2,
      0, 2, 3,
      // Left
      1, 5, 6,
      1, 6, 2,
      // Top
      3, 2, 6,
      3, 6, 7,
      // Back
      5, 4, 7,
      5, 7, 6,
      // Right
      4, 0, 3,
      4, 3, 7,
      // Bottom
      0, 1, 5,
      0, 5, 4
    ],
    colors: [
      ...Colors.red, 1.0,
      ...Colors.green, 1.0,
      ...Colors.blue, 1.0,
      ...Colors.white, 1.0,
      ...Colors.yellow, 1.0,
      ...Colors.black, 1.0,
      ...Colors.cyan, 1.0,
      ...Colors.magenta, 1.0
    ]
  }
};

export const modelAssets = {
  rectangle: new ModelAsset(
    modelDefinitions.rectangle.vertices,
    modelDefinitions.rectangle.indices,
    modelDefinitions.rectangle.colors
  ),
  triangle: new ModelAsset(
    modelDefinitions.triangle.vertices,
    modelDefinitions.triangle.indices,
    modelDefinitions.triangle.colors
  ),
  cube: new ModelAsset(
    modelDefinitions.cube.vertices,
    modelDefinitions.cube.indices,
    modelDefinitions.cube.colors
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
