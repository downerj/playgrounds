package io.github.ascenderx.polyominoes.views;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.List;

import javax.swing.JPanel;

import io.github.ascenderx.polyominoes.models.Drawable;

public class GameCanvas extends JPanel {
  public List<Drawable> drawables;
  private static final long serialVersionUID = 1L;
  
  public GameCanvas(List<Drawable> drawables) {
    this.drawables = drawables;
  }

  @Override
  public void paintComponent(Graphics g) {
    super.paintComponent(g);
    Graphics2D graphics = (Graphics2D) g;

    // Draw the background.
    graphics.setColor(Color.BLACK);
    graphics.fillRect(0, 0, getWidth(), getHeight());

    // Draw everything else.
    for (Drawable drawable : drawables) {
      drawable.draw(graphics);
    }
  }
}
