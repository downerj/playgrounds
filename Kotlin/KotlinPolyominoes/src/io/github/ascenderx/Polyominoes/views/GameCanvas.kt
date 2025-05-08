package io.github.ascenderx.polyominoes.views

import java.awt.Color
import java.awt.Graphics
import java.awt.Graphics2D
import java.util.List

import javax.swing.JPanel

import io.github.ascenderx.polyominoes.models.Drawable

class GameCanvas(drawables: List<Drawable>) : JPanel() {
  var drawables: List<Drawable> = drawables
  
  companion object {
    val serialVersionUID: Long = 1L
  }
  
  override fun paintComponent(g: Graphics) {
    super.paintComponent(g)
    var graphics: Graphics2D = g as Graphics2D
    
    // Draw the background.
    graphics.setColor(Color.BLACK)
    graphics.fillRect(0, 0, getWidth(), getHeight())
    
    // Draw everything else.
    for (drawable: Drawable in drawables) {
      
    }
  }
}
