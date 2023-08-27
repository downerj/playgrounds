function fillHueToRGB(hue: number, output: Array<number>) {
  if (hue < 0) {
    hue += (hue % 360);
  }
  let red: number = 0;
  let green: number = 0;
  let blue: number = 0;
  let hueSection: number = Math.floor(hue / 60);
  let hueDelta: number = hue % 60;
  switch (hueSection) {
    case 0:
      red = 255;
      green = hueDelta;
      break;
      
    case 1:
      red = hueDelta;
      green = 255;
      break;

    case 2:
      green = 255;
      blue = hueDelta;
      break;

    case 3:
      green = hueDelta;
      blue = 255;
      break;

    case 4:
      red = hueDelta;
      blue = 255;
      break;

    case 5:
      red = 255;
      blue = hueDelta;
      break;
  }
}

class Application {
  private context: CanvasRenderingContext2D;

  constructor(private canvas: HTMLCanvasElement) {
    let context: CanvasRenderingContext2D | null = canvas.getContext('2d');
    if (context === null) {
      throw 'Context failed to generate';
    }
    this.context = context;
  }

  private draw(): void {
    let imageData: ImageData = this.context.getImageData(0, 0, this.canvas.width, this.canvas.height);
    let buffer: Uint8ClampedArray = imageData.data;

    for (let y: number = 0; y < this.canvas.height; y++) {
      for (let x: number = 0; x < this.canvas.width; x++) {
        let e: number = (x * 4) + (y * this.canvas.width * 4);
        let r: number = e;
        let g: number = e + 1;
        let b: number = e + 2;
        let a: number = e + 3;

        buffer[r] = 255;
        buffer[g] = 0;
        buffer[b] = 0;
        buffer[a] = 255;
      }
    }

    this.context.putImageData(imageData, 0, 0);
  }

  run(): void {
    this.draw();
  }
}

window.addEventListener('load', (_: Event): void => {
  const canvas: HTMLCanvasElement | null = document.getElementById('cvs') as HTMLCanvasElement;
  const canvasWrapper: HTMLDivElement | null  = document.getElementsByClassName('canvas-wrapper')[0] as HTMLDivElement;
  if (canvas === null || canvasWrapper === null) {
    throw "Error retrieving DOM elements";
  }
  canvas.width = canvasWrapper.offsetWidth;
  canvas.height = canvasWrapper.offsetHeight;
  new Application(canvas).run();
});
