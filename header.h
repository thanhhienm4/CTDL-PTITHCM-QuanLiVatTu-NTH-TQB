#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include<fstream>
#include<ctime>
using namespace std;
template <class Type>
struct NodeQueue
{
    Type Data;
    NodeQueue <Type> *Next;
    NodeQueue () {Next=NULL;}
};
template <class Type>
class Queue
{
    private:
    NodeQueue <Type> *First;
    public:
    void Clear();
    bool Empty();
    void Push(Type);
    void Pop();
    int Size();
    Type Front();
    void Show();
    Queue () {First = NULL;}
    ~Queue() {Clear();}


};
template <class Type>
int Queue <Type>::Size()
{
    if(First==NULL)
       return 0;
    int cnt = 0;
    NodeQueue <Type> *p = First;
    while(p!=NULL)
    {
        cnt++;
        p=p->Next;
    }
    return cnt ;
}
template <class Type>
void Queue <Type>::Clear()
{
    NodeQueue <Type> *p;
    while(First!=NULL)
      {
        p = First;
        First = First->Next;
        delete (p);
      }
}
template <class Type>
bool Queue <Type> :: Empty()
{
    if(First==NULL)
    {
        return 1;
    }
    return 0;
}

template <class Type>
void Queue <Type> :: Push(Type temp)
{
    NodeQueue <Type> *node = new NodeQueue <Type> ;
    node->Data = temp;
    NodeQueue <Type> *pnode = First;
    if(First==NULL)
    {
        First = node;
    }else
    {
        while(pnode->Next!=NULL)
              pnode = pnode->Next;
        pnode->Next = node;
    }
}

template <class Type>
void Queue <Type> :: Pop()
{
    if(First==NULL)
       return ;
    else
    {
        NodeQueue <Type> *p = First;
        First= First->Next;
        delete (p);
    }
}
template <class Type>
Type Queue <Type> :: Front()
{
    return First->Data;
}
// stack
template <class Type>
struct Nodestack
{
    Type Data;
    Nodestack <Type> *Next;
    Nodestack () {Next=NULL;}
};
template <class Type>
class stack
{
    private:
    Nodestack <Type> *First;
    public:
    void Clear();
    bool empty();
    void push(Type);
    void pop();
    int Size();
    void Show();
    Type top();

    stack () {First = NULL;}
    ~stack() {Clear();}


};
template <class Type>
int stack <Type>::Size()
{
    if(First==NULL)
       return 0;
    int cnt = 0;
    Nodestack <Type> *p = First;
    while(p!=NULL)
    {
        cnt++;
        p=p->Next;
    }
    return cnt ;
}
template <class Type>
void stack <Type>::Clear()
{
    Nodestack <Type> *p;
    while(First!=NULL)
      {
        p = First;
        First = First->Next;
        delete (p);
      }
}
template <class Type>
bool stack <Type> :: empty()
{
    if(First==NULL)
    {
        return 1;
    }
    return 0;
}

template <class Type>
void stack <Type> :: push(Type temp)
{
    Nodestack <Type> *node = new Nodestack <Type> ;
    node->Data = temp;
    Nodestack <Type> *pnode = First;
    if(First==NULL)
    {
        First = node;
    }else
    {
        while(pnode->Next!=NULL)
              pnode = pnode->Next;
        pnode->Next = node;
    }
}

template <class Type>
void stack <Type> :: pop()
{
    if(First==NULL)
       return ;
    else
    {
        if(First->Next==NULL)
           {
               delete(First->Next);
                First = NULL;
                return ;
           }
        Nodestack <Type> *p = First;
        while(p->Next->Next!=NULL)
            p=p->Next;
        delete (p->Next);
        p->Next = NULL;
    }
}
template <class Type>
Type stack <Type> :: top()
{
    Nodestack <Type> * p = First;
    while(p->Next!=NULL)
        p=p->Next;
    return p->Data;
}
//

int Dodai(char s[])
{
    int i=0;
    while(s[i]!='\0')
        i++;
    return i;
}

struct Date
{
    long long Ngay;
    long long Thang;
    long long Nam;
    Date(int ngay,int thang,int nam)
    {
        Ngay = ngay;
        Thang = thang;
        Nam = nam;;
    }
    Date()
    {
		time_t now =time(0);
		tm *ltm = localtime(&now);
		Nam = 1900+ltm->tm_year;
		Thang = 1+ltm->tm_mon;
		Ngay = ltm->tm_mday;

    }
};
bool NamNhuan(int nam)
{
    if(nam%4==0)
    {
        if(nam%100==0 && nam %400!=0)
            return false;
        return true;
    }
    return false;
}
bool KiemTraNgay(Date ngay)
{
    if(ngay.Thang >12 || ngay.Thang ==0)
        return false;
    int ntt; // ngay trong thang
    switch(ngay.Thang)
    {
        case 1: ntt = 31; break;
        case 2: if(NamNhuan(ngay.Nam)==1) ntt = 29; else ntt = 28;break;
        case 3: ntt = 31;break;
        case 4: ntt = 30;break;
        case 5: ntt = 31;break;
        case 6: ntt = 30;break;
        case 7: ntt = 31;break;
        case 8: ntt = 31;break;
        case 9: ntt = 30;break;
        case 10:ntt = 31;break;
        case 11:ntt = 30;break;
        case 12:ntt = 31;break;
    }
    if(ngay.Ngay == 0 || ngay.Ngay >ntt)
        return false;
    return true;

}
int SoSanh(long long  &x,long long &y)
{
	if(x>y)
		return 1;
	else
	{
		if(x==y)
			return 0;
	}
	return -1;
}
int SoSanhNgay(Date ngay1, Date ngay2)
{
	if(SoSanh(ngay1.Nam,ngay2.Nam)!=0)
		return SoSanh(ngay1.Nam,ngay2.Nam);
	else
	{
		if(SoSanh(ngay1.Thang,ngay2.Thang)!=0)
			return SoSanh(ngay1.Thang,ngay2.Thang);
		else
		{
			if(SoSanh(ngay1.Ngay,ngay2.Ngay)!=0)
				return SoSanh(ngay1.Ngay,ngay2.Ngay);
			else
				return 0;
		}
	}
}
string upcaseWord(string s){
	for(int i = 0; i < s.size(); i++){
		if(s[i] >= 97 && s[i] <= 122){
			s[i] -= 32;
		}
	}
	return s;
}
#endif // HEADER_H_INCLUDED
