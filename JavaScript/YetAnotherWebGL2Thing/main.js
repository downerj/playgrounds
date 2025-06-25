import { Camera } from "./camera.js";
import { Cube, SimpleTriangle } from "./geometry.js";
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
  canvas.addEventListener('click', (_event) => {
    if (document.pointerLockElement != canvas) {
      canvas.requestPointerLock();
    }
  });
  window.addEventListener('resize', (_event) => resizeCanvas(canvas));
  resizeCanvas(canvas);
  const gfx = new Graphics3D(canvas);
  const camera = new Camera();
  camera.moveZ(2.);
  const rotateSpeed = 0.05;
  window.addEventListener('mousemove', (event) => {
    if (document.pointerLockElement != canvas) {
      return;
    }
    camera.rotateX(event.movementY*rotateSpeed);
    camera.rotateY(event.movementX*rotateSpeed);
  });
  gfx.setCamera(camera);
  gfx.addObject(new SimpleTriangle());
  setFramerateTimer((_timestamp) => {
    gfx.render();
  }, 1000/30);
});
