'use strict';

function gel(id) {
    return document.getElementById(id);
}

function handle(obj, event, callback) {
    obj.addEventListener(event, callback);
}

const config = {
    fps: 60,
}

const cvs = {
    bg: gel('cvsBG'),
    fg: gel('cvsFG'),
};
cvs.width  = cvs.bg.width;
cvs.height = cvs.bg.height;
cvs.bounds = cvs.bg.getBoundingClientRect();

const ctx = {
    bg: cvs.bg.getContext('2d'),
    fg: cvs.fg.getContext('2d'),
    points: [],
    deletedPoints: [],
};
ctx.setStyle = function(style) {
    this.bg.strokeStyle = style;
    this.fg.strokeStyle = style;
    this.bg.fillStyle   = style;
    this.fg.fillStyle   = style;
};

const mouse = {
    x: null,
    y: null,
    oldDown: false,
    down: false,
};
mouse.update = function(event, state) {
    /* TODO: Include window scroll */
    this.x = event.clientX - cvs.bounds.left;
    this.y = event.clientY - cvs.bounds.top;

    if (state === undefined || state === null) {
        return;
    }

    mouse.oldDown = mouse.down;
    mouse.down    = state;
};

const keys = {};

function point(x, y) {
    ctx.fg.fillRect(x, y, 2, 2);
}

function tick() {
    if ('Meta' in keys) {
        let arrpts = ctx.points;
        let delpts = ctx.deletedPoints;

        if ('z' in keys) {
            if (arrpts.length > 0) {
                let pts = arrpts.splice(arrpts.length - 1, 1)[0];
                delpts.push(pts);
            }
            delete keys['z'];
        } else if ('y' in keys) {
            if (delpts.length > 0) {
                let pts = delpts.splice(delpts.length - 1, 1)[0];
                arrpts.push(pts);
            }
            delete keys['y'];
        }
    }

    if (mouse.down && !mouse.oldDown) {
        ctx.points.push([]);
        ctx.deletedPoints.splice(0, ctx.deletedPoints.length);
        mouse.oldDown = mouse.down;
    }

    if (mouse.down) {
        let pts = ctx.points.last();
        pts.push({
            x: mouse.x, 
            y: mouse.y
        });
    }

    ctx.fg.clearRect(0, 0, cvs.width, cvs.height);
    for (let a = 0; a < ctx.points.length; a++) {
        let pts = ctx.points[a];
        if (pts.length > 1) {
            ctx.fg.beginPath();
            ctx.fg.moveTo(pts.x, pts.y);
            for (let p = 1; p < pts.length; p++) {
                let point = pts[p];
                ctx.fg.lineTo(point.x, point.y);
            }
            ctx.fg.stroke();
        }
    }
}

window.wrap('load').handle(function() {
    ctx.bg.fillStyle = '#000';
    ctx.bg.fillRect(0, 0, cvs.width, cvs.height);

    ctx.bg.translate(0.5, 0.5);
    ctx.fg.translate(0.5, 0.5);
    ctx.setStyle('#fff');
    ctx.fg.lineWidth = 2;

    setInterval(tick, 1000 / config.fps);    
});

cvs.fg.wrap('mousedown').handle(function(event) {
    mouse.update(event, true);
});

cvs.fg.wrap('mouseup').handle(function(event) {
    mouse.update(event, false);
});

cvs.fg.wrap('mousemove').handle(function(event) {
    mouse.update(event);
});

window.wrap('keydown').handle(function(event) {
    let key = event.key;
    if (!(key in keys)) {
        keys[key] = 0;
    }
    keys[key]++;
});

window.wrap('keyup').handle(function(event) {
    let key = event.key;
    if (key in keys) {
        delete keys[key];
    }
});