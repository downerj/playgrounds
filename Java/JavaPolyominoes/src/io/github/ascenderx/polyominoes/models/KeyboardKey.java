package io.github.ascenderx.polyominoes.models;

public class KeyboardKey {
  public static final byte RELEASED = 0;
  public static final byte PRESSED = 1;
  public static final byte DEBOUNCED = 2;
  private int value;
  private byte status;

  public KeyboardKey(int value) {
    this.value = value;
    this.status = RELEASED;
  }

  public void press() {
    if (this.status != DEBOUNCED) {
      this.status = PRESSED;
    }
  }

  public void release() {
    this.status = RELEASED;
  }

  public void debounce() {
    this.status = DEBOUNCED;
  }

  public int getValue() {
    return this.value;
  }

  public byte getStatus() {
    return this.status;
  }
}
