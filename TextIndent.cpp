#include "TextIndent.h"
#include "textEdit.h"


TextIndent::TextIndent() {
	this->content = ' ';
	this->tapText = "";
}

TextIndent::TextIndent(char content, string tapText){
	this->content = content;
	this->tapText = tapText;
}

TextIndent::TextIndent(const TextIndent & source){
	this->content = source.content;
	this->tapText = source.tapText;
}

TextIndent::~TextIndent(){
}

void TextIndent::Parenthese(UINT nChar){
	this->content = ' ';

	if (nChar == 123) {
		this->content = '}';
	}
	else if (nChar == 91) {
		this->content = ']';
	}
	else if (nChar == 40) {

		this->content = ')';
	}
	else if (nChar == 34) {
		this->content = '"';
	}
	else if (nChar == 39) {
		this->content = '\'';
	}
	else if (nChar == 60) {
		this->content = '>';
	}

}

char TextIndent::lineAddTap(string text){
	Long i = 0;
	Long textLength;
	string compareText = "";
	string appendText = "";
	char reChar = ' ';

	textLength = text.length();
	while (i < textLength) {
		compareText = text.at(i);
		if (compareText != " ") {
			if (compareText == ")") {
				appendText.append(compareText);
			}
			else if (compareText == "{") {
				appendText.append(compareText);
			}
		}
		i++;
	}
	if (appendText == "){") {
		this->tapText.append("\t");
		reChar = '\t';
	}
	return reChar;
}


TextIndent & TextIndent::operator=(const TextIndent & source){
	this->content = source.content;
	this->tapText = source.tapText;

	return *this;
}

