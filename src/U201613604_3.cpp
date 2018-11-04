#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

class STACK
{
    int *const elems; //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;          //栈实际已有元素个数，栈空时pos=0;
  public:
    STACK(int m);                             //初始化栈：最多m个元素
    STACK(const STACK &s);                    //用栈s拷贝初始化栈
    virtual int size() const;                 //返回栈的最大元素个数max
    virtual operator int() const;             //返回栈的实际元素个数pos
    virtual int operator[](int x) const;      //取下标x处的栈元素
    virtual STACK &operator<<(int e);         //将e入栈,并返回栈
    virtual STACK &operator>>(int &e);        //出栈到e,并返回栈
    virtual STACK &operator=(const STACK &s); //赋s给栈,并返回被赋值的栈
    virtual void print() const;               //打印栈
    virtual void fprint(FILE *p) const;       //向txt中打印栈
    virtual ~STACK();                         //销毁栈
};

bool jdg = 1;

STACK::STACK(int m) : elems(m > 0 ? (new int[m]) : 0), max(elems ? m : 0)
{
    pos = 0;
}

STACK::~STACK()
{
    delete[] elems;
    const_cast<int *&>(elems) = 0;
    pos = 0;
    const_cast<int &>(max) = 0;
}

STACK::STACK(const STACK &s) : elems(new int[s.max]), max(elems ? s.max : 0)
{
    memcpy(elems, s.elems, s.max * sizeof(int));
    pos = s.pos;
}

int STACK::size() const
{
    return max;
}

STACK::operator int() const
{
    return pos;
}

int STACK::operator[](int x) const
{
    if (pos > x)
    {
        //jdg = 1;
        return elems[x];
    }
    else
    {
        //jdg = 0;
        return -1;
    }
}

STACK &STACK::operator<<(int e)
{
    if (pos == max)
    {
        return *this;
    }
    else
    {
        elems[pos] = e;
        ++pos;
        return *this;
    }
}

STACK &STACK::operator>>(int &e)
{
    if (pos == 0)
    {
        return *this;
    }
    else
    {
        e = elems[pos - 1];
        --pos;
        return *this;
    }
}

void STACK::print() const
{
    int i = 0;
    if (pos != 0)
    {
        for (; i < pos; ++i)
        {
            cout << elems[i] << "  ";
        }
    }
}

void STACK::fprint(FILE *p) const
{
    int i = 0;
    if (pos != 0)
    {
        for (; i < pos; ++i)
        {
            fprintf(p, "%d  ", elems[i]);
        }
    }
}

STACK &STACK::operator=(const STACK &s)
{
    if (max == s.max)
    {
        memcpy(elems, s.elems, s.max * sizeof(int));
        pos = s.pos;
    }
    else
    {
        delete[] elems;
        const_cast<int *&>(elems) = new int(s.max);
        memcpy(elems, s.elems, s.max * sizeof(int));
        pos = s.pos;
        const_cast<int &>(max) = s.max;
    }
}

int main(int argc, char *argv[])
{
    STACK *p = 0;
    STACK *s = 0;

    // FILE *fp = fopen("C:\\Users\\45482\\zyh\\C++\\U201613604_3.txt", "w");
    char num[] = "U201613604_3";
    // fprintf(fp, "%s  ", num);
    cout << "U201613604_3  ";

    int temp, length, k;
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-S") == 0)
        {
            char _s = 'S';
            // fprintf(fp, "%c  ", _s);
            cout << "S  ";
            length = atoi(argv[++i]);
            p = new STACK(length);
            // fprintf(fp, "%d  ", length);
            cout << length << "  ";
        }

        else if (strcmp(argv[i], "-I") == 0)
        {
            char _i = 'I';
            char _e = 'E';
            // fprintf(fp, "%c  ", _i);
            cout << "I  ";
            for (k = 0; i + k + 1 < argc;)
            {
                if (strcmp(argv[i + k + 1], "-S") != 0 &&
                    strcmp(argv[i + k + 1], "-I") != 0 &&
                    strcmp(argv[i + k + 1], "-O") != 0 &&
                    strcmp(argv[i + k + 1], "-C") != 0 &&
                    strcmp(argv[i + k + 1], "-A") != 0 &&
                    strcmp(argv[i + k + 1], "-N") != 0)

                    ++k;
                else
                    break;
            }
            for (; k != 0; --k)
            {
                temp = atoi(argv[++i]);
                if (int(*p) < p->size())
                {
                    *p << (temp);
                }
                else
                {
                    // fprintf(fp, "%c", _e);
                    cout << 'E';
                    delete p;
                    delete s;
                    return 0;
                }
            }

            p->print();
            // p->fprint(fp);
        }

        else if (strcmp(argv[i], "-O") == 0)
        {
            int e;
            temp = atoi(argv[++i]);
            char _o = 'O';
            char _e = 'E';
            // fprintf(fp, "%c  ", _o);
            cout << "O  ";
            for (; temp != 0; --temp)
            {
                if (int(*p) != 0)
                {
                    *p >> (e);
                }
                else
                {
                    // fprintf(fp, "%c", _e);
                    cout << 'E';
                    delete p;
                    delete s;
                    return 0;
                }
            }
            p->print();
            // p->fprint(fp);
        }

        else if (strcmp(argv[i], "-N") == 0)
        {
            int hm;
            char _n = 'N';
            hm = int(*p);
            // fprintf(fp, "%c  %d  ", _n, hm);
            cout << "N  " << hm << "  ";
        }

        else if (strcmp(argv[i], "-G") == 0)
        {
            char _g = 'G';
            char _e = 'E';
            int temp_ = atoi(argv[++i]);
            int _temp;
            // fprintf(fp, "%c  ", _g);
            cout << "G  ";
            // p[temp_];
            if ((_temp = (*p)[temp_]) == -1)
            {
                // fprintf(fp, "%c", _e);
                cout << 'E';
                delete p;
                delete s;
                return 0;
            }
            // fprintf(fp, "%d  ", _temp);
            cout << _temp << "  ";
        }

        else if (strcmp(argv[i], "-C") == 0)
        {
            char _c = 'C';
            // fprintf(fp, "%c  ", _c);
            cout << "C  ";
            s = new STACK(*p);
            delete p;
            p = s;
            s = 0;
            p->print();
            // p->fprint(fp);
        }

        else if (strcmp(argv[i], "-A") == 0)
        {
            char _a = 'A';
            char _e = 'E';
            // fprintf(fp, "%c  ", _a);
            cout << "A  ";
            temp = atoi(argv[++i]);
            s = new STACK(temp);
            *s = (*p);
            if (int(*p) != int(*s) || p->size() != s->size())
            {
                // fprintf(fp, "%c", _e);
                cout << 'E';
                delete p;
                delete s;
                return 0;
            }
            delete p;
            p = s;
            s = 0;
            p->print();
            // p->fprint(fp);
        }
    }
    // if (fclose(fp) != 0)
    //     printf("Error in closing file %s\n", argv[1]);
    delete p;
    delete s;
    return 0;
}
