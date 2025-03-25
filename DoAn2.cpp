#include<iostream>
#include<math.h>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<E:\project-algorithm\mylib.h>
#include<vector>
using namespace std;

const int item = 5, sh = 2;
const int cot = 20, dong = 5;
const int Space = 32, Back = 8, ESC = 27;
const int F1 = 59, F2 = 60, F3 = 61, F7 = 65, F5 = 63, Up = 72, Down = 80, Left = 75, Right = 77;
const int MAXNV = 500, MAXVT = 500;

void Normal(){
	SetColor(15);
	SetBGColor(0);
}
void Highlight(){
	SetColor(15);
	SetBGColor(3);
}
void Thongbao(string s){
	Normal();
	int x = wherex(), y = wherey();
	gotoxy(61, 30);
	cout << s;
	Sleep(4000);
	while(_kbhit()){
		_getch();
	}
	gotoxy(61, 30);
	clreol();
	gotoxy(x, y);
}
void Title(){
	SetColor(11);
	SetBGColor(12);
}
void Box(){
	SetColor(4);
	SetBGColor(14);
}
bool is_num(int n){
	if(n >= 48 && n <= 57) return 1;
	return 0;
}
bool is_char(int n){
	if((n >= 65 && n <= 90) || (n >= 97 && n <= 122)) return 1;
	return 0;
}
void format(string &s){ // chuan hoa xoa cac dau cach 2 ben
	while(s[s.size() - 1] == ' '){
		s.pop_back(); 
		if(s.size() == 0) break;
	}
	for(int i = 1; i < s.size(); i++){
		if(s[i] == ' ' && s[i - 1] == ' '){
			s.erase(i, 1); 
			i--;
		} 
	} 
}
void ShowMenu(string menu[], int n, int cot, int dong){
	Normal();
	for(int i = 0; i < n; i++){
		gotoxy(cot, dong + i); cout << menu[i] << "\n";
	}
}
struct Vattu{
	string MAVT, TENVT, DVT;
	bool used = 0;
	int SL;
};
struct nodeVT{
	Vattu data;
	nodeVT* left;
	nodeVT* right;
};
struct CT_HOADON{
	string MAVT;
	int soluong, dongia, VAT;
	float money = 0;
};
struct HOADON{
	int sz = 0;
	int SoHD, dd, mm, yy;
	char type;
	CT_HOADON* cthd; 
};
struct nodeHD{
	HOADON data;
	nodeHD* next;
};
nodeHD* makeHD(HOADON x){
	nodeHD* newnode = new nodeHD;
	newnode->next = NULL;
	newnode->data = x;
	return newnode;
}
struct Nhanvien{
	int SHD = 0;
	string MANV, HO, TEN, PHAI;
	nodeHD* dshd = NULL;
};
struct listNV{
	int n = 0;
	Nhanvien* node[MAXNV] = {NULL};	
};
bool find(listNV &dsnv, string ms){
	for(int i = 0; i < dsnv.n; i++){
		if((*dsnv.node[i]).MANV == ms) return 1;
	}
	return 0;
}
Nhanvien* makeNV(listNV &dsnv){
	int cot = 72, dong = 6, sz = 4, chon = 0;
	gotoxy(cot + 4, dong - 2); Title(); cout << "THEM NHAN VIEN";
	gotoxy(cot, dong);
	string menu[sz] = {"MANV: ", "HO: ", "TEN: ", "PHAI: "}, st[sz]; 
	for(int i = 0; i < 4; i++) st[i] = "";
	ShowMenu(menu, sz, cot, dong);
	Normal();  
	gotoxy(cot - 1, dong - 1); 
	cout << "+-------------------------+";
	gotoxy(cot - 1, 13); 
	cout << "+-------------------------+";
	for(int i = 0; i <= 6; i++){
		gotoxy(cot - 1, dong + i); cout << "|"; 
		gotoxy(cot + 25, dong + i); cout << "|";
	}
	gotoxy(cot , 11); 
	cout << "-------------------------"; gotoxy(cot - 1, 12);
	cout << "|ESC: Thoat   |   F5: Luu";
	Box(); gotoxy(cot, 12); cout << "ESC";
	gotoxy(cot + 17, 12); cout << "F5"; Normal();
	gotoxy(cot, dong); Highlight(); cout << menu[0];
	char c;
	while(1){
		c = getch();
		if(c <= 0){
			c = getch();
			switch(c){
				case Up:
					{
						gotoxy(cot, dong + chon);
						Normal(); cout << menu[chon] << st[chon];
						chon = (chon - 1 + sz) % sz;
						gotoxy(cot, dong + chon);
						Highlight(); cout << menu[chon] << st[chon];			
						break;
					}
				case Down:
					{
						gotoxy(cot, dong + chon);
						Normal(); cout << menu[chon] << st[chon];
						chon = (chon + 1) % sz;
						gotoxy(cot, dong + chon);
						Highlight(); cout << menu[chon] << st[chon];
						break;				
					}
				case F5:
					{
						format(st[1]);
						if(!st[0].size()) Thongbao("Ma nhan vien khong hop le!");
						else if(find(dsnv, st[0])) Thongbao("Ma nhan vien da ton tai!");
						else if(!st[1].size()) Thongbao("Ho nhan vien khong hop le!");
						else if(!st[2].size()) Thongbao("Ten nhan vien khong hop le!");
						else if(st[3] != "NAM" && st[3] != "NU") Thongbao("Gioi tinh khong hop le!");
						else return new Nhanvien{0, st[0], st[1], st[2], st[3], NULL};
						break;
					}		
			}		
		} 
		else{
			int k = int(c);
			if(k == Enter){
				gotoxy(cot, dong + chon);
				Normal(); cout << menu[chon] << st[chon];
				chon = (chon + 1) % sz;
				gotoxy(cot, dong + chon);
				Highlight(); cout << menu[chon] << st[chon];
			} 
			else if(k == Back){
				if(st[chon].size()) st[chon].pop_back();
				gotoxy(cot, dong + chon); 
				Normal(); cout << menu[chon] << st[chon] << " ";
			} 
			else if(k == ESC){
				return NULL;
			}
			else{
				if(chon == 0){
					if((is_num(k) || is_char(k)) && st[chon].size() < 17) st[chon] += toupper(c);
				}
				else if(chon == 1){
					if(st[chon].size() == 21) continue;
					if(k == Space && st[chon].size()){
						st[chon] += toupper(c);
					}
					else if(is_char(k)) st[chon] += toupper(c);
				}
				else if(chon == 2){
					if(st[chon].size() == 13) continue;
					if(is_char(k)) st[chon] += toupper(c);
				}
				else{
					char tmp = toupper(c);
					int _sz = st[chon].size();
					if(_sz == 0){
						if(tmp == 'N') st[chon] += tmp;
					}
					else if(_sz == 1){
						if(tmp == 'A' || tmp == 'U') st[chon] += tmp;
					}
					else if(_sz == 2){
						if(st[chon][_sz - 1] == 'A'){
							if(tmp == 'M') st[chon] += tmp;
						}
					}
				}			
			}
			if(chon != 1) format(st[chon]);
			Highlight(); gotoxy(cot, dong + chon); cout << menu[chon] << st[chon];
		}
	}
	return new Nhanvien{0, st[0], st[1], st[2], st[3], NULL};
}
Nhanvien* resetNV(listNV &dsnv, Nhanvien x){
	int cot = 72, dong = 6, sz = 4, chon = 1;
	gotoxy(cot + 2, dong - 2); Title(); cout << "CHINH SUA NHAN VIEN";
	string menu[4] = {"MANV: ", "HO: ", "TEN: ", "PHAI: "}, st[4];
	st[0] = x.MANV; st[1] = x.HO; st[2] = x.TEN; st[3] = x.PHAI; 
	Normal();
	for(int i = 0; i < 4; i++){
		gotoxy(cot, dong + i); cout << menu[i] << st[i];
	}
	gotoxy(cot - 1, dong - 1); 
	cout << "+-------------------------+";
	gotoxy(cot - 1, 14); 
	cout << "+-------------------------+";
	for(int i = 0; i <= 7; i++){
		gotoxy(cot - 1, dong + i); cout << "|"; 
		gotoxy(cot + 25, dong + i); cout << "|";
	}
	gotoxy(cot , 11); 
	cout << "-------------------------"; gotoxy(cot - 1, 12);
	cout << "|F5: Luu     |    F1: Xoa"; gotoxy(cot - 1, 13);
	cout << "|       ESC: Thoat       ";
	Box(); gotoxy(cot, 12); cout << "F5";
	gotoxy(cot + 17, 12); cout << "F1"; 
	gotoxy(cot + 7, 13); cout << "ESC"; Normal();
	gotoxy(cot, dong + 1); Highlight(); cout << menu[1] << st[1];
	char c;
	while(1){
		c = getch();
		if(c <= 0){
			c = getch();
			switch(c){
				case Up:
					{
						gotoxy(cot, dong + chon);
						Normal(); cout << menu[chon] << st[chon];
						chon = (chon - 1 + sz) % sz;
						if(!chon) chon = sz - 1;
						gotoxy(cot, dong + chon);
						Highlight(); cout << menu[chon] << st[chon];
						break;	
					}
				case Down:
					{
						gotoxy(cot, dong + chon);
						Normal(); cout << menu[chon] << st[chon];
						chon = (chon + 1) % sz;
						if(!chon) chon = 1;
						gotoxy(cot, dong + chon);
						Highlight(); cout << menu[chon] << st[chon];
						break;			
					}
				case F5:
					{
						format(st[1]);
						if(!st[1].size()) Thongbao("Ho nhan vien khong hop le!");
						else if(!st[2].size()) Thongbao("Ten nhan vien khong hop le!");
						else if(st[3] != "NAM" && st[3] != "NU") Thongbao("Gioi tinh khong hop le!");
						else return new Nhanvien{x.SHD, st[0], st[1], st[2], st[3], x.dshd};
						break;
					}
				case F1:
					{	
						if(x.SHD > 0){
							Thongbao("Nhan vien da lap hoa don khong the xoa!");
							return NULL;
						} 
						else{
							gotoxy(cot - 1, 15);
							cout << "Ban co chac muon xoa"; gotoxy(cot - 1, 16);							
							cout << "nhan vien nay ?(Y/N): ";
							char tx;
							while(1){
								tx = getch();
								if(tx == 'Y' || tx == 'y'){
									Normal();
									gotoxy(cot - 1, 15); cout << "                    ";
									gotoxy(cot - 1, 16); cout << "                      ";
									return new Nhanvien{-1, st[0], st[1], st[2], st[3], NULL};
								} 
								else if(tx == 'N' || tx == 'n'){
									Normal();
									gotoxy(cot - 1, 15); cout << "                    ";
									gotoxy(cot - 1, 16); cout << "                      ";
									gotoxy(cot, dong + chon); Highlight(); cout << menu[chon] << st[chon];
									break;
								} 
							} 
							break;	
						}
					}		
			}		
		} 
		else{
			int k = int(c);
			if(k == Enter){
				gotoxy(cot, dong + chon);
				Normal(); cout << menu[chon] << st[chon];
				chon = (chon + 1) % sz;
				if(!chon) chon = 1;
				gotoxy(cot, dong + chon);
				Highlight(); cout << menu[chon] << st[chon];
			} 
			else if(k == Back){
				if(st[chon].size()) st[chon].pop_back();
				gotoxy(cot, dong + chon); 
				Normal(); cout << menu[chon] << st[chon] << " ";
			} 
			else if(k == ESC) return NULL;
			else{
				if(chon == 0){
					if((is_num(k) || is_char(k)) && st[chon].size() < 17) st[chon] += toupper(c);
				}
				else if(chon == 1){
					if(st[chon].size() == 21) continue;
					if(k == Space && st[chon].size()){
						st[chon] += toupper(c);
					}
					else if(is_char(k)) st[chon] += toupper(c);
				}
				else if(chon == 2){
					if(st[chon].size() == 13) continue;
					if(is_char(k)) st[chon] += toupper(c);
				}
				else{
					char tmp = toupper(c);
					int _sz = st[chon].size();
					if(_sz == 0){
						if(tmp == 'N') st[chon] += tmp;
					}
					else if(_sz == 1){
						if(tmp == 'A' || tmp == 'U') st[chon] += tmp;
					}
					else if(_sz == 2){
						if(st[chon][_sz - 1] == 'A'){
							if(tmp == 'M') st[chon] += tmp;
						}
					}
				}			
			}
			if(chon != 1) format(st[chon]);
			Highlight(); gotoxy(cot, dong + chon); cout << menu[chon] << st[chon];
		}
	}
	return new Nhanvien{x.SHD, st[0], st[1], st[2], st[3], x.dshd};
}
void AddNV(listNV &dsnv, Nhanvien* x){
	if(x == NULL) return;
	int i = 0;
	for(; i < dsnv.n; i++){
		int tmp = ((*dsnv.node[i]).TEN).compare((*x).TEN);
		if(tmp > 0) break;
		else if(tmp == 0){
			tmp = ((*dsnv.node[i]).HO).compare((*x).HO);
			if(tmp > 0) break;
		}
	}
	dsnv.n++;
	for(int j = dsnv.n - 1; j > i; j--){
		dsnv.node[j] = dsnv.node[j - 1];
		
	}
	dsnv.node[i] = x;
}
void DelNV(listNV &dsnv, Nhanvien* x){
	if(x == NULL) return;
	int i = 0;
	for(; i < dsnv.n; i++){
		string tmp = (*dsnv.node[i]).MANV;
		if(tmp == (*x).MANV) break;
	}
	Nhanvien* tmp = dsnv.node[i];
	for(int j = i; j < dsnv.n - 1; j++){
		dsnv.node[j] = dsnv.node[j + 1];
	}
	dsnv.node[dsnv.n - 1] = NULL;
	dsnv.n--;
	delete tmp;
}
void SetNV(listNV &dsnv, Nhanvien* x){
	if(x == NULL) return;
	else if((*x).SHD == -1){
		DelNV(dsnv, x);
	}
	else{
		DelNV(dsnv, x);
		AddNV(dsnv, x);
	}
}
void AddHD(listNV &dsnv, int i, nodeHD* &head, HOADON x){
	(*dsnv.node[i]).SHD++;
	nodeHD* newnode = makeHD(x);
	newnode->next = head;
	head = newnode;
	return;
}
void dtest(listNV &dsnv, int i, HOADON x){
	(*dsnv.node[i]).SHD++;
	nodeHD* newnode = makeHD(x);
	newnode->next = (*dsnv.node[i]).dshd;
	(*dsnv.node[i]).dshd = newnode;
}
void inpage(vector<Nhanvien*> vec, int i){
	Nhanvien x = *(vec[i]);
	gotoxy(3, 8 + i % sh); cout << i + 1;
	gotoxy(7, 8 + i % sh); cout << x.MANV;
	gotoxy(25, 8 + i % sh); cout << x.HO;
	gotoxy(48, 8 + i % sh); cout << x.TEN;
	gotoxy(62, 8 + i % sh); cout << x.PHAI;
}
int ShowNV(listNV &dsnv, string &s, int page){
	vector<Nhanvien*> vec;
	for(int i = 0; i < dsnv.n; i++){
		if(((*dsnv.node[i]).MANV).find(s) != string::npos){
			vec.push_back(dsnv.node[i]);
		}
	}
	Normal();
	int chon = 0, cnt = 1;
	system("cls");
	gotoxy(27, 2); Title(); cout << "DANH SACH NHAN VIEN"; gotoxy(2, 4); Highlight();
	cout << "Find: " << s; gotoxy(2, 5); Normal();
	cout << "+---------------------------------------------------------------+"; gotoxy(2, 6);
	cout << "|STT|       MANV      |          HO          |     TEN     |PHAI|"; gotoxy(2, 7);
	cout << "|---|-----------------|----------------------|-------------|----|";
	for(int i = 0; i < 10; i++){
//		gotoxy(2, 8 + i); cout << '|';
//		gotoxy(6, 8 + i); cout << '|';
//		gotoxy(24, 8 + i); cout << '|';
//		gotoxy(47, 8 + i); cout << '|';
//		gotoxy(61, 8 + i); cout << '|';
//		gotoxy(66, 8 + i); cout << '|';
		gotoxy(2, 8 + i); cout << "|   |                 |                      |             |    |";
	}
	gotoxy(0, 18); cout << "  +---------------------------------------------------------------+";
	gotoxy(42, 20); 
	int mxpage = ceil(vec.size() * 1.0 / sh); 
	if(page == 1)          cout << "Trang      " << page << " / " << max(mxpage, 1);
	else if(page > 1) 	   cout << "Trang  <-- " << page << " / " << max(mxpage, 1);
	if(page < mxpage)  	   cout << " -->";
	gotoxy(0, 23);
	cout << "  |---------------------------------------------------------------|"; gotoxy(0, 24);
	cout << "  | ESC: Thoat | F2: Them NV | F3: Sua NV | F7: Sua HD |          |";
	Box(); gotoxy(4, 24); cout << "ESC"; 
	gotoxy(17, 24); cout << "F2"; 
	gotoxy(31, 24); cout << "F3"; 
	gotoxy(44, 24); cout << "F7"; Normal();
	for(int i = sh * (page - 1); i < sh * page; i++){
		if(i >= vec.size()){
			continue;
		}
		inpage(vec, i);
		cnt++;
	}
	gotoxy(8 + s.size(), 4); 
	while(1){
		char c = getch(); 
		if(c <= 0){
			c = getch();
			if(c == Down){
				Normal();
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpage(vec, sh * (page - 1) + chon - 1);
				}
				chon = (chon + 1) % cnt;
				Highlight(); 
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpage(vec, sh * (page - 1) + chon - 1);
				}
			}
			else if(c == Up){
				Normal();
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpage(vec, sh * (page - 1) + chon - 1);
				}
				chon = (chon - 1 + cnt) % cnt;
				Highlight(); 
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpage(vec, sh * (page - 1) + chon - 1);
				}
			}
			else if(c == F2){
				Nhanvien* x = makeNV(dsnv);
				AddNV(dsnv, x);
				if(ShowNV(dsnv, s, 1) == 0) return 0;
			}
			else if(c == F3){
				if(chon <= 0) continue;
				Nhanvien tmp = *vec[sh * (page - 1) + chon - 1];
				Nhanvien* x = resetNV(dsnv, tmp);
				SetNV(dsnv, x);
				if(ShowNV(dsnv, s, 1) == 0) return 0;
			}
			else if(c == Left){
				if(page > 1){
					page--;
					if(ShowNV(dsnv, s, page) == 0) return 0;
				}		
			}
			else if(c == Right){
				if(page < mxpage){
					page++;
					if(ShowNV(dsnv, s, page) == 0) return 0;
				}
			}
		} 
		else{
			if(c == ESC){
				gotoxy(0, 30); Normal(); return 0; 
			} 
			if(chon == 0){
				if(is_char(c) || is_num(c)) s += toupper(c);
				else if(c == Back && s.size()) s.pop_back();
				if(ShowNV(dsnv, s, 1) == 0) return 0;
			} 	
		}	
	}
	return 0;
}
int ShowVT(nodeVT* &dsvt, string &s, int page){
	return 0;
}
void Print(string s, int x, int y, int cd, int cr){
	for(int i = 0; i < cr; i++){
		gotoxy(x, y + i);
		for(int j = 1; j <= cd; j++)
			cout << " ";
	}
	gotoxy(x + int((cd - s.size()) / 2), y + int(cr / 2)); cout << s;
}
int Show(int chon){
	Normal();
	system("cls");
	Box();
	Print("QUAN LY VAT TU", 25, 3, 44, 5);
	Highlight();
	if(chon == 1) Print("VAT TU", 58, 12, 24, 5);
	else Print("NHAN VIEN", 12, 12, 24, 5);
	SetColor(8); SetBGColor(7);
	if(chon == 0) Print("VAT TU", 58, 12, 24, 5);
	else Print("NHAN VIEN", 12, 12, 24, 5);
	Print("THOAT CHUONG TRINH", 34, 21, 26, 5);

//	Highlight();
//	Print("")
}
void OpenFile(listNV &dsnv){
	fstream fs;
	fs.open("Nhanvien.txt", ios::in);
	if(!fs.is_open()){
		Thongbao("Loi mo file!"); return;
	} 
	Nhanvien x;
	while(fs >> x.MANV){
		fs.ignore();
		getline(fs, x.HO);
		fs >> x.TEN; fs >> x.PHAI;
		fs >> x.SHD;
		Nhanvien* tmp = new Nhanvien{x.SHD, x.MANV, x.HO, x.TEN, x.PHAI, NULL};
		AddNV(dsnv, tmp);
//		for(int i = 0; i < *x.SHD; i++){
//			
//		}
	}
}
int main(){
	listNV dsnv;
	nodeVT* dsvt;
	Nhanvien* x = new Nhanvien{0, "N23", "NGUYEN THIEN", "NHAN", "NAM", NULL};
	HOADON y = {0, 1931, 3, 10, 2025, 'N'};
	HOADON z = {0, 2516, 3, 11, 2004, 'X'};
	//AddNV(dsnv, x);
	//AddHD(dsnv, 0, (*dsnv.node[0]).dshd, y);
//	AddHD(dsnv, 0, (*dsnv.node[0]).dshd, z);
//	nodeHD* tmp = (*dsnv.node[0]).dshd;

//	dtest(dsnv, 0, y);
//	if((*dsnv.node[0]).dshd != NULL){
//		nodeHD* head = (*dsnv.node[0]).dshd;
//		cout << head->data.SoHD;
//	}

	OpenFile(dsnv);
	string s = "";
	int chon = 0, st = 0;
	char c;
	Show(chon);
	while(1){
		c = getch();
		if(c <= 0) c = getch();
		if(c == Enter){
			if(st == 0){
				if(chon == 0){
					if(ShowNV(dsnv, s, 1) == 0){
						Show(chon);
						continue;
					} 
				} 
				else{
					if(ShowVT(dsvt, s, 1) == 0){
						Show(chon);
						//chon = 0;
						continue;
					} 
				} 
			}
			else{
				Normal();
				gotoxy(30, 30);
				break;
			}
		}
		else if((c == Left || c == Right) && (st == 0)){
			SetColor(8); SetBGColor(7);
			if(chon == 0) Print("NHAN VIEN", 12, 12, 24, 5);
			else Print("VAT TU", 58, 12, 24, 5);
			chon = 1 - chon;
			Highlight();
			if(chon == 0) Print("NHAN VIEN", 12, 12, 24, 5);
			else Print("VAT TU", 58, 12, 24, 5);
		}
		else if(c == Down || c == Up){
			SetColor(8); SetBGColor(7);
			if(st == 0){
				if(chon == 0) Print("NHAN VIEN", 12, 12, 24, 5);
				else Print("VAT TU", 58, 12, 24, 5);
			}
			else Print("THOAT CHUONG TRINH", 34, 21, 26, 5);
			st = 1 - st;
			Highlight();
			if(st == 0){
				chon = 0;
				Print("NHAN VIEN", 12, 12, 24, 5);
			}
			else Print("THOAT CHUONG TRINH", 34, 21, 26, 5);
		}
	}
	
	

//	ShowNV(dsnv, s, 1);

	//resetNV(dsnv, x);
//	AddHD(dsnv, 0, (*dsnv.node[0]).dshd, y);



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	for(int i = 0; i < dsnv.n; i++){
		delete dsnv.node[i];
	}
	dsnv.n = 0;
}