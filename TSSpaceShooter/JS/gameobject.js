"use strict";
class GameObject {
    constructor(width, height) {
        this.width = width;
        this.height = height;
        this.x = 0;
        this.y = 0;
        this.dx = 0;
        this.dy = 0;
        this.alive = true;
    }
    moveLeft(dx) {
        this.dx = -dx;
        this.dy = 0;
    }
    moveRight(dx) {
        this.dx = dx;
        this.dy = 0;
    }
    moveUp(dy) {
        this.dx = 0;
        this.dy = -dy;
    }
    moveDown(dy) {
        this.dx = 0;
        this.dy = dy;
    }
    move(dx, dy) {
        this.dx = dx;
        this.dy = dy;
    }
    doesCollideWith(target) {
        return (this.x < target.x + target.width) &&
            (this.x + this.width > target.x) &&
            (this.y < target.y + target.height) &&
            (this.y + this.height > target.y);
    }
    update() {
        this.x += this.dx;
        this.y += this.dy;
    }
}
