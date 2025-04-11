#include<iostream>
#include<math.h>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<E:\project-algorithm\mylib.h>
using namespace std;

const int item = 5, sh = 2;
const int cot = 20, dong = 5;
const int Space = 32, Back = 8, ESC = 27;
const int F1 = 59, F2 = 60, F3 = 61, F7 = 65, F5 = 63, F8 = 66, Up = 72, Down = 80, Left = 75, Right = 77;
const int MAXNV = 500;

void Normal(){
	SetColor(15);
	SetBGColor(0);
}
void Highlight(){
	SetColor(15);
	SetBGColor(3);
}
void Title(){
	SetColor(11);
	SetBGColor(12);
}
void Box(){
	SetColor(4);
	SetBGColor(14);
}
void Thongbao(string s){
	Normal();
	int x = wherex(), y = wherey();
	gotoxy(61, 30);
	cout << s;
	Sleep(3000);
	while(_kbhit()){
		_getch();
	}
	gotoxy(61, 30);
	clreol();
	gotoxy(x, y);
}
void Warning(string s, int cot, int dong){
	Highlight();
	int x = wherex(), y = wherey();
	gotoxy(cot, dong);
	cout << s;
	Sleep(3000);
	while(_kbhit()){
		_getch();
	}
	gotoxy(cot, dong);
	string tmp = "";
	for(int i = 0; i < s.size(); i++) tmp += " ";
	Normal();
	cout << tmp;
	gotoxy(x, y);
}
bool is_num(int n){
	if(n >= 48 && n <= 57) return 1;
	return 0;
}
bool is_char(int n){
	if((n >= 65 && n <= 90) || (n >= 97 && n <= 122)) return 1;
	return 0;
}
void xoatab(){
	for(int i = 1; i <= 13; i++){
		gotoxy(71, 3 + i); 
		cout << "                           ";
	}
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


//-------------------------------------//
struct Vattu{
	string MAVT, TENVT, DVT;
	int SL;
	bool used = 0;
};
struct nodeVT{
	Vattu data;
	int height;
	nodeVT* left;
	nodeVT* right;
};
struct arrayVT{
	int MAX;
	int n;
	Vattu** arr;
	arrayVT(int mx){
		n = 0;
		MAX = mx;
		arr = new Vattu*[MAX];
	}
	void expand(){
		MAX *= 2;
		Vattu** newarr = new Vattu*[MAX];
		for(int i = 0; i < n; i++){
			newarr[i] = arr[i];
		}
		delete[] arr;
		arr = newarr;
	}
	void push(Vattu* x){
		if(n == MAX) expand();
		arr[n++] = x;
	}
	~arrayVT(){
		delete[] arr;
	}
};
struct arrayINT{
	int MAX;
	int n = 0; 
	int* arr;
	arrayINT(int mx){
		MAX = mx;
		arr = new int[MAX];
	}
	void expand(){
		MAX *= 2;
		int* nn = new int[MAX];
		for(int i = 0; i < n; i++){
			nn[i] = arr[i];
		}
		delete[] arr;
		arr = nn;
	}
	void push(int x){
		if(n == MAX) expand();
		arr[n++] = x;
	}
	~arrayINT(){
		delete[] arr;
	}
};
int getHeight(nodeVT* &p){
	if(p == NULL) return 0;
	return p->height;
}
int getBalance(nodeVT* &p){
	if(p == NULL) return 0;
	return getHeight(p->left) - getHeight(p->right);
}
nodeVT* RightRotate(nodeVT* &p){
	nodeVT* x = p->left;
	p->left = x->right;
	x->right = p;
	
	p->height = max(getHeight(p->left), getHeight(p->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	return x;
}
nodeVT* LeftRotate(nodeVT* &p){
	nodeVT* x = p->right;
	p->right = x->left;
	x->left = p;
	
	p->height = max(getHeight(p->left), getHeight(p->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	return x;
}
void Clear(nodeVT* &root){
	if(root == NULL) return;
	Clear(root->left);
	Clear(root->right);
	delete root; root = NULL;
}
nodeVT* fmin(nodeVT* &root){
	nodeVT* tmp = root;
	while(tmp->left != NULL){
		tmp = tmp->left;
	}
	return tmp;
}
void vtest(nodeVT* &root){
	if(root == NULL) return;
	cout << (root->data).MAVT << " ";
	cout << ((root->left) ? (root->left->data).MAVT : "NULL") << " ";
	cout << ((root->right) ? (root->right->data).MAVT : "NULL") << "\n";
	vtest(root->left);
	vtest(root->right);
	return;
} 
nodeVT* AddVT(nodeVT* &root, Vattu x){
	if(root == NULL){
		return new nodeVT{x, 1, NULL, NULL};
	} 
	int ss = ((root->data).MAVT).compare(x.MAVT);
	if(ss > 0) root->left = AddVT(root->left, x);
	else if(ss < 0) root->right = AddVT(root->right, x);
	else return root;
	
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	int bf = getBalance(root);
	if(bf > 1){
		int tmp = ((root->left->data).MAVT).compare(x.MAVT);
		if(tmp > 0) return RightRotate(root);
		else if(tmp < 0){
			root->left = LeftRotate(root->left);
			return RightRotate(root);
		}
	}
	else if(bf < -1){
		int tmp = ((root->right->data).MAVT).compare(x.MAVT); 
		if(tmp < 0)  return LeftRotate(root);
		else if(tmp > 0){
			root->right = RightRotate(root->right);
			return LeftRotate(root);
		}
	}
	return root;
}
nodeVT* DelVT(nodeVT* &root, Vattu x){
	if(root == NULL) return root;
	int ss = ((root->data).MAVT).compare(x.MAVT);
	if(ss > 0) root->left = DelVT(root->left, x);
	else if(ss < 0) root->right = DelVT(root->right, x);
	else{
		if(root->left == NULL || root->right == NULL){
			nodeVT* tmp = ((root->left != NULL) ? root->left : root->right);
			delete root; root = NULL;
			return tmp;
		}
		else{
			nodeVT* tmp =  fmin(root->right);
			root->data = tmp->data;
			root->right = DelVT(root->right, tmp->data);
		}
	}
	
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	int bf = getBalance(root), bl = getBalance(root->left), br = getBalance(root->right);
	if(bf > 1){
		if(bl >= 0) return RightRotate(root);
		else{
			root->left = LeftRotate(root->left);
			return RightRotate(root);
		}
	}
	else if(bf < -1){
		if(br <= 0) return LeftRotate(root);
		else{
			root->right = RightRotate(root->right);
			return LeftRotate(root);
		}
	}
	return root;
}
void Travel(nodeVT* &root, arrayVT &vec, string &s){
	if(root == NULL) return;
	if(((root->data).MAVT).find(s) != string::npos){
		vec.push(&(root->data));
	}
	Travel(root->left, vec, s);
	Travel(root->right, vec, s);
	return;
}
bool cmp(Vattu* &x, Vattu* &y){
	int ss = ((*x).TENVT).compare((*y).TENVT);
	return (ss < 0);
}
void Merge(arrayVT &vec, int l, int m, int r){
	arrayVT u{m - l + 1};
	arrayVT v(r - m);
	for(int i = l; i <= m; i++) u.push(vec.arr[i]);
	for(int j = m + 1; j <= r; j++) v.push(vec.arr[j]);
	int i = 0, j = 0;
	while(i < u.n && j < v.n){
		if(cmp(u.arr[i], v.arr[j])){
			vec.arr[l++] = u.arr[i++];
		}
		else{
			vec.arr[l++] = v.arr[j++];
		}
	}
	while(i < u.n) vec.arr[l++] = u.arr[i++];
	while(j < v.n) vec.arr[l++] = v.arr[j++];
}
void MergeSort(arrayVT &vec, int l, int r){
	if(l >= r) return;
	int m = (l + r) / 2;
	MergeSort(vec, l, m);
	MergeSort(vec, m + 1, r);
	Merge(vec, l, m, r);
}
void inpageVT(arrayVT &vec, int i){
	gotoxy(3, 8 + i % sh); cout << i + 1;
	gotoxy(7, 8 + i % sh); cout << (*(vec.arr[i])).MAVT;
	gotoxy(25, 8 + i % sh); cout << (*(vec.arr[i])).TENVT;
	gotoxy(48, 8 + i % sh); cout << (*(vec.arr[i])).SL;
	gotoxy(55, 8 + i % sh); cout << (*(vec.arr[i])).DVT;
}
bool FindVT(nodeVT* &root, string ms){
	nodeVT* tmp = root;
	while(tmp != NULL && (tmp->data).MAVT != ms){
		int ss = (tmp->data).MAVT.compare(ms);
		if(ss > 0) tmp = tmp->left;
		else if(ss < 0) tmp = tmp->right;
	}
	if(tmp == NULL) return 0;
	return 1;
}
Vattu makeVT(nodeVT* &dsvt){
	int cot = 72, dong = 6, sz = 4, chon = 0;
	gotoxy(cot + 4, dong - 2); Title(); cout << "THEM VAT TU";
	gotoxy(cot, dong);
	string menu[sz] = {"MAVT: ", "TEN: ", "DON VI TINH: ", "SO LUONG: "}, st[sz]; 
	Normal();
	for(int i = 0; i < 4; i++){
		st[i] = "";
	}
	for(int i = 0; i <= 6; i++){
		gotoxy(cot - 1, dong + i); 
		cout << "|                         |";
	}  
	ShowMenu(menu, sz, cot, dong); 
	gotoxy(cot - 1, dong - 1); 
	cout << "+-------------------------+";
	gotoxy(cot - 1, 13); 
	cout << "+-------------------------+";
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
						if(!st[0].size()) 				Warning("Ma vat tu khong hop le!", cot, 14);
						else if(FindVT(dsvt, st[0])) 	Warning("Ma vat tu da ton tai!", cot, 14);
						else if(!st[1].size()) 			Warning("Ten vat tu khong hop le!", cot, 14);
						else if(!st[2].size()) 			Warning("Don vi tinh khong hop le!", cot, 14);
						else if(!st[3].size()) 			Warning("So luong khong hop le!", cot, 14);
						else return Vattu{st[0], st[1], st[2], stoi(st[3]), 0};
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
				return Vattu{"", "", "", -2, 0};
			}
			else{
				if(chon == 0){
					if((is_num(k) || is_char(k)) && st[chon].size() < 22 - menu[chon].size()) st[chon] += toupper(c);
				}
				else if(chon == 1){
					if(st[chon].size() == 25 - menu[chon].size()) continue;
					if(k == Space && st[chon].size()){
						st[chon] += toupper(c);
					}
					else if(is_char(k)) st[chon] += toupper(c);
				}
				else if(chon == 2){
					if(st[chon].size() == 22 - menu[chon].size()) continue;
					if(is_char(k)) st[chon] += toupper(c);
				}
				else{
					if(st[chon].size() == 6) continue;
					if(is_num(k)){
						if(st[chon].size() == 0 && c == '0') continue;
						else st[chon] += c;
					} 
				}

			}
			if(chon != 1) format(st[chon]);
			Highlight(); gotoxy(cot, dong + chon); cout << menu[chon] << st[chon];
		} 
	}
	return Vattu{"", "", "", -2, 0};
}
Vattu resetVT(nodeVT* &dsvt, Vattu x){
	int cot = 72, dong = 6, sz = 4, chon = 1;
	gotoxy(cot + 2, dong - 2); Title(); cout << "CHINH SUA VAT TU";
	string menu[sz] = {"MAVT: ", "TEN: ", "DON VI TINH: ", "SO LUONG: "}, st[sz];
	st[0] = x.MAVT; st[1] = x.TENVT; st[2] = x.DVT; st[3] = to_string(x.SL); 
	Normal();
	for(int i = 0; i <= 7; i++){
		gotoxy(cot - 1, dong + i); 
		cout << "|                         |";
	}
	for(int i = 0; i < 4; i++){
		gotoxy(cot, dong + i); cout << menu[i] << st[i];
	}
	gotoxy(cot - 1, dong - 1); 
	cout << "+-------------------------+";
	gotoxy(cot - 1, 14); 
	cout << "+-------------------------+";
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
						chon = 3 - chon;
						gotoxy(cot, dong + chon);
						Highlight(); cout << menu[chon] << st[chon];			
						break;
					}
				case Down:
					{
						gotoxy(cot, dong + chon);
						Normal(); cout << menu[chon] << st[chon];
						chon = 3 - chon;
						gotoxy(cot, dong + chon);
						Highlight(); cout << menu[chon] << st[chon];
						break;				
					}
				case F5:
					{
						format(st[1]);
						if(!st[1].size()) Warning("Ten vat tu khong hop le!", cot, 15);
						else if(!st[2].size()) Warning("Don vi tinh khong hop le!", cot, 15);
						else return Vattu{st[0], st[1], st[2], stoi(st[3]), x.used};
						break;
					}	
				case F1:
					{	
						if(x.used > 0){
							gotoxy(cot, 15); Highlight();
							cout << "Vat tu da lap hoa don"; gotoxy(cot, 16);
							cout << "khong the xoa!";
							Sleep(3000);
							while(_kbhit()){
								_getch();
							}
							Normal(); gotoxy(cot, 15);
							cout << "                     "; gotoxy(cot, 16);
							cout << "              ";
							gotoxy(cot, dong + chon); Highlight(); cout << menu[chon] << st[chon];
						} 
						else{
							gotoxy(cot, 15); Highlight();
							cout << "Ban co chac muon xoa"; gotoxy(cot, 16);							
							cout << "vat tu nay khong? (Y/N): ";
							char tx;
							while(1){
								tx = getch();
								if(tx == 'Y' || tx == 'y'){
									Normal();
									gotoxy(cot, 15); cout << "                    ";
									gotoxy(cot, 16); cout << "                         ";
									return Vattu{st[0], st[1], st[2], -1, x.used};
								} 
								else if(tx == 'N' || tx == 'n'){
									Normal();
									gotoxy(cot, 15); cout << "                    ";
									gotoxy(cot, 16); cout << "                         ";
									gotoxy(cot, dong + chon); Highlight(); cout << menu[chon] << st[chon];
									break;
								} 
							} 
							break;	
						}
						break;
					}	
			}		
		}
		else{
			int k = int(c);
			if(k == Enter){
				gotoxy(cot, dong + chon);
				Normal(); cout << menu[chon] << st[chon];
				chon = 3 - chon;
				gotoxy(cot, dong + chon);
				Highlight(); cout << menu[chon] << st[chon];
			} 
			else if(k == Back){
				if(st[chon].size()) st[chon].pop_back();
				gotoxy(cot, dong + chon); 
				Normal(); cout << menu[chon] << st[chon] << " ";
			}
			else if(k == ESC){
				return Vattu{"", "", "", -2, 0};
			}
			else{
				if(chon == 1){
					if(st[chon].size() == 25 - menu[chon].size()) continue;
					if(k == Space && st[chon].size()){
						st[chon] += toupper(c);
					}
					else if(is_char(k)) st[chon] += toupper(c);
				}
				else if(chon == 2){
					if(st[chon].size() == 22 - menu[chon].size()) continue;
					if(is_char(k)) st[chon] += toupper(c);
				}
			}
			if(chon != 1) format(st[chon]);
			Highlight(); gotoxy(cot, dong + chon); cout << menu[chon] << st[chon];
		} 
	}
	return Vattu{"", "", "", -2, 0};
}
int ShowVT(nodeVT* &dsvt, string &s, int page){
	arrayVT vec{5};
	Travel(dsvt, vec, s);
	MergeSort(vec, 0, vec.n - 1);
//	for(auto x : vec){
//		cout << x.MAVT << "\n";
//	}
	Normal();
	int chon = 0, cnt = 1;
	xoatab();
	gotoxy(2, 4);
	for(int i = 0; i <= 7 + s.size(); i++) cout << " ";
	gotoxy(27, 2); Title(); cout << "DANH SACH VAT TU"; gotoxy(2, 4); Highlight();
	cout << "Find: " << s; gotoxy(2, 5); Normal();
	cout << "+---------------------------------------------------------------+"; gotoxy(2, 6);
	cout << "|STT|       MAVT      |      TEN VAT TU      |  SL  |    DVT    |"; gotoxy(2, 7);
	cout << "|---|-----------------|----------------------|------|-----------|";
	for(int i = 0; i < 10; i++){
		gotoxy(2, 8 + i); cout << "|   |                 |                      |      |           |";
	}
	gotoxy(2, 18); cout << "+---------------------------------------------------------------+";
	gotoxy(42, 20); 
	int mxpage = ceil(vec.n * 1.0 / sh); 
	if(page == 1)          cout << "Trang      " << page << " / " << max(mxpage, 1);
	else if(page > 1) 	   cout << "Trang  <-- " << page << " / " << max(mxpage, 1);
	if(page < mxpage)  	   cout << " -->";
	gotoxy(2, 23);
	cout << "+---------------------------------------------------------------+"; gotoxy(2, 24);
	cout << "| ESC: Thoat | F2: Them VT | F3: Sua VT                         |"; gotoxy(2, 25);
	cout << "+---------------------------------------------------------------+";
	Box(); gotoxy(4, 24); cout << "ESC"; 
	gotoxy(17, 24); cout << "F2"; 
	gotoxy(31, 24); cout << "F3"; Normal();
	for(int i = sh * (page - 1); i < sh * page; i++){
		if(i >= vec.n){
			continue;
		}
		inpageVT(vec, i);
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
					inpageVT(vec, sh * (page - 1) + chon - 1);
				}
				chon = (chon + 1) % cnt;
				Highlight(); 
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpageVT(vec, sh * (page - 1) + chon - 1);
				}
			}
			else if(c == Up){
				Normal();
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpageVT(vec, sh * (page - 1) + chon - 1);
				}
				chon = (chon - 1 + cnt) % cnt;
				Highlight(); 
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpageVT(vec, sh * (page - 1) + chon - 1);
				}
			}
			else if(c == F2){
				Vattu x = makeVT(dsvt);
				if(x.SL != -2) dsvt = AddVT(dsvt, x);
				if(ShowVT(dsvt, s, 1) == 0) return 0;
			}
			else if(c == F3){
				if(chon <= 0) continue;
				Vattu x = *(vec.arr[sh * (page - 1) + chon - 1]);
				x = resetVT(dsvt, x);
				if(x.SL != -2){
					if(x.SL == -1) DelVT(dsvt, x);
					else{
						nodeVT* tmp = dsvt;
						while(1){
							int ss = ((tmp->data).MAVT).compare(x.MAVT);
							if(ss > 0) tmp = tmp->left;
							else if(ss < 0) tmp = tmp->right;
							else{
								tmp->data = x;
								break;
							}
						}
					}
				} 
				if(ShowVT(dsvt, s, 1) == 0) return 0;
			}
			else if(c == Left){
				if(page > 1){
					page--;
					if(ShowVT(dsvt, s, page) == 0) return 0;
				}		
			}
			else if(c == Right){
				if(page < mxpage){
					page++;
					if(ShowVT(dsvt, s, page) == 0) return 0;
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
				if(ShowVT(dsvt, s, 1) == 0) return 0;
			} 	
		}	
	}
	
	return 0;
}

