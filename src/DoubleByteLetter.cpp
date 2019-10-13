// DoubleByteLetter.cpp
/*
���ϸ� : DoubleByteLetter.cpp
�ۼ����� : 2019�� 03�� 27��
�ۼ��� : �����
��� : DoubleByteLetter�� ������, �Ű������� ���� ������, ���������, �Ҹ���, Ŭ��(prototype pattern), ���ڿ� �����, ������ =����
���� : -
*/

#include "DoubleByteLetter.h"

/*
�Լ���: DoubleByteLetter
���: ����Ʈ ������
*/
DoubleByteLetter::DoubleByteLetter() {
	this->content[0] = ' ';
	this->content[1] = ' ';
}

/*
�Լ���: DoubleByteLetter
���: �Ű����� ������
*/
DoubleByteLetter::DoubleByteLetter(char(*content)) {
	this->content[0] = content[0];
	this->content[1] = content[1];
}

/*
�Լ���: DoubleByteLetter
���: ���� ������
*/
DoubleByteLetter::DoubleByteLetter(const DoubleByteLetter& source) {
	this->content[0] = source.content[0];
	this->content[1] = source.content[1];
}

/*
�Լ���: ~DoubleByteLetter
���: �Ҹ���
*/
DoubleByteLetter::~DoubleByteLetter() {
}

/*
�Լ���: GetContents
���: ���ڿ��� �����
*/
string DoubleByteLetter::GetContents() {
	char buffer[3];
	buffer[0] = this->content[0];
	buffer[1] = this->content[1];
	buffer[2] = '\0';
	return string(buffer);
}

/*
�Լ���: Clone
���: �����Ѵ�
*/
Glyph* DoubleByteLetter::Clone() {
	return new DoubleByteLetter(*this);
}

/*
�Լ���: operator=
���: ġȯ ������
*/
DoubleByteLetter& DoubleByteLetter::operator=(const DoubleByteLetter& source) {
	this->content[0] = source.content[0];
	this->content[0] = source.content[1];
	return *this;
}