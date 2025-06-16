export class Geometry {
  get vertices() {}
  get colors() {}
  get indices() {}
}

export class SimpleTriangle extends Geometry {
  #vertices = new Float32Array([
    // Bottom left
    -1., -1., 0.,
    // Bottom right
    1., -1., 0.,
    // Top middle
    0., 1., 0.
  ]);

  get vertices() {
    return this.#vertices;
  }

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

  get colors() {
    return this.#colors;
  }

  #indices = new Uint16Array([
    0, 1, 2
  ]);

  get indices() {
    return this.#indices;
  }
}
