/**
 * @param {number} arg0 Minimum value if two arguments provided; maximum otherwise
 * @param {number?} arg1 Maximum value
 * @returns {Generator<number>}
 */
const range = function*(arg0, arg1 = null) {
  const min = arg1 == null ? 0 : arg0;
  const max = arg1 == null ? arg0 : arg1;
  for (let i = min; i < max; ++i) {
    yield i;
  }
};

document.addEventListener('DOMContentLoaded', () => {
  /**
   * @type {HTMLCanvasElement}
   */
  const cvs = document.getElementById('cvs');
  const ctx = cvs.getContext('2d');

  /**
   *
   */
  const resizeCanvas = () => {
    cvs.width = cvs.parentElement.clientWidth;
    cvs.height = cvs.parentElement.clientHeight;
  };

  /**
   *
   */
  const redraw = () => {
    ctx.setTransform(1, 0, 0, 1, 0, 0);
    ctx.clearRect(0, 0, cvs.width, cvs.height);
    ctx.setTransform(cvs.width/12, 0, 0, -cvs.height/12, cvs.width/2, cvs.height);
    ctx.fillStyle = 'red';
    const maxIterations = 100000;
    for (
      let x = 0, y = 0, t = 0, xn = 0, yn = 0;
      t < maxIterations;
      ++t, x = xn, y = yn
    ) {
      const r = Math.random();
      if (r < .01) {
        xn = 0;
        yn = .16*y;
      } else if (r < .86) {
        xn = .85*x + .04*y;
        yn = -.04*x + .85*y + 1.6;
      } else if (r < 0.93) {
        xn = .2*x - .26*y;
        yn = .23*x + .22*y + 1.6;
      } else {
        xn = -.15*x + .28*y;
        yn = .26*x + .24*y + .44;
      }
      ctx.fillRect(xn, yn, .01, .01);
    }
  };

  window.addEventListener('resize', () => {
    resizeCanvas();
    window.requestAnimationFrame(redraw);
  });
  resizeCanvas();
  window.requestAnimationFrame(redraw);
});