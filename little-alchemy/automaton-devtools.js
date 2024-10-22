const automaton = new class {
  #library;
  #workspace;
  #clearButton;
  #previousDivs = [];
  #completedDivs = [];
  #currentDivs = [];
  #nextDivs = [];
  #previousIndex = 0;
  #testDiv;

  constructor() {
    this.#library = document.getElementById('library');
    this.#workspace = document.getElementById('workspace');
    this.#clearButton = document.getElementById('clearWorkspace');
    for (const div of [...this.#library.children]) {
      this.#previousDivs.push(div);
      this.#currentDivs.push(div);
    }
    this.#testDiv = this.#currentDivs.shift();
  }

  #doDragDrop(div) {
    const mouseDownEvent = new MouseEvent('mousedown', {
      clientX: div.getBoundingClientRect().left,
      clientY: div.getBoundingClientRect().top,
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
    div.dispatchEvent(mouseDownEvent);
    div.dispatchEvent(mouseMoveEvent);
    div.dispatchEvent(mouseUpEvent);
  }

  #getResultName() {
    if (this.#workspace.children.length !== 1) {
      return null;
    }
    return this.#workspace.children[0].textContent;
  }

  #testElements(div1, div2) {
    this.#doDragDrop(div1);
    this.#doDragDrop(div2);
    return this.#getResultName();
  }

  next() {
    this.#clearButton.click();

    const name1 = div1.textContent;
    const name2 = div2.textContent;
    console.log(`${name1} + ${name2} => ${result}`);

    if (this.#previousIndex < this.#previousDivs.length) {
      ++this.#previousIndex;
    }
  }
}();