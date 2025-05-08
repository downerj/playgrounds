"use strict";
class Game {
    constructor(canvas) {
        this.canvas = canvas;
        this.keys = {};
        this.loop = new IntervalLoop(this.onTick.bind(this), Game.INTERVAL);
        let context = canvas.getContext('2d');
        if (context === null) {
            throw "Cannot create 2D rendering context";
        }
        else {
            this.context = context;
        }
    }
    run() {
        this.loop.resume();
    }
    onKeyDown(key) {
        if (!(key in this.keys)) {
            this.keys[key] = true;
        }
    }
    onKeyUp(key) {
        if (key in this.keys) {
            delete this.keys[key];
        }
    }
    debounceKey(key) {
        if (key in this.keys) {
            this.keys[key] = false;
        }
    }
    isKeyDown(key) {
        return this.keys[key];
    }
    onTick() {
        this.handleInput();
        this.updateObjects();
        this.handleCollisions();
        this.cleanUpZombies();
        this.drawAll();
        return true;
    }
    handleInput() {
    }
    updateObjects() {
    }
    handleCollisions() {
    }
    cleanUpZombies() {
    }
    drawAll() {
    }
}
Game.INTERVAL = 10;
