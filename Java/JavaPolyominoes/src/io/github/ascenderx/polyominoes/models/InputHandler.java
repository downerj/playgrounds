package io.github.ascenderx.polyominoes.models;

import java.util.HashMap;
import java.util.Map;

public class InputHandler {
  private Map<Integer, KeyboardKey> keysPressed;
  
  public InputHandler() {
    keysPressed = new HashMap<Integer, KeyboardKey>();
  }

  public void register(int... keyCodes) {
    for (int code : keyCodes) {
      keysPressed.put(code, new KeyboardKey(code));
    }
  }

  public void press(int keyCode) {
    KeyboardKey key = keysPressed.get(keyCode);
    if (key == null) {
      return;
    }

    key.press();
  }

  public void debounce(int keyCode) {
    KeyboardKey key = keysPressed.get(keyCode);
    if (key == null) {
      return;
    }

    key.debounce();
  }

  public void release(int keyCode) {
    KeyboardKey key = keysPressed.get(keyCode);
    if (key == null) {
      return;
    }

    key.release();
  }

  public boolean isKeyPressed(int keyCode) {
    KeyboardKey key = keysPressed.get(keyCode);
    // If the key isn't registered, then it's not pressed.
    if (key == null) {
      return false;
    }

    byte status = key.getStatus();
    return status == KeyboardKey.PRESSED;
  }
}
