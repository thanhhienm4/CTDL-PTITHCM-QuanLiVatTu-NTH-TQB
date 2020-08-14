#pragma once
#include<iostream>
#include<cstring>
#include "khaibao.h"

using namespace std;
void addWord1(NODE *root ,string Manv){ // Tim theo manv

	string s = upcaseWord(Manv); // De tranh truong hop ten bi trung
	NODE *temp = root;
	int ch;

	for(int i = 0; i < s.size(); i++){
		ch = s[i];
		if(temp->child[ch] == NULL){
			temp->child[ch] = newNode();
		}
		temp = temp->child[ch];
	}

	temp->manv = Manv;
	temp->countWord++;
}

void addWord2(NODE *root,string Manv, string Ten){ // Tim theo ten

	string s = upcaseWord(Ten) + upcaseWord(Manv); // De tranh truong hop ten bi trung
	NODE *temp = root;
	int ch;

	for(int i = 0; i < s.size(); i++){
		ch = s[i];
		if(temp->child[ch] == NULL){
			temp->child[ch] = newNode();
		}
		temp = temp->child[ch];
	}

	temp->manv = Manv;
	temp->countWord++;
}
bool findWord(NODE *root, string s){
	NODE *temp = root;
	int ch;
	for(int i = 0; i < s.size(); i++){
		ch = s[i];
		if(temp->child[ch] == NULL){
			return false;
		}
		temp = temp->child[ch];
	}
	return temp->countWord > 0;
}

bool isWord(NODE *root){
	return root->countWord > 0;
}

bool isEmpty(NODE *root){
	NODE *temp = root;

	for(int i = 0; i < MAXTrie; i++){
		if(temp->child[i] == NULL){
			return false;
		}
	}

	return true;
}

bool removeWord(NODE *root, string s, int level, int len){
	if(!root){
		return false;
	}

	int ch = s[level];

	if(level == len){
		if(root->countWord > 0){
			root->countWord--;
			root->manv.clear();
			return true;
		}
		else{
			return false;
		}
	}

	int flag = removeWord(root->child[ch], s, level + 1, len);

	if(flag && !isWord(root->child[ch]) && isEmpty(root->child[ch])){
		delete root->child[ch];
		root->child[ch] = NULL;
		root->manv.clear();
	}

	return flag;
}

NODE* getPointerToEndOfPrefix(NODE *root, string s){
	NODE *tmp = root;
	for(int i = 0; i < s.length(); i++){
		if(tmp->child[s[i]] == NULL){
			return NULL;
		}
		tmp = tmp->child[s[i]];
	}
	return tmp;
}


void printAllWordWithPrefix(NODE *root,DSNhanVien dsnv, string s, Answer &ans, int &x, int &y){
	if(isWord(root)){
		if(ans.cnt + 1 > 10){ 
			return;
		}
		ans.kq[ans.cnt] = root->manv;
        int posNV = SeachNV(dsnv,root->manv);
        if(posNV!=-1)
        {
            NhanVien *nv = dsnv.DsNhanVien[posNV];
            ans.cnt++;
            gotoxy(x, y);
            cout << root->manv;
            x += 20;
            gotoxy(x, y);
            cout << nv->HO;
            x += 20;
            gotoxy(x, y);
            cout << nv->TEN;
            x += 20;
            gotoxy(x, y);
            cout << nv->PHAI;
            y += 2;
            x -= 60;
        }
	}
	for(int i = 0; i < MAXTrie; i++){
		if(root->child[i]){
			printAllWordWithPrefix(root->child[i],dsnv, s + char(i), ans, x, y);
		}
	}
}
string noSpaceWord(string s){
	string ans;
	for(int i = 0; i < s.size(); i++ ){
		if(s[i] != ' '){
			ans += s[i];
		}
	}
	return ans;
}
bool findWordVT(NODEVT *root, string s){
	NODEVT *temp = root;
	int ch;
	for(int i = 0; i < s.size(); i++){
		ch = s[i];
		if(temp->child[ch] == NULL){
			return false;
		}
		temp = temp->child[ch];
	}
	return temp->countWord > 0;
}
void addWordVT1(NODEVT *root, string Mavt){
	string s = upcaseWord(Mavt);
	NODEVT *temp = root;
	int ch;

	for(int i = 0; i < s.size(); i++){
		ch = s[i];
		if(temp->child[ch] == NULL){
			temp->child[ch] = newNodeVT();
		}
		temp = temp->child[ch];
	}

	temp->mavt = Mavt;
	temp->countWord++;
}
void addWordVT2(NODEVT *root, string Mavt, string Tenvt){
	string s = upcaseWord(Tenvt);
	s = noSpaceWord(s);
	if(findWordVT(root, s)){
		return;
	}
	NODEVT *temp = root;
	int ch;

	for(int i = 0; i < s.size(); i++){
		ch = s[i];
		if(temp->child[ch] == NULL){
			temp->child[ch] = newNodeVT();
		}
		temp = temp->child[ch];
	}

	temp->mavt = Mavt;
	temp->countWord++;
}

