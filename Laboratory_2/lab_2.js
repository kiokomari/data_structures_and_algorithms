const { PerformanceObserver, performance } = require('perf_hooks');

//Бинарный поиск
const binarySearch = (target, arr) => {
  let i = 0;
  let j = arr.length;
  let k;
  while (i < j) {
    k = Math.floor((i + j) / 2);
    if (target <= arr[k]) {
      j = k;
    } else {
      i = k + 1;
    }
  }
  if (arr[i] === target) {
    return i;
  } else {
    return -1;
  }
};

//Бинарное удаление
const binaryRemove = (target, arr) => {
  let i = 0;
  let j = arr.length;
  let k;
  while (i < j) {
    k = Math.floor((i + j) / 2);
    if (target <= arr[k]) {
      j = k;
    } else {
      i = k + 1;
    }
  }
  if (arr[i] === target) {
    arr.splice(i, 1);
    return arr;
  } else {
    return -1;
  }
};

//Бинарное добавление
const binaryAdd = (target, arr) => {
  let i = 0;
  let j = arr.length;
  let k;
  while (i < j) {
    k = Math.floor((i + j) / 2);
    if (target <= arr[k]) {
      j = k;
    } else {
      i = k + 1;
    }
  }
  arr.splice(i, 0, target);
  return arr;
};

//Создаю массив длинной 10
let arr = Array.from({ length: 100 }, () => Math.floor(Math.random() * 100));

//Сортирую
arr.sort((a, b) => a - b);

let time = performance.now();
console.log(arr.indexOf(45));
time = performance.now() - time;
console.log('Время выполнения = ', time);

// if (binarySearch(2, arr) !== -1) {
//   console.log('Удалить число 2: ', binaryRemove(2, arr));
//   console.log('Добавить число: 10', binaryAdd(10, arr));
// }

// console.log('Индекс числа 2: ', binarySearch(2, arr));
// console.log('Индекс числа 10: ', binarySearch(10, arr));
// console.log('Массив, с добавлением числа 1:', binaryAdd(1, arr));
