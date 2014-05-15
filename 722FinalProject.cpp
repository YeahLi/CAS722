//============================================================================
// Name        : 722FinalProject.cpp
// Author      : Xiaoxiao Ma
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Lyndon decomposition for indeterminate strings algorithm
//============================================================================
#include "722FinalProject.h"
#include <time.h>
using namespace std;

int main() {
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    bool flag=true;
    string input="";
    while(flag)
    {
    	cout<<"Please input:";
    	cin>>input;
    	//time begin
    	long beginTime =clock();//get beginning time ms unit


    	if(!checkInput(input)){
    		cout<<"Incorrect input!"<<endl;
    		continue;
    	}else{
    		int lettersNum = getLettersNum(input);
    		//cout<<lettersNum<<endl;
    		Letter* letterArray=new Letter[lettersNum];
            int j=0;
    		//get letters and save into array "letterArray"
    		char* s=strdup(input.c_str());
            const char *d = "[]";
            char *p=strtok(s,d);
            while(p){
            	string strletter=p;
            	// to do
            	letterArray[j].setLetter(strletter);
            	//cout<<letterArray[j].s<<"    "<<letterArray[j].value<<endl;
            	p=strtok(NULL,d);
            	j++;
            }
            //Lyndon decomposition
            string res=decomposition(letterArray,lettersNum);
            cout<<"The Lyndon Decomposition result is: "<<res<<endl;
            //time ending
            long endTime=clock();//get the end time
            //show running time
            cout<<"Running time: "<<endTime-beginTime<<" ms"<<endl;
            //release the space
            delete []letterArray;
            cout<<"Continue?(Y/N):";
                	char c;
                	cin>>c;
                	if(c=='Y'){
                		flag=true;
                	}else{
                		flag=false;
                		cout<<"Thank you!"<<endl;
                	}
    	}
    }


	return 0;
}
