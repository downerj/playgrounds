class AnimationTimer {
  constructor(callback, interval) {
    this._callback = callback;
    this._interval = interval;
    this._previous = 0;
    this._handle = null;
  }
  
  _onTick(timestamp) {
    let elapsed = timestamp - this._previous;
    if (elapsed >= this._interval) {
      this._previous = timestamp;
      let status = this._callback();
      if (status === false) {
        this.pause();
        return;
      }
    }
    this._fireNextFrame();
  }
  
  _fireNextFrame() {
    this._handle = window.requestAnimationFrame(this._onTick.bind(this));
  }
  
  resume() {
    if (this._handle !== null) {
      return;
    }
    this._fireNextFrame();
  }
  
  pause() {
    if (this._handle === null) {
      return;
    }
    window.cancelAnimationFrame(this._handle);
    this._handle = null;
  }
}
