import { Camera } from './camera.js';
import { Geometry, SimpleTriangle } from './geometry.js';
import { Graphics3D } from './graphics.js';
import { setFramerateTimer } from './timer.js';

const targetFramerate = 60;
const timerInterval = 1000 / targetFramerate;
const KeyUp = 0;
const KeyDown = 1;
const KeyDebounced = 2;

export class Application {
  /**
   * @param {HTMLCanvasElement} canvas
   */
  constructor(canvas) {
    this.#gfx = new Graphics3D(canvas);
    this.#camera = new Camera();
    this.#camera.moveBackward(2);
    this.#gfx.setCamera(this.#camera);
    const triangle = new SimpleTriangle();
    this.#gfx.addObject(triangle);
    this.#objects.push(triangle);
    this.resize(canvas.clientWidth, canvas.clientHeight);
  }

  /**
   *
   */
  run() {
    setFramerateTimer((_timestamp) => {
      this.#update();
      this.#render();
    }, timerInterval);
  }

  /**
   * @param {string} key
   */
  pressKey(key) {
    if (!(key in this.#keys) || key == KeyDebounced) {
      return;
    }
    this.#keys[key] = KeyDown;
  }

  /**
   * @param {string} key
   */
  releaseKey(key) {
    if (!(key in this.#keys)) {
      return;
    }
    this.#keys[key] = KeyUp;
  }

  /**
   * @param {number} dx
   * @param {number} dy
   */
  moveMouse(dx, dy) {
    const rotateSpeed = 0.05;
    this.#camera.rotateX(dy * rotateSpeed);
    this.#camera.rotateY(dx * rotateSpeed);
  }

  /**
   * @param {number} width
   * @param {number} height
   */
  resize(width, height) {
    this.#gfx.resize(width, height);
  }

  /**
   * @type {Graphics3D}
   */
  #gfx;

  /**
   * @type {Camera}
   */
  #camera;

  /**
   * @type {Geometry[]}
   */
  #objects = [];
  
  /**
   * @type {{[name: string]: number}}
   */
  #keys = {
    a: KeyUp,
    d: KeyUp,
    s: KeyUp,
    w: KeyUp,
    ' ': KeyUp,
    Shift: KeyUp,
  };

  /**
   *
   */
  #update() {
    const moveSpeed = 0.1;
    if (this.#keys.a == KeyDown) {
      this.#camera.moveLeft(moveSpeed);
    } else if (this.#keys.d == KeyDown) {
      this.#camera.moveRight(moveSpeed);
    }
    if (this.#keys.w == KeyDown) {
      this.#camera.moveForward(moveSpeed);
    } else if (this.#keys.s == KeyDown) {
      this.#camera.moveBackward(moveSpeed);
    }
    if (this.#keys.Shift == KeyDown) {
      this.#camera.moveDown(moveSpeed);
    } else if (this.#keys[' '] == KeyDown) {
      this.#camera.moveUp(moveSpeed);
    }
  }

  /**
   *
   */
  #render() {
    this.#gfx.render();
  }
}
