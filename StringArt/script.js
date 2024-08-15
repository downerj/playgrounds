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
    ctx.setTransform(cvs.width/100, 0, 0, -cvs.height/100, 0, cvs.height);
    ctx.clearRect(0, 0, cvs.clientWidth, cvs.clientHeight);
    const numLines = 20;
    const offset = 50/numLines;
    const hueDelta = 360/numLines;
    for (let i = 0; i <= numLines; ++i) {
      const hue = i*hueDelta;
      const dist = i*offset;
      ctx.beginPath();
      ctx.moveTo(50, 100 - dist);
      ctx.lineTo(50 + dist, 50);
      ctx.moveTo(50, 100 - dist);
      ctx.lineTo(50 - dist, 50);
      ctx.moveTo(50, dist);
      ctx.lineTo(50 + dist, 50);
      ctx.moveTo(50, dist);
      ctx.lineTo(50 - dist, 50);
      ctx.strokeStyle = `hsl(${hue}, 100%, 50%)`;
      ctx.stroke();
    }
  };

  window.addEventListener('resize', () => {
    resizeCanvas();
    redraw();
  });
  resizeCanvas();
  redraw();
});