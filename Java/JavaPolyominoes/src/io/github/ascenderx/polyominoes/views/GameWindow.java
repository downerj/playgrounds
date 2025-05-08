package io.github.ascenderx.polyominoes.views;

import java.awt.event.KeyEvent;

import javax.swing.JFrame;

import io.github.ascenderx.polyominoes.models.InputHandler;

public class GameWindow extends JFrame {
  private InputHandler inputHandler;
  private static final int SCALE = 4;
  private static final int WIDTH = 128 * SCALE;
  private static final int HEIGHT = 64 * SCALE;
  private static final String TITLE = "Tiles";
  private static final long serialVersionUID = 1L;

  public GameWindow(GameCanvas canvas, InputHandler inputHandler) {
    super(TITLE);

    // Set properties.
    setSize(WIDTH, HEIGHT);
    setResizable(false);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    
    // Add components.
    add(canvas);

    // Register input handler.
    this.inputHandler = inputHandler;
  }

  public void reveal() {
    setVisible(true);
  }

  @Override
  protected void processKeyEvent(KeyEvent event) {
    // TODO: Bind to an adapter.
  }
}
