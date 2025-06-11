import { setFramerateTimer } from "./timer.js";

/**
 * @param {HTMLCanvasElement} canvas
 * @returns {WebGL2RenderingContext}
 */
const init = (canvas) => {
  const gl = canvas.getContext('webgl2');
  if (!gl) {
    throw 'Unable to get WebGL2 context';
  }
  return gl;
};

/**
 * @param {WebGL2RenderingContext} gl
 */
const render = (gl) => {
  gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);
  gl.clearColor(0., .7, 1., 1.);
  gl.clear(gl.COLOR_BUFFER_BIT);
};

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
  const gl = init(canvas);
  setFramerateTimer((_timestamp) => {
    render(gl);
  }, 1000/30);
});
