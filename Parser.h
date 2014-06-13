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
	//void SetDelimiters(std::vector<const char*> delimiters){_delimiters = delimiters;}
	float ParseInput(char *in);
	
	//void BuildTree(int start, int end, int delimiter);
	
	//void PrintToFile(std::string filename);
	//void Print(std::ostream &out);
	bool StrCompare(char *one, const char *two, unsigned numberOfChars);
	
private:

	void NewInput(char *input);
	/*
	void AddToTreeString(char *character, unsigned numberOfChars);
	void TerminateTreeString();

	void BuildSubtree(int start,int end,int delimiter);
	void BuildTreeNextDelimiter(int start,int end,int delimiter);
	void AddLeaf(int start,int end);
	void AddSubtree(int root);
	*/
	/*
	float BuildSubTree(int start,int end,int delimiter);
	float BuildSubTreeNextDelimiter(int start,int end,int delimiter);
	float Leaf(int start,int end);
	*/
	float BuildSubTree(ExpressionInterval ei,int delimiter);
	float Leaf(ExpressionInterval ei);

	//void CloseSubTreeBranch();

	//std::vector<const char*> _delimiters;
	std::vector<Operator<float>* > _operators;
	/*
	char *_treeString;
	int _lastCharOfTreeString;
	int _limitTreeStringSize;
	*/
	char *_inputString;
};

