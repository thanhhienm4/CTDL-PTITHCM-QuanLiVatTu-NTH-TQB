#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#pragma once
#include "VATTU.h"
#include "nhanvien.h"
#include "nhap.h"
#include <sstream>
#include <iomanip>
using namespace std ;
void InDoanhThu(DSNhanVien &dsnv, int x, int y, int Nam, char &pn);
void ThongKeDT(DSNhanVien &dsnv)
{
    string CaptionDT [2] = {"Nam","ThongKe"};
    long long Nam = 0;
    int chon = 0;
    char pn = 17;
    int x = 167 ; int y = 26;
    bool End = 0;
    Caption(CaptionDT,2,x,y);
    gotoxy(x+20,y);

    while(true)
    {

		if(pn == ESC)
            return;
        if(PhimNong(pn,1)==1)
            XuLiPhimNong(chon,pn,2,x+20,y,End);
        else
        {
            pn = getch();
            if(pn == -32)
                pn = getch();
            if(pn == ESC)
                return ;
            if(chon==1){
            	 InDoanhThu(dsnv,x,y,Nam,pn);

			}
            if(PhimNong(pn,1)==1){
            	XuLiPhimNong(chon,pn,2,x+20,y,End);
			}


        }
        switch(chon)
        {
            case 0:NhapChuoiSo(Nam,x+20,y+chon*2,4,pn);break;
            case 1:
				InDoanhThu(dsnv,x,y,Nam,pn);
        }

    }
}
int Compare(HoaDon a,HoaDon b,int mode)
{
    switch(mode)
    {
        case 1: return (SoSanhNgay(a.NgayLap,b.NgayLap));
        case 2: if(a.SoHD == b.SoHD)
                    return 0;
                else
                {
                    return a.SoHD > b.SoHD ? 1 : -1;
                }
        case 3: if(ThanhTien(a) == ThanhTien (b))
                    return 0;
                else
                {
                    return ThanhTien(a) > ThanhTien(b) ? 1: -1;
                }
    }
    return 1;
}

