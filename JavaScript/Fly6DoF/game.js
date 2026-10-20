import { AnimationTimer } from "./timer.js";

export class Game {
  /**
   * @type {HTMLCanvasElement}
   */
  #canvas;
  /**
   * @type {WebGL2RenderingContext}
   */
  #gl;
  /**
   * @type {AnimationTimer}
   */
  #timer;
  
  /**
   * @param {HTMLCanvasElement} canvas
   */
  constructor(canvas) {
    this.#canvas = canvas;
    this.#gl = Game.initGL(canvas);
    console.log('WebGL 2 context initialized');
    this.#timer = new AnimationTimer(timestamp => this.#onTick(timestamp), 1000/60);
  }

  /**
   * @param {HTMLCanvasElement} canvas
   * @throws An error if unable to initialize a WebGL 2 context
   */
  static initGL(canvas) {
    const gl = canvas.getContext('webgl2');
    if (gl == null) {
      throw 'Unable to initialize WebGL 2 context';
    }
    return gl;
  }

  /**
   * 
   */
  run() {
    this.#timer.resume();
    console.log('Animation timer started');
  }

  /**
   * 
   */
  updateCanvasSize() {

  }

  /**
   * @param {DOMHighResTimeStamp} _timestamp
   */
  #onTick(_timestamp) {

  }
}
