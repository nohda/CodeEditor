//Memo.cpp
/*
���ϸ� : Memo.cpp
�ۼ����� : 2019�� 03�� 27��
�ۼ��� : �����
��� : ������, ���������, �Ҹ���, ���ڿ� �����, ������= ����
���� : 190328 GetContents ����
	   20190410 LeftWord, RightWord �����߰�
*/

#include "Memo.h"
#include "iterator.h"


/*
�Լ��� : Memo
��� : ������
*/
Memo::Memo(Long capacity) :Composite(capacity) {
}

/*
�Լ��� : Memo
��� : ���� ������
*/
Memo::Memo(const Memo& source) : Composite(source) {
}

/*
�Լ��� : ~Memo
��� : �Ҹ���
*/
Memo::~Memo() {
}

/*
�Լ��� : Next
��� : Next �������̵�
*/
Long Memo::Next() {
	this->current++;

	if (this->current >= this->length) {
		this->current = this->length - 1;
	}

	return this->current;
}

/*
�Լ��� : Last
��� : Last �������̵�
*/
Long Memo::Last() {
	Composite::Last();
	this->current = this->length - 1;

	return this->current;
}

/*
�Լ��� : LeftWord
��� : �������� �� �ܾ� �̵�
*/
Long Memo::LeftWord() {
	this->Previous();
	
	return this->current;
}

/*
�Լ��� : RightWord
��� : ���������� �� �ܾ� �̵�
*/
Long Memo::RightWord() {
	this->Next();
	return this->current;
}
/*
�Լ��� : Clone
��� : �����Ѵ�
*/
Glyph* Memo::Clone() {
	return new Memo(*this);
}

/*
�Լ��� : GetContents
��� : ���ڿ��� �����
���� : 20190402 Tabó�� 
       20190403 �������� ����ó�� ����
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
�Լ��� : operator=
��� : ġȯ ������
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

	letter = new DoubleByteLetter((char(*))"��");
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

	letter = new DoubleByteLetter((char(*))"��");
	position = line->Add(letter);
	letter = line->GetAt(position);
	cout << letter->GetContents() << endl;

	if (memo != 0) {
		delete memo;
	}
	return 0;
}*/