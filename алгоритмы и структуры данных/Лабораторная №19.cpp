#include <iostream>
#include <Windows.h>
using namespace std;
struct Stack
{
    int data;
    Stack* last;
    Stack()
    {
        data=0;
        last=NULL;
    }
    ~Stack()
    {
        if (last!=NULL) delete last;
    }
    Stack* PUSH_stack(int x)
    {
        Stack* NEW=new Stack();
        NEW->data=x;
        NEW->last=this;
        return NEW;
    }
    Stack* POP_stack() {return this->last;}
};
int main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    Stack* STACK=new Stack();
    int len=0;
    while (len<=2)
    {
        cout << "Введите длину стека\n";
        cin>>len;
    }
    int x;
    int arr[len];
    int flag=false;
    cout << "Введите число\n";
    cin >> x;
    if (x%2==1) flag++;
    STACK->data=x;
    STACK->last=NULL;
    for (int i=0;i<len-1;i++)
    {
        cout << "Введите число\n";
        cin >> x;
        if (x%2==1) flag=true;
        STACK=STACK->PUSH_stack(x);
    }
    for (int i=0;i<len;i++)
    {
        arr[i]=STACK->data;
        STACK=STACK->POP_stack();
    }
    for (int i=0;i<len;i++) if (arr[i]%2==1) STACK=STACK->PUSH_stack(arr[i]);
    if (flag)
    {
        cout << "Результат\n";
        while (STACK!=NULL)
        {
            cout << STACK->data << endl;
            STACK=STACK->POP_stack();
        }
    }
    else cout << "Стек удален\n";
    system("pause");
}
