class Game {
  private static readonly INTERVAL = 10;
  private readonly context: CanvasRenderingContext2D;
  private readonly keys: { [key: string]: boolean } = {};
  private readonly loop = new IntervalLoop(this.onTick.bind(this), Game.INTERVAL);

  public constructor(private canvas: HTMLCanvasElement) {
    let context: CanvasRenderingContext2D | null = canvas.getContext('2d');
    if (context === null) {
      throw "Cannot create 2D rendering context";
    } else {
      this.context = context;
    }
  }

  public run(): void {
    this.loop.resume();
  }

  public onKeyDown(key: string): void {
    if (!(key in this.keys)) {
      this.keys[key] = true;
    }
  }

  public onKeyUp(key: string): void {
    if (key in this.keys) {
      delete this.keys[key];
    }
  }

  private debounceKey(key: string): void {
    if (key in this.keys) {
      this.keys[key] = false;
    }
  }

  private isKeyDown(key: string): boolean {
    return this.keys[key];
  }

  private onTick(): boolean {
    this.handleInput();
    this.updateObjects();
    this.handleCollisions();
    this.cleanUpZombies();
    this.drawAll();
    return true;
  }

  private handleInput(): void {

  }

  private updateObjects(): void {

  }

  private handleCollisions(): void {

  }

  private cleanUpZombies(): void {

  }

  private drawAll(): void {

  }
}
