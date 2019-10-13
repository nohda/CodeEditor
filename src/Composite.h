/*
���ϸ� : Composite.h
�ۼ����� : 2019�� 03�� 27��
�ۼ��� :�����
��� : Line, Memo�� �����ϴ� �߻� Ŭ������ ������, ���������, �Ҹ���, add, getAt ,Remove,������ =���� (�Ӽ�: �Ҵ緮, ��뷮, ������ġ)
���� : 0328	GetContents Iterator ������ �߰�
	   20190410 FIrst, Previous, Next, Last �����߰�, private -> protected�� ����
*/
//Composite.h

#pragma once
#ifndef _COMPOSITE_H
#define _COMPOSITE_H

#include "Glyph.h"
#include "Array.h"

typedef signed long int Long;

class Composite :public Glyph {
public:
	Composite(Long capacity = 256);
	Composite(const Composite& source);
	virtual ~Composite() = 0;
	virtual Long Add(Glyph* glyph);
	virtual Long Add(Glyph *glyph, Long index);
	virtual Glyph* GetAt(Long index);
	virtual Long Remove(Long index);
	virtual Long First();
	virtual Long Previous();
	virtual Long Next();
	virtual Long Last();
	virtual Long Move(Long index);
	virtual Long GetCapacity()const;
	virtual Long GetLength()const;
	virtual Long GetCurrent()const;
	virtual Iterator<Glyph*>* CreateItorator();
	Composite& operator=(const Composite& source);
	Glyph * operator[](Long index);

protected:
	Array<Glyph*>glyphs;
	Long capacity;
	Long length;
	Long current;
};

inline Long Composite::GetCapacity()const {
	return this->capacity;
}
inline Long Composite::GetLength()const {
	return this->length;
}
inline Long Composite::GetCurrent()const {
	return this->current;
}
#endif //_COMPOSITE_H