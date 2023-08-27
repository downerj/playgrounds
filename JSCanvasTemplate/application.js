class CanvasApplication {
  constructor(canvas) {
    this._canvas = canvas;
    this._graphics = canvas.getContext('2d');
    this._timer = new AnimationTimer(
      this._onTick.bind(this),
      CanvasApplication._INTERVAL
    );
    this._inputHandler = new InputHandler();
  }
  
  _onTick() {
    this._handleInput();
    this._update();
    this._draw();
    return true;
  }
  
  _handleInput() {
    let input = this._inputHandler;
  }
  
  _update() {}
  
  _draw() {
    let graphics = this._graphics;
  }
  
  run() {
    this._timer.resume();
  }
}
CanvasApplication._INTERVAL = 50;
