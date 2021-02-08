#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>
using namespace std;
struct Student
{
    string fio;
    string birthday;
    string adress;
    int rating;
};
void Data_print_console(Student* Data_base)
{
    cout << "������ ��������:\n";
    for (int i=0;i<4;i++)
    {
        cout << "������� " << i+1 << endl;
        cout << Data_base[i].fio << endl;
        cout << Data_base[i].birthday << endl;
        cout << Data_base[i].adress << endl;
        cout << Data_base[i].rating << endl;
    }
}
string NAME(string s)
{
    string result;
    int p=0;
    while (s[p]!=' ')
    {
        result+=s[p];
        p++;
    }
    return result;
}
int main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    Student Data_base[4];
    ifstream F1("F1.txt");
	if (!F1.is_open())
    {
        cout << "������ �� �������\n";
        system("pause");
        return 0;
    }
    try
    {
        for (int i=0;i<4;i++)
        {
            string x;
            getline(F1,Data_base[i].fio);
            getline(F1,Data_base[i].birthday);
            getline(F1,Data_base[i].adress);
            getline(F1,x);
            Data_base[i].rating=stoi(x);
        }
    }
    catch(...)
    {
        cout << "������ ���������� ��� �� ������������� �������\n";
        system("pause");
        return 0;
    }
    Data_print_console(Data_base);
    string find_name;
    cout << endl;
    cout << "������� ������� �������:\n";
    cin >> find_name;
    cin.get();
    ofstream F2("F2.txt");
	for (int i=0;i<4;i++)
    {
        bool flag=true;
        for (int k=0;k<4;k++)
        {
            if (k!=i && Data_base[i].birthday==Data_base[k].birthday)
            {
                flag=false;
                break;
            }
        }
        if (NAME(Data_base[i].fio)==find_name)
        {
            string new_fio;
            string new_birthday;
            string new_adress;
            string new_rating;
            cout << "���������� ������� �������\n";
            cout << "������� ��� ������ ��������\n";
            getline(cin,new_fio);
            cout << "������� ���� �������� ������ ��������\n";
            getline(cin,new_birthday);
            cout << "������� ����� ������ ��������\n";
            getline(cin,new_adress);
            cout << "������� ������� ������ ��������\n";
            getline(cin,new_rating);
            F2<<new_fio<<"\n";
            F2<<new_birthday<<"\n";
            F2<<new_adress<<"\n";
            F2<<new_rating<<"\n";
        }
        if (flag)
        {
            F2<<Data_base[i].fio<<"\n";
            F2<<Data_base[i].birthday<<"\n";
            F2<<Data_base[i].adress<<"\n";
            F2<<Data_base[i].rating<<"\n";
        }
    }
    F1.close();
    F2.close();
    system("pause");
}
