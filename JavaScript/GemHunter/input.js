class InputHandler {
  constructor() {
    this._keys = {};
    window.addEventListener('keydown', (event) => {
      if (!(event.key in this._keys)) {
        this._keys[event.key] = true;
      }
    });
    window.addEventListener('keyup', (event) => {
      if (event.key in this._keys) {
        delete this._keys[event.key];
      }
    });
  }
  
  debounceKey(key) {
    if (key in this._keys) {
      this._keys[key] = false;
    }
  }
  
  hasKey(key) {
    if (!(key in this._keys)) {
      return false;
    }
    
    return this._keys[key];
  }
}
