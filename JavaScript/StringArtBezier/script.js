class Application {
  /**
   * @type {CanvasRenderingContext2D}
   */
  #context;
  
  /**
   * @param {HTMLCanvasElement} canvas
   */
  constructor(canvas) {
    this.#context = canvas.getContext('2d');
  }

  render() {
    const ctx = this.#context;
  }
}

/**
 * @param {HTMLCanvasElement} canvas
 */
const resizeCanvas = canvas => {
  canvas.width = canvas.parentElement.clientWidth;
  canvas.height = canvas.parentElement.clientHeight;
};

document.addEventListener('DOMContentLoaded', _event => {
  const canvas = document.getElementById('cvs');
  const app = new Application(canvas);
  window.addEventListener('resize', _event => {
    resizeCanvas(canvas);
    app.render();
  });
  resizeCanvas(canvas);
  app.render();
});
