#include "lab18.h"
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
void Salary::Show()
    {
        cout << "ФИО " << name << endl;
        cout << "Зарплата " << salary << endl;
        cout << "Премиальный процент " << prem << endl;
    }
void Salary::Set(string n,int s,int p)
{
    name=n;
    salary=s;
    prem=p;
}
Pair Pair::operator-(Pair P1)
{
    Pair P3;
    P3.x=this->x-P1.x;
    P3.y=this->y-P1.y;
    return P3;
}
void Print::Read()
{
    cin.ignore();
    cout << "Введите название\n";
    getline(cin,name);
    cout << "Введите автора\n";
    getline(cin,author);
}
void Magazin::Read()
{
    cin.ignore();
    cout << "Введите название\n";
    getline(cin,name);
    cout << "Введите автора\n";
    getline(cin,author);
    cout << "Введите количество страниц\n";
    cin >> sheet;
}
void Vector8::Add()
{
    int a;
    cout << "Выберите тип добавляемого объекта\n";
    cout << "1. печатное издание\n";
    cout << "2. журнал\n";
    cin >> a;
    switch (a)
    {
    case 1:
        {
            Print* b=new Print;
            b->Read();
            data.push_back(b);
            m_size++;
            break;
        }
    case 2:
        {
            Magazin* b=new Magazin;
            b->Read();
            data.push_back(b);
            m_size++;
            break;
        }
    default:
        cout << "Ошибка: неизвестная команда\n";
    }
}
void Vector8::Dell()
{
    data.pop_back();
    m_size--;
}
void Dialog::GetEvent(TEvent& event)
{
    string commands="+-szq";
    char s;
    cout << "Введите операцию\n+ добавить элемент\n- удалить элемент\ns вывод\nz вывод названий\nq конец\n";
    cin >> s;
    if (commands.find(s)>=0)
    {
        event.what=100;
        event.command=commands.find(s)+1;
    }
    else event.what=0;
}
int Dialog::Execute()
{
    TEvent event;
    do
    {
        EndState=0;
        GetEvent(event);
        HandleEvent(event);
    }
    while(!EndState);
    return EndState;
}
void Dialog::HandleEvent(TEvent& event)
{
    if(event.what==100)
    {
        switch(event.command)
        {
        case 1:
            Add();
            ClearEvent(event);
            break;
        case 2:
            Dell();
            ClearEvent(event);
            break;
        case 3:
            Show();
            ClearEvent(event);
            break;
        case 4:
            ShowName();
            ClearEvent(event);
            break;
        case 5:
            EndState=1;
            ClearEvent(event);
            break;
        }
    }
}
CLI CLI::operator*(CLI add_list)
{
    CLI a(siz,0);
    for (int i=0;i<siz;i++) a.data[i]=add_list.data[i]*data[i];
    return a;
}
void CLI::Show() {for (int i=0;i<siz;i++) cout << i << ". " << data[i] << endl;}
void Dialog::ClearEvent(TEvent& event) {event.what=0;}
int Vector8::operator()() {return this->m_size;}
void Vector8::Show() {for (int i=0;i<m_size;i++) data[i]->Show();}
void Vector8::ShowName() {for (int i=0;i<m_size;i++) cout << data[i]->name << endl;}
int Progress::element(int j) {return a*pow(r,j-1);}
void Pair::operator+=(int z) {this->x+=z;}
void Pair::operator+=(double z) {this->y+=z;}
void Person::NewName(string Name) {name=Name;}
void Person::NewAge(int Age) {age=Age;}
void Student::NewSubject(string Subject) {subject=Subject;}
void Student::NewNum(int Num) {num=Num;}
void Student::Result() {cout<< ((num<3) ? "неудовлетворительная оценка\n":"удовлетворительная оценка\n");}
void Person::Show() {cout <<this->name<<":"<<this->age<<endl;}
void Student::Show() {cout <<this->name<<":"<<this->age<<":"<<this->subject<<":"<<this->num<<endl;}
void Print::Show() {cout <<this->name<<":"<<this->author<<endl;}
void Magazin::Show() {cout <<this->name<<":"<<this->author<<":"<<this->sheet<<endl;}
