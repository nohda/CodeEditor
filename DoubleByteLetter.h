/*
���ϸ� : DoubleByteLetter.h
�ۼ����� : 2019�� 03�� 27��
�ۼ��� : �����
��� : DoubleByteLetter�� ������, �Ű������� ���� ������, ���������, �Ҹ���, Ŭ��(prototype pattern), ���ڿ� �����, ������ =����
���� : -
*/
//DoubleByteLetter.h

#pragma once
#ifndef _DOUBLEBYTELETTER_H
#define _DOUBLEBYTELETTER_H
#include "Letter.h"
#include <string>
using namespace std;

class DoubleByteLetter :public Letter {
public:
	DoubleByteLetter();
	DoubleByteLetter(char(*content));
	DoubleByteLetter(const DoubleByteLetter& source);
	virtual ~DoubleByteLetter();
	virtual string GetContents();
	virtual Glyph* Clone();
	DoubleByteLetter& operator=(const DoubleByteLetter& source);
	char* GetContent()const;
private:
	char content[2];
};
inline char* DoubleByteLetter::GetContent()const {
	return const_cast<char*>(this->content);
}
#endif //_DOUBLEBYTELETTER_H