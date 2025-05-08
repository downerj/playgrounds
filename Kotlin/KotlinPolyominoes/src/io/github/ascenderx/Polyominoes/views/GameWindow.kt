package io.github.ascenderx.polyominoes.views

import java.awt.event.KeyEvent

import javax.swing.JFrame

import io.github.ascenderx.polyominoes.models.InputHandler

class GameWindow(canvas: GameCanvas, inputHandler: InputHandler) : JFrame(TITLE) {
  var inputHandler: InputHandler = inputHandler
  
  companion object {
    val SCALE: Int = 4
    val WIDTH: Int = 128 * SCALE
    val HEIGHT: Int = 64 * SCALE
    val TITLE: String = "Tiles"
    val serialVersionUID: Long = 1L;
  }
  
  init {
    setSize(WIDTH, HEIGHT)
    setResizable(false)
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE)
    
    add(canvas)
  }
  
  fun reveal() {
    setVisible(true)
  }
  
  override fun processKeyEvent(event: KeyEvent) {
    
  }
}
