#ifndef KHAIBAO_H_INCLUDED
#define KHAIBAO_H_INCLUDED
#include "header.h"
#include "editor.h"
#define MaxVT 5000
#define MaxNV 500
#define MAXTrie 128
#define MAXSearch 50000
struct VatTu
{
    string MAVT;
    string TENVT;
    string DVT;
    long long SLT;
    VatTu()
    {
        MAVT = "";
        TENVT = "";
        DVT = "";
        SLT = 0;
    }

};

struct NodeVatTu
{
    VatTu DATA;
    NodeVatTu *RIGHT;
    NodeVatTu *LEFT;
    NodeVatTu()
    {
        RIGHT = NULL;
        LEFT = NULL;
    }

};
typedef struct NodeVatTu *PTRVatTu;
NodeVatTu* SearchVT(NodeVatTu *Root,string  &mavt)
{
    NodeVatTu* Temp = Root;
    while(Temp != NULL){
        if(Temp->DATA.MAVT == mavt)
            return Temp;
        else if(Temp->DATA.MAVT < mavt)
                    Temp = Temp->RIGHT;
                else
                    Temp = Temp->LEFT;
    }
    return Temp;
}

bool EmptyVT(NodeVatTu *Root)
{
    if(Root == NULL)
        return 1;
    else
        return 0;
}

void InsertVT(NodeVatTu *&Root,NodeVatTu* Node)
{
    if(Root == NULL)
    {
        Root = Node;
    }else
    {
        NodeVatTu * Temp = Root;
        while(Temp != NULL)
        {
            if(Node->DATA.MAVT > Temp->DATA.MAVT)
                if(Temp->RIGHT == NULL)
                {
                    Temp->RIGHT = Node;
                    return;
                }else
                Temp = Temp->RIGHT;
            else
                if(Temp->LEFT == NULL)
                {
                    Temp->LEFT = Node;
                    return;
                }else
                Temp = Temp->LEFT;
        }
    }
}
void RemoveVT(NodeVatTu* &Root,string mavt);
void RemoveDB(NodeVatTu* &Root)
{
    NodeVatTu * p = Root->RIGHT; // Tim nut cuc trai cua cay con ben phai
    while(p->LEFT != NULL) // => Vua lon hon cay con trai va be hon cay con phai
    {
        p = p->LEFT;
    }
    VatTu vt = p->DATA;
    RemoveVT(Root, p->DATA.MAVT);
    Root->DATA = vt;
    Root->DATA.MAVT = vt.MAVT;
}

void RemoveVT(NodeVatTu* &Root,string mavt)
{
    if(Root == NULL)
        return;
    if(mavt > Root->DATA.MAVT)
        RemoveVT(Root->RIGHT,mavt);
    else
        if(mavt < Root->DATA.MAVT)
            RemoveVT(Root->LEFT, mavt);
        else
        {
            NodeVatTu *Temp = Root;
            if(Root->LEFT == NULL)// la nut la hoac nut chi co cay con ben phai
                {
                    Root = Temp->RIGHT;// Tao lk tu nut cha toi nut con ben phai
                    delete(Temp);
                }
            else
                if(Root->RIGHT == NULL)// la nut la hoac nut chi co cay con ben trai
                    {
                        Root = Temp->LEFT;// Tao lk tu nut cha toi nut con ben trai
                        delete(Temp);
                    }
                else{
                    //
                    RemoveDB(Root);
				}


        }
}
void ClearVT(NodeVatTu *&Root)
{
    if(Root == NULL)
        return ;
    ClearVT(Root->LEFT);
    ClearVT(Root->RIGHT);
    delete(Root);
}
PTRVatTu CreateNodeVatTu(VatTu info){
	PTRVatTu newVatTu = new NodeVatTu;
	upcaseWord(info.MAVT);
	newVatTu->DATA.MAVT = info.MAVT;
	upcaseWord(info.TENVT);
	newVatTu->DATA.TENVT = info.TENVT;
	upcaseWord(info.DVT);
	newVatTu->DATA.DVT = info.DVT;
	newVatTu->DATA.SLT = info.SLT;
	newVatTu->LEFT = NULL;
	newVatTu->RIGHT = NULL;
	return newVatTu;
}
int SizeVT(NodeVatTu * Root)
{
    if(Root==NULL)
        return 0;

    Queue <NodeVatTu> q;
    q.Push(*Root);
    int cnt = 0;
    while(!q.Empty())
    {
        NodeVatTu p = q.Front(); q.Pop();
        cnt++;
        if(p.LEFT!=NULL)
            q.Push(*p.LEFT);
        if(p.RIGHT!=NULL)
           q.Push(*p.RIGHT);
    }
    return cnt;
}
/// tim kiem
struct Answer{
	int cnt = 0;
	string kq[MAXSearch];
};
struct Node{ // node nhanvien
	struct Node *child[MAXTrie];// ten
	string manv;
	int countWord;
};
typedef struct Node NODE;
struct NodeVT{ // node vattu
	struct NodeVT *child[MAXTrie];// ten
	string mavt;
	int countWord;
};
typedef struct NodeVT NODEVT;

