export const degToRad = degrees => (degrees * Math.PI) / 180;

export class Camera {
  /**
   * @returns {number}
   */
  get x() {
    return this.#x;
  }

  /**
   * @param {number} value
   */
  set x(value) {
    this.#x = value;
  }

  /**
   * @returns {number}
   */
  get y() {
    return this.#y;
  }

  /**
   * @param {number} value
   */
  set y(value) {
    this.#y = value;
  }

  /**
   * @returns {number}
   */
  get z() {
    return this.#z;
  }

  /**
   * @param {number} value
   */
  set z(value) {
    this.#z = value;
  }

  /**
   * @param {number} dr
   */
  moveLeft(dr) {
    const rad = -degToRad(this.#ay);
    this.#x -= dr * Math.cos(rad);
    this.#z += dr * Math.sin(rad);
  }

  /**
   * @param {number} dr
   */
  moveRight(dr) {
    const rad = -degToRad(this.#ay);
    this.#x += dr * Math.cos(rad);
    this.#z -= dr * Math.sin(rad);
  }

  /**
   * @param {number} dr
   */
  moveDown(dr) {
    this.#y -= dr;
  }

  /**
   * @param {number} dr
   */
  moveUp(dr) {
    this.#y += dr;
  }

  /**
   * @param {number} dr
   */
  moveForward(dr) {
    const rad = -degToRad(this.#ay);
    this.#x -= dr * Math.sin(rad);
    this.#z -= dr * Math.cos(rad);
  }

  /**
   * @param {number} dr
   */
  moveBackward(dr) {
    const rad = -degToRad(this.#ay);
    this.#x += dr * Math.sin(rad);
    this.#z += dr * Math.cos(rad);
  }

  /**
   * @returns {number}
   */
  get ax() {
    return this.#ax;
  }

  /**
   * @param {number} value
   */
  set ax(value) {
    this.#ax = value;
  }

  /**
   * @returns {number}
   */
  get ay() {
    return this.#ay;
  }

  /**
   * @param {number} value
   */
  set ay(value) {
    this.#ay = value;
  }

  /**
   * @returns {number}
   */
  get az() {
    return this.#az;
  }

  /**
   * @param {number} value
   */
  set az(value) {
    this.#az = value;
  }

  /**
   * @param {number} dax
   */
  rotateX(dax) {
    this.#ax += dax;
  }

  /**
   * @param {number} day
   */
  rotateY(day) {
    this.#ay += day;
  }

  /**
   * @param {number} daz
   */
  rotateZ(daz) {
    this.#az += daz;
  }

  /**
   * @param {number} dax
   * @param {number} day
   * @param {number} daz
   */
  rotate(dax, day, daz) {
    this.rotateX(dax);
    this.rotateY(day);
    this.rotateZ(daz);
  }

  /**
   * @type {number}
   */
  #x = 0;
  /**
   * @type {number}
   */
  #y = 0;
  /**
   * @type {number}
   */
  #z = 0;
  /**
   * @type {number}
   */
  #ax = 0;
  /**
   * @type {number}
   */
  #ay = 0;
  /**
   * @type {number}
   */
  #az = 0;
}
