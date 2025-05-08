/**
 * 
 * @param {number} degrees
 * @returns {number} 
 */
function degreesToRadians(degrees) {
  return degrees * Math.PI / 180.0;
}

/**
 * 
 * @param {number} radians
 * @returns {number} 
 */
function radiansToDegrees(radians) {
  return radians * 180.0 / Math.PI;
}

class Tree {
  /**
   * 
   * @param {number} x
   * @param {number} y
   * @param {number} trunkLength
   * @param {number} trunkAngle
   * @param {BranchConfig} [config=]
   */
  constructor(x, y, trunkLength, trunkAngle, config) {
    this._x = x;
    this._y = y;
    this._trunkLength = trunkLength;
    this._trunkAngle = trunkAngle;
    if (config) {
      Branch._config = config;
    }
  
    let depth = 0;
    let trunk = new Branch(x, y, trunkLength, trunkAngle, depth);
    this._branches = [trunk,];
    
    /**
     * @type {Branch}
     */
    this._currentBranch = null;
  }

  /**
   * @returns {boolean}
   */
  update() {
    // If the branch list is empty, return false to stop the loop.
    if (this._branches.length === 0) {
      return false;
    }

    let branch = this._branches.shift();
    this._currentBranch = branch;
    // If the next branch is actually a leaf, then return instead of
    // generating children. Return true to keep the loop drawing until
    // the list is empty.
    if (branch.depth >= Branch._config.maxDepth) {
      return true;
    }

    for (let child of branch.generateChildren()) {
      this._branches.push(child);
    }

    return true;
  }

  /**
   * 
   * @param {CanvasRenderingContext2D} context 
   */
  draw(context) {
    this._currentBranch.draw(context);
    this._currentBranch = null;
  }
}

class Branch {
  /**
   * 
   * @param {number} x 
   * @param {number} y 
   * @param {number} length 
   * @param {number} angle
   * @param {number} depth
   */
  constructor(x, y, length, angle, depth) { 
    this._x0 = x;
    this._y0 = y;
    this._length = length;
    this._angle = angle;
    this._depth = depth;
    this._x1 = length * Math.cos(degreesToRadians(angle)) + x;
    this._y1 = length * Math.sin(degreesToRadians(angle)) + y;
  }

  /**
   * 
   * @param {CanvasRenderingContext2D} context 
   */
  draw(context) {
    let hue = (this._depth * Branch._config.deltaHue) % 360;

    context.beginPath();
    context.lineWidth = Branch._config.lineWidth;
    context.strokeStyle = `hsl(${hue}, 100%, 50%)`;
    context.moveTo(this._x0, this._y0);
    context.lineTo(this._x1, this._y1);
    context.stroke();
  }

  /**
   * 
   * @return {Branch[]}
   */
  generateChildren() {
    let x = this._x1;
    let y = this._y1;
    let length = this._length * Branch._config.shrinkRatio;
    let depth = this._depth + 1;
    let branchCountIsOdd = (Branch._config.numChildren % 2 === 1);
    let children = [];

    if (branchCountIsOdd) {
      children.push(new Branch(x, y, length, this._angle, depth));
      for (let b = 1; b < Branch._config.numChildren; b++) {
        let multiplier = Math.floor((b + 1) * 0.5);
        let direction = ((b - 1) % 2 === 0) ? 1 : -1;
        let deltaAngle = Branch._config.deltaAngle * multiplier * direction;
        let angle = this._angle + deltaAngle;
        children.push(new Branch(x, y, length, angle, depth));
      }
    } else {
      for (let b = 0; b < Branch._config.numChildren; b++) {
        let multiplier = Math.floor((b + 2) * 0.5) - 0.5;
        let direction = (b % 2 === 0) ? 1 : -1;
        let deltaAngle = Branch._config.deltaAngle * multiplier * direction;
        let angle = this._angle + deltaAngle;
        children.push(new Branch(x, y, length, angle, depth));
      }
    }

    return children;
  }

  /**
   * @returns {number}
   */
  get depth() {
    return this._depth;
  }
}

class BranchConfig {
  /**
   * 
   * @param {number} numChildren 
   * @param {number} deltaAngle 
   * @param {number} shrinkRatio 
   * @param {number} maxDepth 
   * @param {number} deltaHue 
   * @param {number} lineWidth 
   */
  constructor(numChildren, deltaAngle, shrinkRatio, maxDepth, deltaHue, lineWidth) {
    this.numChildren = numChildren;
    this.deltaAngle = deltaAngle;
    this.shrinkRatio = shrinkRatio;
    this.maxDepth = maxDepth;
    this.deltaAngle = deltaAngle;
    this.deltaHue = deltaHue;
    this.lineWidth = lineWidth;
  }
}

BranchConfig.STANDARD = new BranchConfig(2, 90, 0.6, 10, 30, 2);
BranchConfig.SIERPINSKI_TRIANGLE = new BranchConfig(3, 120, 0.5, 10, 30, 2);
BranchConfig.PINWHEEL = new BranchConfig(4, 90, 0.4, 10, 30, 2);
BranchConfig.MIN_NUM_CHILDREN = 2;
BranchConfig.MAX_NUM_CHILDREN = 4;
BranchConfig.MIN_DELTA_ANGLE = 1.0;
BranchConfig.MAX_DELTA_ANGLE = 180.0
BranchConfig.MIN_SHRINK_RATIO = 0.1;
BranchConfig.MAX_SHRINK_RATIO = 1.0;
BranchConfig.MIN_DELTA_HUE = 1.0;
BranchConfig.MAX_DELTA_ANGLE = 180.0;
BranchConfig.MIN_LINE_WIDTH = 1;
BranchConfig.MAX_LINE_WIDTH = 3;

Branch._config = BranchConfig.STANDARD;
