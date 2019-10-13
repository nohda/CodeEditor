#pragma once
//TextAssort.h
#ifndef _TEXTASSORT_H
#define _TEXTASSORT_H

#include <string>
#include "TextEdit.h"

typedef signed long int Long;

class TextEdit;
class TextAssort{
public:
	TextAssort();
	TextAssort(Long number,string text, Long start,Long end);
	TextAssort(const TextAssort& source);
	~TextAssort();
	Long Assort(string text);
	CString TextColor(CDC *memDC);
	void Reset();
	TextAssort& operator=(const TextAssort& source);
	Long GetNumber() const;
	string GetText() const;

private:
	Long number;
	string text;
	Long start;
	Long end;
};
inline Long TextAssort::GetNumber() const {
	return this->number;
}

inline string TextAssort::GetText() const{
	return this->text;
}

#endif //_TEXTASSORT_H