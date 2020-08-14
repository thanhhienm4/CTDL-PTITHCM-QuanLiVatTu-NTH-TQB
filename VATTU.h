#ifndef DSVATTU_H_INCLUDED
#define DSVATTU_H_INCLUDED

#include <iostream>
#include "header.h"
#include "editor.h"
#include <string.h>
#include "ThanhTimKiem.h"

#define SizeofMAVT 20
#define SizeofTENVT 20
#define SizeofDVT 20
#define SizeofCaptionVT 5
using namespace std ;

string captionVT[5] = {"Ma vat tu :",
                       "Ten vat tu :",
                       "Don vi tinh :",
                       "So luong ton :",
					   "Luu : "};

VatTu str[5000];
void Traversal(NodeVatTu *Root, int &j)//
{
    if(Root == NULL)
        return ;

    Traversal(Root->LEFT, j);

    VatTu tmp = Root->DATA;
    str[j++] = tmp;
    Traversal(Root->RIGHT, j);
}
bool VatTuDaLapHD(string mavt,DSNhanVien dsnv)
{
    for(int i=0;i<dsnv.Size;i++)
    {
        NodeHoaDon *hd = dsnv.DsNhanVien[i]->DSHoaDon;
        while(hd!=NULL)
          {
              NodeCTHoaDon *cthd = hd->Data.DSCTHoaDon;
              while(cthd!=NULL)
              {
                    if(cthd->Data.MAVT == mavt)
                        return true;
                    cthd = cthd->Next;

              }
              hd = hd->Next;
          }
    }
    return false;
}
void InVatTu(int x,int y,VatTu vt)
{
    Caption(captionVT,SizeofCaptionVT,x,y);
    gotoxy(x+20,y);
    cout<<vt.MAVT;
    gotoxy(x+20,y+2);
    cout<<vt.TENVT;
    gotoxy(x+20,y+4);
    cout<<vt.DVT;
    gotoxy(x+20,y+6);
    cout<<vt.SLT;
    gotoxy(x,y);
}
string KiemTraLoiVT(bool mode, VatTu vattu,NodeVatTu *root)
{
    string loi = "";
    if(vattu.DVT=="" || vattu.MAVT=="" || vattu.DVT=="")
        loi+= " Ban nhap khong du noi dung,";
    if(SearchVT(root,vattu.MAVT)!=NULL && mode == 0)
        loi+= " Ma vat tu da bi trung,";
    return loi;
}

void LuuVatTu(char &pn,int &lpn, bool & End,bool mode, VatTu vattu,NodeVatTu *root)
{
        if(pn==ENTER)
        {
            string Loi = KiemTraLoiVT(mode,vattu,root);
            if(Loi!="")
                ThongBaoGet(Loi,pn);
            else
            {
                End = 1;
            }
        }

}

void NhapVT(int x,int y,bool mode, VatTu &vattu,NodeVatTu *&root,char &pn)
{
    InVatTu(x,y,vattu);
    gotoxy(x+20,y);
    int chon = 0;
     pn = 17;
    int lpn = -1;
    bool End = 0;
    while(true)
    {
        if(pn == ESC)
            if(Thoat()==1)
                return;
        if(PhimNong(pn, 1)==1)
                XuLiPhimNong(chon,pn,SizeofCaptionVT,x+20,y,End);
        else
        {
            pn = getch();
            if(pn == -32)
            {
                pn = getch();
                lpn = 1;
            }
            if(pn == ESC)
                if(Thoat()==1)
                    return ;
            if(chon==SizeofCaptionVT-1) LuuVatTu(pn,lpn,End,mode,vattu,root);
            if(End==1)break;
            if(PhimNong(pn, 1)==1)
                XuLiPhimNong(chon,pn,SizeofCaptionVT,x+20,y,End);

        }
        if(End==1) break;
        switch(chon)
        {
            case 0: if(mode==1)
                    {
                        gotoxy(x+20,y+chon*2);cout<<vattu.MAVT;
                        NhapPhimNong(pn,lpn);break;
                    }
                    else
                        NhapChuoi(vattu.MAVT,x+20,y+chon*2,SizeofMAVT,pn,lpn,3);break;
            case 1: NhapChuoi(vattu.TENVT,x+20,y+chon*2,SizeofTENVT,pn,lpn,4);break;
            case 2: NhapChuoi(vattu.DVT,x+20,y+chon*2,SizeofDVT,pn,lpn,4);break;
            case 3: if(mode==1)
                        {
                            gotoxy(x+20,y+chon*2);cout<<vattu.SLT;
                            NhapPhimNong(pn,lpn);break;
                        }
                    else

                        NhapChuoiSo(vattu.SLT,x+20,y+chon*2,10,pn);break;
            case 4: LuuVatTu(pn,lpn,End,mode,vattu,root);

        }
        if(End==1)
            break;

    }
}
int ThemMoiVatTu(NodeVatTu *&root, NODEVT *cur)
{
    int x = 167; int y =26;

    char pn;
    do
    {
        pn = 17;
        ClearInsideBox(23,39,161,206);//Xoa man hinh edit
        Caption(captionVT,SizeofCaptionVT,x,y);

        VatTu vattu ;
        NhapVT(x,y,0,vattu,root,pn);
        if(pn == ENTER)
            {
                NodeVatTu * Node = new NodeVatTu();
                Node->DATA = vattu;
                InsertVT(root,Node);
                addWordVT1(cur, vattu.MAVT);
                addWordVT2(cur, vattu.MAVT, vattu.TENVT);
                return 1;
            }

    }while(pn!=ESC);
    return 0;
}

