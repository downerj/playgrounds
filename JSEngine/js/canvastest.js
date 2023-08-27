var GCW;
var GCH;
var x;
var y;
var r;
var dx;
var dy;
var dr;
var cx;
var cy;
var cr;
var counter;

var COL_BLACK  = color('#000000');
var COL_RED    = color('#ff0000');
var COL_SKY    = color('#007fff');
var COL_YELLOW = color('#ffff00');
var COL_WHITE  = color('#ffffff');
var COL_GREYC  = color('#cccccc');
var COL_GREY9  = color('#999999');
var COL_GREY6  = color('#666666');
var COL_GREY3  = color('#333333');

function init() {
   GCW     = canvas.width;
   GCH     = canvas.height;
   x       = 200;
   y       = 200;
   r       =  50;
   dx      =   0;
   dy      =   0;
   dr      =   0;
   cx      =   0;
   cy      =   0;
   cr      =  15;
   counter =   0;
}

function run() {
   draw();
   handleInput();
   update();
}

function draw() {
   // draw the background
   ctx.setFill(COL_BLACK);
   ctx.fillRect(0, 0, GCW, GCH);
   
   // draw a vertical line
   ctx.setFill(COL_RED);
   ctx.fillRect(x, 0, 2, GCH);
   
   // draw a horizontal line
   ctx.setFill(COL_SKY);
   ctx.fillRect(0, y, GCW, 2);
   
   // draw a circle
   ctx.setStroke(COL_YELLOW);
   ctx.strokeOval(x - r, y - r, 2 * r, 2 * r);
   
   // draw the cursor
   if (counter % 30 < 15) {
      ctx.setStroke(COL_WHITE);
   }
   else {
      ctx.setStroke(COL_GREYC);
   }
   ctx.beginPath();
   ctx.moveTo(cx - cr, cy     );
   ctx.lineTo(cx + cr, cy     );
   ctx.moveTo(cx,      cy - cr);
   ctx.lineTo(cx,      cy + cr);
   ctx.stroke();
}

function update() {
   x += dx;
   y += dy;
   counter++;
   
   if ((x + r > GCW) && (dx > 0)) {
      x  = GCW - r;
      dx = -dx;
   } else if ((x - r < 0) && (dx < 0)) {
      x  = 0 + r;
      dx = -dx;
   }
   
   if ((y + r > GCW) && (dy > 0)) {
      y  = GCH - r;
      dy = -dy;
   } else if ((y - r < 0) && (dy < 0)) {
      y  = 0 + r;
      dy = -dy;
   }
}

function handleInput() {
   cx = ui.x;
   cy = ui.y;
   
   if (ui.keyUp > 0) {
      dy = -5;
   } else if (ui.keyDown > 0) {
      dy = +5;
   } else {
      dy = 0;
   }
   
   if (ui.keyLeft > 0) {
      dx = -5;
   } else if (ui.keyRight > 0) {
      dx = +5;
   } else {
      dx = 0;
   }
}
