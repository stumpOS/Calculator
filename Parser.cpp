#include "Parser.h"


Parser::Parser(void)
{
	
	const unsigned numOps = 5;
	std::string ops[numOps] = {"+","*","^","-","/"};

	auto add = [](float a, float b){return a+b;};
	const char* plus = "+";
	Operator<float> *addition = new Operator<float>(plus,add,2);
	_operators.push_back(addition);

	auto mult = [](float a, float b){return a*b;};
	const char* star = "*";
	Operator<float> *multiplication = new Operator<float>(star,mult,2);
	_operators.push_back(multiplication);

	auto div = [](float a, float b){return a/b;};
	const char* slash = "/";
	Operator<float> *division = new Operator<float>(slash,div,2);
	_operators.push_back(division);

	auto power = [](float a,float b){return pow(a,b);};
	const char* carrot = "^";
	Operator<float> *exponent = new Operator<float>(carrot,power,2);
	_operators.push_back(exponent);

	auto negate = [](float a,float b){return -b;};
	const char* minus = "-";
	Operator<float> *negative = new Operator<float>(minus,negate,1);
	_operators.push_back(negative);


}


Parser::~Parser(void)
{
	_operators.clear();
}


float Parser::ParseInput(char *in)
{
	NewInput(in);

	unsigned len = strlen(in);

	float solution;
	if(len>1)
	{
		solution = BuildSubTree(ExpressionInterval(0,len-1),0);
	}
	else if(len == 1)
	{
		solution = Leaf(ExpressionInterval(0,0));
	}
	
	return solution;
}

void Parser::NewInput(char *in)
{
	_inputString = in;
}

bool Parser::StrCompare(char *one, const char* two, unsigned numOfChars)
{
	int diff = 0;
	for(unsigned i=0;i<numOfChars;i++)
	{
		diff = (*(one+i)) - (*(two+i));
	}

	return (diff == 0);
}

float Parser::BuildSubTree(ExpressionInterval expression, int delimiter)
{
	int k = expression._start;
	bool isFound = false;
	float lhs = 0, rhs = 0, result = 0;

	if(delimiter < _operators.size() && (expression._end < strlen(_inputString) && expression._start <= expression._end))
	{
		while(k <= expression._end && isFound == false)
		{
			if(StrCompare(_inputString+k, _operators[delimiter]->_symbol,1))
			{
				switch(_operators[delimiter]->_arity)
				{
					case 2:
						lhs = BuildSubTree(ExpressionInterval(expression._start,k-1),delimiter+1);
						break;

					case 1:
					default:
						break;
				}
				rhs = BuildSubTree(ExpressionInterval(k+1,expression._end),0);
				isFound = true;
			}
			k++;
		}
		if(!isFound)
		{
			result = BuildSubTree(expression,delimiter+1);
		}
		else
		{
			result = _operators[delimiter]->Fire(lhs,rhs);
		}
	}
	else
	{
		result = Leaf(expression);
	}
	return result;
}
/*
  safely delimit acording to the next order of operations
*/

float Parser::Leaf(ExpressionInterval expression)
{
	unsigned siz = expression._end - expression._start + 1;
	char *number = new char[siz + 1];
	strncpy(number,_inputString+expression._start,siz);
	number[siz] = '\0';
	double result = atof(number);
	delete []number;
	
	return float(result);
}
