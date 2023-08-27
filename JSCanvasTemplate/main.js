let byId = document.getElementById.bind(document);

let app;
window.addEventListener('load', (_) => {
  let canvas = byId('canvas');
  canvas.width = canvas.parentElement.offsetWidth;
  canvas.height = canvas.parentElement.offsetHeight;
  app = new CanvasApplication(canvas);
  app.run();
});
