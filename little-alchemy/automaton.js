class Automaton {
  #history = [];
  #historyGroups = [];
  #current = ['air', 'earth', 'fire', 'water'];
  #results = [];
  #workspace = document.getElementById('workspace');
  #library = library.el;

  constructor() {}

  #doDragDrop(el) {
    const mouseDownEvent = new MouseEvent('mousedown', {
      clientX: el.getBoundingClientRect().left,
      clientY: el.getBoundingClientRect().top,
      bubbles: true,
      cancelable: true,
    });
    const mouseMoveEvent = new MouseEvent('mousemove', {
      clientX: 200,
      clientY: 200,
      bubbles: true,
      cancelable: true,
    });
    const mouseUpEvent = new MouseEvent('mouseup', {
      bubbles: true,
      cancelable: true,
    });
    el.dispatchEvent(mouseDownEvent);
    el.dispatchEvent(mouseMoveEvent);
    el.dispatchEvent(mouseUpEvent);
  }

  next() {
    
  }
}

