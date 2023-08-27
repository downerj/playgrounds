class App {
  /**
   * 
   * @param {HTMLCanvasElement} canvas 
   */
  constructor(canvas) {
    this._canvas = canvas;
    this._context = canvas.getContext('2d');
    let interval = 10;
    this._loop = new Loop(this._tick.bind(this), interval);
    let x = canvas.width * 0.5;
    let y = canvas.height;
    let trunkLength = Math.min(canvas.width, canvas.height) * 0.4;
    let trunkAngle = -90.0;
    this._tree = new Tree(x, y, trunkLength, trunkAngle);
  }

  /**
   * @returns {boolean}
   */
  _tick() {
    let status = this._update();
    if (!status) {
      console.log('Done.');
      return false;
    }
    this._draw();
    return true;
  }

  /**
   * @returns {boolean}
   */
  _update() {
    return this._tree.update();
  }

  /**
   * 
   */
  _draw() {
    this._tree.draw(this._context);
  }

  /**
   * 
   */
  run() {
    this._loop.resume();
  }
}

/**
 * 
 * @param {Event} _ Unused
 */
function onWindowLoad(_) {
  let canvas = document.getElementById('canvas');
  // Resize the canvas to fit its container.
  canvas.width = canvas.parentElement.offsetWidth;
  canvas.height = canvas.parentElement.offsetHeight;
  // Run the app.
  new App(canvas).run();
}

window.addEventListener('load', onWindowLoad);
