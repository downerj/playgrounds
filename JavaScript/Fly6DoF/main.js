import { Game } from "./game.js";

/**
 * @param {HTMLCanvasElement} canvas
 */
const resizeCanvasToParent = (canvas) => {
  canvas.width = canvas.parentElement.clientWidth;
  canvas.height = canvas.parentElement.clientHeight;
};

document.addEventListener('DOMContentLoaded', (_ev) => {
  /**
   * @type {HTMLCanvasElement}
   */
  const cvs = document.getElementById('cvs');
  const game = new Game(cvs);

  window.addEventListener('resize', (_ev) => {
    resizeCanvasToParent(cvs);
    game.updateCanvasSize();
  });
  resizeCanvasToParent(cvs);

  game.run();
});
