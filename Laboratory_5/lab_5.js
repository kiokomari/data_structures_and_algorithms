const canvas = document.getElementById('canvas');
const btn = document.querySelector('.pain');
const fDepth = document.querySelector('.fractal_depth');
const rDepth = document.querySelector('.req_depth');
const fTime = document.querySelector('.fractal_time');

const ctx = canvas.getContext('2d');

let points = [];

const pushPoints = (x, y, dx, dy) => {
  points.push({ x: x, y: y, dx: dx, dy: dy });
};

const buildLine = (deltaX, deltaY) => {
  pushPoints(x, y, deltaX, deltaY);
  x += deltaX;
  y += deltaY;
};

const A = (level) => {
  rDepth.value = val++;
  if (level > 0) {
    A(level - 1);
    buildLine(+dist, +dist);
    B(level - 1);
    buildLine(+2 * dist, 0);
    D(level - 1);
    buildLine(+dist, -dist);
    A(level - 1);
  }
};

const B = (level) => {
  rDepth.value = val++;
  if (level > 0) {
    B(level - 1);
    buildLine(-dist, +dist);
    C(level - 1);
    buildLine(0, +2 * dist);
    A(level - 1);
    buildLine(+dist, +dist);
    B(level - 1);
  }
};

const C = (level) => {
  rDepth.value = val++;
  if (level > 0) {
    C(level - 1);
    buildLine(-dist, -dist);
    D(level - 1);
    buildLine(-2 * dist, 0);
    B(level - 1);
    buildLine(-dist, +dist);
    C(level - 1);
  }
};

const D = (level) => {
  rDepth.value = val++;
  if (level > 0) {
    D(level - 1);
    buildLine(+dist, -dist);
    A(level - 1);
    buildLine(0, -2 * dist);
    C(level - 1);
    buildLine(-dist, -dist);
    D(level - 1);
  }
};

const paint = () => {
  let point = points[p];
  ctx.beginPath();
  ctx.moveTo(point.x, point.y);
  ctx.lineTo(point.x + point.dx, point.y + point.dy);
  ctx.stroke();
  if (p < points.length - 1) {
    p++;
    paint();
  }
};

btn.onclick = () => {
  ctx.clearRect(0, 0, 400, 400);
  level = fDepth.value;

  dist = 100;

  for (var i = level; i > 0; i--) {
    dist = dist / 2;
  }

  val = 0;
  x = dist * 2;
  y = dist;
  p = 0;

  points = [];

  const t1 = performance.now();
  A(level); // start recursion
  buildLine(+dist, +dist);
  B(level); // start recursion
  buildLine(-dist, +dist);
  C(level); // start recursion
  buildLine(-dist, -dist);
  D(level); // start recursion
  buildLine(+dist, -dist);

  paint();
  const t2 = performance.now();
  fTime.value = t2 - t1;
};
