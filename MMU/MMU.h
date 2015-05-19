#include <iostream>
using namespace std;
typedef unsigned int word;
class MMU{
	public:
		word reg[32];
		word main_mem[32];
	public:
		MMU() {  //constructor, basically does nothing
			for(int i=0;i<32;i++) reg[i]=0;
			for(int j=0;j<32;j++) main_mem[j]=0;
			reg[29]=31;
		}
		~MMU() { //destructor, basically does nothing
			
		}
		void setReg(int a, word b) {
			if(a!=0) reg[a]=b;
			else return;
		}
		word getReg(int a) {
			return reg[a];
		}
		void setMem(word ele, int pos) {
			main_mem[pos]=ele;
		}
		word getMem(int pos) {
			return main_mem[pos];
		}
};
