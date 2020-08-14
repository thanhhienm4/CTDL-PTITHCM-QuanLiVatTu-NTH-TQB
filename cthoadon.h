#ifndef CTHOADON_H_INCLUDED
#define CTHOADON_H_INCLUDED
#include "header.h"
#include "nhanvien.h"
#include "iomanip"
#define SizeofCaptionCTHD 5
#define SizeofCaptionHD 5
#define SizeofSoHD 20
using namespace std ;

string captionCTHD[5] = {"Ten vat tu :",
                         "So luong :",
                         "Don gia :",
                         "VAT(%) :",
                         "Luu"};

string captionHD[5] = {"So hoa don :",
                        "Loai :",
                        "Ngay lap :",
                        "Nhap Vat Tu :",
                        "Luu" };
string captionSoHD[1] = {"Nhap so hoa don: "};


NodeHoaDon *SeachHoaDon1(DSNhanVien &dsnv,string &sohd)
{
    for(int i=0;i<dsnv.Size;i++)
    {
        NodeHoaDon * p = dsnv.DsNhanVien[i]->DSHoaDon;
        while(p!=NULL)
        {
            if(p->Data.SoHD==sohd)
                return p;
            else
                p=p->Next;
        }
    }
    return NULL;
}
void InNgay(Date ngay)
{
    int x = wherex(); int y = wherey();
    cout<<"  /  /    ";
    gotoxy(x,y)   ; cout<<ngay.Ngay;
    gotoxy(x+3,y) ; cout<<ngay.Thang;
    gotoxy(x+6,y) ; cout<<ngay.Nam;
}
void InCTHoaDon(int x,int y,CTHoaDon cthd, NodeVatTu *dsvt)
{
	NodeVatTu *vt = SearchVT(dsvt, cthd.MAVT);
	if(vt != NULL){
		Caption(captionCTHD,SizeofCaptionCTHD,x,y);
	    gotoxy(x+20,y);
	    cout<<vt->DATA.TENVT;
	    gotoxy(x+20,y+2);
	    cout<<cthd.SoLuong;
	    gotoxy(x+20,y+4);
	    cout<<cthd.DonGia;
	    gotoxy(x+20,y+6);
	    cout<<cthd.VAT;
	}
    

}
void InHoaDon(int x,int y,HoaDon hd, NhanVien nv)
{
	ClearInsideBox(23,39,161,206);
    Caption(captionHD,SizeofCaptionHD,x,y);
    gotoxy(x+20,y);
    cout<<hd.SoHD;
    gotoxy(x+20,y+2);
    cout<<hd.Loai;
    gotoxy(x+20,y+4);
    InNgay(hd.NgayLap);
	gotoxy(x,y+10);
	SetColor(5);
	cout << "Nguoi Lap: " << nv.HO + " " + nv.TEN;
	SetColor(0);
}
long double ThanhTien(HoaDon hd)
{
    long double TongTien = 0.0;
    NodeCTHoaDon * cthd = hd.DSCTHoaDon;
    while(cthd!=NULL)
    {
        TongTien += 1.0*cthd->Data.DonGia*cthd->Data.SoLuong *(100+cthd->Data.VAT)/100;
        cthd = cthd->Next;
    }
    return TongTien;
}

