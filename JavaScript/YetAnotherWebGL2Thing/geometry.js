export class Geometry {
  get vertices() {}
  get colors() {}
  get indices() {}
}

export class SimpleTriangle extends Geometry {
  get vertices() {
    return this.#vertices;
  }

  get colors() {
    return this.#colors;
  }

  get indices() {
    return this.#indices;
  }

  #vertices = new Float32Array([
    // Bottom left
    -1., -1., 0.,
    // Bottom right
    1., -1., 0.,
    // Top middle
    0., 1., 0.
  ]);

  #colors = new Float32Array([
    // Bottom left
    // Red
    1., 0., 0., 1.,
    // Bottom right
    // Green
    0., 1., 0., 1.,
    // Top middle
    // Blue
    0., 0., 1., 1.
  ]);

  #indices = new Uint16Array([
    0, 1, 2
  ]);
}

export class Cube extends Geometry {
  get vertices() {
    return this.#vertices;
  }

  get colors() {
    return this.#colors;
  }

  get indices() {
    return this.#indices;
  }

  #vertices = new Float32Array([
    // Bottom left front
    -1., -1., -1.,
    // Bottom right front
    1., -1., -1.,
    // Top right front
    1., 1., -1.,
    // Top left front
    -1., 1., -1.,
    // Top left back
    -1., 1., 1.,
    // Top right back
    1., 1., 1.,
    // Bottom right back
    1., -1., 1.,
    // Bottom left back
    -1., -1., 1.
  ]);

  #colors = new Float32Array([
    // Bottom left front
    // Red
    1., 0., 0., 1.,
    // Bottom right front
    // Green
    0., 1., 0., 1.,
    // Top right front
    // Blue
    0., 0., 1., 1.,
    // Top left front
    // White
    1., 1., 1., 1.,
    // Top left back
    // Magenta
    1., 0., 1., 1.,
    // Top right back
    // Cyan
    0., 1., 1., 1.,
    // Bottom right back
    // Black
    0., 0., 0., 1.,
    // Bottom left back
    // Yellow
    1., 1., 0., 1.
  ]);

  #indices = new Uint16Array([
    // Front
    0, 1, 2,
    1, 2, 3,
    // Left
    7, 0, 3,
    7, 3, 4,
    // Bottom
    7, 6, 1,
    7, 1, 0,
    // Right
    1, 6, 5,
    1, 5, 2,
    // Back
    6, 7, 4,
    6, 4, 5,
    // Top
    3, 2, 6,
    3, 6, 7
  ]);
}
