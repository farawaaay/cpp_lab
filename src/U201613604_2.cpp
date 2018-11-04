#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

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
    void fprint(FILE *t) const;    //为文件中写入内容
    ~STACK();                      //销毁栈 (析构函数)
};

bool jdg = 1;

STACK::STACK(int m) : elems(0), max(10) //拷贝构造函数常亮必须要进行初始化
{
    if (!m)
    {
        const_cast<int *&>(elems) = new int[m];
        const_cast<int &>(max) = m;
    }
    else
    {
        const_cast<int *&>(elems) = 0;
        const_cast<int &>(max) = 0;
    }
    pos = 0;
}

STACK::~STACK()
{
    free(elems);
    pos = 0;
    const_cast<int &>(max) = 0;
}

STACK::STACK(const STACK &s) : elems(0), max(10)
{
    const_cast<int *&>(elems) = new int[s.max];
    memcpy(elems, s.elems, (s.pos) * sizeof(int));
    pos = s.pos;
    const_cast<int &>(max) = s.max;
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
    if (pos > x)
        return elems[x];
    else
        return -1;
}

STACK &STACK::push(int e)
{
    if (pos == max)
    {
        jdg = 0;
        return *this;
    }
    else
    {
        jdg = 1;
        elems[pos] = e;
        ++pos;
        return *this;
    }
}

STACK &STACK::pop(int &e)
{
    if (pos != 0)
    {
        e = elems[pos - 1];
        --pos;
        jdg = 1;
        return *this;
    }
    else
    {
        jdg = 0;
        return *this;
    }
}

STACK &STACK::assign(const STACK &s)
{
    if (max == s.max)
    {
        memcpy(elems, s.elems, s.max * sizeof(int));
        pos = s.pos;
        const_cast<int &>(max) = s.max;
    }
    else
    {
        free(elems);
        const_cast<int *&>(elems) = (int *)malloc((s.max) * sizeof(int));
        memcpy(elems, s.elems, (s.pos) * sizeof(int));
        pos = s.pos;
        const_cast<int &>(max) = s.max;
    }
    return *this;
}

void STACK::print() const
{
    if (elems != 0)
    {
        for (int i = 0; i < pos; ++i)
        {
            cout << elems[i] << ' ' << endl;
        }
    }
}

void STACK::fprint(FILE *t) const
{
    if (elems != 0)
    {
        for (int i = 0; i < pos; ++i)
        {
            fprintf(t, "%d  ", elems[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    STACK *p = 0;
    STACK *s = 0;

    FILE *fp = fopen("C:\\Users\\45482\\zyh\\C++\\U201613604_1.txt", "w");
    char num[] = "U201613604_2";
    fprintf(fp, "%s  ", num);
    cout << "U201613604_2  ";

    int i, j, temp, lenth;
    for (i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-S") == 0)
        {
            lenth = atoi(argv[i + 1]);
            p = new STACK(temp);
            fprintf(fp, "S  %d  ", lenth);
            cout << "S  " << lenth << "  ";
        }

        else if (strcmp(argv[i], "-I") == 0)
        {
            for (j = 0; i + j + 1 < argc;)
            {
                if (strcmp(argv[i + j + 1], "-S") != 0 && strcmp(argv[i + j + 1], "-I") != 0 && strcmp(argv[i + j + 1], "-O") != 0 && strcmp(argv[i + j + 1], "-C") != 0 && strcmp(argv[i + j + 1], "-A") != 0 && strcmp(argv[i + j + 1], "-N") != 0)
                    ++j;
                else
                    break;
            }
            char _i = 'I';
            char _e = 'E';
            fprintf(fp, "%c  ", _i);
            cout << "I  ";
            for (; j > 0; --j)
            {
                temp = atoi(argv[i + j + 1]);
                p->push(temp);
                if (jdg == 0)
                {
                    fprintf(fp, "%c", _e);
                    cout << 'E';
                    delete p;
                    delete s;
                    return 0;
                }
            }
            if (p->howMany() != 0)
            {
                p->print();
                p->fprint(fp);
            }
            else
                break;
        }

        else if (strcmp(argv[i], "-O") == 0)
        {
            int e;
            temp = atoi(argv[i + 1]);
            char _o = 'O';
            char _e = 'E';
            fprintf(fp, "%c  ", _o);
            cout << "O  ";
            for (i = 0; i < temp; ++i)
            {
                p->pop(e);
                if (jdg == 0)
                {
                    cout << 'E';
                    fprintf(fp, "%c", _e);
                    delete p;
                    delete s;
                    return 0;
                }
            }
            if (p->howMany() != 0)
            {
                p->print();
                p->fprint(fp);
            }
            else
                break;
        }

        else if (strcmp(argv[i], "-N") == 0)
        {
            char _n = 'N';
            temp = p->howMany();
            fprintf(fp, "%c  %d  ", _n, temp);
            printf("%c  %d  ", _n, temp);
        }

        else if (strcmp(argv[i], "-G") == 0)
        {
            char _g = 'G';
            char _e = 'E';
            temp = atoi(argv[i + 1]);
            int _temp;
            fprintf(fp, "%c  ", _g);
            cout << "G  ";
            if ((_temp = p->getelem(temp)) == -1)
            {
                cout << 'E';
                fprintf(fp, "%c", _e);
                delete p;
                delete s;
                return 0;
            }
            fprintf(fp, "%d  ", _temp);
            cout << _temp << "  ";
        }

        else if (strcmp(argv[i], "-C") == 0)
        {
            char _c = 'C';
            fprintf(fp, "%c  ", _c);
            cout << "C  ";
            s = new STACK(*p);
            delete p;
            p = s;
            s = 0;
            p->print();
            p->fprint(fp);
        }

        else if (strcmp(argv[i], "-A") == 0)
        {
            char _a = 'A';
            char _e = 'E';
            fprintf(fp, "%c  ", _a);
            cout << "A  ";
            temp = atoi(argv[i + 1]);
            s = new STACK(temp);
            s->assign(*p);
            if (s->size() != p->size() || s->howMany() != p->howMany())
            {
                cout << 'E';
                fprintf(fp, "%c", _e);
                delete p;
                delete s;
                return 0;
            }
            delete p;
            p = s;
            s = 0;
            p->print();
            p->fprint(fp);
        }
    }
    if (fclose(fp) != 0)
        printf("Error in closing file %s\n", argv[1]);
    delete p;
    delete s;
    return 0;
}
