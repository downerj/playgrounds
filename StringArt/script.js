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
    const transforms = [
      [cvs.width/200, 0, 0, cvs.height/200, cvs.width/2, cvs.height/2],
      [cvs.width/200, 0, 0, -cvs.height/200, cvs.width/2, cvs.height/2],
      [-cvs.width/200, 0, 0, -cvs.height/200, cvs.width/2, cvs.height/2],
      [-cvs.width/200, 0, 0, cvs.height/200, cvs.width/2, cvs.height/2],
    ];
    const numLines = 20;
    const offset = 100/numLines;
    const hueDelta = 360/numLines;
    for (const [a, b, c, d, e, f] of transforms) {
      ctx.setTransform(a, b, c, d, e, f);
      for (let i of range(numLines + 1)) {
        const hue = i*hueDelta;
        ctx.beginPath();
        ctx.moveTo(0, 100 - i*offset);
        ctx.lineTo(i*offset, 0);
        ctx.strokeStyle = `hsl(${hue}, 100%, 50%)`;
        ctx.stroke();
      }
    }
  };

  window.addEventListener('resize', () => {
    resizeCanvas();
    redraw();
  });
  resizeCanvas();
  redraw();
});