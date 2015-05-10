#include <iostream>
#include <string>
#include <fstream>
#include"MMU.h"
using namespace std;
typedef unsigned int word;
int strtoint(string& s) {
	int i;
	int num=0;
	for(i=0;i<s.length();i++) {
		num=num<<1+s.at(i)-'0';
	}
	return num;
}
int strtocom(string& s) {
	int i;
	int flag=0;
	int num;
	if(s.at(0)=='1') {
		for(i=s.length();i>=0;i--) {
			if(s.at(i)=='1'&&!flag) {
				flag=1;
				continue;
			}
			if(flag) {
				if(s.at(i)=='1') s[i]=0;
				else s[i]='1';
			}
		}	
	}
	for(i=0;i<s.length();i++) {
		num=num<<1+s.at(i)-'0';
	}
	if(flag) num*=-1;
}
void Itype(MMU& mem, string& ins, ifstream& fs) {
	string op,rs,rt,imme;
	op.assign(ins,0,6);
	rs.assign(ins,6,5);
	rt.assign(ins,11,5);
	imme.assign(ins,16,16);
	if(!op.compare("001000")) { //addi
		mem.setReg(strtoint(rt),mem.getReg(strtoint(rs))+strtocom(imme));
	}
	else if(!op.compare("001001")) { //addiu
		mem.setReg(strtoint(rt),mem.getReg(strtoint(rs))+strtocom(imme));
	}
	else if(!op.compare("100011")) { //lw
		mem.setReg(strtoint(rt),mem.getMem(mem.getReg(strtoint(rs))+strtocom(imme)));
	}
	else if(!op.compare("101011")) { //sw
		mem.setMem(mem.getReg(strtoint(rt)),mem.getReg(strtoint(rs))+strtocom(imme));
	}
	else if(!op.compare("000100")) { //beq
		if(mem.getReg(strtoint(rt))==mem.getReg(strtoint(rs))) fs.seekg(34*(fs.tellg()/34+strtocom(imme)));
	}
	else if(!op.compare("000101")) { //bne
		if(mem.getReg(strtoint(rt))!=mem.getReg(strtoint(rs))) fs.seekg(34*(fs.tellg()/34+strtocom(imme)));
	}
}
void Rtype(MMU& mem, string& ins) {
	string func,rs, rt, rd, sa;
	int a,b;//for integer manipulations
	func.assign(ins,26,6);
	rs.assign(ins,6,5);
	rt.assign(ins,11,5);
	rd.assign(ins,16,5);
	sa.assign(ins,21,5);
	a=mem.getReg(strtoint(rs));
	b=mem.getReg(strtoint(rt));
	if(!func.compare("100000")){ //add
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rs))+mem.getReg(strtoint(rt)));
	}
	else if(!func.compare("100001")) { //addu
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rs))+mem.getReg(strtoint(rt)));
	}
	else if(!func.compare("100100")) { //and
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rs))&mem.getReg(strtoint(rt)));
	}
	else if(!func.compare("100111")) {//nor
		mem.setReg(strtoint(rd),~(mem.getReg(strtoint(rs))|mem.getReg(strtoint(rt))));
	}
	else if(!func.compare("100101")) {//or
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rs))|mem.getReg(strtoint(rt)));
	}
	else if(!func.compare("000000")) { //sll
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rt))<<strtoint(sa));
	}
	else if(!func.compare("000100")) {//slv
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rt))<<mem.getReg(strtoint(rs)));
	}
	else if(!func.compare("101010")) { //slt	
		if(a<b) mem.setReg(strtoint(rd),1);
		else mem.setReg(strtoint(rd),0);
	}
	else if(!func.compare("101011")) { //sltu
		if(mem.getReg(strtoint(rs))<mem.getReg(strtoint(rt))) mem.setReg(strtoint(rd),1);
		else mem.setReg(strtoint(rd),0);
	}
	else if(!func.compare("000011")) { //sra
		mem.setReg(strtoint(rd),b>>strtoint(sa));
	}
	else if(!func.compare("000111")) { //srav
		mem.setReg(strtoint(rd),b>>mem.getReg(strtoint(rs)));
	}
	else if(!func.compare("000010")) { //srl
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rt))>>mem.getReg(strtoint(rs)));
	}
	else if(!func.compare("000110")) { //srlv
		mem.setReg(strtoint(rd),b>>mem.getReg(strtoint(rs)));
	}
	else if(!func.compare("100010")) { //sub
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rs))-mem.getReg(strtoint(rt)));
	}
	else if(!func.compare("100011")) { //subu
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rs))-mem.getReg(strtoint(rt)));
	}
	else if(!func.compare("100110")) { //xor
		mem.setReg(strtoint(rd),mem.getReg(strtoint(rs))^mem.getReg(strtoint(rt)));
	}
}
void execute(MMU& mmu) {	
	ifstream instru("out.txt");
	string str;
	string opcode;
	string target;
	while(!instru.eof()) {
		getline(instru,str);
		opcode.assign(str,0,6);
		if(!opcode.compare("000000")) { //R type instructions
			Rtype(mmu,str);
			cout<<opcode<<endl;
		}
		else if(!opcode.compare("000010")) {
			target.assign(str,6,26);
			instru.seekg(34*strtoint(target));
			cout<<opcode<<endl;
		}
		else if(!opcode.compare("000011")) {
			target.assign(str,6,26);
			mmu.setReg(31,(instru.tellg()/34)*34);
			instru.seekg(34*strtoint(target));
			cout<<opcode<<endl;
		}
		else {  //I type instructions
			Itype(mmu,str,instru);
			cout<<opcode<<endl;
		}
		//cout<<opcode<<endl;
	}
	instru.close();
}

int main(void) {
	MMU m;
	execute(m);
}
