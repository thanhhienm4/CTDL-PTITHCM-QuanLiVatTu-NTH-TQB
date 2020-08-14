#include<iostream>
#pragma once
#include "nhap.h"
#include "ThanhTimKiem.h"


using namespace std;
const int TOADOX = 0;
const int TOADOY = 2;
const int CHIEUNGANG = 207;
const int CHIEUDOC = 40;

void Normal () { // Mau khi o khong duoc chon
	SetColor(0);
	SetBGColor(15);
}
void HighLight () { // Mau khi o duoc chon
	SetColor(0);
	SetBGColor(14);
}
void fullScreen() // Toan man hinh
{
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}
void DrawBorder(int toaDoX, int toaDoY, int chieuNgang, int chieuDoc) // Ve o vuong
{
	gotoxy(toaDoX, toaDoY); //goc tren ben trai
	cout << char(218);
	gotoxy(toaDoX, toaDoY + chieuDoc); 	//goc tren ben phai
	cout << char(192);
	gotoxy(toaDoX + chieuNgang, toaDoY); //goc duoi ben trai
	cout << char(191);
	gotoxy(toaDoX + chieuNgang, toaDoY + chieuDoc); //goc duoi ben phai
	cout << char(217);

	//ve hang
	gotoxy(toaDoX + 1, toaDoY);
	for (int i = 0; i < chieuNgang - 1; i++) {
		cout << char(196);
	}
	gotoxy(toaDoX + 1, toaDoY + chieuDoc);
	for (int i = 0; i < chieuNgang - 1; i++) {
		cout << char(196);
	}
	//ve cot
	for (int i = 0; i < chieuDoc - 1; i++) {
		gotoxy(toaDoX, toaDoY + i + 1);
		cout << char(179);
		gotoxy(toaDoX + chieuNgang, toaDoY + i + 1);
		cout << char(179);
	}
	cout << "\n";
}
int XuLiUpDown(int &chon,char &pn,int n,int x, int y)
{
        y = y - n*2;

        switch(pn)
        {
            case UP:
				if(chon > 0){
					gotoxy(x ,y+2*chon);
					cout << "     ";
					chon--;
					gotoxy(x,y+2*chon);
					cout << "[<=]";
				}
				break;
            case DOWN:
				if(chon <n-1){
					gotoxy(x,y+2*chon);
					cout << "    ";
					chon ++ ;
					gotoxy(x,y+2*chon);
					cout << "[<=]";
				}
			 	break;
            case ENTER:
				break;
        }
    if(PhimNong(pn, 1)==1)
        pn=17;
    return chon;
}
void DrawBorderList(int toaDoX, int toaDoY, int soDong, int soCot, int chieuNgangO, int chieuDocO)
{
	for (int i = 0; i < soDong; i++) {
		int tempX = toaDoX;
		for (int j = 0; j < soCot; j++) {
			DrawBorder(tempX, toaDoY, chieuNgangO, chieuDocO + 1);

			if (i == 0 && j > 0) {
				gotoxy(tempX, toaDoY);
				cout << char(194); //doi goc trai tren cua cac o hang tren cung
			}
			if (i == soDong - 1 && j > 0) {
				gotoxy(tempX, toaDoY + chieuDocO + 1); //doi goc trai duoi cua cac o hang cuoi cung
				cout << char(193);
			}
			if (j == 0 && i > 0) {
				gotoxy(tempX, toaDoY);//doi goc trai tren cua nhung o cot dau tien
				cout << char(195);
			}
			if (j == soCot - 1 && i > 0) {
				gotoxy(tempX + chieuNgangO, toaDoY); //doi goc phai duoi cua nhung o cot cuoi cung
				cout << char(180);
			}
			if (j > 0 && j < soCot && i > 0 && i < soDong) {
				gotoxy(tempX, toaDoY); //con cac goc phai tren cua cac o con lai cho thanh dau cong la xong
				cout << char(197);
			}

			tempX += chieuNgangO;
		}
		toaDoY += chieuDocO + 1;
	}
}

string CenterTextInSpace(string str, int wide) // Can giua chu o dong
{
	string strAns;
	strAns.resize(wide, ' ');
	int centerStart = (wide - str.size()) / 2 + (wide - str.size()) % 2;
	for (int i = 0; i < str.size(); i++)
	{
		strAns[centerStart + i] = str[i];
	}
	return strAns;
}
string CharToString(char* t)
{
	int i = 0;
	string ans;
	while (t[i] != '\0'){
		ans += t[i];
		i++;
	}
	return ans;
}
void ClearInsideBox(int top, int down,int left, int right) // Xoa trang man hinh
{
	string clear1;
	clear1.resize(right - left, ' ');
	for(int i = top; i <= down; i++){
		gotoxy(TOADOX + left, TOADOY + i);
		cout << clear1;
	}
}
void ClearFunction(){
	ClearInsideBox(3, 34, 21, 160);// xoa danh sach
	ClearInsideBox(23,39,161,206);//Xoa man hinh edit
	ClearInsideBox(36, 39, 33, 160);// Xoa man hinh thong bao
}

