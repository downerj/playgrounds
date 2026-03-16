import { Ball } from './ball.js';

class AppData {
  /**
   * @type {Ball[]}
   */
  balls = [];
}

/**
 * @type {HTMLCanvasElement} cvs
 */
const init = cvs => {
  window.addEventListener('resize', () => {
    resizeCanvas(cvs);
  });
  resizeCanvas(cvs);

  const data = new AppData();
  const ballCount = 50;
  for (let b = 0; b < ballCount; ++b) {
    data.balls.push(Ball.newRandom(0, 0, cvs.width, cvs.height));
  }

  return data;
};

/**
 * @param {AppData} data
 */
const updateAll = data => {
  for (const ball of data.balls) {
    // Update the ball's radius
    ball.radius += ball.dr;
    if (ball.radius <= 0) {
      ball.radius = 0;
      ball.dr = -ball.dr;
    } else if (ball.radius >= Ball.maxRadius) {
      ball.radius = Ball.maxRadius;
      ball.dr = -ball.dr;
    }
    // If the ball is hitting a wall, then bounce it off
    if (ball.dx < 0 && ball.x <= ball.radius) {
      ball.dx = -ball.dx;
      ball.x = ball.radius;
    } else if (ball.dx > 0 && ball.x + ball.radius >= cvs.width) {
      ball.dx = -ball.dx;
      ball.x = cvs.width - ball.radius;
    }
    if (ball.dy < 0 && ball.y <= ball.radius) {
      ball.dy = -ball.dy;
      ball.y = ball.radius;
    } else if (ball.dy > 0 && ball.y + ball.radius >= cvs.height) {
      ball.dy = -ball.dy;
      ball.y = cvs.height - ball.radius;
    }
    // Update the ball's position
    ball.x += ball.dx;
    ball.y += ball.dy;
    // Update the ball's hue
    ball.hue += 10;
  }
};

/**
 * @param {CanvasRenderingContext2D} ctx
 * @param {AppData} data
 */
const drawAll = (ctx, data) => {
  // Clear the canvas
  // ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
  // Draw the balls
  for (const ball of data.balls) {
    ctx.beginPath();
    ctx.fillStyle = `hsl(${ball.hue}deg 100% 50%)`;
    ctx.arc(ball.x, ball.y, ball.radius, 0, Math.PI*2);
    ctx.fill();
  }
};

/**
 * @param {AppData} data
 * @param {HTMLCanvasElement} cvs
 */
const run = (data, cvs) => {
  /**
   * @type {CanvasRenderingContext2D}
   */
  const ctx = cvs.getContext('2d');
  const targetFramerate = 60;
  const interval = 1000 / targetFramerate;
  let previous = 0;
  /**
   * @param {DOMHighResTimeStamp} timestamp
   */
  const tick = timestamp => {
    if (timestamp - previous >= interval) {
      previous = timestamp;
      updateAll(data);
      drawAll(ctx, data);
    }
    window.requestAnimationFrame(tick);
  };
  window.requestAnimationFrame(tick);
};

/**
 * @param {HTMLCanvasElement} cvs
 */
const resizeCanvas = cvs => {
  if (cvs.width != cvs.parentElement.clientWidth || cvs.height != cvs.parentElement.clientHeight) {
    cvs.width = cvs.parentElement.clientWidth;
    cvs.height = cvs.parentElement.clientHeight;
  }
};

window.addEventListener('DOMContentLoaded', () => {
  /**
   * @type {HTMLCanvasElement}
   */
  const cvs = document.getElementById('cvs');

  const data = init(cvs);
  run(data, cvs);
});
