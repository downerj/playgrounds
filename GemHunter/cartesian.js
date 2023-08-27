class CartesianAcceleration2d {
  constructor(ddx = 0, ddy = 0) {
    this._ddx = ddx;
    this._ddy = ddy;
  }
  
  get ddx() {
    return this._ddx;
  }
  
  get ddy() {
    return this._ddy;
  }
  
  set ddx(value) {
    this._ddx = value;
  }
  
  set ddy(value) {
    this._ddy = value;
  }
  
  clone() {
    return new CartesianAcceleration2d(
      this._ddx,
      this._ddy
    );
  }
}

class CartesianVelocity2d {
  constructor(dx = 0, dy = 0) {
    this._dx = dx;
    this._dy = dy;
  }
  
  get dx() {
    return this._dx;
  }
  
  get dy() {
    return this._dy;
  }
  
  set dx(value) {
    this._dx = value;
  }
  
  set dy(value) {
    this._dy = value;
  }
  
  accelerate(acceleration) {
    this._dx += acceleration.ddx;
    this._dy += acceleration.ddy;
  }
  
  clone() {
    return new CartesianVelocity2d(
      this._dx,
      this._dy
    );
  }
}

class CartesianPoint2d {
  constructor(x = 0, y = 0) {
    this._x = x;
    this._y = y;
  }
  
  get x() {
    return this._x;
  }
  
  get y() {
    return this._y;
  }
  
  set x(value) {
    this._x = value;
  }
  
  set y(value) {
    this._y = value;
  }
  
  move(velocity) {
    this._x += velocity.dx;
    this._y += velocity.dy;
  }
  
  clone() {
    return new CartesianPoint2d(
      this._x,
      this._y
    );
  }
}

class CollisionRectangle {
  constructor(position, width, height) {
    this._position = position;
    this._width = width;
    this._height = height;
  }
  
  get position() {
    return this._position;
  }
  
  get width() {
    return this._width;
  }
  
  get height() {
    return this._height;
  }
  
  isCollidingWith(rectangle) {
    // https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection#Axis-Aligned_Bounding_Box
    return (
      (this._position.x < rectangle._position.x + rectangle._width) &&
      (this._position.x + this._width > rectangle._position.x) &&
      (this._position.y < rectangle._position.y + rectangle._height) &&
      (this._position.y + this._height > rectangle._position.y)
    );
  }
}
