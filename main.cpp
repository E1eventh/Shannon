#include "Shannon.cpp"

int main()
{
	setlocale(LC_ALL, "RUS");
	
	map<char, int> frequency;
	string text, code_text;
	int counter = 0;
	double H;
	char ch;
	
	ifstream in("text_ru.txt", ios::binary);
	int count_t = 0, count_s = 0;
	while(in.get(ch))
	{
		int trust = ch;
		if(trust != 13 && trust != 10)
		{
			text += ch;
			frequency.insert(pair<char, int>(ch, 0));
			frequency.at(ch)++;
			counter++;
		}
	}
	in.close();
	
	push_to_vector(&frequency, counter);
	shannon(&Tab);
	for_each(Tab.begin(), Tab.end(), printCodeTab);
	code_text = encode(text);
	
	H = getEntropy(code_text, 1);
	cout << endl << "ִכÿ מעהוכüםûץ סטלגמכמג: " << H << endl << endl;
	
	H = getEntropy(code_text, 2);
	cout << "ִכÿ ןאנ סטלגמכמג: " << H << endl << endl;
	
	H = getEntropy(code_text, 3);
	cout << "ִכÿ ענמוך סטלגמכמג: " << H << endl << endl;
	
	H = getEntropy(code_text, 4);
	cout << "ִכÿ קועג¸נמך סטלגמכמג: " << H << endl;
	
	//cout << endl << text << " - " << code_text << endl;
	
	return 0;
}
