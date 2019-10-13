
/*
���ϸ� : Line.h
�ۼ����� : 2019�� 03�� 27��
�ۼ��� : �����
��� : ������, ���������, �Ҹ���, , ���ڿ� �����, ������= ����
���� : 0329 ArrayIterator �߰��Ͽ� GetContents ����
	   20190410 LeftWord, RightWord �����߰�
*/
//Line.h

#pragma once
#ifndef _LINE_H
#define _LINE_H
#include "Composite.h"
#include <string>

typedef signed long int Long;

class Line:public Composite {
public:
	Line(Long capacity = 256);
	Line(const Line& source);
	virtual ~Line();
	virtual Long Add(Glyph* glyph);
	virtual Long Add(Glyph *glyph, Long index);
	virtual Long LeftWord();
	virtual Long RightWord();
	virtual Glyph* Clone();
	virtual string GetContent();
	virtual string GetContents();
	Line& operator=(const Line& source);
};

#endif //_LINE_H