const readline = require('readline');
const { PerformanceObserver, performance } = require('perf_hooks');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.question('Введите строку ', (str) => {
  rl.question('Введите строку для поиска ', (target) => {
    rl.question('Игнорировать регистр? да/нет ', (yesNo) => {
      let isLowerCase;
      if (yesNo === 'да') {
        isLowerCase = true;
      }
      let time = performance.now();
      boyer(str, target, isLowerCase);
      time = performance.now() - time;
      console.log('Время выполнения = ', time);
      rl.close;
    });
  });
});

function boyer(str, target, isLowerCase) {
  if (isLowerCase) {
    newStr = str.toLowerCase();
    newTarget = target.toLowerCase();
  } else {
    newStr = str;
    newTarget = target;
  }
  let ret = [];
  let indexLength = newTarget.length - 1,
    obj = {},
    i = 0,
    j = 0,
    char = {};
  for (i; i < indexLength; i++) {
    obj[newTarget.charAt(i)] = indexLength - i;
  }
  i = 0;
  while (i < newStr.length) {
    for (j = indexLength; j >= 0; j--)
      if (newTarget.charAt(j) != newStr.charAt(i + j)) {
        break;
      }
    if (j < 0) {
      i++;
      ret.push(i);
    } else {
      char = obj[newStr.charAt(i + j)];
      if (!char) char = indexLength + 1;
      char += j - indexLength;
      if (char <= 0) char = 1;
      i += char;
    }
  }
  if (ret === []) {
    console.log('Ничего не найдено');
  }
  return ret;
}