bool isWordVT(NODEVT *root){
	return root->countWord > 0;
}

bool isEmptyVT(NODEVT *root){
	NODEVT *temp = root;

	for(int i = 0; i < MAXTrie; i++){
		if(temp->child[i] == NULL){
			return false;
		}
	}

	return true;
}

bool removeWordVT(NODEVT *root, string s, int level, int len){
	if(!root){
		return false;
	}

	int ch = s[level];

	if(level == len){
		if(root->countWord > 0){
			root->countWord--;
			root->mavt.clear();
			return true;
		}
		else{
			return false;
		}
	}

	int flag = removeWordVT(root->child[ch], s, level + 1, len);

	if(flag && !isWordVT(root->child[ch]) && isEmptyVT(root->child[ch])){
		delete root->child[ch];
		root->child[ch] = NULL;
		root->mavt.clear();
	}

	return flag;
}

NODEVT* getPointerToEndOfPrefixVT(NODEVT *root, string s){
	NODEVT *tmp = root;

	for(int i = 0; i < s.length(); i++){
		if(tmp->child[s[i]] == NULL){
			return NULL;
		}
		tmp = tmp->child[s[i]];
	}

	return tmp;
}

void printAllWordWithPrefixVT(NODEVT *root,NodeVatTu *dsvt, string s, Answer &ans, int &x, int &y){
	if(isWordVT(root)){
		if(ans.cnt + 1 > 10){ 
			return;
		}
		ans.kq[ans.cnt] = root->mavt;
		NodeVatTu *vt = SearchVT(dsvt,root->mavt);
		if(vt!= NULL)
        {
            ans.cnt++;
            gotoxy(x,y);
            cout << root->mavt;
            x += 20;
            gotoxy(x, y);
            cout << vt->DATA.TENVT;
            x += 20;
            gotoxy(x, y);
            cout << vt->DATA.DVT;
            x += 20;
            gotoxy(x, y);
            cout << vt->DATA.SLT;
            y += 2;
            x -= 60;
        }

	}

	for(int i = 0; i < MAXTrie; i++){
		if(root->child[i]){
			printAllWordWithPrefixVT(root->child[i],dsvt, s + char(i), ans, x, y);
		}
	}
}
void ClearPrefixTreeNV(NODE *root){
	for(int i = 0; i < MAXTrie; i++){
		if(root->child[i] != NULL){
			root->child[i] = NULL;
			delete root->child[i];
		}
	}
}
void ClearPrefixTreeVT(NODEVT *root){
	for(int i = 0; i < MAXTrie; i++){
		if(root->child[i] != NULL){
			root->child[i] = NULL;
			delete root->child[i];
		}
	}
}
