#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include "mylib1.h"
#include "function.h"
#include<vector>
using namespace std;
const int TOADOX = 0;
const int TOADOY = 2;
const int CHIEUNGANG = 200;
const int CHIEUDOC = 40;
#define MAX 10000
const int so_item = 5;
const int dong =5;
const int cot = 5 ;
const int Up = 72;
const int Down = 80;

void DrawBorder(int toaDoX, int toaDoY, int chieuNgang, int chieuDoc);
void RemoveScroll();
void fullScreen();
string CenterTextInSpace(string str, int wide);
void DrawBorderList(int toaDoX, int toaDoY, int soDong, int soCot, int chieuNgangO, int chieuDocO);

void Normal () { // Mau khi o khong duoc chon
	SetColor(0);
	SetBGColor(15);
}
void HighLight () { // Mau khi o duoc chon
	SetColor(0);
	SetBGColor(14);
}
class MainProject
{
private:
	enum Mode
	{
		VatTu,
		NhanVien,
		HoaDon,
		ThongKe,
		TopDoanhThu,
	};
	Mode mode;
	enum {
		BATDAUX = 3
	};
	int keyhit;
	void FirstCt();
	void DrawMenu();
	void WriteCenterText(string str, int toaDoX, int toaDoY);
	void WriteSelection();
	void ChangeSelect(string &current, string change);
	void ChangeMode();
	void ChangeCT();
	void EscCT();
	char choice[2][15] = { "Thoat","Huy" };
	char thoatCT[10][78] =
	{
		"",
		"",
		"",
		"",
		"Ban muon thoat chuong trinh ?",
		"",
		"",
		"",
		"",
		"",
	};
public:
	MainProject();
	~MainProject();
};
//#include "giaodien.h"
//#include"mylib.h"
void fullScreen() // Toan man hinh
{
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}
void RemoveScroll() // Xoa cuon
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(hstdout, csbi.dwSize);

	HWND x = GetConsoleWindow();
	ShowScrollBar(x, SB_BOTH, FALSE);
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

