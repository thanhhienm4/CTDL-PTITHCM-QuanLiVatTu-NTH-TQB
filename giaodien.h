#include <iostream>
#include <conio.h>
#include <stdio.h>
#include<unistd.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include "mylib1.h"
#include "function.h"
#include "editor.h"
#include "nhanvien.h"
#include "cthoadon.h"
#include "VATTU.h"
#include<vector>
using namespace std;
#define MAX 10000

void DrawBorder(int toaDoX, int toaDoY, int chieuNgang, int chieuDoc);
void fullScreen();
string CenterTextInSpace(string str, int wide);
void DrawBorderList(int toaDoX, int toaDoY, int soDong, int soCot, int chieuNgangO, int chieuDocO);

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
	int keyhit;
	void FirstCt();
	void DrawMenu();
	void WriteSelection();
	void ChangeSelect(string &current, string change);
	void ChangeMode();
	void ChangeCT(NodeVatTu *dsvt, DSNhanVien &dsnv, NODEVT *rootVT, NODE *root);
	void EscCT();
public:
	MainProject();
	~MainProject();
};
void MainProject::FirstCt()
{
	system("color f0");
	fullScreen();
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
	DrawBorder(TOADOX + 160, TOADOY, 47, CHIEUDOC);// Ve khung chuc nang
	//
	DrawBorder(TOADOX + 160, TOADOY, 47, CHIEUDOC/2);
	//
	DrawBorder(TOADOX + 20 , TOADOY + 35,CHIEUNGANG - 20 - 47, 0); // Ve khung thong bao
	//
	gotoxy(TOADOX + 20, TOADOY);
	cout << char(194);
	gotoxy(TOADOX + 20, TOADOY + CHIEUDOC);
	cout << char(193);
	gotoxy(0, CHIEUDOC + 2);
}

int chooseOptionTK(int choose, string s1, string s2){
	choose = 1;
	char key;
	DrawBorder(30, 10, 40, 2);
	gotoxy(31,11);
	HighLight();
	cout << CenterTextInSpace("", (39 - s1.size())/2);
	string a1((38 - s1.size())/2, ' ');
	cout << s1 + a1;
	Normal();
	DrawBorder(100, 10, 40, 2);
	gotoxy(101,11);
	cout << CenterTextInSpace("", (39 - s2.size())/2);
	string a2((38 - s1.size())/2, ' ');
	cout << s2 + a2;
	gotoxy(61, 11);
	while(1){
		key = getch();
		if(key == -32){
			key = getch();
		}
		if(key == KRIGHT){
			if(wherex() < 72 ){
				gotoxy(31,11);
				Normal();
				cout << CenterTextInSpace("", (39 - s1.size())/2);
				cout << s1 + a1;
				gotoxy(101, 11);
				HighLight();
				cout << CenterTextInSpace("", (39 - s2.size())/2);
				cout << s2 + a2;
				choose = 2;
			}
		}
		if(key == KLEFT){
			if(wherex() > 72 ){
				gotoxy(101,11);
				Normal();
				cout << CenterTextInSpace("", (39 - s2.size())/2);
				cout << s2 + a2;
				gotoxy(31, 11);
				HighLight();
				cout << CenterTextInSpace("", (39 - s1.size())/2);
				cout << s1 + a1;
				choose = 1;
			}
		}
		if(key == ENTER){
			break;
		}
		if(key == ESC){
			choose = 0;
			break;
		}
	}
	Normal();
	return choose;
}
void MainProject::WriteSelection()
{
	string select;
	select.resize(18, ' ');
	string select1 = "Vat Tu", select2 = "Nhan Vien",
		select3 = "Hoa Don", select4 = "Thong Ke", select5 = "Top Doanh Thu";
	Normal();
	int i = 0;
	this->ChangeSelect(select, select1);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i, 0);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select2);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i, 0);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select3);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i, 0);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select4);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i, 0);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select5);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i, 0);
	i += CHIEUDOC / 5;
	HighLight();
	switch (mode)
	{
	case MainProject::VatTu:
		this->ChangeSelect(select, select1);
		WriteCenterText(select, TOADOX + 1, TOADOY + 1, 0);
		break;
	case MainProject::NhanVien:
		this->ChangeSelect(select, select2);
		WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5), 0);
		break;
	case MainProject::HoaDon:
		this->ChangeSelect(select, select3);
		WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 2, 0);
		break;
	case MainProject::ThongKe:
		this->ChangeSelect(select, select4);
		WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 3, 0);
		break;
	case MainProject::TopDoanhThu:
		this->ChangeSelect(select, select5);
		WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 4, 0);
		break;
	default:
		break;
	}
	Normal();
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

