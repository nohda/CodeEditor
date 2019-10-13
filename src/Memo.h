/*
���ϸ� : Memo.h
�ۼ����� : 2019�� 03��27��
�ۼ��� : �����
��� : ������, ���������, �Ҹ���, , ���ڿ� �����, ������= ����
���� : 20190410 LeftWord, RightWord �����߰�
*/
//Memo.h

#pragma once
#ifndef _MEMO_H
#define _MEMO_H
#include "Composite.h"

typedef signed long int Long;

class Memo :public Composite {
public:
	Memo(Long capacity = 256);
	Memo(const Memo& source);
	virtual ~Memo();
	virtual Long Next();
	virtual Long Last();
	virtual Long LeftWord();
	virtual Long RightWord();
	virtual Glyph* Clone();
	virtual string GetContents();
	Memo& operator=(const Memo& source);

};
#endif //_MEMO_H