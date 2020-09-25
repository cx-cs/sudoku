#include<iostream>
#include<ctime>
using namespace std;

struct stu {
	int li,ro,num;
}lastadd[81];
int a[9][9],num;

bool judgerule(int& line,int& row,int& k) {
	for(int i=0; i<9; i++)
		if(a[line][i]==k)return false;
	for(int i=0; i<9; i++)
		if(a[i][row]==k)return false;
	for(int i=line/3*3; i<=line/3*3+2; i++)
		for(int j=row/3*3; j<=row/3*3+2; j++)
			if(a[i][j]==k)return false;
	return true;
}

//根据目前数独的情况，确定出可填数字最少的格子，并回传对应的行和列。
void getnext(int & li,int & ro) {
	bool c[9][9][9]={0};
	int min=99999,mint=0;
	int i,j,n,m;
	for(i=0; i<9; i++){
		for(j=0; j<9; j++)
			if(a[i][j]!=-1) {
				for(n=0; n<9; n++) {
					//该位置不能填n+1
					c[i][j][n]=true; 
					//行列不能填 
					c[n][j][a[i][j]-1]=true; 
					c[i][n][a[i][j]-1]=true;
				}
				//九宫格不能填 
				for(n=i/3*3; n<=i/3*3+2; n++)
					for(m=j/3*3; m<=j/3*3+2; m++)
						c[n][m][a[i][j]-1]=true;
			}
	}
	for(i=0; i<9; i++){
		for(j=0; j<9; j++)
			if(a[i][j]==-1) {
				mint=0;//mint表示该格能填多少个数 
				for(n=0; n<9; n++) {
					if(c[i][j][n]!=true)
						mint++;
				}
				if(mint<min) {
					li=i;
					ro=j;
					min=mint;
				}
			}
	}
}

void input(){
	char tmp[]="8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4..";
	//char tmp[]="71..6..2.....894.74...27.53.....8.36.43...17.86.2.....32.95...19.631.....5..7..92";
	for(int i=0; i<9; i++) {
		for(int j=0; j<9; j++) {
			if(tmp[9*i+j]=='.')
				a[i][j]=-1;
			else {
				num++;
				a[i][j]=tmp[9*i+j]-48;
			}
		}
	}
}

void output(){
	for(int i=0; i<9; i++) {
		for(int j=0; j<9; j++) {
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}

void solve(){
	int li=-1,ro=-1,index=-1,testnum=1;
	bool add=true;
	while(num!=81) {
		if(add==true) getnext(li,ro);
		add=false;
		for(; testnum<=9; testnum++) {
			if(judgerule(li,ro,testnum)) {
				a[li][ro]=testnum;
				add=true;
				index++;
				lastadd[index]=stu{li,ro,testnum};
				testnum=1;
				num++;
				break;
			}
		}
		if(add==true)continue;
		else {
			li=lastadd[index].li;
			ro=lastadd[index].ro;
			testnum=lastadd[index].num+1;
			a[li][ro]=-1;
			index--;
			num--;
		}
	}
}

int main() {
	input();
	clock_t start=clock();
	solve();
	clock_t end=clock();
	output();
	printf("time used=%fms\n",1000*(double)(end-start)/CLOCKS_PER_SEC);
}
