#include <iostream>
#include <Windows.h>
using namespace std;
string* CreateArr(int n)
{
    string *mas=new string[n];
    return mas;
}
void PrintArr(string mas[],int n)
{
    cout << "Ìàññèâ\n";
    for (int i=0; i<n;i++) cout << mas[i] << endl;
}
string* AddString(string mas[],int num, string s, int *n)
{
    string *mas2=new string[*n+1];
    for (int i=0; i<*n;i++)
    {
        if (i<num) mas2[i]=mas[i];
        else mas2[i+1]=mas[i];
    }
    mas2[num]=s;
    delete [] mas;
    *n=*n+1;
    return mas2;
}
void DelArr(string mas[])
{
    delete [] mas;
}
int main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    int n=-1;
    while (n<=0)
    {
        cout << "Ââåäèòå äëèíó ìàññèâà\n";
        cin >> n;
    }
    string *mas=CreateArr(n);
    cout << "Ââîäèòå ìàññèâ\n";
    cin.get();
    for (int i=0;i<n;i++) getline(cin,mas[i]);
    PrintArr(mas,n);
    int num=-1;
    string s;
    while (num<=0 || num>n-1)
    {
        cout << "Ââåäèòå íîìåð\n";
        cin >> num;
    }
    cout << "Ââåäèòå ñòðîêó\n";
    cin.get();
    getline(cin,s);
    mas=AddString(mas,num-1,s,&n);
    PrintArr(mas,n);
    DelArr(mas);
    system("pause");
}
