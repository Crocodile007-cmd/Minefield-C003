//Minefield C003
//Crocodile 007
//2020.1.27

#include <windows.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>

#define COLOR_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#define COLOR_YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN)
#define COLOR_BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE)
#define COLOR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED)
#define COLOR_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_GREEN)
using namespace std;

enum Error{TYPE, RANGE, UNKNOWN};
void in_INT(int* x, const int& r1, const int& r2){
	string stmp;
	getline(cin, stmp);
	if(stmp.size() < 1 || stmp.size() > 5){
		throw UNKNOWN;
	}
	for(int i = 0; i < stmp.size(); ++i){
		if(!isdigit(stmp[i])){
			throw TYPE;
		}
	}
	stringstream ios;
	ios << stmp;
	long long ltmp;
	ios >> ltmp;
	if(ltmp < r1 || ltmp > r2){
		throw RANGE;
	}
	*x = ltmp;
}
void read(const string& a, const int& t, const int& T){
	for(int i = 0; i < a.size(); ++i){
		cerr << a[i];
		Sleep(t);
	}
	Sleep(T);
}
class mfd{
	friend ostream& operator<< (ostream& os, const mfd& tmp);
 public:
 	unsigned x, y, m, s;
 	short mine[105][105];
 	char see[105][105];
 	mfd(){x = y = m = s = 0;}
 	void IS(const int& a, const int& b, const int& c);
 	void printf();
 	void F(const int& x, const int& y, int* mark);
 private:
	short replay[105][105];
};
void mfd::IS(const int& a, const int& b, const int& c){
	x = a;
	y = b;
	if(m <= a*b){
		m = c;
		s = a*b-m;
	}
	for(int i = 0; i <= y; ++i){ //0
		for(int j = 0; j <= x; ++j){
			mine[i][j] = replay[i][j] = (s<m);
			see[i][j] = '?';
		}
	}
	int ans = 0;
	srand((unsigned)time(NULL));
	while(ans != (s<m?s:m)){
		int P1 = rand()%y, P2 = rand()%x;
		if(mine[P2][P1] == (s<m)){
			mine[P2][P1] = replay[P2][P1] = (s>=m);
			++ans;
		}
	}
	//Time optimization:
	//if(m < s) initialize to vacant land, and then set the mine randomly.
}
ostream& operator<< (ostream& os, const mfd& tmp){
	for(int i = 1; i <= tmp.x; ++i){
		if(i%10 == 1){
			COLOR_YELLOW;
		}
		os << " " << i%10;
		COLOR_WHITE;
	}
	os << "\n";
	for(int i = 1; i <= tmp.y; ++i){
		if(i%10 == 1){
			COLOR_YELLOW;
		}
		os << i%10;
		COLOR_WHITE;
		for(int j = 0; j < tmp.x; ++j){
			if(tmp.see[i-1][j] == '?'){
				COLOR_GREEN;
				os << "¡ö";
			}
			else{
				if(tmp.see[i-1][j] == 'P')
					COLOR_RED;
				else
					COLOR_BLUE;
				os << tmp.see[i-1][j] << " ";
			}
		}
		COLOR_WHITE;
		if(i%10 == 1){
			COLOR_YELLOW;
		}
		os << i%10 << "\n";
		COLOR_WHITE;
	}
	for(int i = 1; i <= tmp.x; ++i){
		if(i%10 == 1){
			COLOR_YELLOW;
		}
		os << " " << i%10;
		COLOR_WHITE;
	}
	os << "\n";
	return os;
}
void mfd::printf(){
	for(int i = 1; i <= x; ++i){
		cout << " " << i%10;
	}
	cout << "\n";
	for(int i = 1; i <= y; ++i){
		stringstream ios;
		ios << i%10;
		for(int j = 0; j < x; ++j){
			if(replay[i-1][j] == 1) ios << "O ";
			else ios << "# "; //no mine
		}
		ios << i%10;
		string row;
		getline(ios, row);
		cout << row << "\n";
	}
	for(int i = 1; i <= x; ++i){
		cout << " " << i%10;
	}
	cout << "\n";
}
void mfd::F(const int& xx, const int& yy, int* mark){ //Depth-first search
	if(0 <= xx && xx < x && 0 <= yy && yy < y && mine[yy][xx] == 0){
		mine[yy][xx] = -1;
		--s;
		if(see[yy][xx] == 'P'){
			++mark;
		}
		see[yy][xx] = 
		 ((mine[yy+1][xx]   ==1?1:0)
		 +(mine[yy][xx+1]  ==1?1:0)
		 +(mine[yy+1][xx+1]==1?1:0)
		 +(mine[yy+1][xx-1]==1?1:0)
		 +(mine[yy-1][xx-1]==1?1:0)
		 +(mine[yy-1][xx+1]==1?1:0)
		 +(mine[yy-1][xx]  ==1?1:0)
		 +(mine[yy][xx-1]  ==1?1:0))+'0';
		if(see[yy][xx] == '0') see[yy][xx] = ' ';
		if(see[yy][xx] == ' '){
			F(xx+1, yy, mark);
			F(xx, yy+1, mark);
			F(xx-1, yy, mark);
			F(xx, yy-1, mark);
		}
	}
	return;
}
int main(int argc, char* argv[]){
	int x, y, m, mark;
	system("mode con: cols=40 lines=20");
	system("title Minefield C003");
	system("color 0f");
 dog0:
	cerr << "Crocodile 007\n2020.1.27\n\n";
	COLOR_GREEN;
	read("Welcome to minefield C003.\n", 50, 500);
	COLOR_WHITE;
	cerr << "[BIGIN]\n"
		 << "[Site]\n";
	string s_m_n = "";
	try{
		cerr << "Minefield size:\n";
		cerr << " x (2 ~ 100): ";
		in_INT(&x, 2, 100);
		cerr << " y (2 ~ 100): ";
		in_INT(&y, 2, 100);
		cerr << " mines (c,b,a,x / 1 ~ " << x*y-1 << "): ";
		string stmp;
		getline(cin, stmp);
		srand((unsigned)time(NULL));
		if(stmp == "a" || stmp == "A"){
			m = 1+x*y/7;
			s_m_n = "(a)";
		}
		else if(stmp == "b" || stmp == "B"){
			m = 1+x*y/13;
			s_m_n = "(b)";
		}
		else if(stmp == "c" || stmp == "C"){
			m = 1+x*y/15;
			s_m_n = "(c)";
		}
		else if(stmp == "x" || stmp == "X"){
			m = 1+rand()%(x*y-1);
			s_m_n = "(x)";
		}
		else{
			if(stmp.size() < 1 || stmp.size() > 5)
				throw UNKNOWN;
			for(int i = 0; i < stmp.size(); ++i){
				if(!isdigit(stmp[i])){
					throw TYPE;
				}
			}
			stringstream ios;
			ios << stmp;
			long long ltmp;
			ios >> ltmp;
			if(ltmp < 1 || ltmp > x*y-1)
				throw RANGE;
			m = ltmp;
		}
	}
	catch(Error e){
		if(e == TYPE)
			cerr << "[Error]Not a number.\n";
		else if(e == RANGE)
			cerr << "[Error]Out of range.\n";
		else if(e == UNKNOWN)
			cerr << "[Error]Unknown error.\n";
		Sleep(1000);
		system("cls");
		goto dog0;
	}
	mfd M;
	cerr << "[Mode]Random numbers setting.\n\n";
	M.IS(x, y, m);
	mark = m;
		
	short c, l;
	if(x > 80) c = 205;
	else if(x > 70) c = 165;
	else if(x > 60) c = 145;
	else if(x > 40) c = 125;
	else c = 85;
	if(y > 80) l = 125;
	else if(y > 60) l = 105;
	else if(y > 40) l = 85;
	else if(y > 20) l = 65;
	else l = 45;
	stringstream ios;
	ios << "mode con: cols=" << c << " lines=" << l;
	char con[30];
	ios.getline(con, 30);
		
	cerr << "[Information]\n"
		 << "Cols:" << x << " Lines:" << y << " Area:" << x*y << "\nT_mines:" << m << s_m_n << "\n\n";
	
	system("pause");
	system(con); //min: 14*1
	system("title Minefield_C003 Crocodile_007");
	const long long T = clock()/1000;
	system("cls");
		
	for(long long i = 0; M.m; ++i){
	 dog1:			
		cerr << "[Look]\n"
			 << "Round:" << i+1 << " Time(s):" << clock()/1000-T
			 << "\nCols:" << x << " Lines:" << y << " Area:" << x*y
			 << "\nT_mines:" << m << s_m_n << " Unknown:" << M.s+m << "/" << x*y << " Marks:" << mark
			 << "\nMap:\n";
		cout << M << endl;
		try{
			cerr << "[Play]\n";
			cerr << "Choose:\n Space(0)/Mark(1)/Break(2): ";
			int chs;
			in_INT(&chs, 0, 2);
			if(chs == 0){
				int xx, yy;
				cerr << "Coordinate:\n";
				cerr << " x (1 ~ " << x << "): ";
				in_INT(&xx, 1, x);
				cerr << " y (1 ~ " << y << "): ";
				in_INT(&yy, 1, y);
				xx -= 1; yy -= 1;
				if(M.mine[yy][xx] == 1){
					system("color 0c");
					system("cls");
					cerr << "[Replay]\n"
						 << "T_rounds:" << i+1 << " Time_cost(s):" << clock()/1000-T
						 << "\nCols:" << x << " Lines:" << y << " Area:" << x*y
						 << "\nMines:" << M.m << "/" << m << s_m_n << " Unknown:" << M.s+m << "/" << x*y << " Marks:" << mark
						 << "\nMap:\n";
					M.printf();
					read("Game over!\n", 300, 1000);
					cerr << "[END]\n";
					system("pause");
					break;
				}
				else if(M.mine[yy][xx] == 0){
					M.F(xx, yy, &mark);
					cerr << "[Mode]Success(Space)!\n";
				}
				else{
					cerr << "[Mode]Failure(Space)!\n";
				}
			}
			else if(chs == 1){
				int xx, yy;
				cerr << "Coordinate:\n";
				cerr << " x (1 ~ " << x << "):";
				in_INT(&xx, 1, x);
				cerr << " y (1 ~ " << y << "):";
				in_INT(&yy, 1, y);
				xx -= 1; yy -= 1;
				if(M.see[yy][xx] == '?'){
					M.see[yy][xx] = 'P';
					--mark;
					if(M.mine[yy][xx] == 1){
						--M.m;
					}
					cerr << "[Mode]Success(Mark)!\n";
				}
				else if(M.see[yy][xx] == 'P'){
					M.see[yy][xx] = '?';
					++mark;
					if(M.mine[yy][xx] == 1){
						++M.m;
					}
					cerr << "[Mode]Success(Mark)!\n";
				}
				else{
					cerr << "[Mode]Failure(Mark)!\n";
				}
			}
			else if(chs == 2){ //
				cerr << "Sure? yes(y)/no: ";
				string sure;
				getline(cin, sure);
				if(sure == "y" || sure == "Y"){
					system("color 0e");
					system("cls");
					cerr << "[Replay]\n"
						 << "T_rounds:" << i+1 << " Time_cost(s):" << clock()/1000-T
						 << "\nCols:" << x << " Lines:" << y << " Area:" << x*y
						 << "\nMines:" << M.m << "/" << m << s_m_n << " Unknown:" << M.s+m << "/" << x*y << " Marks:" << mark
						 << "\nMap:\n";
					M.printf();
					cerr << "[END]\n";
					system("pause");
					break;
				}
				else{
					cerr << "[Mode]Continue(Break)!\n";
				}
			}
		}
		catch(Error e){
			if(e == TYPE)
				cerr << "[Error]Not a number.\n";
			else if(e == RANGE)
				cerr << "[Error]Out of range.\n";
			else if(e == UNKNOWN)
				cerr << "[Error]Unknown error.\n";
			Sleep(1000);
			system("cls");
			goto dog1;
		}
		
		if(M.m < 1 && mark >= 0 || M.s < 1){
			system("color 0a");
			system("cls");
			cerr << "[Replay]\n"
				 << "T_rounds:" << i+1 << " Time_cost(s):" << clock()/1000-T
				 << "\nCols:" << x << " Lines:" << y << " Area:" << x*y
				 << "\nMines:" << M.m << "/" << m << s_m_n << " Unknown:" << M.s+m << "/" << x*y << " Marks:" << mark
				 << "\nMap:\n";
			M.printf();
			read("Win!\n", 300, 1000);
			cerr << "[END]\n";
			system("pause");
			break;
		}
		Sleep(1000);
		system("cls");
	}
	return main(argc, argv); //32533(main) 65065
}
/*
This version may have bugs. 
'?' was replaced with '(space)'.
New errors may occur!
*/
