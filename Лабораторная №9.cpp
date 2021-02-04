#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
bool Split(string s,int row_num)
{
    int words=0;
    switch (s.length())
    {
    case 1:
        if (s==" ")
        {
            cout << row_num << " Îøèáêà: ñëîâà íå íàéäåíû\n";
            return false;
        }
        else words=1;
        break;
    case 2:
        if (s=="  ")
        {
            cout << row_num << " Îøèáêà: ñëîâà íå íàéäåíû\n";
            return false;
        }
        else words=1;
        break;
    default:
        for (int i=0; i<s.length()-1;i++)
        {
            if (s[i]==' ' && s[i+1]!=' ') words++;
        }
        if (s[0]!=' ') words++;
    }
    if (words==0)
    {
        cout << row_num << " Îøèáêà: ñëîâà íå íàéäåíû\n";
        return false;
    }
    string mas[words];
    string word;
    int c=0;
    for (int i=0;i<s.length();i++)
    {
        if (s[i]==' ' && word.length()!=0)
        {
            mas[c]=word;
            word="";
            c++;
        }
        else word+=s[i];
    }
    mas[c]=word;
    int max_dig=0;
    int wn;
    for (int i=0; i<words; i++)
    {
        int dig=0;
        for (int k=0; k<mas[i].length();k++) if (mas[i][k]>='0'&&mas[i][k]<='9') dig++;
        if (dig>max_dig)
        {
            max_dig=dig;
            wn=i;
        }
    }
    if (max_dig==0) cout << row_num << " Îøèáêà: öèôðû íå íàéäåíû\n";
    else cout << row_num+1 << " " << wn+1 << " " << mas[wn] << " " << max_dig << endl;
    for (int i=0; i<words-1; i++)
    {
        for (int k=i+1;k<words;k++) if (mas[i]==mas[k]) return true;
    }
    return false;
}
int main()
{
    setlocale(LC_ALL,"Russian");
	ifstream F1("F1.txt");
	ofstream F2("F2.txt");
	if (!F1.is_open())
    {
        cout << "Äàííûå íå íàéäåíû\n";
        system("pause");
        return 0;
    }
    cout << "íîìåð ñòðîêè|íîìåð ñëîâà|ñëîâî|êîë-âî öèôð\n";
    int row_num=0;
    while (!F1.eof())
    {
        string row;
        getline(F1,row);
        if (row.length()!=0){ if (Split(row,row_num)) F2<<row+"\n";}
        else cout<< row_num << " Îøèáêà: ïóñòàÿ ñòðîêà\n";
        row_num++;
    }
	F1.close();
	F2.close();
	system("pause");
}
