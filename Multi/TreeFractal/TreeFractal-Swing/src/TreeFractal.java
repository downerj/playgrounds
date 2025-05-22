import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import io.github.downerj.Tree;

class DrawingPanel extends JPanel {
  private void drawTrees(Graphics g) {
    final var size = getSize();
    final var trees = new ArrayList<Tree>();
    final var trunkStartX = size.width / 2.;
    final var trunkStartY = size.height / 2.;
    final var numTrees = 3;
    final var trunkLength = Math.min(size.width, size.height) / 6.;
    final var trunkDeltaAngle = Math.PI * 2. / numTrees;
    for (int t = 0; t < numTrees; t++) {
      final var trunkAngle = -Math.PI / 2. + trunkDeltaAngle * t;
      final var tree = new Tree(trunkStartX, trunkStartY, trunkLength, trunkAngle);
      trees.add(tree);
    }
    for (var tree : trees) {
      for (final var branch : tree) {
        final var color = new Color(branch.getColor());
        g.setColor(color);
        g.drawLine((int)branch.getStartX(), (int)branch.getStartY(), (int)branch.getEndX(), (int)branch.getEndY());
      }
    }
  }

  @Override
  protected void paintComponent(Graphics g) {
    final var size = getSize();
    g.setColor(Color.BLACK);
    g.fillRect(0, 0, size.width, size.height);
    drawTrees(g);
  }
}

class MainFrame extends JFrame implements KeyListener {
  MainFrame() {
    super();
    add(new DrawingPanel());
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setLocationByPlatform(true);
    pack();
    setSize(600, 600);
    addKeyListener(this);
  }

  @Override
  public void keyPressed(KeyEvent e) {
    final var isWPressed = e.getKeyCode() == KeyEvent.VK_W;
    final var isQPressed = e.getKeyCode() == KeyEvent.VK_Q;
    final var isF4Pressed = e.getKeyCode() == KeyEvent.VK_F4;
    if (((isWPressed || isQPressed) && e.isControlDown()) || (isF4Pressed && e.isAltDown())) {
      setVisible(false);
      dispose();
    }
  }

  @Override
  public void keyReleased(KeyEvent e) {}

  @Override
  public void keyTyped(KeyEvent e) {}
}

public class TreeFractal {
  public static void main(String[] args) {
    SwingUtilities.invokeLater(() -> {
      var frame = new MainFrame();
      frame.setVisible(true);
    });
  }
}
