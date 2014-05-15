/*
 * 722FinalProject.h
 *
 *  Created on: Mar 10, 2014
 *      Author: Xiaoxiao Ma
 */
#include <string>
#include <math.h>
#include <iostream>
#include <bitset>
using namespace std;
class Letter
{
public:
	Letter();// construct function
	Letter(string letter);
	string s;
	//double value;
	bitset<26> sValue;
	int length;
	int lastBitPosition;
	void setLetter(string letter);
	int getBit();
};
Letter::Letter(){
	s="";
	//value=0;
	//make sValue="00000000000000000000000000";//26 in total
	sValue.reset();
	length=0;
	lastBitPosition=0;
}
Letter::Letter(string letter){
	setLetter(letter);
}
void Letter::setLetter(string letter){
	s=letter;
	//value=0;
	for(int i=0;i<s.length();i++)
	{
		//value=value+(s[i]-96)*pow(27,25-i);
		//setSvalue
		int j=s[i]-96-1;
		sValue[j]=1;
	}
	//cout<<sValue<<endl;
	length=s.length();
	lastBitPosition=getBit();
}

int Letter::getBit()
{
	int counter=length;
	int j=0;
	for(j=0;j<26;j++){
		if(sValue[j]==1){
			counter--;
			if(counter==0){
				break;
			}
		}
	}
	return j+1;
}
bool biggerOrEqual(Letter s1, Letter s2){
	bool result=true;
	//get the shortest length of two sValues
	int length=s1.length<=s2.length?s1.length:s2.length;
	//get the shortest bit.
	int BitLength=s1.lastBitPosition>=s2.lastBitPosition?s2.lastBitPosition:s1.lastBitPosition;
	int i=0;
	for(i=0;i<BitLength;i++)
	{
		if(s1.sValue[i]<s2.sValue[i]){
			result=true;
			break;
		}else if(s1.sValue[i]>s2.sValue[i]){
			result=false;
			break;
		}
	}
	if(i>=BitLength){
		result=s1.length>=s2.length?true:false;
	}
	//cout<<s1<<">="<<s2<<"?"<<result<<endl;
	return result;
}
bool bigger(Letter s1, Letter s2){
	bool result=true;
		//get the shortest length of two sValues
		int length=s1.length<=s2.length?s1.length:s2.length;
		//get the shortest bit.
		int BitLength=s1.lastBitPosition>=s2.lastBitPosition?s2.lastBitPosition:s1.lastBitPosition;
		int i=0;
		for(i=0;i<BitLength;i++)
		{
			if(s1.sValue[i]<s2.sValue[i]){
				result=true;
				break;
			}else if(s1.sValue[i]>s2.sValue[i]){
				result=false;
				break;
			}
		}
		if(i>=BitLength){
			result=s1.length>s2.length?true:false;
		}
		//cout<<s1<<">"<<s2<<"?"<<result<<endl;
		return result;
}
bool checkInput(string input)
{
	int parenthenFlag=0;
	string letter="";
	for(int i=0;i<input.length();i++)
	{
		if(input[i]=='['){
			if(parenthenFlag!=0||input[i+1]==']'){
				return false;
			}else{
			   parenthenFlag=1;
			   letter="";
			}//make sure that "][abc][" or "[[abc]]" or "[]" will not happen
		}else if(input[i]==']'){
			parenthenFlag--;
			if(parenthenFlag!=0){
				return false;
			}//make sure that "][abc][" or "[[abc]]" will not happen
		}else if(96<input[i]&&123>input[i]){
			int length=letter.length();
			if(length>0&&input[i]<=letter[length-1]){
				return false;// make sure that "[abb]" or "[bac]" will not happen
			}else{
				letter=letter+input[i];
			}
		}else{
			return false;
		}
	}
	if(parenthenFlag!=0){
		return false;
	}else{
		return true;
	}
}
int getLettersNum(string input)
{
	int num=0;
	for(int i=0;i<input.length();i++)
	{
		if(input[i]==']'){
			num++;
		}
	}
	return num;
}
//x is the letters array
//n is the number of letters in the array
//x=x1x2x3
string decomposition(Letter* x, int n){
	string result="";
	int* pos=new int[n];
	int k=0;
//	for(int k=0;k<n;k++)
//	{
//		cout<<x[k].s<<",";
//	}
//	cout<<endl;
//	cout<<"n="<<n<<endl;
	//to do ...
	int h=0;//the length that have done  h=|x1|
	int i=0;
	int j=0;
	while(h<n)
	{
		i=h+1;
		j=h+2;
//		while(x[j-1].value>=x[i-1].value&&i<=n&&j<=n)
//		{
//			if (x[j-1].value>x[i-1].value&&i<=n&&j<=n){
//				i=h+1;
//			}else{
//				i++;
//			}
//			j++;
//		}
        //cout<<"n="<<n<<endl;
		//cout<<"i="<<i<<",j="<<j<<endl;
		while(biggerOrEqual(x[j-1],x[i-1])&&i<=n&&j<=n)
		{
			//cout<<"i="<<i<<",j="<<j<<endl;
			if (bigger(x[j-1],x[i-1])&&i<=n&&j<=n){
				i=h+1;
			}else{
				i++;
			}
			j++;
			//cout<<"i="<<i<<",j="<<j<<endl;
		}
		do
		{
			h=h+(j-i);
			//cout<<h<<endl;
			pos[k]=h-1;
			k++;
		}while(h<i);

	}
	//make the result
	k=0;
	for(int i=0;i<n;i++)
	{
		result=result+"["+x[i].s+"]";
		if(i==pos[k]&&i<n-1){
			result=result+" / ";
			k++;
		}
	}
	delete []pos;
	return result;
}
