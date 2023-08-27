class FramerateTimer {
  constructor(kwargs) {
    // Prep some keyword arguments (no defaults).
    this._callback = null;
    this._interval = null;
    
    // Parse all keyword arguments.
    for (let key in kwargs) {
      let value = kwargs[key];
      
      switch (key) {
        case 'callback':
          this._callback = value;
          break;
        
        case 'interval':
          this._interval = value;
          break;
        
        case 'framerate':
          this._interval = Math.floor(1000 / value);
          break;
        
        default:
          throw `Invalid keyword argument "${key}"`;
      }
    }
    
    // Enforce some keyword arguments.
    if (this._callback === null || this._callback === undefined) {
      throw 'Callback is undefined';
    } else if (this._interval === null || this._interval === undefined) {
      throw 'Interval is undefined';
    }
    
    // Intialize the rest of the members.
    this._handle = null;
    this._previous = 0;
  }
  
  _update() {
    this._handle = window.requestAnimationFrame(this._tick.bind(this));
  }
  
  _clear() {
    window.cancelAnimationFrame(this._handle);
    this._handle = null;
    this._previous = 0;
  }
  
  _tick(timestamp) {
    // Enforce a framerate-based animation.
    let elapsed = timestamp - this._previous;
    if (elapsed >= this._interval) {
      this._previous = timestamp;
      this._callback();
    }
    
    // Continue the recursion.
    this._update();
  }
  
  start() {
    // only start if we haven't already
    if (this._handle !== null) {
      return false;
    }
    
    let previous = null;
    
    // Start the recursion.
    this._update();

    return true;
  }
  
  stop() {
    // Only stop if we've already started and haven't stopped yet.
    if (this._handle === null) {
      return false;
    }
    
    // Stop the recursion.
    this._clear();
    
    return true;
  }
  
  get isRunning() {
    return this._handle !== null;
  }
}