void ClearInsideBox(int top, int down,int left, int right) // Xoa trang man hinh
{
	string blankFill;
	blankFill.resize(right-left-2);//
	SetBGColor(15);
	for (int i = top+1; i < down; i++)
	{
		gotoxy(i,left+1);//
		cout << blankFill;
	}
}
void ClearInsideBox2() // Xoa trang man hinh
{
	string blankFill;
	int num = 41;
	blankFill.resize(CHIEUNGANG - num, ' ');// 
	SetBGColor(15);
	for (int i = 0; i < CHIEUDOC- num; i++)
	{
		gotoxy(TOADOX + num, TOADOY + 1 + i);// 
		cout << blankFill;
	}
}
void MainProject::FirstCt()
{
	system("color f0");
	fullScreen();
	RemoveScroll();
	DrawBorder(TOADOX, TOADOY, CHIEUNGANG, CHIEUDOC);
	for (int i = 0; i < CHIEUDOC; i += (CHIEUDOC / 5)) {
		DrawBorder(TOADOX, TOADOY + i, 20, CHIEUDOC / 5);
	}
	for (int i = CHIEUDOC / 5; i < CHIEUDOC; i += CHIEUDOC / 5) {
		gotoxy(TOADOX, TOADOY + i);
		cout << char(195);
		gotoxy(TOADOX + 20, TOADOY + i);
		cout << char(180);
	}
	// Tao option cho tung selection vattu, nhanvien, hoadon, chitiethoadon...
	DrawBorder(TOADOX + 160, TOADOY, 40, CHIEUDOC);// Ve khung thong bao
	//
	DrawBorder(TOADOX + 160, TOADOY, 40, CHIEUDOC/2);
	//
	gotoxy(TOADOX + 20, TOADOY);
	cout << char(194);
	gotoxy(TOADOX + 20, TOADOY + CHIEUDOC);
	cout << char(193);
	gotoxy(0, CHIEUDOC + 2);
}
void MainProject::WriteCenterText(string str, int toaDoX, int toaDoY)
{
	gotoxy(toaDoX, toaDoY);
	cout << CenterTextInSpace("", 19);
	gotoxy(toaDoX, toaDoY + 1);
	cout << CenterTextInSpace("", 19);
	gotoxy(toaDoX, toaDoY + 2);
	cout << CenterTextInSpace("", 19);
	gotoxy(toaDoX, toaDoY + 3);
	cout << CenterTextInSpace(str, 19);
	gotoxy(toaDoX, toaDoY + 4);
	cout << CenterTextInSpace("", 19);
	gotoxy(toaDoX, toaDoY + 5);
	cout << CenterTextInSpace("", 19);
	gotoxy(toaDoX, toaDoY + 6);
	cout << CenterTextInSpace("", 19);
	gotoxy(toaDoX, toaDoY + 7);
}
//START XU lY GIAO DIEN TUNG CHUC NANG
void DrawDetail(string s1, string s2, string s3, string s4, string s5){
		int WIDE = 20;
		SetColor(5);
		SetBGColor(15);
		int i = 0;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace(s1, WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace(s2, WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace(s3, WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace(s4, WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace(s5, WIDE - 1);
		SetColor(0);
		SetBGColor(15);
}
// START VAT TU
void DrawDetailVatTu(){
		int WIDE = 20;
		SetColor(5);
		SetBGColor(15);
		int i = 0;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("STT", WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("MA VAT TU", WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("TEN VAT TU", WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("SO LUONG TON", WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("DON VI ", WIDE - 1);
		SetColor(0);
		SetBGColor(15);
}

// END VAT TU

// START NHAN VIEN
void DrawDetailNhanvien(){
		int WIDE = 20;
		SetColor(5);
		SetBGColor(15);
		int i = 0;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("STT", WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("MA VAT TU", WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("TEN VAT TU", WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("SO LUONG TON", WIDE - 1);
		i += 20;
		gotoxy(36 + i, 16);
		cout << CenterTextInSpace("DON VI ", WIDE - 1);
		SetColor(0);
		SetBGColor(15);
}
// END NHAN VIEN

// START HOADON

// END HOADON

// START THONGKE

	// MODE 1 : Theo ngay 
	
	// MODE 2 : Theo thang trong nam
	
// END THONGKE
// START TOP DOANH THU

// END TOP DOANH THU

//END XU LY GIAO DIEN TUNG CHUC NANG
void MainProject::WriteSelection()
{
	string select;
	select.resize(18, ' ');
	string select1 = "Vat Tu", select2 = "Nhan Vien",
		select3 = "Hoa Don", select4 = "Thong Ke", select5 = "Top Doanh Thu";
	//SetColor(0);
	//SetBGColor(15);
	Normal();
	int i = 0;
	this->ChangeSelect(select, select1);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select2);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select3);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select4);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select5);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;
	HighLight();
	switch (mode)
	{
	case MainProject::VatTu:
		this->ChangeSelect(select, select1);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1);
		break;
	case MainProject::NhanVien:
		this->ChangeSelect(select, select2);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5));
		break;
	case MainProject::HoaDon:
		this->ChangeSelect(select, select3);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 2);
		break;
	case MainProject::ThongKe:
		this->ChangeSelect(select, select4);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 3);
		break;
	case MainProject::TopDoanhThu:
		this->ChangeSelect(select, select5);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 4);
		break;
	default:
		break;
	}
	Normal();
	//SetColor(7);
	//SetBGColor(0);
	gotoxy(TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 5);
}
void MainProject::ChangeSelect(string& current, string change)
{
	current.clear();
	current.resize(change.size(), ' ');
	current = change;
}

void MainProject::ChangeMode()
{
	if (keyhit == 224) {
		keyhit = _getch();
		switch (keyhit)
		{
		case DOWN:
			switch (mode)
			{
			case MainProject::VatTu:
				mode = NhanVien;
				break;
			case MainProject::NhanVien:
				mode = HoaDon;
				break;
			case MainProject::HoaDon:
				mode = ThongKe;
				break;
			case MainProject::ThongKe:
				mode = TopDoanhThu;
				break;
			case MainProject::TopDoanhThu:
				mode = VatTu;
				break;
			default:
				break;
			}
			break;
		case UP:
			switch (mode)
			{
			case MainProject::VatTu:
				mode = TopDoanhThu;
				break;
			case MainProject::NhanVien:
				mode = VatTu;
				break;
			case MainProject::HoaDon:
				mode = NhanVien;
				break;
			case MainProject::ThongKe:
				mode = HoaDon;
				break;
			case MainProject::TopDoanhThu:
				mode = ThongKe;
				break;
			}
		}
	}
}

void MainProject::ChangeCT()
{
	if (keyhit == ENTER) {
		switch (mode)
		{
		case MainProject::VatTu:
		{
			SetColor(0);
			SetBGColor(7);
			this->WriteCenterText("Vat Tu", TOADOX + 1, TOADOY + 1);
			Normal();
			ClearInsideBox2();
			//
			DrawBorderList(35, 15, 11, 5, 20, 1);
			DrawDetail("STT", "Ma vat tu", "Ten vat tu", "Don vi tinh", "So luong ton");
			Caption(captionVT, 4, 167, 26);
			NhapVT(167,26);
			HighLight();
			this->WriteCenterText("Vat Tu", TOADOX + 1, TOADOY + 1);
			Normal();
			ClearInsideBox2();
		}
			break;
		case MainProject::NhanVien:
		{
			SetColor(0);
			SetBGColor(7);
			this->WriteCenterText("Nhan Vien", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5));
			Normal();
			//
			DrawBorderList(35, 15, 11, 5, 20, 1);
			DrawDetial("STT", "Ma nhan vien", "Ho", "Ten", "Gioi tinh");
			HighLight();
			this->WriteCenterText("Nhan Vien", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5));
			Normal();
			ClearInsideBox2();
		}
			break;
		case MainProject::HoaDon:
		{
			SetColor(0);
			SetBGColor(7);
			this->WriteCenterText("Hoa Don", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 2);
			Normal();
			//
			HighLight();
			this->WriteCenterText("Hoa Don", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 2);
			Normal();
		}
			break;
		case MainProject::ThongKe:
		{
			SetColor(0);
			SetBGColor(7);
			this->WriteCenterText("Thong Ke", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 3);
			Normal();
			//
			HighLight();
			this->WriteCenterText("Thong Ke", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 3);
			Normal();
			ClearInsideBox2();
		}
			break;
		case MainProject::TopDoanhThu:
		{
			SetColor(0);
			SetBGColor(7);
			this->WriteCenterText("Top Doanh Thu", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 4);
			Normal();
			//
			HighLight();
			this->WriteCenterText("Top Top Doanh", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 4);
			Normal();
			ClearInsideBox2();
		}
			break;
		}
	}
}

