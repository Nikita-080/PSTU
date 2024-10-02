#include <iostream>
#include <stack>
#include <windows.h>
using namespace std;
void SortShell(float P[],string chem[],int len)
{
    for(int d=len/2; d!=0; d/=2)
    {
        for(int i=0; i<d; i++)
        {
            for (int j=i; j+d<len; j+=d)
            {
                int num=j+d;
                while (num>=i+d && P[num-d]>P[num])
                {
                    swap(P[num-d],P[num]);
                    swap(chem[num-d],chem[num]);
                    num-=d;
                }
            }
        }
    }
}
void SortChoar(float P[],string chem[],int first,int last)
{
    if (last>first)
    {
        float x=P[(last-first)/2];
        stack <float> STACKminP;
        stack <float> STACKmaxP;
        stack <string> STACKminC;
        stack <string> STACKmaxC;
        stack <float> STACKcenP;
        stack <string> STACKcenC;
        for (int i=first;i<=last;i++)
        {
            if (P[i]<x)
            {
                STACKminP.push(P[i]);
                STACKminC.push(chem[i]);
            }
            else if (P[i]>x)
            {
                STACKmaxP.push(P[i]);
                STACKmaxC.push(chem[i]);
            }
            else
            {
                STACKcenP.push(P[i]);
                STACKcenC.push(chem[i]);
            }
        }
        int num=STACKminP.size();
        int num2=STACKcenP.size();
        for (int i=first;i<first+num;i++)
        {
            P[i]=STACKminP.top();
            STACKminP.pop();
            chem[i]=STACKminC.top();
            STACKminC.pop();
        }
        for (int i=first+num;i<first+num+num2;i++)
        {
            P[i]=STACKcenP.top();
            STACKcenP.pop();
            chem[i]=STACKcenC.top();
            STACKcenC.pop();
        }
        for (int i=first+num+num2;i<=last;i++)
        {
            P[i]=STACKmaxP.top();
            STACKmaxP.pop();
            chem[i]=STACKmaxC.top();
            STACKmaxC.pop();
        }
        SortChoar(P,chem,first,first+num-1);
        SortChoar(P,chem,first+num+num2,last);
    }
}
int main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    int len=-1;
    cout << "Введите кол-во записей\n";
    while (len<2) cin>> len;
    string chem1[len];
    float P1[len];
    string chem2[len];
    float P2[len];
    for (int i=0;i<len;i++)
    {
        cout << "Введите вещество " <<i+1<<endl;
        cin >> chem1[i];
        chem2[i]=chem1[i];
        cout << "Введите плотность " <<i+1<<endl;
        cin >> P1[i];
        P2[i]=P1[i];
    }
    SortShell(P1,chem1,len);
    SortChoar(P2,chem2,0,len-1);
    cout << "Результат сортировки Шелла\n";
    for (int i=0;i<len;i++) cout << chem1[i] << " " << P1[i] << endl;
    cout << "Результат сортировки Хоара\n";
    for (int i=0;i<len;i++) cout << chem2[i] << " " << P2[i] << endl;
    system("pause");
}
