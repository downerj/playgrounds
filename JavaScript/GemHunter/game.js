class Game {
  constructor(canvas) {
    this._canvas = canvas;
    this._context = canvas.getContext('2d');
    this._width = canvas.width;
    this._height = canvas.height;

    this._framerate = 50;
    this._timer = new FramerateTimer({
      callback: this._tick.bind(this),
      framerate: this._framerate,
    });
    this._inputHandler = new InputHandler();
    
    this._player = new Player(
      new CartesianPoint2d(0, this._canvas.height)
    );
  }
  
  _input() {
    if (this._inputHandler.hasKey('ArrowRight')) {
      this._player.moveX(10);
    } else if (this._inputHandler.hasKey('ArrowLeft')) {
      this._player.moveX(-10);
    } else {
      this._player.stopX();
    }
    
    if (this._inputHandler.hasKey(' ')) {
      this._player.moveY(-30);
      this._player.accelerateY(5);
      this._inputHandler.debounceKey(' ');
    }
  }
  
  _detectCollisions() {
    let player = this._player;
    
    // Detect left wall collision.
    if (player.position.x <= 0) {
      if (player.velocity.dx < 0) {
        player.position.x = 0;
        player.stopX();
      }
    // Detect right wall collision.
    } else if (player.collisionBox.width + player.position.x >= this._width) {
      if (player.velocity.dx > 0) {
        player.position.x = this._width - player.collisionBox.width;
        player.stopX();
      }
    }
    
    // Detect ceiling collision.
    if (player.position.y + player.collisionBox.height <= 0) {
      if (player.velocity.dy < 0) {
        player.position.y = 0 - player.collisionBox.height;
        player.velocity.dy = 0;
      }
    // Detect ground collision.
    } else if (player.position.y >= this._height) {
      if (player.velocity.dy > 0) {
        player.position.y = this._height;
        player.stopY();
      }
    }
  }
  
  _update() {
    this._player.update();
  }
  
  _draw() {
    // Draw the background.
    this._context.fillStyle = 'black';
    this._context.fillRect(
      0,
      0,
      this._width,
      this._height
    );
    
    // Draw the player.
    this._player.draw(this._context);
  }
  
  _tick() {
    // Handle input.
    this._input();
    // Handle collisions.
    this._detectCollisions();
    // Update all objects and environment.
    this._update();
    // Draw everything.
    this._draw();
  }
  
  run() {
    this._timer.start();
  }
}
