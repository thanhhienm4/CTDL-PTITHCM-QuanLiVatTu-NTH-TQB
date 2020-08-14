#ifndef NHAP_H_INCLUDED
#define NHAP_H_INCLUDED

#include <conio.h>
#include <cstring>
#include "mylib1.h"
#include "header.h"

#define UP 72
#define DOWN 80
#define KLEFT 75
#define KRIGHT 77
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define DEL 83
#define TAB 9
#define INS 82
#define F9 67
#define F2 60
#define F3 61
#define SPACEBAR 32

using namespace std ;
string ChuanHoaChuoi(string s)
{
    string t = "";
    int st = -1;
    int sp = 0;
    int n = s.size();
    while(st <n && sp <n)
    {
        while(s[st+1]==' ')
            st++;
        sp = st+1;
        while(s[sp+1]!=' ')
            sp++;
        if(t=="")
            t = t+s.substr(st+1,sp-st);
        else
            t = t+" "+s.substr(st+1,sp-st);

        st = sp;
    }
    return t;
}
bool PhimNong(char &c, int mode)
{
	// mode 0 : chi su dung up, down, left, right;
	// mode 1 : su dung tat ca
    if(c==-32)
        c= getch();
    if(mode == 0){
    	if( c==UP || c== DOWN || c==KLEFT || c==KRIGHT )
        return true;
	}
    if(c==ENTER || c==UP || c== DOWN || c== ESC || c==KLEFT || c==KRIGHT )
        return true;
    return false;
}
bool So(char &c)
{
	if(c>='0' && c<='9')
			return 1;
	return 0;
}
bool Chu(char &c)
{
	if((c>='A' && c<='Z'))
		return 1;
	return 0;
}
bool KiTu(char &c)
{
    if(So(c)==1 || Chu(c)==1)
        return 1;
    return 0;
}
bool DieuKien(int &i, char &c)
{
	switch(i)
	{
		case 1 : return So(c); break;
		case 2 : return Chu(c); break;
		case 3 : return (So(c)||Chu(c)); break;
		case 4 : return (So(c)||Chu(c)||(c==SPACEBAR)); break;
		case 5 : return (Chu(c)||(c==SPACEBAR));break;
	}
	return true;
}
void Xoa(int &i)
{
	gotoxy(wherex()-1,wherey());
	cout<<" ";
	gotoxy(wherex()-1,wherey());
    i--;
}

string Nhap(int loai,int KichThuoc,char &pn)
{
    char s[KichThuoc];
    int i =0;
    while(PhimNong(s[i]=getch(), 1)==0)
    {
        if(i==KichThuoc)
            goto a;
    	s[i] = (s[i]);
        if(DieuKien(loai,s[i])==1)
        {
            printf("%c",s[i]);
            i++;
        }
        a:
        if(s[i]==Backspace)
        {
            if(i>0)
        	Xoa(i);
        	s[i+1]=Space ;
        }
    }
    pn = s[i];
    s[i]='\0';
    return s ;


}
string  NhapSo(int kt,char &pn)
{
	return Nhap(1,kt,pn);
}
string  NhapChu(int kt,char &pn)
{
   return Nhap(2,kt,pn);
}
string  NhapKyTu(int kt,char &pn)
{
	return Nhap(3,kt,pn);
}
string  ThayDoi(string s1,int loai,int KichThuoc,char &pn)
{
    int i = s1.size();
    char s[KichThuoc];
    for(int j=0;j<i;j++)
    {
        s[j]=s1[j];
    }

    while(PhimNong(s[i]=getch(), 1)==0)
    {
    	s[i] = toupper(s[i]);
    	if(i==KichThuoc)
            goto a;
        if(DieuKien(loai,s[i])==1)
            {
                printf("%c",s[i]);
                i++;
            }
        a:
        if(s[i]==Backspace && i!= 0)
        {
        	Xoa(i);
        	s[i+1]=Space ;
        }
    }
    pn  = s[i];
    s[i]='\0';
    return s;


}
void NhapPhimNong(char &pn,int &lpn)
{
    do
    {
        pn = getch();
        if(pn==-32)
            pn = getch();
    }while(PhimNong(pn, 1)==0);

}

void NhapChuoi(string &s,int x, int y,int kt,char &pn,int &lpn,int loai)
{
    pn = toupper(pn);
    gotoxy(x,y);
    if(DieuKien(loai,pn)==1)
    {
        if(KiTu(pn)==1 && PhimNong(pn, 1)==0)
            s = s+pn ;
        else
            if(KiTu(pn)==1 && lpn==-1)
                s = s+pn ;
    }
    lpn = 1;
    cout<<s;
    s = ThayDoi(s,loai,kt,pn);
    s = ChuanHoaChuoi(s);
    string temp (kt,' ');
    gotoxy(x,y);
    cout<<temp;
    gotoxy(x,y);
    cout<<s;

}

void NhapChuoiSo(long long & n,int x,int y, int kt,char &pn)
{
    gotoxy(x,y);
    string s = to_string(n);
    if(n==0)
        s="";
    if(So(pn)==1 && PhimNong(pn, 1)==0)
        s = s+pn ;
    cout<<s;
     s = ThayDoi(s,1,kt,pn);
    if(s=="")
        n=0;
    else
        n = stoi(s);
    string temp (kt,' ');
    gotoxy(x,y);
    cout<<temp;
    gotoxy(x,y);
    cout<<n;
}
void NhapKiTu(char &c,int x, int y,int kt,char &pn,int &lpn,int loai)
{
    string s="";
   if(c!='\0')
    s=s+c;
    NhapChuoi(s,x,y,kt,pn,lpn,3);
    s = ChuanHoaChuoi(s);
    if(s!="")
        c = s[0];
    else
        c = '\0';

}

#endif // NHAP_H_INCLUDED