NODE *newNode(){
	NODE *root = new Node;
	root->countWord = 0;
	root->manv = "";

	for(int i = 0;i < MAXTrie; i++){
		root->child[i] = NULL;
	}

	return root;
}

NODEVT *newNodeVT(){
	NODEVT *root = new NodeVT;
	root->countWord = 0;
	root->mavt = "";
	for(int i = 0;i < MAXTrie; i++){
		root->child[i] = NULL;
	}

	return root;
}
 bool removeWord(NODE* root,string s,int level,int len);



/// hoa don
struct CTHoaDon
{
    string MAVT;
    long long  SoLuong;
    long long  DonGia;
    long long VAT;
    CTHoaDon()
    {
        MAVT = "";
        SoLuong = 0;
        DonGia = 0;
        VAT = 0;
    }

};
struct NodeCTHoaDon
{
    CTHoaDon Data;
    NodeCTHoaDon * Next;
    NodeCTHoaDon(){Next = NULL;}
};
void InsertCTHoaDon(NodeCTHoaDon *&First,NodeCTHoaDon *Node)
{
    if(First == NULL)
        First = Node;
    else
    {
        NodeCTHoaDon *p = First;
        while(p->Next!=NULL)
            p=p->Next;
        p->Next = Node;
    }
}
NodeCTHoaDon *SeachCTHoaDon(NodeCTHoaDon *First,string &mavt)
{
    NodeCTHoaDon *p = First;
    while(p!=NULL)
    {
        if(p->Data.MAVT==mavt)
            return p;
        else
            p=p->Next;
    }
      return p;
}
void RemoveCTHoaDon(NodeCTHoaDon*& First,string &mavt)
{
    if(SeachCTHoaDon(First,mavt)==NULL)
        return ;
    else
    {
        if(First->Data.MAVT==mavt)
            First = First->Next;
        else
        {
            NodeCTHoaDon *p = First;
            while(p->Next->Data.MAVT!=mavt)
                p=p->Next;
            p->Next = p->Next->Next;
        }
    }
}
int SizeCTHoaDon(NodeCTHoaDon *First)
{
    NodeCTHoaDon *p = First;
    int cnt = 0;
    while(p!=NULL)
    {
        cnt++;
        p=p->Next;
    }
    return cnt;
}
void ClearCTHoaDon(NodeCTHoaDon * &First)
{
    while(First!=NULL)
    {
        NodeCTHoaDon *p = First;
        First =  First->Next;
        delete(p);
    }
}

struct HoaDon
{
    string SoHD;
    char Loai;
    Date NgayLap ;
    NodeCTHoaDon* DSCTHoaDon;
    //~HoaDon(){ClearCTHoaDon(DSCTHoaDon);}

    HoaDon()
    {
        SoHD = "";
        Loai = '\0';
        DSCTHoaDon = NULL;
    }

};

