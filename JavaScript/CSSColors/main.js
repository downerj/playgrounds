let canvas;
let context;
let color;
let cssColorDropdown;
let rgbHexInput;
let redInput;
let greenInput;
let blueInput;
let redLabel;
let greenLabel;
let blueLabel;

function padStringLeft(text, width, character = ' ') {
  let output = text.split('');
  for (let t = text.length; t < width; t++) {
    output.unshift(character);
  }
  
  return output.join('');
}

function findCSSColorByValue(colorString) {
  for (let colorName in CSS_COLORS) {
    let colorValue = CSS_COLORS[colorName];
    if (colorValue === colorString) {
      return colorName;
    }
  }
  
  return null;
}

function initializeElements() {
  canvas = document.getElementById('canvas');
  context = canvas.getContext('2d');
  cssColorDropdown = document.getElementById('cssColorDropdown');
  rgbHexInput = document.getElementById('rgbHexInput');
  redInput = document.getElementById('redInput');
  greenInput = document.getElementById('greenInput');
  blueInput = document.getElementById('blueInput');
  redLabel = document.getElementById('redLabel');
  greenLabel = document.getElementById('greenLabel');
  blueLabel = document.getElementById('blueLabel');
}

function resizeCanvas() {
  canvas.width = canvas.parentElement.clientWidth;
  canvas.height = canvas.parentElement.clientHeight;
  
  colorCanvas();
}

function initializeCSSColors() {
  let customColorOption = document.createElement('OPTION');
  customColorOption.innerText = 'Custom';
  customColorOption.value = 'custom';
  cssColorDropdown.appendChild(customColorOption);
  
  for (let colorName in CSS_COLORS) {
    let colorValue = CSS_COLORS[colorName];
    let option = document.createElement('OPTION');
    option.innerText = colorName;
    option.value = colorName;
    cssColorDropdown.appendChild(option);
  }
  
  cssColorDropdown.addEventListener('input', cssColorDropdown_onInput);
}

function initializeRGB() {
  rgbHexInput.addEventListener('input', rgbHexInput_onInput);
  
  for (let element of [redInput, greenInput, blueInput]) {
    element.min = 0;
    element.max = 255;
    element.value = 0;
    element.step = 1;
    element.addEventListener('input', rgbInput_onInput);
    element.addEventListener('mousedown', rgbInput_onMouseDown);
    element.addEventListener('mouseup', rgbInput_onMouseUp);
  }
  
  compileRGBFromSliders();
  updateRGB();
}

function colorCanvas() {
  context.fillStyle = color;
  context.fillRect(0, 0, canvas.width, canvas.height);
}

function computeRGBFromCanvas() {
  let data = context.getImageData(0, 0, 1, 1).data;
  
  redInput.value = data[0];
  greenInput.value = data[1];
  blueInput.value = data[2];
}

function compileRGBFromSliders() {
  let red = parseInt(redInput.value).toString(16);
  let green = parseInt(greenInput.value).toString(16);
  let blue = parseInt(blueInput.value).toString(16);
  
  let redString = padStringLeft(red, 2, '0');
  let greenString = padStringLeft(green, 2, '0');
  let blueString = padStringLeft(blue, 2, '0');
  let rgbString = `${redString}${greenString}${blueString}`;
  
  rgbHexInput.value = rgbString;
  color = `#${rgbString}`;
  colorCanvas();
}

function updateCSSColorDropdown() {
  let colorName = findCSSColorByValue(color);
  cssColorDropdown.value = (colorName !== null) ? colorName : 'custom';
}

function updateRGB() {
  redLabel.innerText = redInput.value;
  greenLabel.innerText = greenInput.value;
  blueLabel.innerText = blueInput.value;
}

function cssColorDropdown_onInput(_) {
  let cssColorName = cssColorDropdown.value;
  if (cssColorName == 'custom') {
    return;
  }
  
  color = cssColorName;
  colorCanvas();
  computeRGBFromCanvas();
  compileRGBFromSliders();
  updateRGB();
}

function rgbHexInput_onInput(_) {
  color = `#${rgbHexInput.value}`;
  colorCanvas();
  computeRGBFromCanvas();
  updateRGB();
  updateCSSColorDropdown();
}

function rgbInput_onInput(_) {
  compileRGBFromSliders();
  updateRGB();
  updateCSSColorDropdown();
}

function rgbInput_onMouseDown(event) {
  event.target.style.cursor = 'grabbing';
}

function rgbInput_onMouseUp(event) {
  event.target.style.cursor = 'grab';
}

function window_onLoad(_) {
  initializeElements();
  initializeCSSColors();
  initializeRGB();
  resizeCanvas();
}

function window_onResize(_) {
  resizeCanvas();
}

window.addEventListener('load', window_onLoad);
window.addEventListener('resize', window_onResize);