void Partition(HoaDon arr[],int left, int right, int &i, int &j,int mode)
{
    i = left;
    j = right;
    if(i+1==j && Compare(arr[i],arr[j],mode)<0)
    {
        i==j;
        return ;
    }
    if(left<right)
    {

        int mid = (left+right)/2;
        HoaDon pivot = arr[mid];
        while(i<j)
        {
            while(Compare(arr[i],pivot,mode)<0)
                i++;
            while(Compare(arr[j],pivot,mode)>0)
                j--;
            if(i<j)
            {
                swap(arr[i],arr[j]);
                i++;
                j--;
            }
        }
    }
}
void QuickSort(HoaDon arr[],int n,int mode)
{
    int i,j;
    stack <int> s1;
    stack <int> s2;
    s1.push(0);
    s2.push(n-1);
    int b = 0;
    while(!s1.empty())
    {
        int left = s1.top(); s1.pop();
        int right = s2.top(); s2.pop();
        Partition(arr,left,right,i,j,mode);
        if(left < i )
        {
            if(left<j)
            {
                s1.push(left);
                s2.push(j);
            }
        }
        if(j<right)
        {
            if(i<right)
            {
                s1.push(i);
                s2.push(right);
            }
        }
    }
}
void InDoanhThu(DSNhanVien &dsnv, int x,int y,int Nam,char &pn)
{

    if(pn==ENTER)
    {
        // tinh doanh thu
        long double DT[13];
        for(int i=1;i<13;i++)
            DT[i]=0.0;
        for(int i=0;i<dsnv.Size;i++)
        {
            NodeHoaDon * hd = dsnv.DsNhanVien[i]->DSHoaDon;
            while(hd!=NULL)
            {
                if(hd->Data.NgayLap.Nam == Nam)
                {
                    DT[hd->Data.NgayLap.Thang] += ThanhTien(hd->Data);
                }
                hd = hd->Next;
            }
        }
        long double DTNam = 0.0;
        for(int i=1;i<13;i++)
            DTNam += DT[i];
		ClearInsideBox(3, 34, 21, 160);
        gotoxy(75,4);
        cout<<"BANG THONG KE DOANH THU NAM "<<Nam;
        DrawBorderList(70,6,14,2,20,1);
        SetColor(5);
        gotoxy(71,7);
        cout<<"Thang";
        gotoxy(91,7);
        cout<<"Doanh thu";
        SetColor(0);
        for(int i=1;i<=12;i++)
        {
            gotoxy(71,7+i*2);
            cout<<i;
            gotoxy(91,7+i*2);
            cout<<fixed<<setprecision(3)<<1.0*DT[i];

        }
        gotoxy(71,7+2*13);
        cout<<"Tong";
        gotoxy(91,7+2*13);
        cout<<fixed<<setprecision(3)<<1.0*DTNam;
    }
    //Chi so in ra trong mang doanh thu;
    // in ra man hinh
}
void InThongKeHD(DSNhanVien &dsnv,HoaDon dshd[],int bd, int n)//
{
    ClearInsideBox(3, 34, 21, 160);
	DrawBorderList(28,10,11,1,6,1);
    DrawBorderList(34,10,11,3,21,1);
    DrawBorderList(97,10,11,1,41,1);
    DrawBorderList(138,10,11,1,21,1);
    ClearInsideBox(6, 18, 161, 206); // Xoa man hinh huong dan
    string str;
    str = "*Nhan 1 de sap xep theo ngay";
    gotoxy(161, 8);
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	str = "*Nhan 2 de sap xep theo ma";
	gotoxy(161, 12);
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
	str = "*Nhan 3 de sap xep theo gia tri";
	gotoxy(161, 16);
	cout << CenterTextInSpace("", (47 - str.size())/2);
	cout << str;
    ///
    SetColor(5);
    gotoxy(30,11);
    cout<<"STT";
    gotoxy(36,11);
    cout<<"So hoa don";
    gotoxy(57,11);
    cout<<"Ngay lap";
    gotoxy(80,11);
    cout<<"Loai";
    gotoxy(99,11);
    cout<<"Ho va ten ";
    gotoxy(139,11);
    cout<<"Thanh tien";
    gotoxy(80, 35);
	cout << "[<-] Tro lai | Tiep Theo [->]";
	gotoxy(125, 34);
	cout << "Trang: " << bd/10 + 1 << "/" << n/10 + 1;
    SetColor(0);


    for(int i=0;i<10 && i+bd <n ;i++)
    {
        gotoxy(30,i*2+13);
        cout<<i+bd+1 ;
        gotoxy(36,i*2+13);
        cout<<dshd[i+bd].SoHD;
        gotoxy(57,i*2+13);
        InNgay(dshd[i+bd].NgayLap);
        gotoxy(80,i*2+13);
        cout<<dshd[i+bd].Loai;
        gotoxy(99,i*2+13);
        NhanVien *nv = FindNVBySoHD(dsnv,dshd[i+bd].SoHD);
        if(nv!=NULL)
           {
               cout<<nv->HO<<" "<<nv->TEN;
           }

        gotoxy(139,i*2+13);
        cout << fixed << setprecision(3) << ThanhTien(dshd[i + bd]);

    }


}
int SoHoaDonTTG(DSNhanVien &dsnv,HoaDon dshd[],Date NgayBD,Date NgayKT) // tinh so hoa don lap trong jthoi gian
{
    int cnt = 0;
    for(int i=0;i<dsnv.Size;i++)
    {
        NodeHoaDon *hd = dsnv.DsNhanVien[i]->DSHoaDon;
        while(hd!=NULL)
        {
            if(SoSanhNgay(hd->Data.NgayLap,NgayBD)>=0 && SoSanhNgay(hd->Data.NgayLap,NgayKT)<=0)
            {
                dshd[cnt] = hd->Data;
                cnt ++;

            }
            hd = hd->Next;
        }
    }
    return cnt;

}
void KieuThongKeHD(DSNhanVien &dsnv,NodeVatTu *dsvt,Date NgayBD,Date ngayKT, char &pn)
{


    if(pn==Enter)
    {
        if(SoSanhNgay(NgayBD,ngayKT) > 0 || KiemTraNgay(NgayBD)==0 || KiemTraNgay(ngayKT)==0)
        {
            ThongBaoGet("Ngay ban nhap chua hop li",pn);
            return;
        }

        HoaDon dshd[1000];
        int n = SoHoaDonTTG(dsnv,dshd,NgayBD,ngayKT);
        if(n == 0){
        	ThongBao("Khong ton tai hoa don nao trong khoang thoi gian nay");
		}
        QuickSort(dshd,n,1);
        gotoxy(60,4);
        cout<<"BANG LIET KE CAC HOA DON DUOC LAP TRONG KHOANG THOI GIAN";
        gotoxy(70,5);
        cout<<"Tu Ngay "; InNgay(NgayBD) ; cout<<" Den Ngay "; InNgay(ngayKT);
        InThongKeHD(dsnv,dshd,0,n);
        int now = 0;
        char key;
        while(true)
        {
            //ClearInsideBox(3, 34, 21, 160);
			gotoxy(60,4);
	        cout<<"BANG LIET KE CAC HOA DON DUOC LAP TRONG KHOANG THOI GIAN";
	        gotoxy(70,5);
	        cout<<"Tu Ngay "; InNgay(NgayBD) ; cout<<" Den Ngay "; InNgay(ngayKT);
			key = getch();
            if(key==-32)
                key = getch();
            switch(key)
            {
                case KLEFT :if(now-10>=0) now-= 10; break;
                case KRIGHT :if(now+10<n) now+=10; break;
                case 49 :QuickSort(dshd,n,1); break;
                case 50 :QuickSort(dshd,n,2); break;
                case 51 :QuickSort(dshd,n,3); break;
                case ESC :return;
            }
            ClearInsideBox(11, 33, 28, 160);
            InThongKeHD(dsnv,dshd,now,n);
        }

    }
}
void ThongKeHD(DSNhanVien &dsnv,NodeVatTu *dsvt)
{
    Date NgayBD;
    Date NgayKT;
    string CaptionTKHD [3] = {"Ngay bat dau","Ngay ket thuc","Thong ke"};
    int x = 167 ;int y = 26;
    Caption(CaptionTKHD,3,x,y);
    gotoxy(x+20,y);
    InNgay(NgayBD);
    gotoxy(x+20,y+2);
    InNgay(NgayKT);
    gotoxy(x+20,y);
    int chon = 0;
    char pn = 17;
    bool End = 0;
    while(true)
    {
        if(pn == ESC){
            ClearInsideBox(36, 39, 33, 159);// Xoa man hinh thong bao;
            return;
    	}
        if(PhimNong(pn,1)==1)
            XuLiPhimNong(chon,pn,3,x,y,End);
        else
        {
            pn = getch();
            if(pn == -32)
            {
                pn = getch();
            }
            if(pn == ESC)
                    return ;
            if(chon == 2) {
                    gotoxy(x+20,y+chon*2);
                    KieuThongKeHD(dsnv,dsvt,NgayBD,NgayKT,pn);
            }
            if(End==1)break;
            if(PhimNong(pn, 1)==1)
                XuLiPhimNong(chon,pn,3,x,y,End);

        }switch(chon)
        {
            case 0:NhapNgay(x+20,y+chon*2,NgayBD,pn);break;
            case 1:NhapNgay(x+20,y+chon*2,NgayKT,pn);break;
            case 2:gotoxy(x+20,y+chon*2);KieuThongKeHD(dsnv,dsvt,NgayBD,NgayKT,pn);break;
        }
    }

}
void InHoaDonTheoSoHD(DSNhanVien &dsnv, NodeVatTu *dsvt){
	string curhd = "";
	ClearInsideBox(1, 34, 21, 159);// xoa man hinh chinh
	Caption(captionSoHD, 1, 167, 26);
	char pn = 17;
	int lpn = -1;
	NhapChuoi(curhd,187,26,SizeofSoHD,pn,lpn,1);
	NhanVien *nv = FindNVBySoHD(dsnv,curhd);
	if(nv != NULL){
		NodeHoaDon * tmp = SeachHoaDon(nv->DSHoaDon, curhd);
		XuatHoaDon(nv,dsvt,tmp,1);
	}
	else{
		ThongBao("So hoa don khong ton tai");
		sleep(1);
	}
}


