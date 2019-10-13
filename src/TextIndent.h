//TextIndent.h
#ifndef _TEXTINDENT_H
#define _TEXTINDENT_H

#pragma once
#include "afxwin.h"
#include <string>

using namespace std;

class TextIndent {
public:
	TextIndent();
	TextIndent(char content , string tapText );
	TextIndent(const TextIndent& source);
	~TextIndent();
	void Parenthese(UINT nChar);
	char lineAddTap(string text);
	TextIndent& operator=(const TextIndent& source);
	char GetContent()const;
	string GetTapText()const;

private:
	char content;
	string tapText;

};

inline char TextIndent::GetContent() const {
	return this->content;
}
inline string TextIndent::GetTapText() const {
	return this->tapText;
}
#endif //_TEXTINDENT_H
