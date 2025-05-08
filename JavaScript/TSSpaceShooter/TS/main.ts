let game: Game;
window.addEventListener("load", (_: Event): void => {
  let canvas = document.getElementById('canvas') as HTMLCanvasElement;
  game = new Game(canvas);
  window.addEventListener('keydown', (event: KeyboardEvent): void => {
    game.onKeyDown(event.key);
  });
  window.addEventListener('keyup', (event: KeyboardEvent): void => {
    game.onKeyUp(event.key);
  });
  game.run();
});
