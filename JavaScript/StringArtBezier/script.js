/**
 * @param {number} a
 * @param {number} b
 * @param {number} t
 * @returns {number}
 */
const lerp = (a, b, t) => {
  return a*(1 - t) + b*t;
};

class Application {
  /**
   * @type {CanvasRenderingContext2D}
   */
  #context;
  #points = [
    50, 10,
    10, 50,
    90, 90,
    10, 90,
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
    const numPoints = Math.floor(this.#points.length / 2);
    // Draw the outlines.
    if (numPoints < 2) {
      return;
    }
    const x0 = this.#points[0];
    const y0 = this.#points[1];
    ctx.strokeStyle = '#ffffff';
    ctx.beginPath();
    ctx.moveTo(x0, y0);
    for (let p = 0; p < numPoints; ++p) {
      ctx.lineTo(this.#points[p*2], this.#points[p*2 + 1]);
    }
    ctx.stroke();
    // Draw the intermediate lines.
    if (numPoints < 3) {
      return;
    }
    for (let c = 0; c <= 10; ++c) {
      const percent = c/10;
      const hue = Math.floor(360*percent);
      ctx.strokeStyle = `hsl(${hue}, 100%, 50%)`;
      ctx.beginPath();
      for (let p = 0; p < numPoints; ++p) {
        const xP0 = this.#points[p*2];
        const yP0 = this.#points[p*2 + 1];
        const xP1 = this.#points[p*2 + 2];
        const yP1 = this.#points[p*2 + 3];
        const xP2 = this.#points[p*2 + 4];
        const yP2 = this.#points[p*2 + 5];
        const xL0 = lerp(xP0, xP1, percent);
        const yL0 = lerp(yP0, yP1, percent);
        const xL1 = lerp(xP1, xP2, percent);
        const yL1 = lerp(yP1, yP2, percent);
        ctx.moveTo(xL0, yL0);
        ctx.lineTo(xL1, yL1);
      }
      ctx.stroke();
    }
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
