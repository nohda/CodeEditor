//CaretCoordinator.cpp
/*
파일명 : CaretCoordinator.cpp
작성일자 : 2019년 03월 29일
작성자 : 김영재
기능 : 캐럿의 위치지정
수정 :
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
함수명: CaretCoordinator
기능: 생성자
*/
CaretCoordinator::CaretCoordinator(CodeEditorForm * codeEditorForm){
	this->codeEditorForm = codeEditorForm;
	this->x = 0;
	this->y = 0;
	this->aveWidth = 0;
}

/*
함수명: CaretCoordinator
기능: 복사생성자
*/
CaretCoordinator::CaretCoordinator(const CaretCoordinator& source) {
	this->codeEditorForm = codeEditorForm;
	this->x = source.x;
	this->y = source.y;
	this->aveWidth = source.aveWidth;
	
}

/*
함수명: ~CaretCoordinator
기능: 소멸자
*/
CaretCoordinator::~CaretCoordinator() {
}

/*
함수명: GetLineWidth
기능: 현재줄의 모든 글자에 대한 Width를 구한다
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
함수명: GetXPos
기능: 현재 위치의 폭을 구한다
수정: 
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
함수명: operator=
기능: 치환연산자
*/
CaretCoordinator& CaretCoordinator::operator=(const CaretCoordinator& source) {
	this->codeEditorForm = codeEditorForm;
	this->x = source.x;
	this->y = source.y;
	this->aveWidth = source.aveWidth;

	return *this;
}