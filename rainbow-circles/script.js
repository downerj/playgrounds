class Circle {
  x = 0;
  y = 0;
  vx = 0;
  vy = 0;
  hue = 0;
  radius = 1;
}

/**
 * 
 * @param {number} min 
 * @param {number} max 
 */
const range = function*(min, max) {
  for (let i = min; i < max; ++i) {
    yield i;
  }
};

document.addEventListener('DOMContentLoaded', () => {
  /**
   * @type {HTMLCanvasElement}
   */
  const cvs = document.getElementById('cvs');
  const ctx = cvs.getContext('2d');

  /**
   * 
   */
  const onResize = () => {
    cvs.width = cvs.parentElement.clientWidth;
    cvs.height = cvs.parentElement.clientHeight;
  };

  const circles = [...range(0, 10)].map(() => {
    const circle = new Circle();
    const minRadius = 0.1;
    const maxRadius = 0.8;
    circle.radius = Math.random()*(maxRadius - minRadius) + minRadius;
    circle.lineWidth = circle.radius/5;
    circle.x = Math.random()*(10 - 2*circle.radius) + circle.radius;
    circle.y = Math.random()*(10 - 2*circle.radius) + circle.radius;
    const minVelocity = -0.01;
    const maxVelocity = 0.01;
    circle.vx = Math.random()*(maxVelocity - minVelocity) + minVelocity;
    circle.vy = Math.random()*(maxVelocity - minVelocity) + minVelocity;
    circle.hue = Math.floor(Math.random()*360);
    return circle;
  });

  /**
   * 
   */
  const update = () => {
    for (const circle of circles) {
      circle.x += circle.vx;
      circle.y += circle.vy;
      if (circle.x > 10 - circle.radius && circle.vx > 0) {
        circle.x = 10 - circle.radius;
        circle.vx = -circle.vx;
      } else if (circle.x < circle.radius && circle.vx < 0) {
        circle.x = circle.radius;
        circle.vx = -circle.vx;
      }
      if (circle.y > 10 - circle.radius && circle.vy > 0) {
        circle.y = 10 - circle.radius;
        circle.vy = -circle.vy;
      } else if (circle.y < circle.radius && circle.vy < 0) {
        circle.y = circle.radius;
        circle.vy = -circle.vy;
      }
      circle.hue += 1;
    }
  };

  /**
   * 
   */
  const render = () => {
    // ctx.resetTransform();
    // ctx.clearRect(0, 0, cvs.width, cvs.height);
    for (const circle of circles) {
      ctx.setTransform(cvs.width/10, 0, 0, -cvs.height/10, 0, cvs.height);
      ctx.translate(circle.x, circle.y);
      ctx.lineWidth = circle.lineWidth;
      ctx.beginPath();
      ctx.strokeStyle = `hsl(${circle.hue}, 100%, 50%)`;
      ctx.arc(0, 0, circle.radius, 0, 2*Math.PI);
      ctx.stroke();
    }
  };

  const interval = 10;
  let previous = 0;
  /**
   * 
   * @param {DOMHighResTimeStamp} timestamp 
   */
  const onTick = (timestamp) => {
    if (timestamp - previous >= interval) {
      previous = timestamp;
      update();
      render();
    }
    window.requestAnimationFrame(onTick);
  };

  window.addEventListener('resize', onResize);
  onResize();

  window.requestAnimationFrame(onTick);
});

