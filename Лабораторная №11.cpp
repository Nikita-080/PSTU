#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <Windows.h>
using namespace std;
int len=-1;
int work=-1;
struct Queue
{
    string data;
    Queue* last;
};
struct List2
{
    string data;
    List2* next;
    List2* last;
};
struct Stack
{
    int data;
    Stack* last;
};
struct List
{
    int data;
    List* next;
};
void DEL_list_2(List2* LIST)
{
    List2* p=LIST;
    List2* h;
    while (p!=NULL)
    {
        h=p->next;
        delete p;
        p=h;
    }
}
void PRINT_list_2(List2* LIST)
{
    cout << "Ðåçóëüòàò:\n";
    List2* p=LIST;
    while (p!=NULL)
    {
        cout << p->data << endl;
        p=p->next;
    }
}
void DO_list_2(List2* LIST)
{
    List2* p=LIST;
    string s;
    while (p->next!=NULL)
    {
        cout << "Ââåäèòå íîâîå ñëîâî\n";
        cin >> s;
        List2* NEW=new List2;
        NEW->data=s;
        NEW->next=p->next;
        NEW->last=p;
        p->next=NEW;
        p->next->last=NEW;
        p=NEW->next;
    }
}
void PUSH_list_2(List2* LIST,string s)
{
    List2* NEW=new List2;
    List2* p=LIST;
    NEW->data=s;
    NEW->next=NULL;
    while (p->next!=NULL) p=p->next;
    p->next=NEW;
    NEW->last=p;
}
void PUSH_list_1(List* LIST,int x)
{
    List* NEW=new List;
    List* p=LIST;
    NEW->data=x;
    NEW->next=NULL;
    while (p->next!=NULL) p=p->next;
    p->next=NEW;
}
List* DO_list_1(List* LIST)
{
    List* p=LIST->next;
    List* h=LIST;
    while (p->next!=NULL)
    {
        if (p->data%2==0)
        {
            h->next=p->next;
            delete p;
            p=h->next;
        }
        else
        {
            p=p->next;
            h=h->next;
        }
    }
    if (LIST->data%2==0) LIST=LIST->next;
    if (p->data%2==0)
    {
        h->next=NULL;
        delete p;
    }
    return LIST;
}
void PRINT_list_1(List* LIST)
{
    cout << "Ðåçóëüòàò:\n";
    List* p=LIST;
    while (p!=NULL)
    {
        cout << p->data << endl;
        p=p->next;
    }
}
void DEL_list_1(List* LIST)
{
    List* p=LIST;
    List* h;
    while (p!=NULL)
    {
        h=p->next;
        delete p;
        p=h;
    }
}
void Proc_list_1()
{
    List* LIST=new List;
    int x;
    bool flag=false;
    LIST->next=NULL;
    cout << "Ââåäèòå ÷èñëî\n";
    cin >> x;
    LIST->data=x;
    for (int i=0;i<len-1;i++)
    {
        cout << "Ââåäèòå ÷èñëî\n";
        cin >> x;
        if (x%2==1) flag=true;
        PUSH_list_1(LIST,x);
    }
    if (flag)
    {
        LIST=DO_list_1(LIST);
        PRINT_list_1(LIST);
    }
    else cout << "Ðåçóëüòàò: ñïèñîê óäàëåí\n";
    DEL_list_1(LIST);
}
void Proc_list_2_fun()
{
    List2* LIST=new List2;
    LIST->last=NULL;
    LIST->next=NULL;
    string s;
    cout << "Ââåäèòå ñëîâî\n";
    cin >> s;
    LIST->data=s;
    for (int i=0;i<len-1;i++)
    {
        cout << "Ââåäèòå ñëîâî\n";
        cin >> s;
        PUSH_list_2(LIST,s);
    }
    DO_list_2(LIST);
    PRINT_list_2(LIST);
    DEL_list_2(LIST);
}
void Proc_list_2_lib()
{
    list <string> LIST;
    string s;
    for (int i=0;i<len;i++)
    {
        cout << "Ââåäèòå ñëîâî\n";
        cin >> s;
        LIST.push_back(s);
    }
    for (auto iter=LIST.begin();iter!=LIST.end();iter++)
    {
        cout << "Ââåäèòå íîâûé ýëåìåíò\n";
        cin >> s;
        LIST.insert(iter,s);
    }
    cout << "Ðåçóëüòàò\n";
    for (auto iter=LIST.begin();iter!=LIST.end();iter++) cout << *iter << endl;
}
Stack* PUSH_stack(Stack* STACK, int x)
{
    Stack* NEW=new Stack;
    NEW->data=x;
    NEW->last=STACK;
    return NEW;
}
Stack* POP_stack(Stack* STACK)
{
    Stack* El=STACK->last;
    delete STACK;
    return El;
}
void Proc_stack_fun()
{
    Stack* STACK=new Stack;
    int x;
    int arr[len];
    int flag=0;
    cout << "Ââåäèòå ÷èñëî\n";
    cin >> x;
    if (x%2==1) flag++;
    STACK->data=x;
    STACK->last=NULL;
    for (int i=0;i<len-1;i++)
    {
        cout << "Ââåäèòå ÷èñëî\n";
        cin >> x;
        if (x%2==1) flag++;
        STACK=PUSH_stack(STACK,x);
    }
    for (int i=0;i<len;i++)
    {
        arr[i]=STACK->data;
        STACK=POP_stack(STACK);
    }
    for (int i=0;i<len;i++) if (arr[i]%2==1) STACK=PUSH_stack(STACK,arr[i]);
    if (flag>0)
    {
        cout << "Ðåçóëüòàò\n";
        while (STACK!=NULL)
        {
            cout << STACK->data << endl;
            STACK=POP_stack(STACK);
        }
    }
    else cout << "Ñòåê óäàëåí\n";
}
void Proc_stack_lib()
{
    stack <int> STACK;
    int x;
    int arr[len];
    for (int i=0;i<len;i++)
    {
        cout << "Ââåäèòå ÷èñëî\n";
        cin >> x;
        STACK.push(x);
    }
    for (int i=0;i<len;i++)
    {
        arr[i]=STACK.top();
        STACK.pop();
    }
    for (int i=0;i>len;i++) if (arr[i]%2==1) STACK.push(arr[i]);
    if (STACK.empty()) cout << "Ðåçóëüòàò: ñòåê óäàëåí\n";
    else
    {
        cout << "Ðåçóëüòàò\n";
        for (int i=0;i<STACK.size();i++)
        {
            cout << STACK.top() << endl;
            STACK.pop();
        }
    }
}
void PUSH_queue(Queue* QUEUE, string s)
{
    Queue* El=QUEUE;
    Queue* NEW=new Queue;
    while (El->last!=NULL) El=El->last;
    NEW->data=s;
    NEW->last=NULL;
    El->last=NEW;
}
Queue* POP_queue(Queue* QUEUE)
{
    Queue* El=QUEUE->last;
    delete QUEUE;
    return El;
}
void Proc_queue_fun()
{
    Queue* QUEUE=new Queue;
    stack <string> STACK;
    string arr[len];
    string s;
    cout << "Ââåäèòå ñëîâî\n";
    cin >> s;
    QUEUE->data=s;
    QUEUE->last=NULL;
    for (int i=0;i<len-1;i++)
    {
        cout << "Ââåäèòå ñëîâî\n";
        cin >> s;
        PUSH_queue(QUEUE,s);
    }
    for (int i=0;i<len;i++)
    {
        cout << "Ââåäèòå íîâûé ýëåìåíò\n";
        cin >> arr[i];
    }
    for (int i=0;i<len;i++)
    {
        PUSH_queue(QUEUE,QUEUE->data);
        PUSH_queue(QUEUE,arr[len-i-1]);
        QUEUE=POP_queue(QUEUE);
    }
    for (int i=0;i<len*2;i++)
    {
        STACK.push(QUEUE->data);
        QUEUE=POP_queue(QUEUE);
    }
    cout << "Ðåçóëüòàò\n";
    for (int i=0;i<len*2;i++)
    {
        cout << STACK.top() << endl;
        STACK.pop();
    }
}
void Proc_queue_lib()
{
    queue <string> QUEUE;
    stack <string> STACK;
    string arr[len];
    string s;
    for (int i=0;i<len;i++)
    {
        cout << "Ââåäèòå ñëîâî\n";
        cin >> s;
        QUEUE.push(s);
    }
    for (int i=0;i<len;i++)
    {
        cout << "Ââåäèòå íîâûé ýëåìåíò\n";
        cin >> arr[i];
    }
    for (int i=0;i<len;i++)
    {
        QUEUE.push(QUEUE.front());
        QUEUE.push(arr[len-i-1]);
        QUEUE.pop();
    }
    for (int i=0;i<len*2;i++)
    {
        STACK.push(QUEUE.front());
        QUEUE.pop();
    }
    cout << "Ðåçóëüòàò\n";
    for (int i=0;i<len*2;i++)
    {
        cout << STACK.top() << endl;
        STACK.pop();
    }
}
int main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    while (true)
    {
        cout << "\n";
        cout << "Îäíîíàïðàâëåííûé ñïèñîê.............1\n";
        cout << "Äâóíàïðàâëåííûé ñïèñîê (ôóíêöèè)....2\n";
        cout << "Äâóíàïðàâëåííûé ñïèñîê (áèáëèîòåêà).3\n";
        cout << "Ñòåê (ôóíêöèè)......................4\n";
        cout << "Ñòåê (áèáëèîòåêà)...................5\n";
        cout << "Î÷åðåäü (ôóíêöèè)...................6\n";
        cout << "Î÷åðåäü (áèáëèîòåêà)................7\n";
        cout << endl;
        cout << "Ââåäèòå íîìåð ðàáîòû\n";
        cin >> work;
        while (len<2)
        {
            cout << "Ââåäèòå äëèíó ñòðóêòóðû:\n";
            cin >> len;
        }
        switch (work)
        {
        case 1:
            Proc_list_1();
            break;
        case 2:
            Proc_list_2_fun();
            break;
        case 3:
            Proc_list_2_lib();
            break;
        case 4:
            Proc_stack_fun();
            break;
        case 5:
            Proc_stack_lib();
            break;
        case 6:
            Proc_queue_fun();
            break;
        case 7:
            Proc_queue_lib();
            break;
        default:
            cout << "Äàííûé íîìåð îòñóòñòâóåò\n:(\n";
        }
        len=-1;
        work=-1;
    }
}
