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
void Print(CITIZEN a)
{
    cout << "ÔÈÎ            : " << a.fio << endl;
    cout << "Äàòà ðîæäåíèÿ  : " << a.birthday << endl;
    cout << "Íîìåð ïàññïîðòà: " << a.passport << endl;
}
int Linear(string s, string x)
{
    bool flag;
    for (int i=0;i<(len-1)*8;i++)
    {
        flag=true;
        for (int k=0;k<8;k++)
        {
            if (x[k]!=s[i+k])
            {
                flag=false;
                break;
            }
        }
        if (flag) return i/8;
    }
    return -1;
}
int KMP(string s, string x)
{
	int ls = s.size();
	int lx = x.size();
	int pi[lx];
	pi[0] = 0;
	int i = 1;
	int j = 0;
	int index_str = 0;
	int index_pod = 0;
	while (i<lx)
    {
		if (x[i] != x[j])
        {
			if (j == 0)
			{
			    pi[i] = 0;
			    i++;
			}
			else j = pi[j - 1];
		}
		else
        {
            pi[i] = j + 1;
            i++;
            j++;
        }
	}
	while (index_str < ls)
	{
		if (s[index_str] == x[index_pod])
		{
			index_str++;
			index_pod++;
			if (index_pod == lx) return (index_str-8)/8;
		}
		else
		{
			if (index_pod == 0) index_str++;
			else index_pod = pi[index_pod - 1];
		}
	}
	return -1;
}
int BM(string s, string x)
{
    int l=x.size();
    int arr[l];
    int delta;
    bool flag=false;
    bool flag2;
    for (int i=0;i<l-2;i++) for (int k=l-2;k>-1;k--) if (x[i]==x[k])
    {
        arr[i]=l-k-1;
        break;
    }
    arr[l-2]=1;
    for (int i=l-2;i>-1;i--) if (s[i]==s[l-1])
    {
        arr[l-1]=l-i-1;
        flag=true;
        break;
    }
    if (!flag) arr[l-1]=l;
    for (int i=0;i<(len-1)*8;i++)
    {
        flag=true;
        for (int k=l-1;k>-1;k--) if (s[i+k]!=x[k])
        {
            flag=false;
            flag2=false;
            for (int j=0;j<l;j++) if (s[i+k]==x[j])
            {
                flag2=true;
                delta=arr[j];
                break;
            }
            if (!flag2) delta=l;
            break;
        }
        if (flag) return i/8;
        i+=delta-1;
    }
    return -1;
}
int main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string user_search;
	while (len<2 || len>100)
    {
        cout << "Ââåäèòå ðàçìåð òàáëèöû\n";
        cin >> len;
    }
    cin.get();
    CITIZEN *data_base=new CITIZEN[len];
    string mas="";
    ifstream F1("F1.txt");
    for (int i=0;i<len;i++)
    {
        getline(F1,data_base[i].fio);
        getline(F1,data_base[i].birthday);
        getline(F1,data_base[i].passport);
        mas+=data_base[i].birthday;
    }
    while (true)
    {
        user_search="1";
        cout << "Ââåäèòå çàïðîñ\n";
        while (user_search.size()<8) cin >> user_search;
        int pos1=Linear(mas,user_search);
        cout << 1;
        int pos2=KMP(mas,user_search);
        cout << 2;
        int pos3=BM(mas,user_search);
        cout << 3;
        if (pos1==-1 || pos2==-1 || pos3==-1) cout << "Ýëåìåíò íå íàéäåí\n";
        else
        {
            cout << "Ðåçóëüòàò ïðÿìîãî ïîèñêà:\n";
            Print(data_base[pos1]);
            cout << "Ðåçóëüòàò ìåòîäà ÊÌÏ:\n";
            Print(data_base[pos2]);
            cout << "Ðåçóëüòàò ìåòîäà ÁÌ:\n";
            Print(data_base[pos3]);
            cout << endl;
        }
    }
}
