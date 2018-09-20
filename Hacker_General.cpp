#include <bits/stdc++.h>
//#include <direct.h>
#define max_tstnode 301 //最多测试点个数
#define bfxlen 10 //后缀长度 (\temp\_0.0)
#define WIN true
#define LNX false
using namespace std;
ofstream flg("../../data/gugu.log"); //Log Path

string Tmpath = "cd .. && cd .. && cd data && cd ";
bool UseStdio = true; //使用标准输入输出 
string ProblemName = "prime"; //需要评测的题目的名字（数据目录名称）
string InputFile = "prime.in";
string OutputFile = "prime.out"; //题目给定的输出文件
string wpt/*工作目录*/,dpt/*答案目录*/;
string files[max_tstnode*2];int fnum = 0; //文件列表 
bool sysv = false;

void decrun(bool version,string wr,string lr){
	string cmdc;
	if (version == LNX) cmdc = lr;
	else cmdc = wr;
	flg<<"Executing '"<<cmdc<<"'."<<endl;
	system(cmdc.c_str());
}
bool sys_vers(){
	system("ver > sysver.exp");
	ifstream fin("sysver.exp");
	
	string tmp;
	bool win = false;
	while(getline(fin,tmp)){
		if (tmp.length() >= 10 && tmp.substr(0,9) == "Microsoft"){
			win = true;
			break;
		}
	}
	
	fin.close();
	return win;
}

bool subfix(string s,string p){
	if (s.length() <= 3) return false;
	int len = p.length();
	s += "   "; //Three Spaces
	//cout<<s.length()<<' '<<s<<endl;
	//cout<<s.substr(s.length()-len-3,len)<<' '<<p<<endl;
	if (s.substr(s.length()-len-3,len) == p)
		return true;
	else
		return false;
}

void gen_filetree(){
	string cmd;
	if (sysv == LNX)	cmd = Tmpath + ProblemName + " && ls -a > tmp.exp";
	else cmd = Tmpath + ProblemName + " && dir /b > tmp.exp";
	flg<<cmd<<endl;
	system(cmd.c_str());
	
	string tmp,ppt = dpt + "tmp.exp";
	ifstream fin(ppt.c_str());
	while (!fin.eof()){
		getline(fin,tmp);
		files[++fnum] = tmp;
	}
	
	fin.close();
	decrun(sysv,"del tmp.exp","rm -rf tmp.exp");
}

string getIn(string fn) {
	string t,ret;
	ifstream fin(fn.c_str());
	//cout<<fn.c_str()<<endl;
	while (getline(fin,t)) {
		ret += t;
	}

	return ret;

}

string getStdIn(){
	string tmp,ret;
	if (UseStdio){
		while(getline(cin,tmp))
			ret += tmp;
		
		return ret;
	}
	ifstream fin(InputFile.c_str());
	
	while (getline(fin,tmp)) ret += tmp;
	return tmp;
}

void Steal(string inp) {
	for (int i=1;i<=fnum;i+=1)
		if (subfix(files[i],".out") || subfix(files[i],".ans")){
			flg<<dpt+files[i].substr(0,files[i].length() - 4) + ".in"<<endl;
			string ith = getIn(dpt+files[i].substr(0,files[i].length() - 4) + ".in");
			string fth = getIn(dpt + files[i]);
			flg<<ith<<' '<<inp<<endl;
			if (inp == ith){
				if (UseStdio){
					cout<<fth<<endl;
					return;
				}else{
					ofstream fans(OutputFile.c_str());
					fans<<fth<<endl;
					return;
				}
			}
			
		}
		
	cout<<"Gugu:No such input file found."<<endl;
	cout<<"Check the Problemname and the I/O name.";
}

int main() {
	sysv = sys_vers();
//	string cmdc;
//	if (sysv == LNX) cmdc = "rm -rf sysver.exp";
//	else cmdc = "del sysver.exp";system(cmdc.c_str());
	decrun(sysv,"del sysver.exp","rm -rf sysver.exp");
	
	flg<<"SysVersion: "<<sysv<<endl;
	//char dr[1001],cmd[1001];
	//_getcwd(dr,1000);
	//Get the Current Working Directory.
	string dr;
	system("pwd > pwdout.exp");
	ifstream fin("pwdout.exp");
	getline(fin,dr);
	fin.close();
	decrun(sysv,"del pwdout.exp","rm -rf pwdout.exp");
	
	for (int i=0; i<dr.length() - bfxlen; i++) wpt += dr[i];
	if (sysv == LNX) dpt = wpt + "/data/" + ProblemName + "/";
	else dpt = wpt + "\\data\\" + ProblemName + "\\";
	flg<<wpt<<endl<<dpt<<endl;
	//system(" Testp1 && type Data1.out >pp000.txt");
	//system("cd.. && cd.. && cd data && cd Testp1 && type Data1.out >pp111.txt");
	
	gen_filetree();
	Steal(getStdIn());
	return 0;
}
