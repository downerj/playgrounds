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
  camera.moveBackward(2.);
  const rotateSpeed = 0.05;
  window.addEventListener('mousemove', (event) => {
    if (document.pointerLockElement != canvas) {
      return;
    }
    camera.rotateX(event.movementY*rotateSpeed);
    camera.rotateY(event.movementX*rotateSpeed);
  });
  const KeyUp = 0;
  const KeyDown = 1;
  const KeyDebounced = 2;
  const keys = {
    a: KeyUp,
    d: KeyUp,
    s: KeyUp,
    w: KeyUp,
    ' ': KeyUp,
    Shift: KeyUp
  };
  window.addEventListener('keydown', (event) => {
    if (!(event.key in keys) || event.key == KeyDebounced) {
      return;
    }
    keys[event.key] = KeyDown;
  });
  window.addEventListener('keyup', (event) => {
    if (!(event.key in keys)) {
      return;
    }
    keys[event.key] = KeyUp;
  });
  gfx.setCamera(camera);
  gfx.addObject(new SimpleTriangle());
  const moveSpeed = 0.1;
  setFramerateTimer((_timestamp) => {
    if (keys.a == KeyDown) {
      camera.moveLeft(moveSpeed);
    } else if (keys.d == KeyDown) {
      camera.moveRight(moveSpeed);
    }
    if (keys.w == KeyDown) {
      camera.moveForward(moveSpeed);
    } else if (keys.s == KeyDown) {
      camera.moveBackward(moveSpeed);
    }
    if (keys.Shift == KeyDown) {
      camera.moveDown(moveSpeed);
    } else if (keys[' '] == KeyDown) {
      camera.moveUp(moveSpeed);
    }
    gfx.render();
  }, 1000/100);
});
