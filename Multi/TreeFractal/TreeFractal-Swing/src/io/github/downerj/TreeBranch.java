package io.github.downerj;

public class TreeBranch {
  private final double startX;
  private final double startY;
  private final double endX;
  private final double endY;
  private final double length;
  private final double angle;
  private final int depth;
  private final int color;

  public TreeBranch(double startX, double startY, double endX, double endY, double length, double angle, int depth, int color) {
    this.startX = startX;
    this.startY = startY;
    this.endX = endX;
    this.endY = endY;
    this.length = length;
    this.angle = angle;
    this.depth = depth;
    this.color = color;
  }

  public double getStartX() { return startX; }
  public double getStartY() { return startY; }
  public double getEndX() { return endX; }
  public double getEndY() { return endY; }
  public double getLength() { return length; }
  public double getAngle() { return angle; }
  public int getDepth() { return depth; }
  public int getColor() { return color; }
}
