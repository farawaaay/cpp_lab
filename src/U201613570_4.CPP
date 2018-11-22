#include <stdlib.h>
#include <cstring>
#include <iostream>

bool error = false;
FILE* f;

class STACK {
  int* const elems;  //申请内存用于存放栈的元素
  const int max;     //栈能存放的最大元素个数
  int pos;           //栈实际已有元素个数，栈空时pos=0;
 public:
  STACK(int m);                              //初始化栈：最多m个元素
  STACK(const STACK& s);                     //用栈s拷贝初始化栈
  virtual int size() const;                  //返回栈的最大元素个数max
  virtual operator int() const;              //返回栈的实际元素个数pos
  virtual int operator[](int x) const;       //取下标x处的栈元素
  virtual STACK& operator<<(int e);          //将e入栈,并返回栈
  virtual STACK& operator>>(int& e);         //出栈到e,并返回栈
  virtual STACK& operator=(const STACK& s);  //赋s给栈,并返回被赋值的栈
  virtual void print() const;                //打印栈
  virtual ~STACK();                          //销毁栈
};

class QUEUE : public STACK {
  STACK s2;

 public:
  QUEUE(int m);                              //每个栈最多m个元素，要求实现的队列最多能入2m个元素
  QUEUE(const QUEUE& s);                     //用队列s拷贝初始化队列
  virtual operator int() const;              //返回队列的实际元素个数
  virtual int full() const;                  //返回队列是否已满，满返回1，否则返回0
  virtual int operator[](int x) const;       //取下标为x的元素，第1个元素下标为0
  virtual QUEUE& operator<<(int e);          //将e入队列,并返回队列
  virtual QUEUE& operator>>(int& e);         //出队列到e,并返回队列
  virtual QUEUE& operator=(const QUEUE& s);  //赋s给队列,并返回被赋值的队列
  virtual void print() const;                //打印队列
  virtual ~QUEUE();                          //销毁队列
};

STACK::STACK(int m)
    : elems(new int(m)), max(m) {
  pos = 0;
}
STACK::STACK(const STACK& s)
    : elems(new int[s.max]), max(s.max) {
  // memcpy(this->elems, s.elems, (s.pos) * sizeof(int));
  for (int i = 0; i < s.max; i++) {
    this->elems[i] = s.elems[i];
  }
  this->pos = s.pos;
}
STACK::~STACK() {
  if (this->elems != 0) {
    free(this->elems);
  }
  const_cast<int*&>(this->elems) = 0;  // 防止反复析构
  this->pos = 0;
  const_cast<int&>(this->max) = 0;
}

int STACK::size() const {
  return max;
}
void STACK::print() const {
  for (int i = 0; i < this->pos; i++)
    printf("%d  ", this->elems[i]);
  return;
}

STACK::operator int() const {
  return pos;
}
int STACK::operator[](int x) const {
  if (x > this->pos - 1) {
    error = 1;
  }
  return this->elems[x];
}

STACK& STACK::operator<<(int e) {
  if (this->pos == this->max)
    error = 1;
  else
    elems[this->pos++] = e;
  return *this;
}

STACK& STACK::operator>>(int& e) {
  if (this->pos > 0)
    e = this->elems[--this->pos];
  else
    error = 1;
  return *this;
}

STACK& STACK::operator=(const STACK& s) {
  const_cast<int*&>(this->elems) = (int*)malloc((s.max) * sizeof(int));
  memcpy(this->elems, s.elems, (s.pos) * sizeof(int));
  this->pos = s.pos;
  const_cast<int&>(this->max) = s.max;

  return *this;
}

QUEUE::QUEUE(int m)
    : STACK(m), s2(STACK(m)) {
}

QUEUE::QUEUE(const QUEUE& s)
    : STACK(s), s2(STACK(s.s2)) {
}

QUEUE::operator int() const {
  return STACK::operator int() + int(s2);
}

int QUEUE::full() const {
  // 当左边的栈为满且右边的栈不为空，则视为队列满了
  return STACK::operator int() > 0 && int(s2) == s2.size();
}

int QUEUE::operator[](int x) const {
  if (x >= int(*this)) {
    error = true;
    return -1;
  }
  int n = STACK::operator int();
  if (x >= n)
    return s2[x - n];
  return STACK::operator[](n - x - 1);
}

