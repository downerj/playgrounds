// Get the canvas and its context.
let cvs = document.getElementById('cvs');
let ctx = cvs.getContext('2d');
// Resize the canvas to fit its container.
cvs.width = cvs.parentElement.offsetWidth;
cvs.height = cvs.parentElement.offsetHeight;

// Set ball properties and initial conditions.
let ball = {
  radius: 15,
  x: cvs.width * 0.5,
  y: cvs.height * 0.5,
  vx: 15,
  vy: 30,
  ax: 0,
  ay: 2,
};
const FRICTION = 0.05;

/**
 * Updates the ball and checks for collisions.
 */
function update() {
  // Move the ball, if necessary.
  ball.vx += ball.ax;
  ball.vy += ball.ay;
  ball.x += ball.vx;
  ball.y += ball.vy;
  
  // Detect horizontal wall collisions.
  // - If the ball has collided with the left wall...
  if (ball.x - ball.radius <= 0) {
    // then bounce it right.
    ball.vx = -ball.vx;
    ball.x = ball.radius;
    // Truncate the velocity.
    if (ball.vx < ball.ax + 1) {
      ball.vx = 0;
    }
    // Slow down a bit each collision.
    ball.vx *= (1 - FRICTION);
    if (ball.vx == 0) {
      ball.vy *= (1 - FRICTION);
    }
  // - If the ball has collided with the right wall...
  } else if (ball.x + ball.radius >= cvs.width) {
    // then bounce it left.
    ball.vx = -ball.vx;
    ball.x = cvs.width - ball.radius;
    // Truncate the velocity.
    if (ball.vx > -ball.ax - 1) {
      ball.vx = 0;
    }
    // Slow down a bit each collision.
    ball.vx *= (1 - FRICTION);
    if (ball.vx == 0) {
      ball.vy *= (1 - FRICTION);
    }
  }
  
  // Detect vertical wall collisions.
  // - If the ball has collided with the ceiling...
  if (ball.y - ball.radius <= 0) {
    // then bounce it down.
    ball.vy = -ball.vy;
    ball.y = ball.radius;
    // Truncate the velocity.
    if (ball.vy < ball.ay + 1) {
      ball.vy = 0;
    }
    // Slow down a bit each collision.
    ball.vy *= (1 - FRICTION);
    if (ball.vy == 0) {
      ball.vx *= (1 - FRICTION);
    }
  // - If the ball has collided with the floor...
  } else if (ball.y + ball.radius >= cvs.height) {
    // then bounce it up.
    ball.vy = -ball.vy;
    ball.y = cvs.height - ball.radius;
    // Truncate the velocity.
    if (ball.vy > -ball.ay - 1) {
      ball.vy = 0;
    }
    // Slow down a bit each collision.
    ball.vy *= (1 - FRICTION);
    if (ball.vy == 0) {
      ball.vx *= (1 - FRICTION);
    }
  }
}

/**
 * Draws the ball to the screen.
 */
function draw() {
  // Clear the canvas.
  ctx.clearRect(0, 0, cvs.width, cvs.height);
  
  // Draw the ball.
  // - Set the color.
  ctx.strokeStyle = '#0f0';
  // - Set the thickness.
  ctx.lineWidth = 2;
  // - Draw the arc.
  ctx.beginPath();
  ctx.arc(ball.x, ball.y, ball.radius, 0, 2 * Math.PI);
  ctx.stroke();
}

// Get the value display labels.
let lblR = document.getElementById('lblR');
let lblF = document.getElementById('lblF');
let lblX = document.getElementById('lblX');
let lblY = document.getElementById('lblY');
let lblVX = document.getElementById('lblVX');
let lblVY = document.getElementById('lblVY');
let lblAX = document.getElementById('lblAX');
let lblAY = document.getElementById('lblAY');

/**
 * Updates the value display labels.
 */
function displayValues() {
  // Display the radius and friction as-is.
  lblR.innerText = ball.radius;
  lblF.innerText = FRICTION;
  
  // Round the position to the nearest integer.
  lblX.innerText = ball.x.toFixed(0);
  lblY.innerText = ball.y.toFixed(0);
  
  // Round the velocity to two decimal places.
  lblVX.innerText = ball.vx.toFixed(2);
  lblVY.innerText = ball.vy.toFixed(2);
  
  // Display the acceleration as-is.
  lblAX.innerText = ball.ax;
  lblAY.innerText = ball.ay;
}

// Set the values for animation.
let handle;
let previousTime = 0;
const INTERVAL = 10;

/**
 * Advances the animation by one frame. This is called (at most) every
 * INTERVAL milliseconds.
 * 
 * @param timestamp  The current time, updated each time the function is called 
 */
function tick(timestamp) {
  // Calculate the last time this function was called.
  let elapsed = timestamp - previousTime;
  // If it's time to update and draw, then do it now.
  if (elapsed >= INTERVAL) {
    previousTime = timestamp;
    update();
    draw();
    displayValues();
  }
  // Continue the animation (recursively).
  handle = window.requestAnimationFrame(tick);
}

// Start the animation.
handle = window.requestAnimationFrame(tick);
