#pragma once
#include<cstring>
#include<vector>
#include<list>
#include<string>
#include<fstream>
#include<cmath>
#include<functional>
#include<cstdlib>


typedef std::vector<const char*>::iterator t_dlmt_iter;
typedef std::list<char*>::iterator t_char_iter;

template<class T>
struct Operator{
	Operator(const char *s, std::function<T(T,T)> f, unsigned short arity):_symbol(s),_function(f),_arity(arity){}
	T Fire(T a,T b){return _function(a,b);}

	const char* _symbol;
	std::function<T(T,T)> _function;
	unsigned short _arity;
	
};
struct ExpressionInterval{
	ExpressionInterval(unsigned i, unsigned j):_start(i),_end(j){}
	void Set(unsigned i, unsigned j){_start=i;_end=j;}
	unsigned _start;
	unsigned _end;
};
class Parser
{
public:
	Parser(void);
	~Parser(void);

	float ParseInput(char *in);
	

	bool StrCompare(char *one, const char *two, unsigned numberOfChars);
	
private:

	void NewInput(char *input);

	float BuildSubTree(ExpressionInterval ei,int delimiter);
	float Leaf(ExpressionInterval ei);


	std::vector<Operator<float>* > _operators;

	char *_inputString;
};

