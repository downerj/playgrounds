"use strict";
class IntervalLoop {
    constructor(callback, interval) {
        this.callback = callback;
        this.interval = interval;
        this.previousTime = 0;
        this.frameHandle = null;
    }
    resume() {
        if (this.frameHandle !== null) {
            return;
        }
        this.update();
    }
    pause() {
        if (this.frameHandle === null) {
            return;
        }
        window.cancelAnimationFrame(this.frameHandle);
        this.frameHandle = null;
    }
    update() {
        this.frameHandle = window.requestAnimationFrame(this.onTick.bind(this));
    }
    onTick(timestamp) {
        let elapsed = timestamp - this.previousTime;
        if (elapsed >= this.interval) {
            let status = this.callback();
            if (!status) {
                this.pause();
                return;
            }
            this.previousTime = timestamp;
        }
        this.update();
    }
}
