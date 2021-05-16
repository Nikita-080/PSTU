#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm>
using namespace std;
int len=-1;
struct CITIZEN
{
    string fio;
    string birthday;
    string passport;
};
int Dig(string a)
{
    return (int)(a[6]+a[7]+a[3]+a[4]+a[0]+a[1]);
}
bool comp(CITIZEN a, CITIZEN b)
{
    return (Dig(a.birthday)<Dig(b.birthday));
}
void Print(CITIZEN a)
{
    cout << "ФИО            : " << a.fio << endl;
    cout << "Дата рождения  : " << a.birthday << endl;
    cout << "Номер пасспорта: " << a.passport << endl;
}
int Linear(CITIZEN arr[], string x)
{
    for (int i=0;i<len;i++) if (arr[i].birthday==x) return i;
    return -1;
}
int Binary(CITIZEN arr[], string x)
{
    string mas="";
    bool flag;
    for (int i=0;i<len;i++) mas+=arr[i].birthday;
    for (int i=0;i<=(len-1)*8;i++)
    {
        flag=true;
        for (int k=0;k<8;k++)
        {
            if (x[k]!=mas[i+k])
            {
                flag=false;
                break;
            }
        }
        if (flag) return i/8;
    }
    return -1;
}
int Interpol(CITIZEN arr[], string x)
{
    int L=0;
    int R=len-1;
    while (R-L>1)
    {
        int mid=L+(Dig(x)-Dig(arr[L].birthday))*(R-L)/(Dig(arr[R].birthday)-Dig(arr[L].birthday));
        if (Dig(x)<Dig(arr[mid].birthday)) R=mid;
        else if (Dig(x)>Dig(arr[mid].birthday)) L=mid;
        else return mid;
    }
    if (Dig(x)==Dig(arr[L].birthday)) return L;
    if (Dig(x)==Dig(arr[R].birthday)) return R;
    return -1;
}
int main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string user_search;
	while (len<2 || len>100)
    {
        cout << "Введите размер таблицы\n";
        cin >> len;
    }
    cin.get();
    CITIZEN *data_base=new CITIZEN[len];
    ifstream F1("F1.txt");
    for (int i=0;i<len;i++)
    {
        getline(F1,data_base[i].fio);
        getline(F1,data_base[i].birthday);
        getline(F1,data_base[i].passport);
    }
    sort(data_base,data_base+len,comp);
    while (true)
    {
        cout << "Введите запрос\n";
        cin >> user_search;
        int pos1=Linear(data_base,user_search);
        int pos2=Binary(data_base,user_search);
        int pos3=Interpol(data_base,user_search);
        if (pos1==-1 || pos2==-1 || pos3==-1) cout << "Элемент не найден\n";
        else
        {
            cout << "Результат линейного поиска:\n";
            Print(data_base[pos1]);
            cout << "Результат прямого поиска подстроки в строке:\n";
            Print(data_base[pos2]);
            cout << "Результат интерполяционного поиска:\n";
            Print(data_base[pos3]);
            cout << endl;
        }
    }
}
