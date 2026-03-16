import { randomInteger } from "./math.js";

export class Ball {
  /**
   * @type {number}
   */
  x;
  /**
   * @type {number}
   */
  y;
  /**
   * @type {number}
   */
  dx;
  /**
   * @type {number}
   */
  dy;
  /**
   * @type {number}
   */
  hue;
  /**
   * @type {number}
   */
  radius;
  /**
   * @type {number}
   */
  dr;

  static maxRadius = 20;

  /**
   * @param {number} leftBound
   * @param {number} topBound
   * @param {number} rightBound
   * @param {number} bottomBound
   * @returns {Ball}
   */
  static newRandom(leftBound, topBound, rightBound, bottomBound) {
    const ball = new Ball();
    ball.x = randomInteger(leftBound, rightBound);
    ball.y = randomInteger(topBound, bottomBound);
    ball.dx = randomInteger(-10, 10);
    if (ball.dx === 0) {
      ball.dx = 10;
    }
    ball.dy = -randomInteger(-10, 10);
    if (ball.dy === 0) {
      ball.dy = 10;
    }
    ball.hue = randomInteger(0, 35) * 10;
    ball.radius = randomInteger(1, Ball.maxRadius);
    ball.dr = randomInteger(1, 100) / 100;
    return ball;
  }
}
