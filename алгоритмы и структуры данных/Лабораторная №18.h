#pragma once
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
using namespace std;
//собственные классы исключений
struct MyError
{
    virtual void what()=0;
};
struct InvalidIndexError: public MyError
{
    string m_msg;
    InvalidIndexError() {m_msg="Exception: invalid list index";}
    void what() {cout << m_msg << endl;}
};
struct NoMatchSizes: public MyError
{
    string m_msg;
    NoMatchSizes() {m_msg="Exception: sizes of lists are different";}
    void what() {cout << m_msg << endl;}
};
//шаблонный класс-контейнер-список и его методы
template <typename T>
struct ClassList
{
    ClassList(int s,T el)
    {
        if (s<=0) throw 1;
        for (int i=0;i<s;i++) m_list.push_back(el);
    }
    ~ClassList(){}
    list <T> m_list;
    T operator[](int i);
    int operator()();
    ClassList<T> operator*(ClassList<T> add_list);
    void Show();
    void Change(int index, T el)
    {
        auto it=m_list.begin();
        advance(it,index);
        *it=el;
    }
};
template <typename T>
T ClassList<T>::operator[](int i)
{
    if (i<0 || i>=this->m_list.size()) {throw InvalidIndexError();}
    auto it=this->m_list.begin();
    advance(it,i);
    return *it;
}
template <typename T>
void ClassList<T>::Show()
{
    for (auto it=this->m_list.begin();it!=this->m_list.end();it++) cout << *it << " ";
    cout << endl;
}
template <typename T>
ClassList<T> ClassList<T>::operator*(ClassList<T> add_list)
{
    if (this->m_list.size()!=add_list.m_list.size()) throw NoMatchSizes();
    ClassList<T> new_list(this->m_list.size(),add_list[0]);
    auto it1=this->m_list.begin();
    auto it2=add_list.m_list.begin();
    auto it3=new_list.m_list.begin();
    while (it1!=this->m_list.end())
    {
        *it3=(*it2)*(*it1);
        it1++;it2++;it3++;
    }
    *it3=(*it2)*(*it1);
    return new_list;
}
template <typename T>
int ClassList<T>::operator()() {return this->m_list.size();}
//класс геометрической прогрессии
class Progress
{
    public:
        int a;
        int r;
        int element(int j);
        Progress(int A,int R)
        {
            a=A;
            r=R;
        }
};
//зарплата
class Salary
{
    public:
        string name;
        int salary;
        int prem;
        Salary()
        {
            name="";
            salary=0;
            prem=0;
        }
        Salary(string n,int s,int p)
        {
            name=n;
            salary=s;
            prem=p;
        }
        Salary(const Salary &e)
        {
            name=e.name;
            salary=e.salary;
            prem=e.prem;
        }
        ~Salary(){}
        void Show();
        void Set(string n,int s,int p);
};
//пара чисел
class Pair
{
public:
    int x;
    double y;
    Pair()
    {
        x=0;
        y=0.0;
    }
    Pair(int X,double Y)
    {
        x=X;
        y=Y;
    }
    Pair operator-(Pair P1);
    void operator+=(int z);
    void operator+=(double z);
    friend bool operator<(const Pair &P1, const Pair &P2); //внимание
};
inline bool operator<(const Pair &P1, const Pair &P2) {return P1.y<P2.y;} //внимание
//иерархия классов объект-человек-студент
class Object
{
public:
    virtual void Show()=0;
};
class Person: public Object
{
public:
    string name;
    int age;
    Person(string Name,int Age)
    {
        name=Name;
        age=Age;
    }
    void NewName(string Name);
    void NewAge(int Age);
    void Show();
private:
    void f(int a){};
};
class Student: public Person
{
public:
    string subject;
    int num;
    Student(string Name,int Age,string Subject,int Num):Person(Name,Age)
    {
        subject=Subject;
        num=Num;
    }
    void NewSubject(string Subject);
    void NewNum(int Num);
    void Result();
    void Show();
};
//иерархия издание-журнал, обработка событий
class Object8
{
public:
    string name;
    virtual void Show()=0;
    virtual void Read()=0;
};
class Print: public Object8
{
public:
    string author;
    Print(){}
    Print(string Name,string Author)
    {
        name=Name;
        author=Author;
    }
    void Show();
    void Read();
};
class Magazin: public Print
{
public:
    int sheet;
    Magazin(){}
    Magazin(string Name,string Author,int Sheet):Print(Name,Author)
    {
        sheet=Sheet;
    }
    void Show();
    void Read();
};
struct Vector8
{
    vector <Object8*> data;
    int m_size;
    int cur;
    void Add();
    void Dell();
    void Show();
    void ShowName();
    int operator()();
    Vector8() {m_size=0;}
};
struct TEvent
{
    int what;
    union
    {
        int command;
        struct
        {
            int message;
            int a;
        };
    };
};
struct Dialog: Vector8
{
    int EndState;
    int Valid();
    void EndExec();
    int Execute();
    void GetEvent(TEvent& event);
    void HandleEvent(TEvent& event);
    void ClearEvent(TEvent& event);
    Dialog(){EndState=0;}
};
//класс контейнер список с итераторами
struct CLI // Class List Iterator
{
    int * data;
    int siz;
    int* first;
    int* last;
    CLI(int s,int el)
    {
        data=new int[s];
        for (int i=0;i<s;i++) data[i]=el+i;
        siz=s;
        first=&data[0];
        last=&data[s-1];
    }
    ~CLI(){delete data;}
    int operator[](int i) {return data[i];}
    int operator()(){return siz;}
    CLI operator*(CLI add_list);
    void Show();
};
struct Iterator
{
    Iterator(int* Elem){elem=Elem;}
    bool operator==(const Iterator&it){return elem==it.elem;}
    bool operator!=(const Iterator&it){return elem!=it.elem;}
    void operator++(int){elem++;}
    void operator--(int){elem--;}
    int& operator *() const{ return*elem;}
    int *elem;
};
