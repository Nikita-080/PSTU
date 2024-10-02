#include <iostream>
#include <fstream>
#include "lab18.h"
#include <string>
#include <windows.h>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;
void Proc1()
{
    cout << "system information - task 1\n\n";
    int a,r,j=-1;
    cout << "Введите первый член прогрессии\n";
    cin >> a;
    cout << "Введите частное прогрессии\n";
    cin >> r;
    Progress e(a,r);
    while (j<0)
    {
        cout << "Введите индекс искомого члена прогрессии\n";
        cin >> j;
    }
    cout << e.element(j) << endl;
}
void Proc2()
{
    cout << "system information - task 2\n\n";
    Salary a;
    Salary b("Рябов Никита Андреевич",100000,10);
    Salary c(b);
    Salary d;
    d.Set("Иванов Иван Иванович",30000,10);
    a.Show();
    b.Show();
    c.Show();
    d.Show();
}
ostream& operator << (ostream& out,Pair P1)
{
    return (out<<P1.x<<":"<<P1.y<<endl);
}
istream& operator >> (istream& in,Pair &P1)
{
    cout << "введите целое число\n";
    in >> P1.x;
    cout << "введите дробное число\n";
    in >> P1.y;
    return in;
}
fstream& operator >> (fstream& fin, Pair &P1)
{
    fin>>P1.x;
    fin>>P1.y;
    return fin;
}
fstream& operator<<(fstream& fout, Pair P1)
{
    fout<<P1.x<<"\n"<<P1.y<<"\n";
    return fout;
}
ostream& operator << (ostream& out,Person P1)
{
    return (out<<P1.name<<":"<<P1.age<<endl);
}
ostream& operator << (ostream& out,Student P1)
{
    return (out<<P1.name<<":"<<P1.age<<":"<<P1.subject<<":"<<P1.num<<endl);
}
ostream& operator << (ostream& out,Object* P1)
{
    P1->Show();
    return out;
}
void Ad1810()
{
    fstream stream("TestFile.txt",ios::in);
    fstream help("TestFile2.txt",ios::out);
    int K,L,c=0;
    Pair p;
    cout << "введите позицию нового элемента\n";
    cin >> K;
    cout << "введите количество новых элементов\n";
    cin >> L;
    while (c!=K)
    {
        stream>>p;
        help<<p;
        c++;
    }
    for (int i=0;i<L;i++)
    {
        cin>>p;
        help<<p;
    }
    while (stream>>p) help<<p;
    stream.close();
    help.close();
    remove("TestFile.txt");
    rename("TestFile2.txt","TestFile.txt");
}
void Del1810()
{
    fstream stream("TestFile.txt",ios::in);
    fstream help("TestFile2.txt",ios::out);
    int K,c=0;
    Pair p;
    cout << "введите позицию удаляемого элемента\n";
    cin >> K;
    while (stream>>p)
    {
        if (c!=K) help<<p;
        c++;
    }
    stream.close();
    help.close();
    remove("TestFile.txt");
    rename("TestFile2.txt","TestFile.txt");
}
void Show1810()
{
    fstream stream("TestFile.txt",ios::in);
    Pair p;
    while(!stream.eof())
    {
        stream>>p;
        cout<<p;
    }
    stream.close();
}
void F1_1810()
{
    fstream stream("TestFile.txt",ios::in);
    fstream help("TestFile2.txt",ios::out);
    int K,c=0;
    Pair p;
    cout << "введите целое число\n";
    cin >> K;
    while (stream>>p)
    {
        if (p.x>=K) help<<p;
        c++;
    }
    stream.close();
    help.close();
    remove("TestFile.txt");
    rename("TestFile2.txt","TestFile.txt");
}
void F2_1810()
{
    fstream stream("TestFile.txt",ios::in);
    fstream help("TestFile2.txt",ios::out);
    int K,L,c=0;
    Pair p;
    cout << "введите значение искомых элементов\n";
    cin >> K;
    cout << "введите надбавку\n";
    cin >> L;
    while (stream>>p)
    {
        if (p.x==K)
        {
            p+=L;
            help<<p;
        }
        c++;
    }
    stream.close();
    help.close();
    remove("TestFile.txt");
    rename("TestFile2.txt","TestFile.txt");
}
void Proc3()
{
    cout << "system information - task 3\n\n";
    Pair P1(3,5.6);
    Pair P2(6,1.3);
    Pair P3=P2-P1;
    cout << "P1 "<<P1;
    cout << "P2 "<<P2;
    cout << "P3=P2-P1 "<<P3;
    P1+=4;
    P2+=2.2;
    cout << "P1+=4 "<<P1;
    cout << "P2+=2.2 "<<P2;
}
void Proc4()
{
    cout << "system information - task 4\n\n";
    Student S1("Никита",19,"Физика",5);
    Student S2("Борис",18,"Математика",2);
    cout<<"S1 "<<S1;
    cout<<"S2 "<<S2;
    S1.NewName("Виктор");
    S1.NewSubject("Химия");
    S2.NewAge(20);
    S2.NewNum(1);
    cout<<"==========\n";
    cout<<"S1 "<<S1;
    S1.Result();
    cout<<"S2 "<<S2;
    S2.Result();
}
void Proc5()
{
    cout << "system information - task 5\n\n";
    vector <Object*> Vector;
    Student S1("Никита",19,"Физика",5);
    Person P1("Борис",18);
    Vector.push_back(&S1);
    Vector.push_back(&P1);
    cout << "Student " << S1;
    cout << "Person " << P1;
    cout << "Vector: \n";
    cout << Vector[0];
    cout << Vector[1];
}
void Proc6()
{
    cout << "system information - task 6\n\n";
    CLI a(4,5);
    Iterator i(a.first);
    cout << "i   " <<*i<<endl;
    i++;
    cout << "i++ " <<*i<<endl;
    cout << "All data\n";
    i--;
    while (i.elem!=a.last)
    {
        cout<<*i<<endl;
        i++;
    }
    cout<<*i<<endl;
}
void Proc7()
{
    cout << "system information - task 7\n\n";
    ClassList<int> LIST(5,4);
    ClassList<int> LIST2(5,3);
    cout << "Size: " <<LIST() << endl;
    cout << "LIST[2]="<<LIST[2] << endl;
    cout << "LIST2[3]="<<LIST2[3] << endl;
    cout << "LIST, LIST2, LIST3\n";
    ClassList<int> LIST3(LIST*LIST2);
    LIST.Show();
    LIST2.Show();
    LIST3.Show();
}
void Proc8()
{
    cout << "system information - task 8\n\n";
    Vector8 V;
    Dialog D;
    D.Execute();
}
void Proc9()
{
    cout << "system information - task 9\n\n";
    int s,el,ind,s2,el2;
    try
    {
        cout << "Введите длину списка 1\n";
        cin >> s;
        cout << "Введите элемент, которым будет заполнен список 1\n";
        cin >> el;
        cout << "Введите длину списка 2\n";
        cin >> s2;
        cout << "Введите элемент, которым будет заполнен список 2\n";
        cin >> el2;
        ClassList<int> LIST(s,el);
        ClassList<int> LIST2(s2,el2);
        LIST.Show();
        LIST2.Show();
        cout << "Введите номер элемента\n";
        cin >> ind;
        cout << "LIST[" << ind << "]=" << LIST[ind] << endl;
        cout << "LIST2[" << ind << "]=" << LIST2[ind] << endl;
        ClassList<int> LIST3(LIST*LIST2);
        cout << "LIST3=LIST1*LIST2\n";
        LIST3.Show();
    }
    catch(int) {cout << "Exception: error with int\ninvalid list size\n";}
    catch(MyError &e) {e.what();}
    catch(...) {cout << "Unknow exception...\n";}
}
void Proc10()
{
    cout << "system information - task 10\n\n";
    while (true)
    {
        int comand;
        cout << "Меню\n";
        cout << "1. добавить элемент\n";
        cout << "2. удалить элемент\n";
        cout << "3. показать\n";
        cout << "4. удалить все записи меньшие заданного значения\n";
        cout << "5. увеличить все записи с заданным значением на число L\n";
        cout << "7. выход\n";
        cin >> comand;
        if (comand==7) break;
        switch (comand)
        {
        case 1:
            Ad1810();
            break;
        case 2:
            Del1810();
            break;
        case 3:
            Show1810();
            break;
        case 4:
            F1_1810();
            break;
        case 5:
            F2_1810();
            break;
        default:
            cout << "неизвестная команда\n";
        }
    }
}
stack <Pair> A02;  //вспомогательный контейнер
stack <double> A0; //вспомогательный контейнер
list <double> A1={4.6,7.8,3.2,9.9,4,4};
list <Pair> A2;
ClassList<double> A3(5,4);
priority_queue <double> A4;
void PrintATD(string s)
{
    cout << s+"\n";
    cout << "список (double)\n";
    for (auto iter=A1.begin();iter!=A1.end();iter++) cout << *iter << endl;
    cout << "список (Pair)\n";
    for (auto iter=A2.begin();iter!=A2.end();iter++) cout << *iter;
    cout << "класс-список\n";
    A3.Show();
    cout << "очередь\n";
    while (!A4.empty())
    {
        cout << A4.top() << endl;
        A0.push(A4.top());
        A4.pop();
    }
    while (!A0.empty())
    {
        A4.push(A0.top());
        A0.pop();
    }
}
void Proc11()
{
    cout << "system information - task 11\n\n";
    A4.push(3.3); A4.push(4.2); A4.push(0.1); A4.push(3.5); A4.push(5.7);
    for (int i=0;i<5;i++)
    {
        Pair P1;
        cin>>P1;
        A2.push_back(P1);
    }
    PrintATD("Исходные данные");
    double sum=0;
    for (auto iter=A1.begin();iter!=A1.end();iter++) sum+=*iter;
    A1.push_back(sum/5);
    sum=0;
    for (auto iter=A2.begin();iter!=A2.end();iter++) sum+=(*iter).y;
    Pair P1(0,sum/5);
    A2.push_back(P1);
    sum=0;
    for (int i=0;i<5;i++) sum+=A3[i];
    A3.m_list.push_back(sum/5);
    sum=0;
    for (int i=0;i<5;i++)
    {
        sum+=A4.top();
        A0.push(A4.top());
        A4.pop();
    }
    for (int i=0;i<5;i++)
    {
        A4.push(A0.top());
        A0.pop();
    }
    A4.push(sum/5);
    PrintATD("задача 1. добавить в конец среднее арифметическое");
    double x1;
    double x2;
    cout << "Укажите начало диапозона\n";
    cin >> x1;
    cout << "Укажите конец диапозона\n";
    cin >> x2;
    for (auto iter=A1.begin();iter!=A1.end();iter++) if (*iter>x1 && *iter<x2) A0.push(*iter);
    A1.clear();
    while (!A0.empty())
    {
        A1.push_back(A0.top());
        A0.pop();
    }
    for (auto iter=A2.begin();iter!=A2.end();iter++) if ((*iter).y>x1 && (*iter).y<x2) A02.push(*iter);
    A2.clear();
    while (!A02.empty())
    {
        A2.push_back(A02.top());
        A02.pop();
    }
    for (int i=0;i<6;i++) if (A3[i]>x1 && A3[i]<x2) A0.push(A3[i]);
    A3.m_list.clear();
    while (!A0.empty())
    {
        A3.m_list.push_back(A0.top());
        A0.pop();
    }
    for (int i=0;i<6;i++)
    {
        if (A4.top()>x1 && A4.top()<x2) A0.push(A4.top());
        A4.pop();
    }
    while (!A0.empty())
    {
        A4.push(A0.top());
        A0.pop();
    }
    PrintATD("задача 2. удалить элементы из диапозона");
    double up,down;
    if (!A1.empty())
    {
        up=*(A1.begin());down=*(A1.begin());
        for (auto iter=A1.begin();iter!=A1.end();iter++)
        {
            up=*iter>up ? *iter: up;
            down=*iter<down ? *iter: down;
        }
        for (auto iter=A1.begin();iter!=A1.end();iter++) *iter+=up+down;
    }
    if (!A2.empty())
    {
        up=(*(A2.begin())).y;down=(*(A2.begin())).y;
        for (auto iter=A2.begin();iter!=A2.end();iter++)
        {
            up=(*iter).y>up ? (*iter).y: up;
            down=(*iter).y<down ? (*iter).y: down;
        }
        for (auto iter=A2.begin();iter!=A2.end();iter++) (*iter).y+=up+down;
    }
    if (!A3.m_list.empty())
    {
        up=A3[0];down=A3[0];
        for (int i=0;i<5;i++)
        {
            up=A3[i]>up ? A3[i]: up;
            down=A3[i]<down ? A3[i]: down;
        }
        for (auto iter=A3.m_list.begin();iter!=A3.m_list.end();iter++) *iter+=up+down;
    }
    if (!A4.empty())
    {
        up=A4.top();down=A4.top();
        for (int i=0;i<5;i++)
        {
            up=A4.top()>up ? A4.top(): up;
            down=A4.top()<down ? A4.top(): down;
            A0.push(A4.top());
            A4.pop();
        }
        for (int i=0;i<5;i++)
        {
            A4.push(A0.top()+up+down);
            A0.pop();
        }
    }
    PrintATD("задача 3. добавить сумму минимума и максимума");
}
//stack <Pair> A02;  //вспомогательный контейнер
//stack <double> A0; //вспомогательный контейнер
multiset <double> A5={5.5,6.2,1.8,3.7,2.9};
multiset <Pair> A6;
ClassList<double> A7(5,4);
void PrintATD12(string s)
{
    cout << s+"\n";
    cout << "мультимножество (double)\n";
    for (auto iter=A5.begin();iter!=A5.end();iter++) cout << *iter << endl;
    cout << "мультимножество (Pair)\n";
    for (auto iter=A6.begin();iter!=A6.end();iter++) cout << *iter;
    cout << "класс-список\n";
    A7.Show();
}
void Proc12()
{
    cout << "system information - task 12\n\n";
    for (int i=0;i<5;i++)
    {
        Pair P1;
        cin>>P1;
        A6.insert(P1);
    }

    PrintATD12("Исходные данные");
    double sum=0;
    for (auto iter=A5.begin();iter!=A5.end();iter++) sum+=*iter;
    A5.insert(sum/5);
    sum=0;
    for (auto iter=A6.begin();iter!=A6.end();iter++) sum+=(*iter).y;
    Pair P1(0,sum/5);
    A6.insert(P1);
    sum=0;
    for (int i=0;i<5;i++) sum+=A7[i];
    A7.m_list.push_back(sum/5);
    PrintATD12("задача 1. добавить в конец среднее арифметическое");
    double x1;
    double x2;
    cout << "Укажите начало диапозона\n";
    cin >> x1;
    cout << "Укажите конец диапозона\n";
    cin >> x2;
    for (auto iter=A5.begin();iter!=A5.end();iter++) if (*iter>x1 && *iter<x2) A0.push(*iter);
    A5.clear();
    while (!A0.empty())
    {
        A5.insert(A0.top());
        A0.pop();
    }
    for (auto iter=A6.begin();iter!=A6.end();iter++) if ((*iter).y>x1 && (*iter).y<x2) A02.push(*iter);
    A6.clear();
    while (!A02.empty())
    {
        A6.insert(A02.top());
        A02.pop();
    }
    for (int i=0;i<6;i++) if (A7[i]>x1 && A7[i]<x2) A0.push(A7[i]);
    A7.m_list.clear();
    while (!A0.empty())
    {
        A7.m_list.push_back(A0.top());
        A0.pop();
    }
    PrintATD12("задача 2. удалить элементы из диапозона");
    double up,down;
    if (A5.size()>0)
    {
        up=*(A5.begin());down=*(A5.begin());
        for (auto iter=A5.begin();iter!=A5.end();iter++)
        {
            up=*iter>up ? *iter: up;
            down=*iter<down ? *iter: down;
        }
        for (auto iter=A5.begin();iter!=A5.end();iter++) A0.push(up+down);
        A5.clear();
        while (!A0.empty())
        {
            A5.insert(A0.top());
            A0.pop();
        }
    }
    if (A6.size()>0)
    {
        up=(*(A6.begin())).y;down=(*(A6.begin())).y;
        for (auto iter=A6.begin();iter!=A6.end();iter++)
        {
            up=(*iter).y>up ? (*iter).y: up;
            down=(*iter).y<down ? (*iter).y: down;
        }
        for (auto iter=A6.begin();iter!=A6.end();iter++)
        {
            Pair P1;
            P1.x=(*iter).x;
            P1.y=(*iter).y+up+down;
            A02.push(P1);
        }
        A6.clear();
        while (!A02.empty())
        {
            A6.insert(A02.top());
            A02.pop();
        }
    }
    if (!A7.m_list.empty())
    {
        up=A7[0];down=A7[0];
        for (int i=0;i<5;i++)
        {
            up=A7[i]>up ? A7[i]: up;
            down=A7[i]<down ? A7[i]: down;
        }
        for (auto iter=A7.m_list.begin();iter!=A7.m_list.end();iter++) *iter+=up+down;
    }
    PrintATD12("задача 3. добавить сумму минимума и максимума");

}
list <Pair> A9;
map <string,double> A10={{"Mercury",0},{"Venus",0},{"Earth",1},{"Mars",2}};
double up,down;
Pair upP,downP;
void PrintATD13(string s)
{
    cout << s+"\n";
    cout << "список (Pair)\n";
    for (auto iter=A9.begin();iter!=A9.end();iter++) cout << *iter;
    cout << "словарь (string,double)\n";
    for (auto iter=A10.begin();iter!=A10.end();iter++) if (iter->second!=-1) cout<<iter->first<<":"<<iter->second<<endl;;
}
void AddMinMax(Pair &i) {i.y+=upP.y+downP.y;}
void Proc13()
{
    cout << "system information - task 13\n\n";
    for (int i=0;i<5;i++)
    {
        Pair P1;
        cin>>P1;
        A9.push_back(P1);
    }
    PrintATD13("Исходные данные");
    double sum=0;
    for (auto iter=A9.begin();iter!=A9.end();iter++) sum+=(*iter).y;
    Pair P1(0,sum/5);
    A9.push_back(P1);
    sum=0;
    for (auto iter=A10.begin();iter!=A10.end();iter++) sum+=iter->second;
    A10["EmptyPlanet"]=sum/A10.size();
    PrintATD13("задача 1. добавить в конец среднее арифметическое");
    double x1;
    double x2;
    cout << "Укажите начало диапозона\n";
    cin >> x1;
    cout << "Укажите конец диапозона\n";
    cin >> x2;
    for (auto iter=A9.begin();iter!=A9.end();iter++) if ((*iter).y<x1 || (*iter).y>x2) A02.push(*iter);
    A9.clear();
    while (!A02.empty())
    {
        A9.push_back(A02.top());
        A02.pop();
    }
    for (auto iter=A10.begin();iter!=A10.end();iter++) if (iter->second>x1 && iter->second<x2) iter->second=-1;
    PrintATD13("задача 2. удалить элементы из диапозона");
    upP=*max_element(A9.begin(),A9.end());
    downP=*min_element(A9.begin(),A9.end());
    for_each(A9.begin(),A9.end(),AddMinMax);
    up=A10.begin()->second;
    down=A10.begin()->second;
    for (auto iter=A10.begin();iter!=A10.end();iter++) if (iter->second>up) up=iter->second;
    for (auto iter=A10.begin();iter!=A10.end();iter++) if (iter->second<down && iter->second!=-1) down=iter->second;
    for (auto iter=A10.begin();iter!=A10.end();iter++) if (iter->second!=-1) iter->second+=up+down;
    PrintATD13("задача 3. добавить сумму минимума и максимума");
}
int main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int num=0;
	while (true)
    {
        cout << "\nВведите номер подзадачи\n\n";
        cout << "1. геометрическая прогрессия\n";
        cout << "2. база данных работников\n";
        cout << "3. пары чисел\n";
        cout << "4. человек->студент\n";
        cout << "5. вектор людей\n";
        cout << "6. класс-итератор\n";
        cout << "7. класс контейнер список\n";
        cout << "8. обработка событий\n";
        cout << "9. обработка исключений\n";
        cout << "10. файловые потоки\n";
        cout << "11. последовательные контейнеры\n";
        cout << "12. ассоциативные контейнеры\n";
        cout << "13. алгоритмы STL\n\n";
        cin >> num;
        switch (num)
        {
        case 1:
            Proc1();
            break;
        case 2:
            Proc2();
            break;
        case 3:
            Proc3();
            break;
        case 4:
            Proc4();
            break;
        case 5:
            Proc5();
            break;
        case 6:
            Proc6();
            break;
        case 7:
            Proc7();
            break;
        case 8:
            Proc8();
            break;
        case 9:
            Proc9();
            break;
        case 10:
            Proc10();
            break;
        case 11:
            Proc11();
            break;
        case 12:
            Proc12();
            break;
        case 13:
            Proc13();
            break;
        default:
            cout << "неизвестная подзадача\n";
        }
    }
}
