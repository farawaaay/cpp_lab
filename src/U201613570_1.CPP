#include <stdlib.h>
#include <cstring>
#include <iostream>

struct STACK {
  int* elems;  //申请内存用于存放栈的元素
  int max;     //栈能存放的最大元素个数
  int pos;     //栈实际已有元素个数，栈空时pos=0;
};
void initSTACK(STACK* const p, int m);                //初始化p指向的栈：最多m个元素
void initSTACK(STACK* const p, const STACK& s);       //用栈s初始化p指向的栈
int size(const STACK* const p);                       //返回p指向的栈的最大元素个数max
int howMany(const STACK* const p);                    //返回p指向的栈的实际元素个数pos
int getelem(const STACK* const p, int x);             //取下标x处的栈元素
STACK* const push(STACK* const p, int e);             //将e入栈，并返回p
STACK* const pop(STACK* const p, int& e);             //出栈到e，并返回p
STACK* const assign(STACK* const p, const STACK& s);  //赋s给p指的栈,并返回p
void print(const STACK* const p);                     //打印p指向的栈
void destroySTACK(STACK* const p);                    //销毁p指向的栈

bool error = false;
FILE* f;

void initSTACK(STACK* const p, int m) {
  p->elems = (int*)malloc(m * sizeof(int));
  p->max = m;
  p->pos = 0;
}

void initSTACK(STACK* const p, const STACK& s) {
  assign(p, s);
}

int size(const STACK* const p) {
  return p->max;
}

int getelem(const STACK* const p, int x) {
  if (x > p->pos - 1) {
    error = 1;
  }
  return p->elems[x];
}

int howMany(const STACK* const p) {
  return p->pos;
}

STACK* const push(STACK* const p, int e) {
  if (p->pos == p->max)
    error = 1;
  else
    p->elems[p->pos++] = e;
  return p;
}

STACK* const pop(STACK* const p, int& e) {
  if (p->pos > 0)
    e = p->elems[--p->pos];
  else
    error = 1;

  return p;
}

STACK* const assign(STACK* const p, const STACK& s) {
  memcpy(p, &s, sizeof(STACK));
  int bl = sizeof(int) * s.max;
  int* newElems = (int*)malloc(bl);
  memcpy(newElems, s.elems, bl);
  p->elems = newElems;
  return p;
}

void print(const STACK* const p) {
  for (int i = 0; i < p->pos; i++)
    fprintf(f, "%d  ", p->elems[i]);
}

void destroySTACK(STACK* const p) {
  if (p->elems != 0) {
    free(p->elems);
  }
  p->elems = 0;  // 防止反复析构
  p->max = 0;
  p->pos = 0;
}

int main(int argc, char* argv[]) {
  STACK* p = (STACK*)malloc(sizeof(STACK));
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
            fprintf(f, "%d  ", p->max);
            break;
          case 'N':
            fprintf(f, "%d  ", p->pos);
            break;
          case 'G':
            fprintf(f, "%d  ", g_value);
            break;
          default:
            print(p);
        }
      }
      if (i != argc)
        type = argv[i][1];
    } else {
      switch (type) {
        case 'S':
          initSTACK(p, atoi(argv[i]));
          break;
        case 'I':
          push(p, atoi(argv[i]));
          break;
        case 'O':
          for (int j = 0; j < atoi(argv[i]); j++) {
            int _ = 0;
            pop(p, _);
          }
          break;
        case 'A': {
          STACK* const ap = (STACK* const)malloc(sizeof(STACK));
          initSTACK(ap, *p);
          p = ap;
          break;
        }
        case 'C': {
          STACK* const cp = (STACK* const)malloc(sizeof(STACK));
          initSTACK(cp, *p);
          p = cp;
          break;
        }
        case 'G':
          g_value = getelem(p, atoi(argv[i]));
          break;
      }
    }
  }
  fprintf(f, "\n");
}
