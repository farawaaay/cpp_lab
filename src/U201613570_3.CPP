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
  free(this->elems);
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

int main(int argc, char* argv[]) {
  STACK* p;
  char* filename = argv[0];
  char type = 'S';
  int g_value;

  int dotIndex = -1;
  int slashIndex = -1;
  for (int i = strlen(filename) - 1; i >= 0; i--) {
    if (filename[i] == '.' && dotIndex == -1)
      dotIndex = i;
    if (filename[i] == '\\' && dotIndex != -1 && slashIndex == -1)
      slashIndex = i;
  }
  filename[dotIndex] = 0;

  f = fopen(strcat(filename + slashIndex + 1, ".TXT"), "w");

  for (int i = 2; i < argc + 1; i++) {
    if (i == argc || (i != 2 && argv[i][0] == '-' && strlen(argv[i]) == 2)) {
      if (error) {
        printf("%c  %c  ", type, 'E');
        break;
      } else {
        printf("%c  ", type);
        switch (type) {
          case 'S':
            printf("%d  ", p->size());
            break;
          case 'N':
            printf("%d  ", int(*p));
            break;
          case 'G':
            printf("%d  ", g_value);
            break;
          case 'C': {
            STACK* ap = new STACK(*p);
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
          p = new STACK(num);
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
          STACK* cp = new STACK(num);
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
  printf("\n");
}