//---------------------------------------------------------//
struct CT_HOADON{
	string MAVT;
	int soluong, dongia, VAT;
};
struct HOADON{
	int MAX;
	int n = 0;
	string SoHD;
	int dd, mm, yy;
	char type;
	CT_HOADON* cthd; 
	
	HOADON(int mx){
		MAX = mx;
		cthd = new CT_HOADON[MAX];
	}
	void expand(){
		MAX *= 2;
		CT_HOADON* nn = new CT_HOADON[MAX];
		for(int i = 0; i < n; i++){
			nn[i] = cthd[i];
		}
		delete[] cthd;
		cthd = nn;
	}
	void push(CT_HOADON x){
		if(n == MAX) expand();
		cthd[n++] = x;
	}
	~HOADON(){
		delete[] cthd;
	}
};
struct nodeHD{
	HOADON data;
	nodeHD* next;
};
nodeHD* makeHD(HOADON x){
	nodeHD* newnode = new nodeHD{5};
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
struct arrayNV{
	int MAX;
	int n;
	Nhanvien** arr;
	arrayNV(int mx){
		n = 0;
		MAX = mx;
		arr = new Nhanvien*[MAX];
	}
	void expand(){
		MAX *= 2;
		Nhanvien** newarr = new Nhanvien*[MAX];
		for(int i = 0; i < n; i++){
			newarr[i] = arr[i];
		}
		delete[] arr;
		arr = newarr;
	}
	void push(Nhanvien* x){
		if(n == MAX) expand();
		arr[n++] = x;
	}
	~arrayNV(){
		delete[] arr;
	}
};
bool FindNV(listNV &dsnv, string ms){
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
	Normal();
	for(int i = 0; i <= 6; i++){
		gotoxy(cot - 1, dong + i); 
		cout << "|                         |";
	}
	ShowMenu(menu, sz, cot, dong);   
	gotoxy(cot - 1, dong - 1); 
	cout << "+-------------------------+";
	gotoxy(cot - 1, 13); 
	cout << "+-------------------------+";
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
						if(!st[0].size()) 							Warning("Ma nhan vien khong hop le!", cot, 14);
						else if(FindNV(dsnv, st[0])) 				Warning("Ma nhan vien da ton tai!", cot, 14);
						else if(!st[1].size()) 						Warning("Ho nhan vien khong hop le!", cot, 14);
						else if(!st[2].size()) 						Warning("Ten nhan vien khong hop le!", cot, 14);
						else if(st[3] != "NAM" && st[3] != "NU") 	Warning("Gioi tinh khong hop le!", cot, 14);
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
					if((is_num(k) || is_char(k)) && st[chon].size() < 25 - menu[chon].size()) st[chon] += toupper(c);
				}
				else if(chon == 1){
					if(st[chon].size() == 25 - menu[chon].size()) continue;
					if(k == Space && st[chon].size()){
						st[chon] += toupper(c);
					}
					else if(is_char(k)) st[chon] += toupper(c);
				}
				else if(chon == 2){
					if(st[chon].size() == 25 - menu[chon].size()) continue;
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
	for(int i = 0; i <= 7; i++){
		gotoxy(cot - 1, dong + i); 
		cout << "|                         |";
	}
	for(int i = 0; i < 4; i++){
		gotoxy(cot, dong + i); cout << menu[i] << st[i];
	}
	gotoxy(cot - 1, dong - 1); 
	cout << "+-------------------------+";
	gotoxy(cot - 1, 14); 
	cout << "+-------------------------+";
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
						if(!st[1].size()) Warning("Ho nhan vien khong hop le!", cot, 15);
						else if(!st[2].size()) Warning("Ten nhan vien khong hop le!", cot, 15);
						else if(st[3] != "NAM" && st[3] != "NU") Warning("Gioi tinh khong hop le!", cot, 15);
						else return new Nhanvien{x.SHD, st[0], st[1], st[2], st[3], x.dshd};
						break;
					}
				case F1:
					{	
						if(x.SHD > 0){
							gotoxy(cot, 15); Highlight();
							cout << "Nhan vien da lap hoa don"; gotoxy(cot, 16);
							cout << "khong the xoa!";
							Sleep(3000);
							while(_kbhit()){
								_getch();
							}
							Normal(); gotoxy(cot, 15);
							cout << "                        "; gotoxy(cot, 16);
							cout << "              ";
							gotoxy(cot, dong + chon); Highlight(); cout << menu[chon] << st[chon];
						} 
						else{
							gotoxy(cot, 15);Highlight();
							cout << "Ban co chac muon xoa"; gotoxy(cot, 16);							
							cout << "nhan vien nay khong?(Y/N): ";
							char tx;
							while(1){
								tx = getch();
								if(tx == 'Y' || tx == 'y'){
									Normal();
									gotoxy(cot, 15); cout << "                    ";
									gotoxy(cot, 16); cout << "                           ";
									return new Nhanvien{-1, x.MANV, x.HO, x.TEN, x.PHAI, NULL};
								} 
								else if(tx == 'N' || tx == 'n'){
									Normal();
									gotoxy(cot, 15); cout << "                    ";
									gotoxy(cot, 16); cout << "                           ";
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
					if((is_num(k) || is_char(k)) && st[chon].size() < 25 - menu[chon].size()) st[chon] += toupper(c);
				}
				else if(chon == 1){
					if(st[chon].size() == 25 - menu[chon].size()) continue;
					if(k == Space && st[chon].size()){
						st[chon] += toupper(c);
					}
					else if(is_char(k)) st[chon] += toupper(c);
				}
				else if(chon == 2){
					if(st[chon].size() == 25 - menu[chon].size()) continue;
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
void AddNV(listNV &dsnv, Nhanvien* &x){
	if(x == NULL) return;
	if(dsnv.n >= MAXNV){
		delete x; x = NULL;
		Thongbao("Danh sach nhan vien da day!");
		return;
	}
	int l = 0, r = dsnv.n;
	while(l < r){
		int mid = (l + r) / 2;
		int tmp = ((*dsnv.node[mid]).TEN).compare((*x).TEN);
		if(tmp == 0) tmp = ((*dsnv.node[mid]).HO).compare((*x).HO);
		if(tmp <= 0) l = mid + 1;
		else r = mid;
	}
	dsnv.n++;
	for(int j = dsnv.n - 1; j > l; j--){
		dsnv.node[j] = dsnv.node[j - 1];
		
	}
	dsnv.node[l] = x;
}
void DelNV(listNV &dsnv, Nhanvien* &x){
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
void SetNV(listNV &dsnv, Nhanvien* &x){
	if(x == NULL) return;
	else if((*x).SHD == -1){
		DelNV(dsnv, x);
		delete x;
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
void inpageNV(listNV &dsnv, arrayINT &vec, int i){
	Nhanvien x = *(dsnv.node[vec.arr[i]]);
	gotoxy(3, 8 + i % sh); cout << i + 1;
	gotoxy(7, 8 + i % sh); cout << x.MANV;
	gotoxy(25, 8 + i % sh); cout << x.HO;
	gotoxy(48, 8 + i % sh); cout << x.TEN;
	gotoxy(62, 8 + i % sh); cout << x.PHAI;
}
int ShowNV(listNV &dsnv, string &s, int page){
	arrayINT vec{5};
	for(int i = 0; i < dsnv.n; i++){
		if(((*dsnv.node[i]).MANV).find(s) != string::npos){
			vec.push(i);
		}
	}
	Normal();
	int chon = 0, cnt = 1;
	Normal();
	xoatab();
	gotoxy(2, 4);
	for(int i = 0; i <= 7 + s.size(); i++) cout << " ";
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
	gotoxy(2, 18); cout << "+---------------------------------------------------------------+";
	gotoxy(42, 20); 
	int mxpage = ceil(vec.n * 1.0 / sh); 
	if(page == 1)          cout << "Trang      " << page << " / " << max(mxpage, 1);
	else if(page > 1) 	   cout << "Trang  <-- " << page << " / " << max(mxpage, 1);
	if(page < mxpage)  	   cout << " -->";
	gotoxy(2, 23);
	cout << "+---------------------------------------------------------------+"; gotoxy(2, 24);
	cout << "| ESC: Thoat | F2: Them NV | F3: Sua NV |                       |"; gotoxy(2, 25);
	cout << "+---------------------------------------------------------------+";
	Box(); gotoxy(4, 24); cout << "ESC"; 
	gotoxy(17, 24); cout << "F2"; 
	gotoxy(31, 24); cout << "F3"; Normal();
	for(int i = sh * (page - 1); i < sh * page; i++){
		if(i >= vec.n){
			continue;
		}
		inpageNV(dsnv, vec, i);
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
					inpageNV(dsnv, vec, sh * (page - 1) + chon - 1);
				}
				chon = (chon + 1) % cnt;
				Highlight(); 
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpageNV(dsnv, vec, sh * (page - 1) + chon - 1);
				}
			}
			else if(c == Up){
				Normal();
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpageNV(dsnv, vec, sh * (page - 1) + chon - 1);
				}
				chon = (chon - 1 + cnt) % cnt;
				Highlight(); 
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpageNV(dsnv, vec, sh * (page - 1) + chon - 1);
				}
			}
			else if(c == F2){
				Nhanvien* x = makeNV(dsnv);
				AddNV(dsnv, x);
				if(ShowNV(dsnv, s, 1) == 0) return 0;
			}
			else if(c == F3){
				if(chon <= 0) continue;
				Nhanvien tmp = *(dsnv.node[vec.arr[sh * (page - 1) + chon - 1]]);
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

//----------------------------------------------//
int is_day(int day, int month, int year){
	time_t now = time(0);
	tm* ct = localtime(&now);
	int cy = ct->tm_year + 1900;
	if(year < 1900) return -3;
	if(month < 1 || month > 12) return -2;
	int mxday;
	switch (month){
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:{
			mxday = 31;
			break;
		}
		case 4 : case 6: case 9: case 11:{
			mxday = 30;
			break;
		}
		case 2:{
			if(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) mxday = 29;
			else mxday = 28;
			break;
		}
	}
	if(day < 1 || day > mxday) return -1;
	if(year > 1900 + ct->tm_year) return -3;
	else if(year == 1900 + ct->tm_year){
		if(month > 1 + ct->tm_mon) return -2;
		else if(month == 1 + ct->tm_mon){
			if(day > ct->tm_mday) return -1;
		}
	}
	return 0;
}
//void showCTHD(string ms, nodeHD* &x){
//	Normal();
//	system("cls");
//	gotoxy()
//}
nodeHD* findHD(listNV &dsnv, string ms){
	for(int i = 0; i < dsnv.n; i++){
		nodeHD* tmp = (dsnv.node[i])->dshd;
		while(tmp != NULL){
			if((tmp->data).SoHD == ms) return tmp;
			tmp = tmp->next;
		}
	}
	return NULL;
}
void inpageHD(){
	
}
void makeCTHD(HOADON &tmp){
	Normal();
	system("cls");
	int cot = 3, dong = 1;
	string s = "  HOA DON ";
	s += tmp.SoHD; s += "  ";
	gotoxy(cot + 20, dong); Title(); cout << s;
	gotoxy(cot + 1, dong + 1); Normal(); cout << "Ngay: " << tmp.dd << '/' << tmp.mm << '/' << tmp.yy;
	gotoxy(cot + 1, dong + 2); cout << "Loai: " << (tmp.type == 'N' ? "Nhap" : "Xuat");
	gotoxy(cot, dong + 3); 
	cout << "+--------------------------------------------------------------------------------+"; gotoxy(cot, dong + 4); 
	cout << "|STT|       MAVT      |      TEN VAT TU      |  SL  |   GIA  |VAT(%)|    TIEN    |"; gotoxy(cot, dong + 5); 
	cout << "|---|-----------------|----------------------|------|--------|------|------------|";
	for(int i = 0; i < 10; i++){
		gotoxy(cot, dong + 6 + i);
		cout << "|   |                 |                      |      |        |     |             |";
	}
	gotoxy(cot, dong + 16);
	cout << "+--------------------------------------------------------------------------------+";
	

}
nodeHD* makeHD(listNV &dsnv){
	int cot = 72, dong = 6, sz = 5, chon = 0;
	gotoxy(cot + 4, dong - 2); Title(); cout << "THEM HOA DON";
	gotoxy(cot, dong);
	string menu[sz] = {"So HD: ", "Ngay: ", "Thang: ", "Nam: ", "Loai: "}, st[sz]; 
	for(int i = 0; i < 4; i++) st[i] = "";
	time_t now = time(0);
	tm* ct = localtime(&now);
	st[1] = to_string(ct->tm_mday);
	st[2] = to_string(ct->tm_mon);
	st[3] = to_string(ct->tm_year);
	Normal();
	for(int i = 0; i <= 7; i++){
		gotoxy(cot - 1, dong + i); 
		cout << "|                         |";
	}
	for(int i = 0; i <= 4; i++){
		gotoxy(cot, dong + i); cout << menu[i] << st[i];
	}
	gotoxy(cot - 1, dong - 1); 
	cout << "+-------------------------+";
	gotoxy(cot - 1, 14); 
	cout << "+-------------------------+";
	gotoxy(cot , 12); 
	cout << "-------------------------"; gotoxy(cot - 1, 13);
	cout << "|ESC: Thoat  |  F5: Nhap HD";
	Box(); gotoxy(cot, 13); cout << "ESC";
	gotoxy(cot + 15, 13); cout << "F5"; Normal();
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
						int x = is_day(stoi(st[1]), stoi(st[2]), stoi(st[3]));
						if(!st[0].size()) 						Warning("So hoa don khong hop le!", cot, 15);
						else if(findHD(dsnv, st[0]) != NULL) 	Warning("So hoa don da ton tai!", cot, 15);
						else if(x == -1) 						Warning("Ngay khong hop le!", cot, 15);
						else if(x == -2) 						Warning("Thang khong hop le!", cot, 15);
						else if(x == -3) 						Warning("Nam khong hop le!", cot, 15);
						else if(!st[4].size()) 					Warning("Loai hoa don khong hop le!", cot, 15);
						else{
							//them chi tiet hoa don
							HOADON tmp{5};
							tmp.SoHD = st[0]; tmp.type = st[4][0];
							tmp.dd = stoi(st[1]); tmp.mm = stoi(st[2]), tmp.yy = stoi(st[3]);
							nodeHD* x = new nodeHD{tmp, NULL};
							return x; 
						} 
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
					if((is_num(k) || is_char(k)) && st[chon].size() < 25 - menu[chon].size()) st[chon] += toupper(c);
				}
				else if(chon == 1 || chon == 2 || chon == 3){
					if(is_num(k)){
						if(chon == 1 || chon == 2){
							if(st[chon].size() < 1) st[chon] += c;
						}
						else if(st[chon].size() < 4) st[chon] += c;
					} 
				}
				else{
					c = toupper(c);
					if((c == 'N' || c == 'X') && st[chon].size() < 1) st[chon] += c;
				}					
			}
			Highlight(); gotoxy(cot, dong + chon); cout << menu[chon] << st[chon];
		}
	}
}
int ShowHD(listNV &dsnv, string &s, int page){
	arrayINT vec{5};
	for(int i = 0; i < dsnv.n; i++){
		if(((*dsnv.node[i]).MANV).find(s) != string::npos){
			vec.push(i);
		}
	}
	Normal();
	int chon = 0, cnt = 1;
	Normal();
	xoatab();
	gotoxy(2, 4);
	for(int i = 0; i <= 7 + s.size(); i++) cout << " ";
	gotoxy(27, 2); Title(); cout << "DANH SACH NHAN VIEN"; gotoxy(2, 4); Highlight();
	cout << "Find: " << s; gotoxy(2, 5); Normal();
	cout << "+---------------------------------------------------------------+"; gotoxy(2, 6);
	cout << "|STT|       MANV      |          HO          |     TEN     |PHAI|"; gotoxy(2, 7);
	cout << "|---|-----------------|----------------------|-------------|----|";
	for(int i = 0; i < 10; i++){
		gotoxy(2, 8 + i); cout << "|   |                 |                      |             |    |";
	}
	gotoxy(2, 18); cout << "+---------------------------------------------------------------+";
	gotoxy(42, 20); 
	int mxpage = ceil(vec.n * 1.0 / sh); 
	if(page == 1)          cout << "Trang      " << page << " / " << max(mxpage, 1);
	else if(page > 1) 	   cout << "Trang  <-- " << page << " / " << max(mxpage, 1);
	if(page < mxpage)  	   cout << " -->";
	gotoxy(2, 23);
	cout << "+---------------------------------------------------------------+"; gotoxy(2, 24);
	cout << "| ESC: Thoat | F2: Them HD | F3: Sua HD |                       |"; gotoxy(2, 25);
	cout << "+---------------------------------------------------------------+";
	Box(); gotoxy(4, 24); cout << "ESC"; 
	gotoxy(17, 24); cout << "F2"; 
	gotoxy(31, 24); cout << "F3"; Normal();
	for(int i = sh * (page - 1); i < sh * page; i++){
		if(i >= vec.n){
			continue;
		}
		inpageNV(dsnv, vec, i);
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
					inpageNV(dsnv, vec, sh * (page - 1) + chon - 1);
				}
				chon = (chon + 1) % cnt;
				Highlight(); 
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpageNV(dsnv, vec, sh * (page - 1) + chon - 1);
				}
			}
			else if(c == Up){
				Normal();
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpageNV(dsnv, vec, sh * (page - 1) + chon - 1);
				}
				chon = (chon - 1 + cnt) % cnt;
				Highlight(); 
				if(!chon){
					gotoxy(2, 4); cout << "Find: " << s;
				}
				else{
					inpageNV(dsnv, vec, sh * (page - 1) + chon - 1);
				}
			}
			else if(c == F2){
				if(chon <= 0) continue;
				if(ShowHD(dsnv, s, 1) == 0) return 0;
			}
			else if(c == F3){
				
				if(ShowHD(dsnv, s, 1) == 0) return 0;
			}
			else if(c == Left){
				if(page > 1){
					page--;
					if(ShowHD(dsnv, s, page) == 0) return 0;
				}		
			}
			else if(c == Right){
				if(page < mxpage){
					page++;
					if(ShowHD(dsnv, s, page) == 0) return 0;
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
				if(ShowHD(dsnv, s, 1) == 0) return 0;
			} 	
		}	
	}
	return 0;
}

