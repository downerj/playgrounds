class CanvasApplication {
  constructor(canvas) {
    this._canvas = canvas;
    this._context = canvas.getContext('2d');
    let interval = 10;
    this._loop = new Loop(this._tick.bind(this), interval);
  }
  
  run() {
    this._loop.resume();
  }
  
  _input() {
    
  }
  
  _update() {
    
  }
  
  _draw() {
    
  }
  
  _tick() {
    this._input();
    this._update();
    this._draw();
  }
}

function windowOnLoad(_) {
  let canvas = document.getElementById('canvas');
  // Resize canvas to fit container.
  canvas.width = canvas.parentElement.offsetWidth;
  canvas.height = canvas.parentElement.offsetHeight;
  
  new CanvasApplication(canvas).run();
}

window.addEventListener('load', windowOnLoad);
// Have the user confirm when refreshing or navigating away from the page.
window.onBeforeUnload = (_) => 0;

