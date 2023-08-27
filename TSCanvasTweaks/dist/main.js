"use strict";
function fillHueToRGB(hue, output) {
    if (hue < 0) {
        hue += (hue % 360);
    }
    var red = 0;
    var green = 0;
    var blue = 0;
    var hueSection = Math.floor(hue / 60);
    var hueDelta = hue % 60;
    switch (hueSection) {
        case 0:
            red = 255;
            green = hueDelta;
            break;
        case 1:
            red = hueDelta;
            green = 255;
            break;
        case 2:
            green = 255;
            blue = hueDelta;
            break;
        case 3:
            green = hueDelta;
            blue = 255;
            break;
        case 4:
            red = hueDelta;
            blue = 255;
            break;
        case 5:
            red = 255;
            blue = hueDelta;
            break;
    }
}
var Application = (function () {
    function Application(canvas) {
        this.canvas = canvas;
        var context = canvas.getContext('2d');
        if (context === null) {
            throw 'Context failed to generate';
        }
        this.context = context;
    }
    Application.prototype.draw = function () {
        var imageData = this.context.getImageData(0, 0, this.canvas.width, this.canvas.height);
        var buffer = imageData.data;
        for (var y = 0; y < this.canvas.height; y++) {
            for (var x = 0; x < this.canvas.width; x++) {
                var e = (x * 4) + (y * this.canvas.width * 4);
                var r = e;
                var g = e + 1;
                var b = e + 2;
                var a = e + 3;
                buffer[r] = 255;
                buffer[g] = 0;
                buffer[b] = 0;
                buffer[a] = 255;
            }
        }
        this.context.putImageData(imageData, 0, 0);
    };
    Application.prototype.run = function () {
        this.draw();
    };
    return Application;
}());
window.addEventListener('load', function (_) {
    var canvas = document.getElementById('cvs');
    var canvasWrapper = document.getElementsByClassName('canvas-wrapper')[0];
    if (canvas === null || canvasWrapper === null) {
        throw "Error retrieving DOM elements";
    }
    canvas.width = canvasWrapper.offsetWidth;
    canvas.height = canvasWrapper.offsetHeight;
    new Application(canvas).run();
});
