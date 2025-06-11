import { SimpleTriangle } from "./geometry.js";
import { Graphics3D } from "./graphics.js";
import { setFramerateTimer } from "./timer.js";

/**
 * @param {HTMLCanvasElement} canvas
 */
const resizeCanvas = (canvas) => {
  canvas.width = canvas.parentElement.clientWidth;
  canvas.height = canvas.parentElement.clientHeight;
};

document.addEventListener('DOMContentLoaded', (_event) => {
  /**
   * @type {HTMLCanvasElement}
   */
  const canvas = document.getElementById('cvs');
  window.addEventListener('resize', (_event) => resizeCanvas(canvas));
  resizeCanvas(canvas);
  const gfx = new Graphics3D(canvas);
  gfx.addObject(new SimpleTriangle());
  setFramerateTimer((_timestamp) => {
    gfx.render();
  }, 1000/30);
});
