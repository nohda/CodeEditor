/*
���ϸ� : Letter.h
�ۼ����� : 2019�� 03�� 27��
�ۼ��� : �����
��� : Letter(�̱�, ����) �߻� Ŭ���� ����
���� : -
*/

//Letter.h

#pragma once
#ifndef _LETTER_H
#define _LETTER_H
#include "Glyph.h"

class Letter :public Glyph {
public:
	Letter() {}
	virtual ~Letter() = 0;
};

#endif //_LETTER_H