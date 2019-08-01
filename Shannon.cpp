#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

#define ll long long

using namespace std;

class CodeTab 
{
	private:
	   	char symbol;
	   	string code;
	   	double p;
	   	double p_sum;
	   
	public:
	   	CodeTab(char symbol, double p);
	   	void addCode(string code);
	   	void addSum(double p_sum);
	   	char getSymbol();
	   	double getFrequency();
	   	double getSum();
	   	string getCode();
};

CodeTab::CodeTab(char symbol, double p) 
{
   	this->symbol = symbol;
   	this->p = p;
   	p_sum = 0;
   	code = "";
}

char CodeTab::getSymbol() 
{
   	return symbol;
}

double CodeTab::getFrequency() 
{
   	return p;
}

double CodeTab::getSum()
{
	return p_sum;
}

string CodeTab::getCode() 
{
   	return code;
}

void CodeTab::addCode(string code) 
{
   	this->code += code;
}

void CodeTab::addSum(double p_sum)
{
	this->p_sum += p_sum;
}

void printCodeTab(CodeTab tab) 
{
   cout << "Symbol: " << tab.getSymbol();
   cout << " Freq: " << tab.getFrequency();
   cout << " Sum: " << tab.getSum();
   cout << " Code: " << tab.getCode() << endl;
}

vector<CodeTab> Tab;

string to_bin(double code, int times)
{
	double base = 0, fraction = 0;
	string result;
	for(int i = 0; i < times; i++)
	{
		code *= 2;
		fraction = modf(code, &base);
		result += base + '0';
		code = fraction;
	}
	
	return result;
}

void shannon(vector<CodeTab> *tab) 
{
	int length = 0, dec_code = 0;
	double temp = 0;
	
	tab->at(0).addSum(0);
	temp = tab->at(0).getFrequency();
	length = ceil((log10(1 / temp) / log10(2)));
	tab->at(0).addCode(to_bin(tab->at(0).getSum(), length));
   	for(int i = 1; i < tab->size(); i++)
   	{
   		for(int j = 0; j < i; j++)
   		{
   			tab->at(i).addSum(tab->at(j).getFrequency());
		}
		
		temp = tab->at(i).getFrequency();
		length = ceil((log10(1 / temp) / log10(2)));
		tab->at(i).addCode(to_bin(tab->at(i).getSum(), length));
	}
}

void push_to_vector(map<char, int> *frequency, int counter)
{
	map<char,int>::iterator it;
	vector<CodeTab>::iterator jt; 
	double P;
	
	for(it = frequency->begin(); it != frequency->end(); it++)
	{
		P = (double) it->second / (double) counter;
		if(Tab.empty())
		{
			CodeTab newTab(it->first, P);
			Tab.push_back(newTab);
		}
		
		else
		{
			jt = Tab.begin();
			for(int j = 0; j < Tab.size(); j++)
			{
				if(P >= Tab[j].getFrequency())
				{
					CodeTab newTab(it->first, P);
					Tab.insert(jt, newTab);
					break;
				}
				else if(j == Tab.size() - 1)
				{
					CodeTab newTab(it->first, P);
					Tab.push_back(newTab);
					break;
				}
				jt++;
			}
		}
	}
}

string encode(string text)
{
	string code;
    for(int i = 0; i < text.size(); i++)
	{
		for(int j = 0; j < Tab.size(); j++)
		{
			if(Tab[j].getSymbol() == text[i])
			{
				code += Tab[j].getCode();
				j = Tab.size();
			}
		}
	}
	return code;	
}

double getEntropy(string code_text, int symb)
{
	map<string, int> count;
	map<string, int>::iterator it;
	string temp;
	int size = code_text.size();
	double H = 0, P = 0;	
	
	for(int i = 0; i < size; i++)
	{
		temp += code_text[i];
		if(temp.size() < symb)
			continue;
		count.insert(pair<string, int>(temp, 0));
		count.at(temp)++;
		temp = temp.substr(1);
	}
	
	for(it = count.begin(); it != count.end(); it++)
	{
		P = (double) it->second / (double) (code_text.size() - (symb - 1));
		H += P * (log10(1 / P) / log10(2));
	}
	
	H /= symb;
		
	return H;
}
