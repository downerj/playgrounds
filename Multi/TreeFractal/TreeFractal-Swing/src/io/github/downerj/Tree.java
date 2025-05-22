package io.github.downerj;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

public class Tree implements Iterable<TreeBranch> {
  public double trunkStartX;
  public double trunkStartY;
  public double trunkLength;
  public double trunkAngle;
  public double branchLengthRatioCCW = .6;
  public double branchLengthRatioCW = branchLengthRatioCCW;
  public int maxDepth = 8;
  public int depthToSwitchColors = 5;
  public double deltaAngleCCW = Math.PI / 3.;
  public double deltaAngleCW = deltaAngleCCW;
  public int branchColor = 0xffff7700;
  public int leafColor = 0xff00ff00;

  private Queue<TreeBranch> branches;

  private enum Direction { CCW, CW }

  public Tree(double trunkStartX, double trunkStartY, double trunkLength, double trunkAngle) {
    this.trunkStartX = trunkStartX;
    this.trunkStartY = trunkStartY;
    this.trunkLength = trunkLength;
    this.trunkAngle = trunkAngle;
    branches = new LinkedList<>();
  }

  private void makeTrunk() {
    final var newEndX = trunkStartX + Math.cos(trunkAngle) * trunkLength;
    final var newEndY = trunkStartY + Math.sin(trunkAngle) * trunkLength;
    final var newDepth = 0;
    final var newBranch = new TreeBranch(trunkStartX, trunkStartY, newEndX, newEndY, trunkLength, trunkAngle, newDepth, branchColor);
    branches.add(newBranch);
  }

  private void replaceBranchWithChildren() {
    if (branches.isEmpty()) {
      return;
    }
    final var branch = branches.remove();
    for (final var direction : Direction.values()) {
      final var newStartX = branch.getEndX();
      final var newStartY = branch.getEndY();
      final var newLength = branch.getLength() * (direction == Direction.CCW ? branchLengthRatioCCW : branchLengthRatioCW);
      final var newAngle = branch.getAngle() + (direction == Direction.CCW ? -deltaAngleCCW : deltaAngleCW);
      final var newEndX = newStartX + Math.cos(newAngle) * newLength;
      final var newEndY = newStartY + Math.sin(newAngle) * newLength;
      final var newDepth = branch.getDepth() + 1;
      final var newColor = newDepth < depthToSwitchColors ? branchColor : leafColor;
      final var newBranch = new TreeBranch(newStartX, newStartY, newEndX, newEndY, newLength, newAngle, newDepth, newColor);
      branches.add(newBranch);
    }
  }

  @Override
  public Iterator<TreeBranch> iterator() {
    return new TreeIterator(this);
  }

  class TreeIterator implements Iterator<TreeBranch> {
    private Tree tree;

    TreeIterator(Tree tree) {
      this.tree = tree;
      tree.makeTrunk();
    }

    @Override
    public boolean hasNext() {
      return !tree.branches.isEmpty();
    }

    @Override
    public TreeBranch next() {
      final var branch = tree.branches.peek();
      if (branch != null && branch.getDepth() < tree.maxDepth) {
        tree.replaceBranchWithChildren();
        return branch;
      } else {
        return tree.branches.remove();
      }
    }
  }
}
