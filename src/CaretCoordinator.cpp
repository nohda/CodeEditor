//CaretCoordinator.cpp
/*
���ϸ� : CaretCoordinator.cpp
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : �迵��
��� : ĳ���� ��ġ����
���� :
*/

#include "CaretCoordinator.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "FontMatrix.h"
#include <string>
using namespace std;

CaretCoordinator::CaretCoordinator() {
	this->codeEditorForm = 0;
	this->x = 0;
	this->y = 0;
	this->aveWidth = 0;
}

/*
�Լ���: CaretCoordinator
���: ������
*/
CaretCoordinator::CaretCoordinator(CodeEditorForm * codeEditorForm){
	this->codeEditorForm = codeEditorForm;
	this->x = 0;
	this->y = 0;
	this->aveWidth = 0;
}

/*
�Լ���: CaretCoordinator
���: ���������
*/
CaretCoordinator::CaretCoordinator(const CaretCoordinator& source) {
	this->codeEditorForm = codeEditorForm;
	this->x = source.x;
	this->y = source.y;
	this->aveWidth = source.aveWidth;
	
}

/*
�Լ���: ~CaretCoordinator
���: �Ҹ���
*/
CaretCoordinator::~CaretCoordinator() {
}

/*
�Լ���: GetLineWidth
���: �������� ��� ���ڿ� ���� Width�� ���Ѵ�
*/
Long CaretCoordinator::GetLineWidth(FontMatrix *fontMatrix, Glyph *line) {
	Long i = 0;
	Glyph* letter = NULL;
	Long lineLength;

	this->x = 0;
	lineLength = line->GetLength();

	while (i < lineLength) {
		letter = line->GetAt(i);

		this->x += fontMatrix->GetWidth(letter);
		i++;
	}
	return this->x + this->codeEditorForm->marginWidth;
}

Long CaretCoordinator::GetLongestWidth(FontMatrix * fontMatrix, Glyph * memo) {
	Glyph* line;
	Long memoLength;
	Long lineWidth;
	Long i = 0;
	Long longestWidth = 0;

	longestWidth = this->codeEditorForm->marginWidth;
	memoLength = memo->GetLength();

	while (i < memoLength) {
		line = memo->GetAt(i);
		lineWidth = this->GetLineWidth(fontMatrix, line);

		if (longestWidth < lineWidth) {
			longestWidth = lineWidth;
			if (line->GetLength() == 0) {
				this->aveWidth = 0;
			}
			else {
				this->aveWidth = longestWidth / line->GetLength();
			}
		}
		i++;
	}
	return longestWidth;
}

/*
�Լ���: GetXPos
���: ���� ��ġ�� ���� ���Ѵ�
����: 
*/
Long CaretCoordinator::GetXPos(FontMatrix *fontMatrix, Glyph *line) {
	Long i = 0;
	Glyph* letter;

	this->x = this->codeEditorForm->marginWidth;

	while (i < line->GetCurrent()) {
		letter = line->GetAt(i);
		this->x += fontMatrix->GetWidth(letter);
		i++;
	}

	return this->x;
}

Long CaretCoordinator::GetYPos(FontMatrix * fontMatrix, Long row) {
	Long yPos;

	yPos = row * (fontMatrix->GetHeight());
	return yPos;
}

Long CaretCoordinator::GetSelectXPos(FontMatrix * fontMatrix, Glyph * line, Long current){
	Long i = 0;
	Glyph* letter;

	this->x = this->codeEditorForm->marginWidth;

	while (i < current) {
		letter = line->GetAt(i);
		this->x += fontMatrix->GetWidth(letter);
		i++;
	}

	return this->x;
}

/*
�Լ���: operator=
���: ġȯ������
*/
CaretCoordinator& CaretCoordinator::operator=(const CaretCoordinator& source) {
	this->codeEditorForm = codeEditorForm;
	this->x = source.x;
	this->y = source.y;
	this->aveWidth = source.aveWidth;

	return *this;
}