string KiemTraLoiCTHD(bool mode,string MAVTBD,long long SLBD,CTHoaDon cthd,NodeHoaDon *hd,NodeVatTu *dsvt)
{
    string loi = "";
    if(cthd.MAVT=="" || cthd.DonGia==0 || cthd.SoLuong==0)
        loi+= " Ban nhap chu du du lieu,";
    NodeVatTu * nodevattu = SearchVT(dsvt,cthd.MAVT);
    if(nodevattu==NULL)
        loi += " Ma vat tu khong co can nhap lai,";
    else
        if(nodevattu->DATA.SLT < cthd.SoLuong-SLBD && hd->Data.Loai=='X')
            loi += " So luong kha dung cua "+ nodevattu->DATA.TENVT +" " + to_string(nodevattu->DATA.SLT+SLBD)+",";
    if(mode==0)
    {
        if(SeachCTHoaDon(hd->Data.DSCTHoaDon,cthd.MAVT)!=NULL)
            loi +=  " Ma vat tu ban nhap da bi trung, can nhap lai,";
    }else
         if(SeachCTHoaDon(hd->Data.DSCTHoaDon,cthd.MAVT)!=NULL && cthd.MAVT!=MAVTBD)
            loi+= "Ma vat tu ban nhap da bi trung, can nhap lai,";
    return loi;
}
string KiemTraLoiHD(NodeHoaDon *hoadon,DSNhanVien dsnv,NodeVatTu *dsvt)
{
    string loi = "";
    NodeCTHoaDon * cthd = hoadon->Data.DSCTHoaDon;
    if(hoadon->Data.Loai=='X')
    while (cthd!=0)
    {
        NodeVatTu *vt = SearchVT(dsvt,cthd->Data.MAVT);
        if(cthd->Data.SoLuong>vt->DATA.SLT)
            loi += vt->DATA.TENVT + " kha dung " + to_string(vt->DATA.SLT) +" so voi " + to_string(cthd->Data.SoLuong)+ ",";
        cthd = cthd->Next;
    }
    if(hoadon->Data.DSCTHoaDon==NULL)
        loi+=  " Hoa don dang rong,";
    if(hoadon->Data.SoHD=="" || hoadon->Data.Loai=='\0')
        loi += " Thong tin ban nhap chu day du,";
    if(KiemTraNgay(hoadon->Data.NgayLap)==0)
        loi += " ngay lap hoa don khong hop le,";
     if(hoadon->Data.Loai !='N' && hoadon->Data.Loai!= 'X')
        loi += " Loai hoa don chi co the la (N/X),";
     if(SeachHoaDon1(dsnv,hoadon->Data.SoHD)!=NULL)
        loi += " Ma hoa don ban nhap da bi trung,";
     return loi;
}

void XuLiRight(NodeCTHoaDon *&cthd,NodeHoaDon *hoadon,int &chon )
{
    int i = 0;
    if(chon+10<SizeCTHoaDon(hoadon->Data.DSCTHoaDon))
    {
        while(i<10 && cthd!=NULL)
        {
            cthd = cthd->Next;
            i++;
        }
        chon+= 10;
    }
}
void XuLiLeft(NodeCTHoaDon *&cthd,NodeHoaDon *hoadon,int &chon)
{
    int i = 0;
    cthd = hoadon->Data.DSCTHoaDon;
    if(chon-10>=0)
    {
         while(i<chon-10)
        {
            cthd = cthd->Next;
            i++;
        }
        chon -= 10;
    }

}
void HienThiHoaDon(NodeCTHoaDon *CThd,NodeVatTu *dsvt, int bd, int Size)
{
	ClearInsideBox(11,30,35,160);
    DrawBorderList(35,10,11,1,5,1);
    DrawBorderList(40,10,11,5,20,1);
    SetColor(5);
    gotoxy(36,11); cout<<"STT";
    gotoxy(41,11); cout<<"Ten vat tu";
    gotoxy(61,11); cout<<"So luong ";
    gotoxy(81,11); cout<<"Don gia";
    gotoxy(101,11); cout<<"VAT(%)";
    gotoxy(121,11); cout<<"Thanh Tien";
    gotoxy(80, 35);
	cout << "[<-] Tro lai | Tiep Theo [->]";
	gotoxy(125, 35);
	cout << "Trang: " << bd/10 + 1 << "/" << Size/10 + 1;
    int i = 0;
    SetColor(0);
     //NodeVatTu * vattu = SearchVT(dsvt,cthd->Data.MAVT);
    NodeVatTu * vattu;
    NodeCTHoaDon * cthd = CThd;
    while (cthd!=NULL && i< 10)
    {

        vattu =  SearchVT(dsvt,cthd->Data.MAVT);
        gotoxy(36,13+i*2); cout<<i+bd+1;
        gotoxy(41,13+i*2); if(vattu!=NULL) cout<<vattu->DATA.TENVT;
        gotoxy(61,13+i*2); cout<<cthd->Data.SoLuong;
        gotoxy(81,13+i*2); cout<<cthd->Data.DonGia;
        gotoxy(101,13+i*2); cout<<cthd->Data.VAT;
        gotoxy(121,13+i*2); cout<<1.0*cthd->Data.DonGia*cthd->Data.SoLuong *(100+cthd->Data.VAT)/100;
        i++;
        cthd=cthd->Next;
        if(cthd == NULL){//
        	break;//
		}//
    }
}

