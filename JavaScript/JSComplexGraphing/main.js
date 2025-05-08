let grapher;

window.addEventListener('load', () => {
  let cvs = document.getElementById('cvs');
  cvs.width = cvs.parentElement.offsetWidth;
  cvs.height = cvs.parentElement.offsetHeight;
  let ctx = cvs.getContext('2d');

  grapher = new Grapher(ctx);
  grapher.plot((z) => {
    return z;
  });
});
