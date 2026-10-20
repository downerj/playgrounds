import { Game } from './game.js';

/**
 * @param {HTMLCanvasElement} canvas
 */
const resizeCanvasToParent = canvas => {
  canvas.width = canvas.parentElement.clientWidth;
  canvas.height = canvas.parentElement.clientHeight;
};

document.addEventListener('DOMContentLoaded', async _ev => {
  /**
   * @type {HTMLCanvasElement}
   */
  const cvs = document.getElementById('cvs');
  const game = new Game(cvs);
  const areGraphicsReady = await game.initializeGraphicsAsync();
  if (!areGraphicsReady) {
    return;
  }

  window.addEventListener('resize', _ev => {
    resizeCanvasToParent(cvs);
    game.updateCanvasSize();
  });
  resizeCanvasToParent(cvs);
  game.updateCanvasSize();

  game.run();
});
