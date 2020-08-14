#pragma once
#include<iostream>
#include<cstring>
#define MAXTrie 128
#define MAXSearch 50000
using namespace std;
struct Answer1{
	int cnt = 0;
	string kq[MAXSearch];
};
struct Node1{ // node vattu
	struct Node1 *child[MAXTrie];// ten
	string mavt;
	string tenvt;
	string dvt;
	long long slt;
	int countWord;
};
typedef struct Node1 NODE1;
NODE1 *newNode1(){
	NODE1 *root1 = new Node1;
	root1->countWord = 0;
	root1->mavt = "";
	root1->tenvt = "";
	root1->dvt = "";
	root1->slt = 0;
	for(int i = 0;i < MAXTrie; i++){
		root1->child[i] = NULL;
	}
	
	return root1;
}

string upcaseWord1(string s){
	for(int i = 0; i < s.size(); i++){
		if(s[i] >= 97 && s[i] <= 122){
			s[i] -= 32;
		}
	}
	return s;
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
void addWordVT1(NODE1 *root, string Mavt, string Tenvt, string Dvt, long long Slt){
	string s = upcaseWord1(Mavt);
	NODE1 *temp1 = root;
	int ch;
	
	for(int i = 0; i < s.size(); i++){
		ch = s[i];
		if(temp1->child[ch] == NULL){
			temp1->child[ch] = newNode1();
		}
		temp1 = temp1->child[ch];
	}
	
	temp1->mavt = Mavt;
	temp1->tenvt = Tenvt;
	temp1->dvt = Dvt;
	temp1->slt = Slt;
	temp1->countWord++;
}
void addWordVT2(NODE1 *root, string Mavt, string Tenvt, string Dvt, long long Slt){
	string s = upcaseWord1(Tenvt);
	s = noSpaceWord(s);
	NODE1 *temp = root;
	int ch;
	
	for(int i = 0; i < s.size(); i++){
		ch = s[i];
		if(temp->child[ch] == NULL){
			temp->child[ch] = newNode1();
		}
		temp = temp->child[ch];
	}
	
	temp->mavt = Mavt;
	temp->tenvt = Tenvt;
	temp->dvt = Dvt;
	temp->slt = Slt;
	temp->countWord++;
}
