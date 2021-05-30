#include <iostream>
#include <list>
#include <fstream>
#include <windows.h>
#include <math.h>
#include <string>
using namespace std;
struct CITIZEN
{
    string fio;
    string birthday;
    string phone;
    string passport;
};
int Hash_task(string s,int n)
{
    int x=0;
    for (int i=0;i<s.size();i++) x+=(int)(s[i])*(i+1);
    return (int)(n*(0.3*x-(int)(0.3*x)));
}
int Hash_quadro(string s,int n)
{
    int x=0;
    int l;
    for (int i=0;i<s.size();i++) x+=(int)(s[i])*(i+1);
    x=x*x;
    l=to_string(x).size();
    return stoi(to_string(x).substr(l/3,l*2/3));
}
int Hash_ss(string s,int n)
{
    int x=0;
    int result;
    for (int i=0;i<s.size();i++) x+=(int)(s[i])*(i+1);
    for (int i=0;i<to_string(x).size();i++) result+=x/((int)pow(10,i))%10*((int)pow(11,i));
    return result/10;
}
int SwitchHash(string s, int n)
{
    int x=1;
    switch (x)
    {
    case 1:
        return Hash_task(s, n);
    case 2:
        return Hash_quadro(s, n);
    case 3:
        return Hash_ss(s, n);
    }
}
int main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int len=-1;
	int adress;
	CITIZEN x;
	string user_search;
	int error=0;
	while (len<2 || len>100)
    {
        cout << "Введите размер таблицы\n";
        cin >> len;
    }
    const int N=len;
    cin.get();
    CITIZEN *data_base=new CITIZEN[len];
    string *key=new string[len];
    for (int i=0;i<len;i++) key[i]="404";
    ifstream F1("F1.txt");
    for (int i=0;i<N;i++)
    {
        getline(F1,x.fio);
        getline(F1,x.birthday);
        getline(F1,x.phone);
        getline(F1,x.passport);
        adress=SwitchHash(x.birthday,N);
        while (adress>=len || key[len-1]!="404")
        {
            CITIZEN *data_base_new=new CITIZEN[len*2];
            string *key_new=new string[len*2];
            for (int i=0;i<len;i++)
            {
                data_base_new[i]=data_base[i];
                key_new[i]=key[i];
            }
            for (int i=len;i<len*2;i++) key_new[i]="404";
            delete [] data_base;
            delete [] key;
            data_base=data_base_new;
            key=key_new;
            len*=2;
        }
        if (key[adress]!="404")
        {
           error++;
           while (key[adress]!="404") adress++;

        }
        data_base[adress]=x;
        key[adress]=x.birthday;
    }
    cout << "Таблица создана. Коллизий: " << error << endl;
    for (int i=0; i<len;i++)
    {
        cout << i << endl;
        cout << key[i] << endl;
        cout << "ФИО            - " << data_base[i].fio << endl;
        cout << "Дата рождения  - " << data_base[i].birthday << endl;
        cout << "Номер телефона - " << data_base[i].phone << endl;
        cout << "Номер паспорта - " << data_base[i].passport << endl;
    }
    while (true)
    {
        cout << "Введите запрос\n";
        cin >> user_search;
        adress=SwitchHash(user_search,N);
        while (adress<len)
        {
            if (key[adress]==user_search)
            {
                cout << "Объект найден:\n";
                cout << "ФИО            - " << data_base[adress].fio << endl;
                cout << "Дата рождения  - " << data_base[adress].birthday << endl;
                cout << "Номер телефона - " << data_base[adress].phone << endl;
                cout << "Номер паспорта - " << data_base[adress].passport << endl;
                break;
            }
            if (key[adress]=="404")
            {
                cout << "Неизвестный объект [404]\n";
                break;
            }
            adress++;
        }
        if (adress==len) cout << "Неизвестный объект [404]\n";
    }
}
