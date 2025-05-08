class IntervalLoop {
  private previousTime: number = 0;
  private frameHandle: number | null = null;

  public constructor(private callback: () => boolean, private interval: number) {}

  public resume(): void {
    if (this.frameHandle !== null) {
      return;
    }
    this.update();
  }

  public pause(): void {
    if (this.frameHandle === null) {
      return;
    }
    window.cancelAnimationFrame(this.frameHandle);
    this.frameHandle = null;
  }

  private update(): void {
    this.frameHandle = window.requestAnimationFrame(this.onTick.bind(this));
  }

  private onTick(timestamp: number): void {
    let elapsed: number = timestamp - this.previousTime;
    if (elapsed >= this.interval) {
      let status: boolean = this.callback();
      if (!status) {
        this.pause();
        return;
      }
      this.previousTime = timestamp;
    }
    this.update();
  }
}
