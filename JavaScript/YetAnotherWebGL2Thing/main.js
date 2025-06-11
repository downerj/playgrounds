/**
 * 
 */
const resizeCanvas = () => {
  /**
   * @type {HTMLCanvasElement}
   */
  const canvas = document.getElementById('cvs');
  canvas.width = canvas.parentElement.clientWidth;
  canvas.height = canvas.parentElement.clientHeight;
};

/**
 * @param {Event} _event 
 */
const window_resize = (_event) => resizeCanvas();

/**
 * @param {Event} _event 
 */
const document_DOMContentLoaded = (_event) => {
  resizeCanvas();
};

document.addEventListener('DOMContentLoaded', document_DOMContentLoaded);
window.addEventListener('resize', window_resize);