int ChinhSuaVatTu(NodeVatTu *&root,NodeVatTu *&Vattucu,NODEVT *cur)
{

    int x = 167; int y =26;
    ClearInsideBox(23,39,161,206);//Xoa man hinh edit
    Caption(captionVT,SizeofCaptionVT,x,y);
    char pn = 17;
    VatTu vattu = Vattucu->DATA;
    NhapVT(x,y,1,vattu,root,pn);
    if(pn == ENTER)
    {
        removeWordVT(cur, Vattucu->DATA.MAVT, 0, Vattucu->DATA.MAVT.size());//
    	removeWordVT(cur, Vattucu->DATA.TENVT, 0, Vattucu->DATA.TENVT.size());//
		Vattucu->DATA = vattu;
        addWordVT1(cur, vattu.MAVT);//
        addWordVT2(cur, vattu.MAVT, vattu.TENVT);//
        ThongBao("Du lieu da duoc cap nhat");
        return 1;
    }
    return 0;
}
int deletePrefixVatTu(NodeVatTu* ds, string mavt, NODEVT* root){
	PTRVatTu currentVT = SearchVT(ds, mavt);
	if(currentVT == NULL){
		return 0;
	}
	removeWordVT(root, currentVT->DATA.MAVT, 0, currentVT->DATA.MAVT.size());
	removeWordVT(root, currentVT->DATA.MAVT, 0, currentVT->DATA.MAVT.size());
	return 1;
}
void swap(VatTu &a, VatTu &b)
{
    VatTu t = a;
    a = b;
    b = t;
}


int partition (VatTu arr[], int low, int high)
{
    string pivot = arr[high].TENVT; // chon goc la dinh cuoi    
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && arr[left].TENVT < pivot) left++;
        while(right >= left && arr[right].TENVT > pivot) right--;
        if (left >= right) break;
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
    swap(arr[left], arr[high]);
    return left;
}

