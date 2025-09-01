class Application {
  /**
   * @type {CanvasRenderingContext2D}
   */
  #context;
  #points = [
    50, 10,
    10, 50,
    90, 90,
  ];
  
  /**
   * @param {HTMLCanvasElement} canvas
   */
  constructor(canvas) {
    this.#context = canvas.getContext('2d');
  }

  render() {
    const ctx = this.#context;
    /**
     * [a c e]
     * [b d f]
     * [0 0 1]
     */
    ctx.setTransform(
      ctx.canvas.width/100, 0,
      0, ctx.canvas.height/100,
      0, 0
    );
    if (this.#points.length < 2) {
      return;
    }
    ctx.strokeStyle = '#ffffff';
    ctx.beginPath();
    const [x0, y0] = this.#points;
    ctx.moveTo(x0, y0);
    for (let p = 2; p < this.#points.length - 1; p += 2) {
      ctx.lineTo(this.#points[p], this.#points[p + 1]);
    }
    ctx.stroke();
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