void getData(int &i, string line, string &newString){
	while(line[i] != ','){
		newString += line[i];
		i++;
	}
}

void DrawDetail(string s1, string s2, string s3, string s4, string s5, string s6){
		int WIDE = 20;
		SetColor(5);
		SetBGColor(15);
		int i = 0;
		gotoxy(36 + i, 11);
		cout << CenterTextInSpace(s1, WIDE - 1);
		i += 20;
		gotoxy(36 + i, 11);
		cout << CenterTextInSpace(s2, WIDE - 1);
		i += 20;
		gotoxy(36 + i, 11);
		cout << CenterTextInSpace(s3, WIDE - 1);
		i += 20;
		gotoxy(36 + i, 11);
		cout << CenterTextInSpace(s4, WIDE - 1);
		i += 20;
		gotoxy(36 + i, 11);
		cout << CenterTextInSpace(s5, WIDE - 1);
		i += 20;
		gotoxy(36 + i, 11);
		cout << CenterTextInSpace(s6, WIDE - 1);
		SetColor(0);
		SetBGColor(15);
}
void WriteCenterText(string str, int toaDoX, int toaDoY, int mode)
{
	int x;
	if(mode ==  0){
		x = 19;
	}
	else{
		x = 50;
	}
	gotoxy(toaDoX, toaDoY);
	cout << CenterTextInSpace("", x);
	gotoxy(toaDoX, toaDoY + 1);
	cout << CenterTextInSpace("", x);
	gotoxy(toaDoX, toaDoY + 2);
	cout << CenterTextInSpace("", x);
	gotoxy(toaDoX, toaDoY + 3);
	cout << CenterTextInSpace(str, x);
	gotoxy(toaDoX, toaDoY + 4);
	cout << CenterTextInSpace("", x);
	gotoxy(toaDoX, toaDoY + 5);
	cout << CenterTextInSpace("", x);
	gotoxy(toaDoX, toaDoY + 6);
	cout << CenterTextInSpace("", x);
	gotoxy(toaDoX, toaDoY + 7);
}

void ThongBao(string noidung)
{
    ClearInsideBox(36, 39, 33, 160);
	int x = wherex(); int y = wherex();
    int pos = 0;
    SetColor(5);
    int i;
    if(noidung.size()>=120)
    {
        for(i=120;i>=0;i--)
            if(noidung[i]==' ')
            break;
        string noidung1 = noidung.substr(0,i);
        string noidung2 = noidung.substr(i+1);
        gotoxy(33, 39);
        cout<<noidung1;
        gotoxy(34, 39);
        cout<<noidung2;
        gotoxy(x,y);
    }else
        gotoxy(33, 39);
        cout<<noidung;
	SetColor(0);

}
void ThongBaoGet(string noidung,char &pn)
{
    ThongBao(noidung);
    pn = getch();
    if(pn == -32) pn = getch();

}
bool CoHayKhong(string a)
{
    ThongBao(a + "Y/N: ");
    char pn;
    do
    {
        pn = getch();
        pn = toupper(pn);
        if(pn=='Y')
            return 1;
        if(pn=='N')
            return 0;
    }while(true);
    return 0;
}
void Caption(string caption[],int n,int x, int y)
{
    for(int i=0;i<n;i++)
    {
        gotoxy(x,y+i*2);
        cout<<caption[i];
    }
}

int XuLiPhimNong(int &chon,char &pn,int n,int x, int y,bool End)
{
        switch(pn)
        {
            case UP: if(chon > 0) chon--;gotoxy(x,y+2*chon);break;
            case DOWN: if(chon <n-1) chon ++ ;gotoxy(x,y+2*chon);break;
            case ENTER: if(chon <n-1) chon ++ ;gotoxy(x,y+2*chon);break;
        }
    if(PhimNong(pn, 1)==1)
        pn=17;
    return chon;
}
bool Thoat()
{
    ThongBao("Neu thoat du lieu se mat , ban co muon thoat (Y/N) :");
    int x=wherex(); int y = wherey(); char kt ;
    do
    {
        gotoxy(x,y);
        kt = getch(); kt = toupper(kt); cout<<kt;
        if(kt=='Y') return 1;
        if(kt=='N') return 0;
    }while(kt!='X'&& kt!='Y');
    return 0;

}

