#include <iostream>
#include <stdlib.h>
#include <cstring>

bool error = false;

class STACK
{
    int *const elems; //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;          //栈实际已有元素个数，栈空时pos=0;
  public:
    STACK(int m);                  //初始化栈：最多m个元素
    STACK(const STACK &s);         //用栈s拷贝初始化栈
    int size() const;              //返回栈的最大元素个数max
    int howMany() const;           //返回栈的实际元素个数pos
    int getelem(int x) const;      //取下标x处的栈元素
    STACK &push(int e);            //将e入栈,并返回栈
    STACK &pop(int &e);            //出栈到e,并返回栈
    STACK &assign(const STACK &s); //赋s给栈,并返回被赋值的栈
    void print() const;            //打印栈
    ~STACK();                      //销毁栈
};

STACK::STACK(int m) : elems(new int(m)), max(m)
{
    pos = 0;
}
STACK::STACK(const STACK &s) : elems(new int[s.max]), max(s.max)
{
    memcpy(this->elems, s.elems, (s.pos) * sizeof(int));
    this->pos = s.pos;
}

int STACK::size() const
{
    return max;
}

int STACK::howMany() const
{
    return pos;
}

int STACK::getelem(int x) const
{
    if (x > this->pos - 1)
    {
        error = 1;
    }
    return this->elems[x];
}

STACK &STACK::push(int e)
{
    if (this->pos == this->max)
        error = 1;
    else
        elems[this->pos++] = e;
    return *this;
}

STACK &STACK::pop(int &e)
{
    if (this->pos > 0)
        e = this->elems[--this->pos];
    else
        error = 1;
    return *this;
}

STACK &STACK::assign(const STACK &s)
{
    free(this->elems);
    const_cast<int *&>(this->elems) = (int *)malloc((s.max) * sizeof(int));
    memcpy(this->elems, s.elems, (s.pos) * sizeof(int));
    this->pos = s.pos;
    const_cast<int &>(this->max) = s.max;

    return *this;
}

void STACK::print() const
{
    for (int i = 0; i < this->pos; i++)
        printf("%d  ", this->elems[i]);
    return;
}

STACK::~STACK()
{
    free(this->elems);
    this->pos = 0;
    const_cast<int &>(this->max) = 0;
}

int main(int argc, char *argv[])
{
    STACK *p;
    char *filename = argv[1];
    char type = 'S';
    int g_value;

    for (int i = 2; i < argc + 1; i++)
    {
        if (i == argc || (i != 2 && argv[i][0] == '-' && strlen(argv[i]) == 2))
        {
            if (error)
            {
                printf("%c  %c  ", type, 'E');
                break;
            }
            else
            {
                printf("%c  ", type);
                switch (type)
                {
                case 'S':
                    printf("%d  ", p->size());
                    break;
                case 'N':
                    printf("%d  ", p->howMany());
                    break;
                case 'G':
                    printf("%d  ", g_value);
                    break;
                default:
                    p->print();
                }
            }
            if (i != argc)
                type = argv[i][1];
        }
        else
        {
            switch (type)
            {
            case 'S':
                p = new STACK(atoi(argv[i]));
                break;
            case 'I':
                p->push(atoi(argv[i]));
                break;
            case 'O':
                for (int j = 0; j < atoi(argv[i]); j++)
                {
                    int _ = 0;
                    p->pop(_);
                }
                break;
            case 'A':
            {
                STACK *const ap = new STACK(*p);
                delete p;
                p = ap;
                break;
            }
            case 'C':
            {
                STACK *cp;
                cp->assign(*p);
                delete p;
                p = cp;
                break;
            }
            case 'G':
                g_value = p->getelem(atoi(argv[i]));
                break;
            }
        }
    }
    printf("\n");
}