// --------------------------------------------------------- //
void Print(string s, int x, int y, int cd, int cr){
	for(int i = 0; i < cr; i++){
		gotoxy(x, y + i);
		if(cd == 24) cout << "                         ";
		else if(cd == 44) cout << "                                             ";
	}
	gotoxy(x + int((cd - s.size()) / 2), y + int(cr / 2)); cout << s;
}
void pscr(int row, int col){
	if(row == 0){
		if(col == 0) Print("NHAN VIEN", 12, 12, 24, 5);
		else Print("VAT TU", 58, 12, 24, 5);
	}
	else{
		if(col == 0) Print("HOA DON", 12, 21, 24, 5);
		else Print("THOAT CHUONG TRINH", 58, 21, 24, 5);
	}
}
void Screen(){
	Normal();
	system("cls");
	Box();
	Print("QUAN LY VAT TU", 25, 3, 44, 5);
	SetColor(8); SetBGColor(7);
	pscr(0, 0); pscr(0, 1); pscr(1, 0); pscr(1, 1);
}

// ---------------------------------------------------------- //

bool OpenFileNV(listNV &dsnv){
	fstream fs;
	fs.open("Nhanvien.txt", ios::in);
	if(!fs.is_open()){
		Thongbao("Mo File Nhan vien that bai!"); return 0;
	} 
	Nhanvien x;
	while(fs >> x.MANV){
		fs.ignore();
		getline(fs, x.HO);
		fs >> x.TEN; fs >> x.PHAI;
		fs >> x.SHD;
		Nhanvien* tmp = new Nhanvien{x.SHD, x.MANV, x.HO, x.TEN, x.PHAI, NULL};
		AddNV(dsnv, tmp);
	}
	return 1;
}
bool OpenFileVT(nodeVT* &root){
	fstream fs;
	fs.open("Vattu.txt", ios::in);
	if(!fs.is_open()){
		Thongbao("Mo File Vat Tu that bai!"); return 0;
	}
	Vattu x;
	while(fs >> x.MAVT){
		fs.ignore();
		getline(fs, x.TENVT);
		fs >> x.DVT;
		fs >> x.SL;
		fs >> x.used; 
		root = AddVT(root, x);
	}
	return 1;
}