QUEUE& QUEUE::operator<<(int e) {
  if (full()) {
    // 队列满了直接抛出错误
    error = true;
    return *this;
  }

  if (int(s2) == s2.size()) {
    // 将s2全部移到s1
    int x;
    while (int(s2) > 0) {
      s2 >> x;
      STACK::operator<<(x);
    }
  }
  s2 << e;
  return *this;
}

QUEUE& QUEUE::operator>>(int& e) {
  if (int(*this) == 0) {
    error = true;
    return *this;
  }

  if (STACK::operator int() > 0)
    STACK::operator>>(e);
  else {
    int x;
    while (int(s2) > 1) {
      s2 >> x;
      STACK::operator<<(x);
    }
    s2 >> e;
  }
  return *this;
}

QUEUE& QUEUE::operator=(const QUEUE& s) {
  STACK::operator=(s);
  s2 = s.s2;
  return *this;
}

void QUEUE::print() const {
  for (int i = STACK::operator int() - 1; i >= 0; i--)
    fprintf(f, "%d  ", STACK::operator[](i));
  for (int i = 0; i < int(s2); i++)
    fprintf(f, "%d  ", s2[i]);
}

QUEUE::~QUEUE() {
  // s2.~STACK();
  // 不需要额外析构
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    int menNum, womenNum, m, f;
    printf("Input amount of man, woman, and order of man,woman.\n(Split by comma):");
    if (scanf("%d,%d,%d,%d", &menNum, &womenNum, &m, &f) &&
        menNum && womenNum && m && f) {
      QUEUE queueMen(2 * menNum + 1);
      QUEUE queueWomen(2 * womenNum + 1);
      for (int i = 0; i < menNum; ++i)
        queueMen << i + 1;
      for (int i = 0; i < womenNum; ++i)
        queueWomen << i + 1;

      int currentMan, currentWoman, counter = 1;
      while (1) {
        queueMen >> currentMan;
        queueWomen >> currentWoman;
        if (currentMan == m && currentWoman == f) {
          printf("Round %d\n", counter);
          break;
        }
        queueMen << currentMan;
        queueWomen << currentWoman;
        ++counter;
      }
    }

    return 0;
  }

  QUEUE* p;
  char* filename = argv[0];
  char type = 'S';
  int g_value;

  int dotIndex = -1;
  int slashIndex = -1;
  for (int i = strlen(filename) - 1; i >= 0; i--) {
    if (filename[i] == '.' && dotIndex == -1)
      dotIndex = i;
    if (filename[i] == '\\' && dotIndex != -1 && slashIndex == -1) {
      slashIndex = i;
      break;
    }
  }
  filename[dotIndex] = 0;

  f = fopen(strcat(filename + slashIndex + 1, ".TXT"), "w");

  for (int i = 2; i < argc + 1; i++) {
    if (i == argc || (i != 2 && argv[i][0] == '-' && strlen(argv[i]) == 2)) {
      if (error) {
        fprintf(f, "%c  %c  ", type, 'E');
        break;
      } else {
        fprintf(f, "%c  ", type);
        switch (type) {
          case 'S':
            fprintf(f, "%d  ", p->size());
            break;
          case 'N':
            fprintf(f, "%d  ", int(*p));
            break;
          case 'G':
            fprintf(f, "%d  ", g_value);
            break;
          case 'C': {
            QUEUE* ap = new QUEUE(*p);
            delete p;
            p = ap;
            p->print();
            break;
          }
          default:
            p->print();
        }
      }
      if (i != argc)
        type = argv[i][1];
    } else {
      int num = atoi(argv[i]);
      switch (type) {
        case 'S':
          p = new QUEUE(num);
          break;
        case 'I':
          (*p) << num;
          break;
        case 'O':
          for (int j = 0; j < num; j++) {
            int _ = 0;
            (*p) >> _;
          }
          break;
        case 'A': {
          QUEUE* cp = new QUEUE(num);
          *cp = (*p);
          delete p;
          p = cp;
          break;
        }
        case 'G':
          g_value = (*p)[num];
          break;
        default:
          break;
      }
    }
  }
  fprintf(f, "\n");
}