void MainProject::ChangeCT(NodeVatTu *dsvt, DSNhanVien &dsnv, NODEVT *rootVT, NODE *root)
{

	if (keyhit == ENTER) {
		switch (mode)
		{
		case MainProject::VatTu:
		{
			SetColor(0);
			SetBGColor(10);
			WriteCenterText("Vat Tu", TOADOX + 1, TOADOY + 1, 0);
			Normal();
			ClearFunction();
			gotoxy(64,5);
			WriteCenterText("DANH SACH VAT TU", 80, 5, 0);
			DrawBorderList(35, 10, 11, 5, 20, 1);
			DrawDetail("STT", "Ma vat tu", "Ten vat tu", "Don vi tinh", "So luong ton", "");
            PrintdsVatTu(dsvt,rootVT,dsvt,dsnv);//
			//
			HighLight();
			WriteCenterText("Vat Tu", TOADOX + 1, TOADOY + 1, 0);
			Normal();
			ClearFunction();
		}
			break;
		case MainProject::NhanVien:
		{
			SetColor(0);
			SetBGColor(10);
			WriteCenterText("Nhan Vien", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5), 0);
			Normal();
			ClearFunction();
			WriteCenterText("DANH SACH NHAN VIEN", 80, 5, 0);
			//
			DrawBorderList(35, 10, 11, 5, 20, 1);
			DrawDetail("STT", "Ma nhan vien", "Ho", "Ten", "Gioi tinh", "");
			printdsNhanVien(dsnv, root,dsnv);
			//
			HighLight();
			WriteCenterText("Nhan Vien", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5), 0);
			Normal();
			ClearFunction();
		}
			break;
		case MainProject::HoaDon:
		{
			SetColor(0);
			SetBGColor(10);
			WriteCenterText("Hoa Don", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 2, 0);
			Normal();
			ClearFunction();
			WriteCenterText("HOA DON CHI TIET", 80, 5, 0);
			int choose = 0;
			choose = chooseOptionTK(choose, "LAP HOA DON", "IN HOA DON");
			if(choose == 1){
				string curNV = "";
				curNV = searchEngine(root,dsnv);
				int posNV = SeachNV(dsnv, curNV);
				if(posNV != -1){
					ThemMoiHoaDon(dsnv.DsNhanVien[posNV], dsvt,dsnv,rootVT);
					WriteDataVatTu(dsvt);
					WriteDataHoaDon(dsnv);//
				}
			}
			else if(choose == 2){
				ClearInsideBox(1, 34, 21, 159);// xoa man hinh chinh
				InHoaDonTheoSoHD(dsnv, dsvt);
				ClearInsideBox(1, 34, 21, 159);
			}

			//
			DrawBorderList(35, 10, 11, 6, 20, 1);
			DrawDetail("STT", "Ma vat tu", "Ten VT", "So luong", "Don gia", "VAT");
			HighLight();
			WriteCenterText("Hoa Don", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 2, 0);
			Normal();
			ClearFunction();
			//
		}
			break;
		case MainProject::ThongKe:
		{
			SetColor(0);
			SetBGColor(10);
			WriteCenterText("Thong Ke", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 3, 0);
			Normal();
			ClearFunction();
			WriteCenterText("THONG KE CAC HOA DON TRONG MOT KHOANG THOI GIAN", 70, 5, 1);
			//
			int choose = 0;
			choose = chooseOptionTK(choose, "THONG KE DOANH THU TUNG THANG", "THONG KE HOA DON THEO THOI GIAN");
			if(choose == 1){
				ClearInsideBox(3, 34, 21, 159);// xoa danh sach
				ThongKeDT(dsnv);
				ClearInsideBox(1, 34, 21, 159);// xoa danh sach
			}
			else if(choose == 2){
				ClearInsideBox(1, 34, 21, 159);// xoa danh sach
				ThongKeHD(dsnv, dsvt);
				ClearFunction();
				ClearInsideBox(1, 34, 21, 159);// xoa danh sach
			}


			HighLight();
			WriteCenterText("Thong Ke", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 3, 0);
			Normal();
			ClearFunction();
		}
			break;
		case MainProject::TopDoanhThu:
		{
			SetColor(0);
			SetBGColor(10);
			WriteCenterText("Top Doanh Thu", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 4, 0);
			Normal();
			ClearFunction();
			WriteCenterText("THONG KE TOP 10 DOANH THU THEO THOI GIAN", 70, 5, 1);
			ThongKeTDT(dsnv,dsvt);
			HighLight();
			WriteCenterText("Top Doanh Thu", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 4, 0);
			Normal();
			ClearFunction();
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
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	position += 2;
	str = "Nhan Enter de chon";
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	str = "Nhan Esc de thoat khoi CT hien tai";
	position += 2;
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	str = "Nhan Insert de them";
	position += 2;
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	str = "Nhan Delete de xoa";
	position += 2;
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	str = "Nhan F2 de sua";
	position += 2;
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	str = "Nhan Backspace de xoa ky tu";
	position += 2;
	gotoxy(TOADOX + 161, TOADOY + 3 + position);
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	// Thong Bao
	position = 1;
	gotoxy(TOADOX + 161, TOADOY + CHIEUDOC/2 + 1 +position);
	str = "**CHUC NANG**";
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	gotoxy(TOADOX + 21, TOADOY + 37);
	str = "THONG BAO: ";
	cout << str;
}

void MainProject::EscCT()
{
	if (keyhit == ESC)
	{
		Normal();
		gotoxy(33,39);
		int i = 1 ;
		SetColor(5);
		cout << "Ban co muon thoat chuong trinh? Y/N: ";
		SetColor(0);
		int key = getch();

		if(key == -32){
			key = getch();
			if(key == 89 || key == 121){
				i = 0;
			}
		}
		else if(key == 89 || key == 121){
			i = 0;
		}

		if (i == 0)
		{
			system("color f0");
			clrscr();
			exit(0);
		}
		else
			ClearFunction();
	}
}

MainProject::MainProject()
{
	DSNhanVien dsnv;
	NodeVatTu * dsvt = NULL;
	NODEVT *rootVT = newNodeVT();
    ReadFileVT(dsvt, rootVT);
    NODE *root = newNode();
	ReadFileNhanVien(dsnv, root);
	ReadDataHoaDon(dsnv);
	mode = VatTu;
	keyhit = 0;
	this->FirstCt();
	while (1)
	{
		this->DrawMenu();
		this->ChangeMode();
		this->WriteSelection();
		this->ChangeCT(dsvt, dsnv, rootVT, root);
		this->EscCT();
		keyhit = _getch();
	}
	ClearVT(dsvt);
	ClearNV(dsnv);
	ClearPrefixTreeVT(rootVT);
	ClearPrefixTreeNV(root);
}
MainProject::~MainProject()
{
}





