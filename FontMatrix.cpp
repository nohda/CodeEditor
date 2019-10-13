//FontMatrix.cpp
/*���ϸ�: FontMatrix.cpp
	�ۼ����� : 2019�� 03�� 29��
	�ۼ��� : �迵��
	��� : ��Ʈ�� �ʺ�� ���̸� ���Ѵ�.
	���� :
	*/

#include "FontMatrix.h"
#include "Glyph.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include <string>
using namespace std;

/*
�Լ��� : FontMatrix
��� : �Ű����� ������
���� : �� ���� ����
*/
FontMatrix::FontMatrix(CDC *dc) {
	char code[3] = { 0, };
	int i;
	CSize sz;

	for (i = 127; i > 0; i--) {
		if (i == 9) { //9��°��� (TABŰ���)
			this->widths[9] = this->widths[32] * 8; //9��° Tab�� 32��°�� Space�� ���� * 8�� �����Ѵ�.
			continue; //7��°�� �Ѿ��.
		}

		code[0] = i;
		sz = dc->GetTextExtent(code);
		this->widths[i] = (BYTE)sz.cx;
	}

	this->widths[0] = 0;

	strcpy(code, "��");
	sz = dc->GetTextExtent(code);
	this->widths[128] = (BYTE)sz.cx;
	this->height = sz.cy;
}

/*
�Լ��� : FontMatrix
��� : ���� ������
*/
FontMatrix::FontMatrix(const FontMatrix& source) {
	Long i;
	
	for (i = 0; i < 128; i++) {
		this->widths[i] = source.widths[i];
	}
	this->height = source.height;
}

/*
�Լ��� : ~FontMatrix
��� : �Ҹ���
*/
FontMatrix::~FontMatrix() {
}

/*
�Լ��� : GetSingleByteWidth
��� : widths���� width�� �����´�
*/
Long FontMatrix::GetSingleByteWidth(Long code) {
	return this->widths[code];
}

/*
�Լ��� : GetDoubleByteWidth
��� : widths���� width�� �����´�
*/
Long FontMatrix::GetDoubleByteWidth() {
	return this->widths[128];
}

Long FontMatrix::GetWidth(Glyph *letter) {
	string content;
	Long code;
	Long width = 0;
	if (dynamic_cast<SingleByteLetter*>(letter)) {
		content = letter->GetContents();
		
		if (content != "        ") { //��Ű�� �ƴϸ�
			code = content.at(0);
		}
		else {
			code = 9; //��Ű�̸�
		}
		width = this->GetSingleByteWidth(code);
	}
	else if (dynamic_cast<DoubleByteLetter*>(letter)) {
		width = this->GetDoubleByteWidth();
	}

	return width;
}

/*
�Լ��� : operator=
��� : ġȯ ������
*/
FontMatrix& FontMatrix::operator=(const FontMatrix& source) {
	Long i;
	
	for (i = 0; i < 128; i++) {
		this->widths[i] = source.widths[i];
	}
	this->height = source.height;

	return *this;
}