abstract class GameObject {
  public x: number = 0;
  public y: number = 0;
  public dx: number = 0;
  public dy: number = 0;
  public alive: boolean = true;
  
  public constructor(public readonly width: number, public readonly height: number) {}

  public moveLeft(dx: number): void {
    this.dx = -dx;
    this.dy = 0;
  }

  public moveRight(dx: number): void {
    this.dx = dx;
    this.dy = 0;
  }

  public moveUp(dy: number): void {
    this.dx = 0;
    this.dy = -dy;
  }

  public moveDown(dy: number): void {
    this.dx = 0;
    this.dy = dy;
  }

  public move(dx: number, dy: number): void {
    this.dx = dx;
    this.dy = dy;
  }

  public doesCollideWith(target: GameObject): boolean {
    return (this.x < target.x + target.width) &&
      (this.x + this.width > target.x) &&
      (this.y < target.y + target.height) &&
      (this.y + this.height > target.y);
  }

  public update(): void {
    this.x += this.dx;
    this.y += this.dy;
  }

  public abstract draw(context: CanvasRenderingContext2D): void;
}
