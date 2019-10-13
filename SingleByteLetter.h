/*
���ϸ� : SingleByteLetter.h
�ۼ����� : 2019�� 03�� 27��
�ۼ��� : �����
��� : SingleByteCharacter�� ������, �Ű������� ���� ������, ���������, �Ҹ���, Ŭ��(prototype pattern), ���ڿ� �����, ������ =����
���� : -
*/
//SingleByteLetter.h

#pragma once
#ifndef _SINGLEBYTELETTER_H
#define _SINGLEBYTELETTER_H
#include "Letter.h"
#include <string>
using namespace std;

class SingleByteLetter :public Letter {
public:
	SingleByteLetter();
	SingleByteLetter(char content);
	SingleByteLetter(const SingleByteLetter& source);
	virtual ~SingleByteLetter();
	virtual string GetContents();
	virtual Glyph* Clone();
	SingleByteLetter& operator=(const SingleByteLetter& source);
	char GetContent()const;

private:
	char content;
};

inline char SingleByteLetter::GetContent() const {
	return this->content;
}
#endif //_SINGLEBYTELETTER_H
 