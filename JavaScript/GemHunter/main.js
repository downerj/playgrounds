// Make the game available to the debugger.
let game;

window.addEventListener('load', function main() {
  let canvas = byID('game-canvas');
  let canvasContainer = byID('canvas-container');
  
  // Resize the canvas to fill its container.
  canvas.width = canvasContainer.offsetWidth;
  canvas.height = canvasContainer.offsetHeight;
  
  // Start a new game.
  game = new Game(canvas);
  game.run();
});
