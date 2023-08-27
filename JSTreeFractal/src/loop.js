class Loop {
  /**
   * 
   * @param {function} callback 
   * @param {number} interval 
   */
  constructor(callback, interval) {
    this._callback = callback;
    this._interval = interval;
    this._previous = 0;
    /**
     * @property {number}
     */
    this._handle = null;
  }

  /**
   * 
   */
  _update() {
    this._handle = requestAnimationFrame(this._tick.bind(this));
  }

  /**
   * 
   */
  _clear() {
    cancelAnimationFrame(this._handle);
    this._handle = null;
  }

  /**
   * 
   * @param {number} timestamp 
   */
  _tick(timestamp) {
    let elapsed = timestamp - this._previous;
    if (elapsed >= this._interval) {
      let status = this._callback();
      if (!status) {
        this._clear();
        return;
      }
      this._previous = timestamp;
    }
    this._update();
  }

  /**
   * 
   */
  resume() {
    if (this._handle !== null) {
      return;
    }
    this._update();
  }

  /**
   * 
   */
  pause() {
    if (this._handle === null) {
      return;
    }
    this._clear();
  }
}