void LayDuLieuTDT(string mavt[],NodeVatTu *dsvt)
{
    Queue <NodeVatTu *> qvt;
    if(dsvt==NULL)
       return;
    qvt.Push(dsvt);
    int i = 0;
    while(!qvt.Empty())
    {
        NodeVatTu * Tem = qvt.Front();
            qvt.Pop();
        mavt[i++]=Tem->DATA.MAVT;

        if(Tem->LEFT!=NULL)
           {
               qvt.Push(Tem->LEFT);
           }
        if(Tem->RIGHT!=NULL)
           {
               qvt.Push(Tem->RIGHT);
           }
    }
}
void TinhDoanhThu(string mavt[],long double  dtvt[],int n,DSNhanVien dsnv,Date NgayBD, Date NgayKT)
{
    for(int i=0;i<dsnv.Size;i++)
    {
        NodeHoaDon * hd = dsnv.DsNhanVien[i]->DSHoaDon;
        while(hd!=NULL)
        {
            if(hd->Data.Loai=='X' && SoSanhNgay(NgayBD,hd->Data.NgayLap)<=0 && SoSanhNgay(NgayKT,hd->Data.NgayLap)>=0)
            {
                NodeCTHoaDon * cthd = hd->Data.DSCTHoaDon;
                while (cthd!=NULL)
                {
                    for(int j=0;j<n;j++)
                    {
                        if(mavt[j]==cthd->Data.MAVT)
                        {
                            dtvt[j]+= 1.0*cthd->Data.DonGia * cthd->Data.SoLuong*(100+cthd->Data.VAT)/100;
                            break;
                        }

                    }
                    cthd = cthd->Next;

                }

            }
             hd = hd->Next;

        }
    }
}
void TopDoanhThuVT(NodeVatTu *dsvt, DSNhanVien dsnv,Date NgayBD, Date NgayKT,char pn)
{
    if(pn==ENTER)
    {
        if(SoSanhNgay(NgayBD,NgayKT) > 0 || KiemTraNgay(NgayBD)==0 || KiemTraNgay(NgayKT)==0)
        {
            ThongBaoGet("Ngay ban nhap chua hop li",pn);
            return;
        }
		string mavt[MaxVT];
        long double  dtvt[MaxVT];
        for(int i=0;i<MaxVT;i++)
            dtvt[i] = 0;
        int slvt = SizeVT(dsvt);
        LayDuLieuTDT(mavt,dsvt);
        TinhDoanhThu(mavt,dtvt,slvt,dsnv,NgayBD,NgayKT);

        for(int i=0;i<slvt;i++)
        {
            for(int j=i+1;j<slvt;j++)
            {
                if(dtvt[i] < dtvt[j])
                    {
                        swap(dtvt[i],dtvt[j]);
                        swap(mavt[i],mavt[j]);
                    }
            }
        }

        // in ra man hinh
        ClearInsideBox(3, 34, 21, 160);
        gotoxy(60,5);
        cout<<"TOP  10 BAN CHAY "<<"TU NGAY "; InNgay(NgayBD); cout <<" DEN NGAY "; InNgay(NgayKT);
        SetColor(5);
		DrawBorderList(45,10,11,1,5,1);
		gotoxy(46,11);
		cout << "STT";
        DrawBorderList(50,10,11,3,21,1);
        gotoxy(51,11);
        cout<<"Ma vat tu";
        gotoxy(72,11);
        cout<<"Ten vat tu";
        gotoxy(93,11);
        cout<<"Doanh thu";
        SetColor(0);
        for(int i=0;i<10 && i<slvt;i++)
        {
        	gotoxy(46, 13 + i * 2);
            cout << i + 1; 
			gotoxy(51,13+i*2);
            cout<<mavt[i];
            gotoxy(72,13+i*2);
            cout<<SearchVT(dsvt,mavt[i])->DATA.TENVT;
            gotoxy(93,13+i*2);
            cout << fixed << setprecision(3) << dtvt[i];
        }
        while(true)
        {
            pn = getch();
            if(pn==ESC)
                return ;
        }
    }

}

