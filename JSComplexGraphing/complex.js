function degToRad(degrees) {
  return Math.PI * degrees / 180.0;
}

function radToDeg(radians) {
  return 180.0 * radians / Math.PI;
}

class Complex {
  constructor(r, i) {
    this._value = [r, i];
  }

  get real() {
    return this._value[0];
  }

  get imaginary() {
    return this._value[1];
  }

  get conjugate() {
    return new Complex(
      this._value[0],
      -this._value[1]
    );
  }

  get argument() {
    return Math.atan2(
      this._value[1],
      this._value[0]
    );
  }

  get modulus() {
    let x = this._value[0];
    let y = this._value[1];

    return Math.sqrt((x * x) + (y * y));
  }

  get inverse() {
    let x = this._value[0];
    let y = this._value[1];
    let d = (x * x) + (y * y);
    let u = x / d;
    let v = -y / d;
    return new Complex(u, v);
  }

  add(rhs) {
    return new Complex(
      this._value[0] + rhs._value[0],
      this._value[1] + rhs._value[1],
    );
  }

  sub(rhs) {
    return new Complex(
      this._value[0] - rhs._value[0],
      this._value[1] + rhs._value[1],
    );
  }

  mult(rhs) {
    let x0 = this._value[0];
    let y0 = this._value[1];
    let x1 = rhs._value[0];
    let y1 = rhs._value[1];
    let u = (x0 * x1) - (y0 * y1);
    let v = (x0 * y1) + (x1 * y0);

    return new Complex(u, v);
  }

  div(rhs) {
    let x0 = this._value[0];
    let y0 = this._value[1];
    let x1 = rhs._value[0];
    let y1 = rhs._value[1];
    let d = (x1 * x1) + (y1 * y1);
    let u = ((x0 * x1) + (y0 * y1)) / d;
    let v = ((y0 * x1) - (x0 * y1)) / d;

    return new Complex(u, v);
  }
}
