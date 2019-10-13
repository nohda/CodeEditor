//Composite.cpp
/*
���ϸ� : Composite.cpp
�ۼ����� : 2019�� 03�� 27��
�ۼ��� :�����
��� : Memo�� line�� �����ϴ� �߻� Ŭ������ ������, ���������, �Ҹ���, add, getAt ������ =���� (�Ӽ�: �Ҵ緮, ��뷮, ������ġ)
���� : 0328	GetContents Iterator ������ �߰�
	   20194010 First, Previous, Next, Last �����߰�
*/
#include "Composite.h"
#include "Iterator.h"
#include "ArrayIterator.h"


/*
�Լ���: Composite
���: ������
*/
Composite::Composite(Long capacity):glyphs (capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}

/*
�Լ���: Composite
���: ���� ������
*/
Composite::Composite(const Composite& source) : glyphs(source.glyphs) {
	Long i = 0;

	while (i < source.length) {
		Glyph *glyph = (const_cast<Composite&>(source)).glyphs.GetAt(i);
		this->glyphs.Modify(i, glyph->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

/*
�Լ���: ~Composite
���: �Ҹ���
*/
Composite::~Composite() {
	Long i = 0;

	while (i < this->length) {
		delete this->glyphs[i];
		i++;
	}
}

/*
�Լ���: Add
���: ���� �߰��Ѵ�
*/
Long Composite::Add(Glyph* glyph) {
	if (this->capacity > this->length) {
		this->current = glyphs.Store(this->length, glyph) ;
	}
	else
	{
		this->current = glyphs.AppendFromRear(glyph) ;
		this->capacity++;
	}

	this->length++;
	return this->current;
}

Long Composite::Add(Glyph * glyph, Long index) {
	this->current = this->glyphs.Insert(index, glyph);
	this->capacity++;
	this->length++;

	return this->current;
}

/*
�Լ���: Remove
���: ���� �����
*/
Long Composite::Remove(Long index) {

	if (this->glyphs[index] != 0) {
		delete this->glyphs[index];
	}
	
	this->glyphs.Delete(index);
	this->capacity--;
	this->length--;

	if (this->length > 0 && this->current > this->length - 1) {
		this->current --; //--�� ����
	}
	//�߰�
	if (this->length <= 0) {
		this->current = 0;
	}

	return -1;
}

/*
�Լ���: First
���: ó������ �̵��Ѵ�
*/
Long Composite::First() {
	return this->current = 0;
}

/*
�Լ���: Previous
���: �������� �̵��Ѵ�
*/
Long Composite::Previous() {
	this->current--;

	if (this->current < 0) {
		this->current = 0;
	}

	return this->current;
}

/*
�Լ���: Next
���: �������� �̵��Ѵ�
*/
Long Composite::Next() {
	this->current++;

	if (this->current > this->length) {
		this->current = this->length;
	}

	return this->current;
}

/*
�Լ���: Last
���: ���������� �̵��Ѵ�
*/
Long Composite::Last() {
	return this->current = this->length;
}

Long Composite::Move(Long index) {
	this->current = index;
	return this->current;
}

/*
�Լ���: GetAt
���: ���� �����´�
*/
Glyph* Composite::GetAt(Long index) {
	return this->glyphs[index];
}

/*
�Լ���: operator=
���: ġȯ ������
*/
Composite& Composite::operator=(const Composite& source) {
	Long i = 0;

	while (i < this->length) {
		delete this->glyphs[i];
		i++;
	}

	this->glyphs = source.glyphs;
	i = 0;

	while (i < source.length) {
		Glyph *glyph = (const_cast<Composite&>(source)).glyphs.GetAt(i);
		this->glyphs.Modify(i, glyph->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	return *this;
}

/*
�Լ���: operator[]
���: 
*/
Glyph* Composite::operator[](Long index) {
	return this->glyphs[index];
}

/*
�Լ���: CreateIterator
���: ���ͷ����͸� �����
*/
Iterator<Glyph*>* Composite::CreateItorator() {
	return new ArrayIterator<Glyph*>(&this->glyphs);
}