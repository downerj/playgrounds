import { Application } from './app.js';

/**
 * @param {HTMLCanvasElement} canvas
 */
const resizeCanvas = canvas => {
  canvas.width = canvas.parentElement.clientWidth;
  canvas.height = canvas.parentElement.clientHeight;
};

document.addEventListener('DOMContentLoaded', _event => {
  /**
   * @type {HTMLCanvasElement}
   */
  const canvas = document.getElementById('cvs');
  resizeCanvas(canvas);
  const app = new Application(canvas);
  canvas.addEventListener('click', _event => {
    if (document.pointerLockElement != canvas) {
      canvas.requestPointerLock();
    }
  });
  window.addEventListener('resize', _event => {
    resizeCanvas(canvas);
    app.resize(canvas.clientWidth, canvas.clientHeight);
  });
  window.addEventListener('mousemove', event => {
    if (document.pointerLockElement != canvas) {
      return;
    }
    app.moveMouse(event.movementX, event.movementY);
  });
  window.addEventListener('keydown', event => {
    app.pressKey(event.key);
  });
  window.addEventListener('keyup', event => {
    app.releaseKey(event.key);
  });
  app.run();
});
