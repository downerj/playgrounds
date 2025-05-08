package io.github.ascenderx.polyominoes.models;

public class FramerateTimer {
  private Thread thread;
  private Tickable handler;
  private long previous;
  private long interval;

  public FramerateTimer(Tickable handler, long interval) {
    previous = 0L;
    this.interval = interval;
    this.handler = handler;

    thread = new Thread(() -> {
      long timestamp;
      long elapsed;
      
      while (true) {
        timestamp = System.currentTimeMillis();
        elapsed = timestamp - previous;

        if (elapsed >= this.interval) {
          previous = timestamp;
          this.handler.tick();
        }
      }
    });
  }

  public void start() {
    thread.start();
  }
}