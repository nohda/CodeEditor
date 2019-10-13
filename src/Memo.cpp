//Memo.cpp
/*
파일명 : Memo.cpp
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : 생성자, 복사생성자, 소멸자, 문자열 만들기, 연산자= 선언
수정 : 190328 GetContents 정의
	   20190410 LeftWord, RightWord 연산추가
*/

#include "Memo.h"
#include "iterator.h"


/*
함수명 : Memo
기능 : 생성자
*/
Memo::Memo(Long capacity) :Composite(capacity) {
}

/*
함수명 : Memo
기능 : 복사 생성자
*/
Memo::Memo(const Memo& source) : Composite(source) {
}

/*
함수명 : ~Memo
기능 : 소멸자
*/
Memo::~Memo() {
}

/*
함수명 : Next
기능 : Next 오버라이드
*/
Long Memo::Next() {
	this->current++;

	if (this->current >= this->length) {
		this->current = this->length - 1;
	}

	return this->current;
}

/*
함수명 : Last
기능 : Last 오버라이드
*/
Long Memo::Last() {
	Composite::Last();
	this->current = this->length - 1;

	return this->current;
}

/*
함수명 : LeftWord
기능 : 왼쪽으로 한 단어 이동
*/
Long Memo::LeftWord() {
	this->Previous();
	
	return this->current;
}

/*
함수명 : RightWord
기능 : 오른쪽으로 한 단어 이동
*/
Long Memo::RightWord() {
	this->Next();
	return this->current;
}
/*
함수명 : Clone
기능 : 복사한다
*/
Glyph* Memo::Clone() {
	return new Memo(*this);
}

/*
함수명 : GetContents
기능 : 문자열을 만든다
수정 : 20190402 Tab처리 
       20190403 마지막줄 개행처리 수정
*/
string Memo::GetContents() {
	Glyph *line;
	string text = "";
	string contents;
	Glyph *letter;
	Long i = 1;

	Iterator<Glyph*>*memoIterator = this->CreateItorator();
	
	
	for (memoIterator->First(); !memoIterator->IsDone(); memoIterator->Next()) {
		line = memoIterator->CurrentItem();

		Iterator<Glyph*>*lineIterator = line->CreateItorator();

		for (lineIterator->First(); !lineIterator->IsDone(); lineIterator->Next()) {
			letter = lineIterator->CurrentItem();
			contents = letter->GetContents();
			text += contents;
		}
		if (i < this->GetLength()) {
			text += "\r\n";
			i++;
		}
	}
	
	return text;
}
	
/*
함수명 : operator=
기능 : 치환 연산자
*/
Memo& Memo::operator=(const Memo& source) {
	Composite::operator=(source);
	return *this;
}

/*
#include <iostream>
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "Line.h"

using namespace std;
int main(int argc, char *argv[]) {
	Glyph *memo = new Memo;
	Glyph* line;
	//Glyph* lineTwo;
	Long position;
	Long lineIndex;
	Glyph* letter;
	//Glyph* letterTwo;

	memo->Add(new Line);
	line = memo->GetAt(0);
	letter = new SingleByteLetter('6');
	position = line->Add(letter);
	letter = line->GetAt(position);
	cout << letter->GetContents() << endl;

	letter = new DoubleByteLetter((char(*))"박");
	position = line->Add(letter);
	letter = line->GetAt(position);
	cout << letter->GetContents() << endl;

	line = new Line;
	lineIndex = memo->Add(line);
	line = memo->GetAt(lineIndex);
	letter = new SingleByteLetter('7');
	position = line->Add(letter);
	letter = line->GetAt(position);
	cout << letter->GetContents() << endl;

	letter = new DoubleByteLetter((char(*))"컴");
	position = line->Add(letter);
	letter = line->GetAt(position);
	cout << letter->GetContents() << endl;

	if (memo != 0) {
		delete memo;
	}
	return 0;
}*/