char XuatHoaDon(NhanVien *nhanvien,NodeVatTu *dsvt,NodeHoaDon *hoadon,bool mode)
{
	gotoxy(60,5);
    cout<<"Nhan vien lap :" << nhanvien->HO << " "<<nhanvien->TEN;
    gotoxy(60,6);
    cout<<"Ma hoa don :" << hoadon->Data.SoHD;
    gotoxy(60,7);
    cout<<"Ngay lap :";InNgay(hoadon->Data.NgayLap);
    gotoxy(60,8);
    cout<<"Loai hoa don :";
    if(hoadon->Data.Loai=='N')
        cout<<"Nhap";
    else
        cout<<"Xuat";
    char pn = 17;
    gotoxy(111,33);
    cout<<"Tong ";
    gotoxy(121,33);
    cout<<ThanhTien(hoadon->Data);
    NodeCTHoaDon *cthd = hoadon->Data.DSCTHoaDon;
    int now = 0;
    while(true)
    {
        HienThiHoaDon(cthd,dsvt,now, SizeCTHoaDon(hoadon->Data.DSCTHoaDon));
        pn = getch();
        if(pn==-32)
        {
            pn = getch();
        }
        if(pn==ESC)
            return pn;
        if(mode == 0)
        if(pn == INS || pn == F2 || pn == DEL)
            return pn;
        switch(pn)
        {
            case KRIGHT:XuLiRight(cthd,hoadon,now); break;
            case KLEFT:XuLiLeft(cthd,hoadon,now); break;
        }

    }



}

