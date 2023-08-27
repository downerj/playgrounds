class Entity {
  constructor(
    position,
    velocity,
    acceleration,
    collisionWidth = 0,
    collisionHeight = 0
  ) {
    this._position = position || new CartesianPoint2d();
    this._velocity = velocity || new CartesianVelocity2d();
    this._acceleration = acceleration || new CartesianAcceleration2d();
    
    // Set other members.
    this._collisionBox = new CollisionRectangle(
      this._position,
      collisionWidth,
      collisionHeight
    );
  }
  
  update() {
    // Update the Cartesian coordinate values.
    this._velocity.accelerate(this._acceleration);
    this._position.move(this._velocity);
  }
  
  // Abstract: override this.
  draw(context) {}
  
  get collisionBox() {
    return this._collisionBox;
  }
  
  isCollidingWith(entity) {
    return this._collisionBox.isCollidingWith(entity._collisionBox);
  }
  
  get position() {
    return this._position;
  }
  
  get velocity() {
    return this._velocity;
  }
  
  get acceleration() {
    return this._acceleration;
  }
  
  setX(x) {
    this._position.x = x;
  }
  
  setY(y) {
    this._position.y = y;
  }
  
  moveX(dx) {
    this._velocity.dx = dx;
  }
  
  moveY(dy) {
    this._velocity.dy = dy;
  }
  
  accelerateX(ddx) {
    this._acceleration.ddx = ddx;
  }
  
  accelerateY(ddy) {
    this._acceleration.ddy = ddy;
  }
  
  stopX() {
    this._velocity.dx = 0;
    this._acceleration.ddx = 0;
  }
  
  stopY() {
    this._velocity.dy = 0;
    this._acceleration.ddy = 0;
  }
}