void MainProject::DrawMenu(){
	// Huong dan
	int position = 1;
	string str ;
	str = "**HUONG DAN**";
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (40 - str.size())/2);
	cout << str;
	position += 2;
	str = "Nhan Enter de chon";
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (40 - str.size())/2);
	cout << str;
	str = "Nhan ESC de thoat khoi CT hien tai";
	position += 2;
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (40 - str.size())/2);
	cout << str;
	str = "Nhan Insert de them";
	position += 2;
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (40 - str.size())/2);
	cout << str;
	str = "Nhan Delete de xoa";
	position += 2;
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (40 - str.size())/2);
	cout << str;
	str = "Nhan Backspace de xoa ky tu";
	position += 2;
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (40 - str.size())/2);
	cout << str;
	// Thong Bao
	position = 1;
	gotoxy(TOADOX + 161, TOADOY + CHIEUDOC/2 + 1 +position);
	str = "**THONG BAO**";
	cout << CenterTextInSpace("", (40 - str.size())/2);
	cout << str;
}

void MainProject::EscCT()
{
	if (keyhit == ESC)
	{
		SetColor(15);
		SetBGColor(0);
		//int i = DrawNoti(thoatCT, choice, 2);
		int i = 0;
		if (i == 0)
		{
			system("color f0");
			clrscr();
			exit(0);
		}
		else
			ClearInsideBox2();
	}
}

MainProject::MainProject()
{

	mode = VatTu;
	keyhit = 0;
	this->FirstCt();
	while (1)
	{
		this->DrawMenu();
		this->ChangeMode();
		this->WriteSelection();
		this->ChangeCT();
		this->EscCT();
		keyhit = _getch();
	}
}
MainProject::~MainProject()
{
}