void LuuCTHoaDon(char &pn,int &lpn, bool & End,bool mode,string MAVTBD,long long SLBD,CTHoaDon cthd,NodeHoaDon *hd,NodeVatTu *dsvt)
{
    if(pn==ENTER)
    {
        string Loi = KiemTraLoiCTHD(mode,MAVTBD,SLBD,cthd,hd,dsvt);
        if(Loi!="")
            ThongBaoGet(Loi,pn);
        else
            End = 1;

    }
}
void NhapCTHD(int x,int y,char &pn,bool mode,CTHoaDon &cthd,NodeHoaDon * &hd,NodeVatTu *dsvt,NodeVT *root)
{
    InCTHoaDon(x,y,cthd, dsvt);
    string MAVTBD = cthd.MAVT;
    long long SLBD = cthd.SoLuong;
    gotoxy(x+20,y);
    int chon = 0;
    pn = 17;
    int lpn = -1;
    bool End = 0;
    if(mode == 0)
        cthd.MAVT = searchEngineVT(root,dsvt);
    InCTHoaDon(x,y,cthd, dsvt);
    gotoxy(x+20+cthd.MAVT.size(),y);
    while(true)
    {
        if(pn == ESC)
            if(CoHayKhong("Ban co chac muon thoat "))
                return;
        if(PhimNong(pn,1)==1)
                XuLiPhimNong(chon,pn,SizeofCaptionCTHD,x+20,y,End);
        else
        {
            pn = getch();
            if(pn == -32)
            {
                pn = getch();
                lpn = 1;
            }
            if(pn == ESC)
                if(CoHayKhong("Ban co chac muon thoat "))
                    return ;
            if(chon==SizeofCaptionCTHD-1) LuuCTHoaDon(pn,lpn,End,mode,MAVTBD,SLBD,cthd,hd,dsvt);
            if(End==1) break;
            if(PhimNong(pn, 1)==1)
                XuLiPhimNong(chon,pn,SizeofCaptionCTHD,x+20,y,End);
        }


        switch(chon)
        {
            case 0:
                    {
                    	cthd.MAVT = searchEngineVT(root,dsvt);
	                    NodeVatTu *vt = SearchVT(dsvt, cthd.MAVT);
	                    if(vt != NULL){
	                    	InCTHoaDon(x,y,cthd, dsvt); gotoxy(x+20+vt->DATA.TENVT.size(),y);
						}
	                    break;
					}
            case 1:NhapChuoiSo(cthd.SoLuong,x+20,y+chon*2,10,pn);break;
            case 2:NhapChuoiSo(cthd.DonGia,x+20,y+chon*2,10,pn);break;
            case 3:NhapChuoiSo(cthd.VAT,x+20,y+chon*2,10,pn);break;
            case 4:LuuCTHoaDon(pn,lpn,End,mode,MAVTBD,SLBD,cthd,hd,dsvt);break;
        }
    }
}
void ThemMoiCTHoaDon(NodeHoaDon *&hoadon,NodeVatTu * dsvt,NODEVT *root)
{
    int  x = 167 ; int y = 26;
    char pn = 17;
            ClearInsideBox(23,39,167,206);//Xoa man hinh edit
            Caption(captionCTHD,SizeofCaptionCTHD,x,y);
            CTHoaDon cthd;
            NhapCTHD(x,y,pn,0,cthd,hoadon,dsvt,root);
            if(pn==ENTER)
            {
                NodeCTHoaDon *newnode = new NodeCTHoaDon();
                newnode->Data = cthd;
                InsertCTHoaDon(hoadon->Data.DSCTHoaDon,newnode);
                ThongBao("Da them vao hoa don.");
            }
}
void ChinhSuaCTHoaDon(NodeHoaDon *&hoadon,NodeVatTu *dsvt,NODEVT * root)
{
    int  x = 167 ; int y = 26;
    char pn = 17;
    ClearInsideBox(23,39,167,206);//Xoa man hinh edit
    Caption(captionCTHD,SizeofCaptionCTHD,x,y);

    NodeCTHoaDon * nodecthd ;
    string mavt;
    while(true)
    {
        mavt = searchEngineVT(root,dsvt);
        if(mavt=="")
            if(CoHayKhong("ban muon thoat hay khong")==1)
                return;
        nodecthd = SeachCTHoaDon(hoadon->Data.DSCTHoaDon,mavt);
        if(nodecthd==NULL)
            ThongBao("Vat tu khong co trong hoa don, vui long nhap lai");
        else
            break;

    }

    CTHoaDon cthd = nodecthd->Data;
    NhapCTHD(x,y,pn,1,cthd,hoadon,dsvt,root);
    if(pn==ENTER)
        {
            nodecthd->Data = cthd;
            ThongBao("Du lieu da duoc cap nhat.");
        }

}
void DeleleCTHoaDon(NodeHoaDon *&hoadon,NodeVatTu *dsvt,NODEVT *root)
{
    string mavt;
    NodeCTHoaDon * cthd;
    while(true)
    {
        mavt = searchEngineVT(root,dsvt);
        if(mavt=="")
            return ;
        cthd = SeachCTHoaDon(hoadon->Data.DSCTHoaDon,mavt);
        if(cthd==NULL)
            ThongBao("Vat tu khong co trong hoa don, vui long nhap lai");
        else
            break;
    }
    NodeVatTu *vt = SearchVT(dsvt, cthd->Data.MAVT);
    if(vt != NULL)
    	if(CoHayKhong("Ban muon xoa "+ vt->DATA.TENVT + " ra khoi hoa don hien tai ")==1){
    		RemoveCTHoaDon(hoadon->Data.DSCTHoaDon,cthd->Data.MAVT);
    		ThongBao("Da xoa khoi hoa don.");
		}
    

}
void ChiTietHoaDon(int x, int y,NodeVatTu *dsvt,NodeHoaDon *hoadon,char pn,NODEVT *root,NhanVien *&nhanvien )
{

    if(pn==ENTER)
    {
        ClearFunction();
        ThemMoiCTHoaDon(hoadon,dsvt,root);
        while(true)
        {
            if(!(pn==ESC || pn == INS || pn == F2 || pn == DEL))
            {
                pn = getch();
                if(pn==-32)
                pn = getch();
            }
            switch(pn)
            {
                case INS: ThemMoiCTHoaDon(hoadon,dsvt,root);break;
                case DEL: DeleleCTHoaDon(hoadon,dsvt,root);break;
                case F2 : ChinhSuaCTHoaDon(hoadon,dsvt,root);break;
                case ESC: if(CoHayKhong("Ban co chac muon thoat? ")) InHoaDon(167,26,hoadon->Data, *nhanvien); return ;

            }
            pn = XuatHoaDon(nhanvien,dsvt,hoadon,0);
        }

    }
    //Caption()
    //in lai hd ;

}

