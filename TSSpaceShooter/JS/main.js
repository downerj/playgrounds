"use strict";
let game;
window.addEventListener("load", (_) => {
    let canvas = document.getElementById('canvas');
    game = new Game(canvas);
    window.addEventListener('keydown', (event) => {
        game.onKeyDown(event.key);
    });
    window.addEventListener('keyup', (event) => {
        game.onKeyUp(event.key);
    });
    game.run();
});
