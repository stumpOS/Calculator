#include"Parser.h"
#include<string>
#include<iostream>
#include<cstring>

int main(int argc,char* argv[])
{

	Parser parser;
 
	while(true)
	{
		std::string in;
		std::cout << "Enter an arithmetic expression using {0-9}*+{+*^} or 'quit' to quit" << std::endl;
		std::cin >> in;
		int l = in.length();
		char *arr = new char[l+1];
		strcpy(arr,in.c_str());
		if(strcmp(arr,"quit")==0)
			break;
		float sol = parser.ParseInput(arr);
		std::cout << sol << std::endl;
	
		delete [] arr;
	}

	
}