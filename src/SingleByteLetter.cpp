//SingleByteLetter.cpp
/*
���ϸ� : SingleByteLetter.cpp
�ۼ����� : 2019�� 03�� 27��
�ۼ��� : �����
��� : SingleByteCharacter�� ������, �Ű������� ���� ������, ���������, �Ҹ���, Ŭ��(prototype pattern), ���ڿ� �����, ������ =����
���� : -
*/

#include "SingleByteLetter.h"

/*
�Լ���: SingleByteLetter
���: ����Ʈ ������
*/
SingleByteLetter::SingleByteLetter() {
	this->content = ' ';
}

/*
�Լ���: SingleByteLetter
���: �Ű����� ������
*/
SingleByteLetter::SingleByteLetter(char content) {
	this->content = content;
}

/*
�Լ���: SingleByteLetter
���: ���� ������
*/
SingleByteLetter::SingleByteLetter(const SingleByteLetter& source) {
	this->content = source.content;
}

/*
�Լ���: ~SingleByteLetter
���: �Ҹ���
*/
SingleByteLetter::~SingleByteLetter(){
}


/*
�Լ���: Gecontents
���: ���ڸ� �����
*/
string SingleByteLetter::GetContents() {
	char buffer[9]; //�ǹ���, �����̽��� 8�� NULL���� 1��
	Long i;

	if (this->content == '\t') {
		for (i = 0; i < 8; i++) {
			buffer[i] = ' ';
		}
			buffer[8] = '\0';
	}
	else {
		buffer[0] = this->content;
		buffer[1] = '\0';
	}

	return string(buffer);
}

/*
�Լ���: Clone
���: �����Ѵ�
*/
Glyph* SingleByteLetter::Clone() {
	return new SingleByteLetter(*this);
}

/*
�Լ���: operator=
���: ġȯ ������
*/
SingleByteLetter& SingleByteLetter::operator=(const SingleByteLetter& source) {
	this->content = source.content;
	return *this;
}