void NhapNgay(int x, int y,Date &ngay,char &pn)
{
	int chon = 2;
    gotoxy(x,y);
    InNgay(ngay);
	while(true)
	{

		switch(chon)
		{
		    case 0: NhapChuoiSo(ngay.Ngay,x,y,2,pn);break;
		    case 1: NhapChuoiSo(ngay.Thang,x+3,y,2,pn);break;
		    case 2: NhapChuoiSo(ngay.Nam,x+6,y,4,pn);break;
		}
		if(PhimNong(pn,1 )==1)
        {
            if(pn==ESC||pn ==ENTER || pn ==UP || pn == DOWN)
                return ;
            if(pn==KRIGHT)
                if(chon<2) chon++;
            if(pn==KLEFT)
                if(chon>0) chon--;
        }

	}

}

void LuuHoaDon(char &pn,int&lpn,bool &End,NodeHoaDon *hoadon,DSNhanVien &dsnv,NodeVatTu *dsvt)
{

    if(pn==ENTER)
    {

        string Loi = KiemTraLoiHD(hoadon,dsnv,dsvt);
        if(Loi!="")
            ThongBaoGet(Loi,pn);

        else
            End = 1;
    }

}
void NhapHoaDon(int x, int y,char &pn,bool mode,NodeHoaDon *hoadon,DSNhanVien dsnv,NodeVatTu *dsvt,NODEVT *root,NhanVien *&nhanvien)
{
	bool check = true;
    InHoaDon(x,y,hoadon->Data, *nhanvien);
    gotoxy(x+20,y);
    int chon = 0;
    pn = 17;
    int lpn = -1;
    bool End = 0;
    while(true)
    {
        if(pn == ESC)
            if(CoHayKhong("Ban co chac muon thoat ")){
            	check = false;
            	break;
			}
        if(PhimNong(pn, 1)==1)
                XuLiPhimNong(chon,pn,SizeofCaptionHD,x+20,y,End);
        else
        {
            pn = getch();
            if(pn == -32)
            {
                pn = getch();
                lpn =1 ;
            }
            if(pn == ESC)
                if(CoHayKhong("Ban co chac muon thoat ")){
            	check = false;
            	break;
			}
            if(chon==3) {
                    ChiTietHoaDon(x+20,y+chon*2,dsvt,hoadon,pn,root,nhanvien);
                    InHoaDon(x,y,hoadon->Data, *nhanvien);
            }
            if(chon==SizeofCaptionHD-1)
                LuuHoaDon(pn,lpn,End,hoadon,dsnv,dsvt);
            if(End==1) return;
            if(PhimNong(pn, 1)==1)
                XuLiPhimNong(chon,pn,SizeofCaptionHD,x+20,y,End);

        }
        switch(chon)
        {
            case 0:NhapChuoi(hoadon->Data.SoHD,x+20,y+chon*2,SizeofSoHD,pn,lpn,1);break;
            case 1:NhapKiTu(hoadon->Data.Loai,x+20,y+chon*2,1,pn,lpn,2);break;
            case 2:NhapNgay(x+20,y+chon*2,hoadon->Data.NgayLap,pn);break;
            case 3:ChiTietHoaDon(x+20,y+chon*2,dsvt,hoadon,pn,root,nhanvien);break;
            case 4:LuuHoaDon(pn,lpn,End,hoadon,dsnv,dsvt);break;

        }
         if(End==1) return ;
    }
    if(check == false){
    	return ;
	}
}
void CapNhatSLT(NodeHoaDon *hd,NodeVatTu *dsvt)
{
    NodeCTHoaDon * cthd = hd->Data.DSCTHoaDon;
    while(cthd!=NULL)
      {
        NodeVatTu * vattu = SearchVT(dsvt,cthd->Data.MAVT);
        if(vattu!=NULL)
        if(hd->Data.Loai=='N')
            vattu->DATA.SLT += cthd->Data.SoLuong;
        else
            vattu->DATA.SLT -= cthd->Data.SoLuong;
        cthd = cthd->Next;
        if(cthd == NULL){
        	break;
		}
      }
}
void ThemMoiHoaDon(NhanVien *&nhanvien,NodeVatTu * dsvt,DSNhanVien dsnv,NODEVT *root)
{
    int  x = 167 ; int y = 26;
    char pn = 17;
    ClearInsideBox(23,39,167,206);
    Caption(captionHD,SizeofCaptionCTHD,x,y);
    NodeHoaDon *newhoadon = new NodeHoaDon;
    NhapHoaDon(x,y,pn,0,newhoadon,dsnv,dsvt,root,nhanvien);
    if(pn==ENTER)
    {
        CapNhatSLT(newhoadon,dsvt);
        InsertHoaDon(nhanvien->DSHoaDon,newhoadon);
        ThongBao("Da lap hoa don thanh cong.");
        XuatHoaDon(nhanvien,dsvt,newhoadon,1);
    }else
    {
        delete(newhoadon);////
        return;
    }
}
void ReadDataHoaDon(DSNhanVien &ds){
    ifstream file;
    file.open("DataHoaDon.txt",ios::in);
    int sonv ;
    file >> sonv;
    for(int i=0;i<sonv;i++)
    {
        string manv;
        file >> manv;
        int pos = SeachNV(ds,manv);
        if(pos!=-1)
        {
            NhanVien *nv = ds.DsNhanVien[pos];
            int slhd;
            file >> slhd;
            for(int j=0;j<slhd;j++)
            {
                NodeHoaDon *hd = new NodeHoaDon;
                file >> hd->Data.SoHD;
                file >> hd->Data.Loai;
                file >> hd->Data.NgayLap.Ngay;
                file >> hd->Data.NgayLap.Thang;
                file >> hd->Data.NgayLap.Nam;

                int slvt;
                file >> slvt;
                for(int x =0;x<slvt;x++)
                {
                    NodeCTHoaDon *cthd = new NodeCTHoaDon ;
                    file >> cthd->Data.MAVT;
                    file >> cthd->Data.DonGia;
                    file >> cthd->Data.SoLuong;
                    file >> cthd->Data.VAT;
                    InsertCTHoaDon(hd->Data.DSCTHoaDon,cthd);
                }
                InsertHoaDon(nv->DSHoaDon,hd);
            }
        }
    }

}
int slNVcoHoaDon(DSNhanVien &ds){
	int dem = 0;
	for(int i = 0; i< ds.Size; i++){
		if(ds.DsNhanVien[i]->DSHoaDon != NULL){
			dem++;
		}
	}
	return dem;
}
void WriteDataHoaDon(DSNhanVien &ds){
	ofstream write;
	write.open("DataHoaDon.txt",ios::trunc);//
	int n = slNVcoHoaDon(ds);
	write << n;
	write << "\n";
	for(int i = 0; i < ds.Size; i++){
        if(ds.DsNhanVien[i]!=NULL)
        {
            NodeHoaDon * roothd = ds.DsNhanVien[i]->DSHoaDon;
            if(roothd != NULL){
                write << ds.DsNhanVien[i]->MANV<<endl;
                int p = SizeHoaDon(roothd);
                write << p;
                write << "\n";
                while(roothd != NULL){
                    write << roothd->Data.SoHD << " ";
                    write << roothd->Data.Loai << " ";
                    write << roothd->Data.NgayLap.Ngay << " ";
                    write << roothd->Data.NgayLap.Thang << " ";
                    write << roothd->Data.NgayLap.Nam << "\n";
                    NodeCTHoaDon * rootcthd = roothd->Data.DSCTHoaDon; /// loi
                    int d = SizeCTHoaDon(rootcthd);
                    write << d << "\n";
                    while(rootcthd != NULL){
                        write << rootcthd->Data.MAVT << " ";
                        write << rootcthd->Data.DonGia << " ";
                        write << rootcthd->Data.SoLuong << " ";
                        write << rootcthd->Data.VAT << "\n";
                        rootcthd = rootcthd->Next;
                    }
                    roothd = roothd->Next;
                }
            }

        }

	}
	write.close();
}

#endif // CTHOADON_H_INCLUDED
