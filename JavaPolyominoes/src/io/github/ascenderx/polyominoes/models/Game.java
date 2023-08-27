package io.github.ascenderx.polyominoes.models;

import java.util.LinkedList;
import java.util.List;

import java.awt.Point;
import java.awt.event.KeyEvent;

import io.github.ascenderx.polyominoes.elements.TestBlock;
import io.github.ascenderx.polyominoes.models.Drawable;

public class Game {
  private List<Drawable> drawables;
  private TestBlock player;
  private InputHandler inputHandler;

  public Game(InputHandler inputHandler) {
    drawables = new LinkedList<Drawable>();
    player = new TestBlock(new Point(0, 0));
    drawables.add(player);
    this.inputHandler = inputHandler;
  }

  public List<Drawable> getDrawables() {
    return drawables;
  }

  public void update() {
    if (inputHandler.isKeyPressed(KeyEvent.VK_LEFT)) {
      player.getPosition().translate(-5, 0);
    }
  }
}