void quickSort(VatTu arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
string MaVT = "", TenVT = "", Dvt = "";
long long Slt = 0;

void getDataVT(int &i, string line, string &newString){
	while(line[i] != ','){
		newString += line[i];
		i++;
	}
}

void ReadDataVT(string line){
	string newString = "";
	int i = 0;
	getDataVT(i, line, newString);
	MaVT = newString;
	newString = "";
	i++;
	getDataVT(i, line, newString);
	TenVT = newString;
	newString = "";
	i++;
	getDataVT(i, line, newString);
	Dvt = newString;
	newString = "";
	i++;
	getDataVT(i, line, newString);
	string tmp = newString;
	Slt = atoi(tmp.c_str());

}

void ReadFileVT(NodeVatTu* &ds, NODEVT *root){
	ifstream read;
	string line;
	read.open("DataVatTu.txt",ios::in);
	string s = "";
	while(getline(read, line)){
		if(line[0] == '-'){
			break;
		}
		MaVT = "";
		TenVT = "";
		Dvt = "";
		Slt = 0;
		ReadDataVT(line);
		VatTu newVatTu;
		newVatTu.TENVT = TenVT;
		newVatTu.MAVT = MaVT;
		newVatTu.SLT = Slt;
		newVatTu.DVT = Dvt;
		InsertVT(ds, CreateNodeVatTu(newVatTu));
		addWordVT1(root, MaVT);
		addWordVT2(root, MaVT, TenVT);
	}
	read.close();

}
void WriteDataVatTu(NodeVatTu *&ds){
	ofstream write;
	write.open("DataVatTu.txt",ios::trunc);
	int sizeVT = SizeVT(ds);
	if(ds==NULL)
        return ;
    Queue <NodeVatTu*> q;
	q.Push(ds);
	while(!q.Empty()){
		NodeVatTu* cur = q.Front();
		q.Pop();
		write << cur->DATA.MAVT;
		write << ",";
		write << cur->DATA.TENVT;
		write << ",";
		write << cur->DATA.DVT;
		write << ",";
		write << cur->DATA.SLT;
		write << ",\n";
		if(cur->LEFT != NULL){
			q.Push(cur->LEFT);
		}
		if(cur->RIGHT != NULL){
			q.Push(cur->RIGHT);
		}
	}
	write << "-";
	write.close();
}
void PrintdsVatTu(PTRVatTu &ds, NODEVT *root,NodeVatTu *dsvt, DSNhanVien dsnv){//
	int beg = 0;
	Traversal(ds,beg);
	quickSort(str, 0, SizeVT(ds) - 1);
	string duocChon = "";
	int nextX = 0;
	int stt = 1;
	int trang = 1;
	int sotrang = 1;
	int sl = SizeVT(ds);
	if(sl <= 10){
		trang = 1;
		sotrang = 1;
	}
	else{
		sotrang = sl / 11 + 1;
	}
	while(1){
		Print:
		beg = 0;//
		Traversal(ds,beg);//
		quickSort(str, 0, SizeVT(ds) - 1);//
		sl = SizeVT(ds);
		nextX = 0;
		if(trang ==1 ){
			stt = 1;
		}
		else{
			stt = 10 * (trang - 1) + 1;
		}
		WriteCenterText("DANH SACH VAT TU", 80, 5, 0);
		DrawBorderList(35, 10, 11, 5, 20, 1);
		DrawDetail("STT", "Ma vat tu", "Ten vat tu", "Don vi tinh", "So luong ton", "");
		for(int i = 0 + (trang - 1) * 10; i < 10 + (trang - 1) * 10 && i < sl; i++){
			gotoxy(36 + nextX, 13 + (i % 10) * 2);
			cout << stt;
			stt++;
			nextX += 20;
			gotoxy(36 + nextX, 13 + (i % 10) * 2);
			cout << str[i].MAVT;
			nextX += 20;
			gotoxy(36 + nextX, 13 + (i % 10) * 2);
			cout << str[i].TENVT;
			nextX += 20;
			gotoxy(36 + nextX, 13 + (i % 10) * 2);
			cout << str[i].DVT;
			nextX += 20;
			gotoxy(36 + nextX, 13 + (i % 10) * 2);
			cout << str[i].SLT;
			nextX = 0;

		}
		gotoxy(80, 36);
		cout << "[<-] Tro lai | Tiep Theo [->]";
		gotoxy(125, 34);
		cout << "Trang: " << trang << "/" << sotrang;
		int c = 0;
		do{
			c = getch();
		}while(c != KLEFT && c != KRIGHT && c!= ESC && c != DEL && c != INS && c != F2);
		if(c == ESC){
			break;
		}
		else if(c == KLEFT){
			if(sotrang > 1 && trang > 1){
				ClearFunction();
				WriteCenterText("DANH SACH VAT TU", 80, 5, 0);
				DrawBorderList(35, 10, 11, 5, 20, 1);
				DrawDetail("STT", "Ma vat tu", "Ten vat tu", "Don vi tinh", "So luong ton", "");
				stt -= (10 + stt % 10);
				stt += 1;
				trang--;
				goto Print;
			}
			else{
				stt = 1;
			}
		}
		else if(c == KRIGHT){
			if(sotrang > 1 && trang < sotrang){
				ClearFunction();
				WriteCenterText("DANH SACH VAT TU", 80, 5, 0);
				DrawBorderList(35, 10, 11, 5, 20, 1);
				DrawDetail("STT", "Ma vat tu", "Ten vat tu", "Don vi tinh", "So luong ton", "");
				trang++;
				goto Print;
			}
			else{
				stt = sl / 10;
				stt = stt * 10 + 1;
			}
		}
		else if(c == F2){
			duocChon = "";
			duocChon = searchEngineVT(root,dsvt);
			PTRVatTu curVatTu = SearchVT(ds, duocChon);

			if(curVatTu != NULL){
				int x = ChinhSuaVatTu(ds, curVatTu, root);
				beg = 0;
				Traversal(ds,beg);
				quickSort(str, 0, SizeVT(ds) - 1);
				WriteDataVatTu(ds);
				if(x != 0){
					ClearInsideBox(23,39,161,206);//Xoa man hinh edit
					ThongBao("Da sua du lieu thanh cong");
				}

			}
			else{
				ClearInsideBox(23,39,161,206);//Xoa man hinh edit
				ThongBao("Vat tu khong ton tai trong danh sach");
			}
			sleep(1);
			ClearFunction();
		}
		else if (c == INS){
			int x =ThemMoiVatTu(ds, root);

			beg = 0;
			Traversal(ds,beg);
			quickSort(str, 0, SizeVT(ds) - 1);

			WriteDataVatTu(ds);
			if (x == 1){

				ThongBao("Da them vao danh sach");
			}

			sleep(1);
			stt = 1;
			ClearFunction();
		}
		else if (c == DEL){
			duocChon = "";
			duocChon = searchEngineVT(root,dsvt);

			if(VatTuDaLapHD(duocChon,dsnv)==1){
				ThongBao("Khong the xoa vat tu ");
			}
            else
            {
            	NodeVatTu * vt = SearchVT(dsvt, duocChon);
            	if(vt != NULL){
            		if(CoHayKhong("Ban co chac muon xoa " + vt->DATA.TENVT + " ") ){
            			int x = deletePrefixVatTu(ds, duocChon, root);
		                RemoveVT(ds, duocChon);
		                WriteDataVatTu(ds);
		                if(x == 1){
		                    ClearInsideBox(23,39,161,206);//Xoa man hinh edit
		                    ThongBao("Da xoa khoi danh sach");
		                }
					}
	                
				}
            	
            }

		}
	}
}
#endif // DSVATTU_H_INCLUDED
