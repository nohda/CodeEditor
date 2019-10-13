//Composite.cpp
/*
파일명 : Composite.cpp
작성일자 : 2019년 03월 27일
작성자 :허수진
기능 : Memo와 line을 포함하는 추상 클래스로 생성자, 복사생성자, 소멸자, add, getAt 연산자 =정의 (속성: 할당량, 사용량, 현재위치)
수정 : 0328	GetContents Iterator 생성자 추가
	   20194010 First, Previous, Next, Last 연산추가
*/
#include "Composite.h"
#include "Iterator.h"
#include "ArrayIterator.h"


/*
함수명: Composite
기능: 생성자
*/
Composite::Composite(Long capacity):glyphs (capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}

/*
함수명: Composite
기능: 복사 생성자
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
함수명: ~Composite
기능: 소멸자
*/
Composite::~Composite() {
	Long i = 0;

	while (i < this->length) {
		delete this->glyphs[i];
		i++;
	}
}

/*
함수명: Add
기능: 줄을 추가한다
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
함수명: Remove
기능: 줄을 지운다
*/
Long Composite::Remove(Long index) {

	if (this->glyphs[index] != 0) {
		delete this->glyphs[index];
	}
	
	this->glyphs.Delete(index);
	this->capacity--;
	this->length--;

	if (this->length > 0 && this->current > this->length - 1) {
		this->current --; //--로 변경
	}
	//추가
	if (this->length <= 0) {
		this->current = 0;
	}

	return -1;
}

/*
함수명: First
기능: 처음으로 이동한다
*/
Long Composite::First() {
	return this->current = 0;
}

/*
함수명: Previous
기능: 이전으로 이동한다
*/
Long Composite::Previous() {
	this->current--;

	if (this->current < 0) {
		this->current = 0;
	}

	return this->current;
}

/*
함수명: Next
기능: 다음으로 이동한다
*/
Long Composite::Next() {
	this->current++;

	if (this->current > this->length) {
		this->current = this->length;
	}

	return this->current;
}

/*
함수명: Last
기능: 마지막으로 이동한다
*/
Long Composite::Last() {
	return this->current = this->length;
}

Long Composite::Move(Long index) {
	this->current = index;
	return this->current;
}

/*
함수명: GetAt
기능: 줄을 가져온다
*/
Glyph* Composite::GetAt(Long index) {
	return this->glyphs[index];
}

/*
함수명: operator=
기능: 치환 연산자
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
함수명: operator[]
기능: 
*/
Glyph* Composite::operator[](Long index) {
	return this->glyphs[index];
}

/*
함수명: CreateIterator
기능: 이터레이터를 만든다
*/
Iterator<Glyph*>* Composite::CreateItorator() {
	return new ArrayIterator<Glyph*>(&this->glyphs);
}