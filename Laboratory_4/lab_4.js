const fs = require('fs');
const { type } = require('os');

class Deque {
  constructor() {
    this.front = this.back = undefined;
    this.regroupArr = ['', ''];
  }
  //Добавить в дек спереди
  addFront(value) {
    if (!this.front) this.front = this.back = { value };
    else this.front = this.front.next = { value, prev: this.front };
  }
  //Убрать из дека спереди
  removeFront() {
    let value = this.peekFront();
    if (this.front === this.back) this.front = this.back = undefined;
    else (this.front = this.front.prev).next = undefined;
    return value;
  }
  peekFront() {
    return this.front && this.front.value;
  }
  peekBack() {
    return this.back && this.back.value;
  }
  //Добавить в дек сзади
  addBack(value) {
    if (!this.front) this.front = this.back = { value };
    else this.back = this.back.prev = { value, next: this.back };
  }
  //Убрать из дека сзади
  removeBack() {
    let value = this.peekBack();
    if (this.front === this.back) this.front = this.back = undefined;
    else (this.back = this.back.next).back = undefined;
    return value;
  }
  //Разбить дек на буквы и цифры, и очищает дек
  regroup() {
    while (this.front !== undefined) {
      let char = this.removeBack();
      if (/^[^\d]$/.test(char)) {
        this.regroupArr[0] += char;
      }
      if (/^[\d]$/.test(char)) {
        this.regroupArr[1] += char;
      }
    }
    return this.regroupArr;
  }
}
//Создание дека
let deque = new Deque();

//Вывод из файла
let str = fs.readFileSync(process.cwd() + '/' + 'beginTextFile.txt').toString();

//Запись в дек
for (let i = 0; i < str.length; i++) {
  deque.addFront(str[i]);
}
// console.log('Сформированный дек', deque);

//Вызов функции перегруппирования фразы на цифры и буквы
let resultArr = deque.regroup().join(' | ');
// console.log('Сгруппированный дек', deque);
fs.writeFileSync('endTextFile.txt', resultArr);
