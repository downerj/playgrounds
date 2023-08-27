class Grapher {
  constructor(context) {
    this._ctx = context;
    this._cvs = context.canvas;
    let w = this._cvs.width;
    let h = this._cvs.height;
    this._minX = -10;
    this._maxX = 10;
    this._minY = -10;
    this._maxY = 10;
  }

  plot(func) {
    this._ctx.clearRect(
      0,
      0,
      this._cvs.width,
      this._cvs.height
    );
    
    let dx = (this._maxX - this._minX) / this._cvs.width;
    let dy = (this._maxY - this._minY) / this._cvs.height;
    let rx = this._cvs.width / (this._maxX - this._minX);
    let ry = this._cvs.height / (this._maxY - this._minY);
    
    let x = this._minX;
    let y = this._minY;
    let handle = null;
    
    function updateAndDraw() {
      for (let k = 0; k < 1000; k++) {
        let w = new Complex(x, y);
        let z = func(w);
        let a = z.argument;
        let m = z.modulus;

        let b = 0.9;
        let h = radToDeg(a) % 360;
        while (h < 0) {
          h += 360;
        }
        let s = 100.0;
        let l = (1 - Math.pow(b, m)) * 100.0;

        let xc = this._cvs.width * 0.5;
        let yc = this._cvs.height * 0.5;

        this._ctx.fillStyle = `hsl(${h}, ${s}%, ${l}%)`;
        this._ctx.fillRect(xc + (x * rx), yc - (y * ry), 1, 1);

        x += dx;
        if (x >= this._maxX) {
          x = this._minX;
          y += dy;
        }

        if (y > this._maxY) {
          cancelAnimationFrame(handle);
          handle = null;
          console.log('Done');
          return;
        }
      }
      handle = requestAnimationFrame(updateAndDraw.bind(this));
    }
    handle = requestAnimationFrame(updateAndDraw.bind(this));
  }
}