int main(){
	listNV dsnv;
	nodeVT* dsvt = NULL;
	string s = "";
	//Nhanvien* x = new Nhanvien{0, "N23", "NGUYEN THIEN", "NHAN", "NAM", NULL};
//	HOADON y = {0, 1931, 3, 10, 2025, 'N'};
//	HOADON z = {0, 2516, 3, 11, 2004, 'X'};

	//AddNV(dsnv, x);
	//AddHD(dsnv, 0, (*dsnv.node[0]).dshd, y);
//	AddHD(dsnv, 0, (*dsnv.node[0]).dshd, z);
//	nodeHD* tmp = (*dsnv.node[0]).dshd;

//	dtest(dsnv, 0, y);
//	if((*dsnv.node[0]).dshd != NULL){
//		nodeHD* head = (*dsnv.node[0]).dshd;
//		cout << head->data.SoHD;
//	}

	if(OpenFileNV(dsnv) == 0) return 0;
	if(OpenFileVT(dsvt) == 0) return 0;
	
	//makeHD();
	//gotoxy(0, 30);
	//return 0;
	
	
//	Vattu x = makeVT(dsvt);
//	gotoxy(0, 25);
//	cout << x.MAVT << "\n" << x.TENVT << "\n" << x.SL + 13 << "\n" << x.DVT << "\n" << x.used;
	//makeNV(dsnv);
	//ShowNV(dsnv, s, 1);
	//ShowVT(dsvt, s, 1);
	
	
//	gotoxy(30, 30);
//	Normal();
//	return 0;
	
	
	
	
	int col = 0, row = 0;
	char c;
	Screen();
	Highlight();
	pscr(row, col);
	while(1){
		c = getch();
		if(c <= 0) c = getch();
		if(c == Up || c == Down){
			SetColor(8); SetBGColor(7);
			pscr(row, col);
			row = 1 - row;
			Highlight();
			pscr(row, col);
		}
		else if(c == Left || c == Right){
			SetColor(8); SetBGColor(7);
			pscr(row, col);
			col = 1 - col;
			Highlight();
			pscr(row, col);
		}
		else if(c == ESC){
			break;
		}
		else if(c == Enter){
			Normal(); system("cls");
			if(row == 0 && col == 0){
				ShowNV(dsnv, s, 1);
			} 
			else if(row == 0 && col == 1){
				ShowVT(dsvt, s, 1);
			} 
			else if(row == 1 && col == 0){
//				break;
				ShowHD(dsnv, s, 1);
			} 
			else if(row == 1 && col == 1) break;
			Screen();
			Highlight();
			pscr(row, col);
			s = "";
		}
	}
	gotoxy(30, 30);

//	ShowNV(dsnv, s, 1);

	//resetNV(dsnv, x);
//	AddHD(dsnv, 0, (*dsnv.node[0]).dshd, y);



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	Clear(dsvt);
	for(int i = 0; i < dsnv.n; i++){
		delete dsnv.node[i];
	}
	dsnv.n = 0;
}
