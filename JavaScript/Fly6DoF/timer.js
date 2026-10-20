/**
 * @typedef {(timestamp: DOMHighResTimeStamp) => void} AnimationCallback
 */

export class AnimationTimer {
  /**
   * @type {number | null}
   */
  #handle = null;
  /**
   * @type {DOMHighResTimeStamp}
   */
  #previous = 0;
  /**
   * @type {DOMHighResTimeStamp}
   */
  #targetInterval;
  /**
   * @type {AnimationCallback}
   */
  #callback;

  /**
   * @param {AnimationCallback} callback
   * @param {DOMHighResTimeStamp} targetInterval
   */
  constructor(callback, targetInterval) {
    this.#callback = callback;
    this.#targetInterval = targetInterval;
  }

  /**
   * @returns {boolean}
   */
  resume() {
    if (this.#handle != null) {
      return false;
    }

    /**
     * @param {DOMHighResTimeStamp} timestamp
     */
    const onTick = (timestamp) => {
      if (timestamp - this.#previous >= this.#targetInterval) {
        this.#previous = timestamp;
        this.#callback(timestamp);
      }
      this.#handle = window.requestAnimationFrame(onTick);  
    };
    this.#handle = window.requestAnimationFrame(onTick);
    
    return true;
  }

  /**
   * @returns {boolean}
   */
  suspend() {
    if (this.#handle == null) {
      return false;
    }
    window.cancelAnimationFrame(this.#handle);
    this.#handle = null;
    return true;
  }
}