void ThongKeTDT(DSNhanVien &dsnv,NodeVatTu *dsvt)
{
    Date NgayBD;
    Date NgayKT;
    string CaptionTKHD [3] = {"Ngay bat dau","Ngay ket thuc","Thong ke"};
    int x = 167 ;int y = 26;
    Caption(CaptionTKHD,3,x,y);
    gotoxy(x+20,y);
    InNgay(NgayBD);
    gotoxy(x+20,y+2);
    InNgay(NgayKT);
    gotoxy(x+20,y);
    int chon = 0;
    char pn = 17;
    bool End = 0;
    while(true)
    {
        if(pn == ESC)
            {
                ClearInsideBox(36, 39, 33, 159);// Xoa man hinh thong bao;
                return;
            }
        if(PhimNong(pn,1)==1)
            XuLiPhimNong(chon,pn,3,x,y,End);
        else
        {
            pn = getch();
            if(pn == -32)
            {
                pn = getch();
            }
            if(pn == ESC)
                return ;
            if(chon == 2) {
                    gotoxy(x+20,y+chon*2);
                    TopDoanhThuVT(dsvt,dsnv,NgayBD,NgayKT,pn);
            }
            if(End==1)break;
            if(PhimNong(pn, 1)==1)
                XuLiPhimNong(chon,pn,3,x,y,End);

        }switch(chon)
        {
            case 0:NhapNgay(x+20,y+chon*2,NgayBD,pn);break;
            case 1:NhapNgay(x+20,y+chon*2,NgayKT,pn);break;
            case 2:ClearInsideBox(1, 34, 21, 160); gotoxy(x+20,y+chon*2);TopDoanhThuVT(dsvt,dsnv,NgayBD,NgayKT,pn);break;
        }
    }

}
#endif // FUNCTION_H_INCLUDED