string searchEngine(NODE *root,DSNhanVien dsnv){
	string NvDuocChon = "";
	Answer ans;
	ClearFunction();
	SetColor(3);
	gotoxy(35, 9);
	cout << "TIM KIEM NHAN VIEN (SU DUNG MA NHAN VIEN HOAC TEN NHAN VIEN)";
	SetColor(0);
	DrawBorderList(35, 10, 1, 1, 100, 1);
	gotoxy(36,11);
	cout << "Search: ";
	char pn = 0;
	int x = 35;
	int y = 14;
	int dem = 0;
	int lpn = 0;
	int sl = 0;
	int chon = 0;
	string sosanh = "";
    while(true)
    {
        pn = getch();
        if(pn==-32)
        {
            pn = getch();
            lpn = 1;
        }
        pn = toupper(pn);

        /// in goi y

        if((KiTu(pn)==1 || pn == SPACEBAR) && lpn == 0)
        {
            ClearInsideBox(12, 34, 23, 106);
            gotoxy(43 + dem, 11);
            if(lpn != 1)
                cout << char(pn);
            dem++;
            sosanh = sosanh + char(pn);
            y = 14;
            NODE *prefixPosition = getPointerToEndOfPrefix(root, sosanh);
            gotoxy(x+65,14);
            cout << "[<=]";

            if(prefixPosition != NULL){
                ans.cnt = 0;
                printAllWordWithPrefix(prefixPosition,dsnv, sosanh, ans, x, y);
            }
            chon = 0;
        }
        /// xoa ki tu
        if(pn == BACKSPACE)
        {
            ClearInsideBox(12, 34, 23, 106);
            y = 14;
            sosanh = sosanh.substr(0, sosanh.size() - 1);
            dem--;
            if(dem >= 0){
                gotoxy(43 + dem, 11);
                cout << " ";
            }
            else
                dem = 0;
            NODE *prefixPosition = getPointerToEndOfPrefix(root, sosanh);
            if(prefixPosition != NULL && dem > 0){
                ans.cnt = 0;
                printAllWordWithPrefix(prefixPosition,dsnv, sosanh, ans, x, y);
                gotoxy(x+65,14);
                cout << "[<=]";
            }


        }
        /// di chuyen chon nhan vien
        if(lpn==1 && (pn == UP || pn==DOWN))
        {
            XuLiUpDown(chon,pn,ans.cnt,x+65,y);
        }
        if(pn==ENTER)
        {
        	ClearInsideBox(1, 34, 21, 160);// xoa man hinh chinh
           if(ans.cnt==0)
            return "";
           else
            return ans.kq[chon];
        }
        if(pn==ESC){
        	ClearInsideBox(1, 34, 21, 160);// xoa man hinh chinh
        	return "";
		}
            
	lpn = 0;
}
}
string searchEngineVT(NODEVT *root,NodeVatTu *dsvt){
	//string VTDuocChon = "";
	Answer ans;
	ClearFunction();
	SetColor(3);
	gotoxy(35, 9);
	cout << "TIM KIEM VAT TU (SU DUNG MA VAT TU HOAC TEN VAT TU)";
	SetColor(0);
	DrawBorderList(35, 10, 1, 1, 100, 1);
	gotoxy(36,11);
	cout << "Search: ";
	char pn = 0;
	int x = 35;
	int y = 14;
	int dem = 0;
	int lpn = 0;
	int sl = 0;
	int chon = 0;
	string sosanh = "";
    while(true)
    {
        pn = getch();
        if(pn==-32)
        {
            pn = getch();
            lpn = 1;
        }
        pn = toupper(pn);

        /// in goi y

        if((KiTu(pn)==1 || pn == SPACEBAR) && lpn == 0)
        {
            ClearInsideBox(12, 34, 23, 106);
            gotoxy(43 + dem, 11);
            if(lpn != 1)
                cout << char(pn);
            dem++;
            sosanh = sosanh + char(pn);
            y = 14;
            NODEVT *prefixPosition = getPointerToEndOfPrefixVT(root, sosanh);
            gotoxy(x+65,y);
            cout << "[<=]";

            if(prefixPosition != NULL){
                ans.cnt = 0;
                printAllWordWithPrefixVT(prefixPosition,dsvt, sosanh, ans, x, y);
            }
            chon = 0;
        }
        /// xoa ki tu
        if(pn == BACKSPACE)
        {
            ClearInsideBox(12, 34, 23, 106);
            y = 14;
            sosanh = sosanh.substr(0, sosanh.size() - 1);
            dem--;
            if(dem >= 0){
                gotoxy(43 + dem, 11);
                cout << " ";
            }
            else
                dem = 0;
            NODEVT *prefixPosition = getPointerToEndOfPrefixVT(root, sosanh);
            if(prefixPosition != NULL && dem > 0){
                ans.cnt = 0;
                printAllWordWithPrefixVT(prefixPosition,dsvt, sosanh, ans, x, y);
                gotoxy(x+65,14);
                cout << "[<=]";
            }


        }
        /// di chuyen chon nhan vien
        if(lpn==1 && (pn == UP || pn==DOWN))
        {
            XuLiUpDown(chon,pn,ans.cnt,x+65,y);
        }
        if(pn==ENTER)
        {
        	ClearInsideBox(1, 34, 21, 160);// xoa man hinh chinh
           if(ans.cnt==0)
            return "";
           else
            return ans.kq[chon];
        }
        if(pn==ESC){
        	ClearInsideBox(1, 34, 21, 160);// xoa man hinh chinh
        	return "";
		}
            
	lpn = 0;
	}
}