struct NodeHoaDon
{
    HoaDon Data;
    NodeHoaDon * Next;
    NodeHoaDon(){Next = NULL;}
};
void InsertHoaDon(NodeHoaDon *&First,NodeHoaDon *Node)
{
    if(First == NULL)
        First = Node;
    else
    {
        NodeHoaDon *p = First;
        while(p->Next!=NULL)
            p=p->Next;
        p->Next = Node;
    }
}
NodeHoaDon * SeachHoaDon(NodeHoaDon *First,string &sohd)
{
	NodeHoaDon *p = First;
    while(p!=NULL)
    {
        if(p->Data.SoHD==sohd)
            return p;
        else
            p=p->Next;
    }
      return p;
}
void RemoveHoaDon(NodeHoaDon*& First,string &sohd)
{
    if(SeachHoaDon(First,sohd)==NULL)
        return ;
    else
    {
        if(First->Data.SoHD==sohd)
            First = First->Next;
        else
        {
            NodeHoaDon *p = First;
            while(p->Next->Data.SoHD!=sohd)
                p=p->Next;
            p->Next = p->Next->Next;
        }
    }
}
int SizeHoaDon(NodeHoaDon *First)
{
    NodeHoaDon *p = First;
    int cnt = 0;
    while(p!=NULL)
    {
        cnt++;
        p=p->Next;
    }
    return cnt;
}
void ClearHoaDon(NodeHoaDon * &First)
{
    while(First!=NULL)
    {
        NodeHoaDon *p = First;
        First =  First->Next;
        delete(p);
    }
}
/// nhan vien
struct NhanVien{
    string MANV;
    string HO;
    string TEN;
    string PHAI;
    NodeHoaDon *DSHoaDon = NULL;
};

struct DSNhanVien{
    int Size = 0;
    NhanVien * DsNhanVien[MaxNV];
};
bool CompareNV (NhanVien a, NhanVien b){
    if(a.TEN > b.TEN)
        return 1;
    if(a.TEN == b.TEN)
        if(a.HO > b.HO)
        return 1;
    return 0;
}

int EmptyNVList(DSNhanVien &ds){
	return ds.Size == 0;
}

int FullNVList(DSNhanVien &ds){
	return (ds.Size == MaxNV ? 1 : 0);
}

int SeachNV(DSNhanVien &ds,string &manv){
    for(int i=0;i<ds.Size;i++)
        if(ds.DsNhanVien[i]->MANV==manv)
            return i;
    return -1;
}

int InsertNV(DSNhanVien &ds,NhanVien nv)
{
    if(FullNVList(ds)){
    	return 0;
	}
	ds.DsNhanVien[ds.Size]= new NhanVien;
    *ds.DsNhanVien[ds.Size] = nv;
    ds.Size++;
    return 1;
}

int RemoveNV(DSNhanVien &ds, string manv, NODE *root)
{
    int i = SeachNV(ds,manv);
    NhanVien *nv;
    if(i != -1){
    	nv = ds.DsNhanVien[i];
    	removeWord(root, nv->TEN + nv->MANV, 0, nv->TEN.size() + nv->MANV.size());
    	removeWord(root, nv->MANV, 0,nv->MANV.size());
	}

    if(i<0 || EmptyNVList(ds))
        return 0;
    else
    {
        for(int j=i+1;j<ds.Size;j++)
            *ds.DsNhanVien[j-1]= *ds.DsNhanVien[j];
        delete(ds.DsNhanVien[ds.Size - 1]);
        ds.Size--;
        return 1;
    }
}

void ClearNV(DSNhanVien dsnv)
{
    for(int i=0;i<dsnv.Size;i++)
    {
        NhanVien *nv = dsnv.DsNhanVien[i];
        NodeHoaDon *hd = nv->DSHoaDon;
        while(hd!=NULL)
        {
            ClearCTHoaDon(hd->Data.DSCTHoaDon);
            hd=hd->Next;
        }
        ClearHoaDon(nv->DSHoaDon);
        delete(nv);
    }
}

void SortNV(DSNhanVien &ds ){
    for(int i=0;i<ds.Size;i++)
    {
        for(int j=i+1;j<ds.Size;j++)
            {
                if(CompareNV(*ds.DsNhanVien[i],*ds.DsNhanVien[j])>0)
                {
                    NhanVien t = *ds.DsNhanVien[i];
                    *ds.DsNhanVien[i]=*ds.DsNhanVien[j];
                    *ds.DsNhanVien[j]=t;
                }

        }
    }
}

#endif // KHAIBAO_H_INCLUDED
