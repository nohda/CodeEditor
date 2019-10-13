//TextCoordinator.cpp

#include "TextCoordinator.h"
#include "CaretCoordinator.h"
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "Glyph.h"


TextCoordinator::TextCoordinator(CodeEditorForm *codeEditorForm){
	this->codeEditorForm = codeEditorForm;
	this->point.SetPoint(0, 0);
}

TextCoordinator::TextCoordinator(const TextCoordinator & source){
	this->codeEditorForm = source.codeEditorForm;
	this->point = source.point;
}

TextCoordinator::~TextCoordinator(){
}

CPoint TextCoordinator::TextPos(CPoint nPos){
	CPoint text;

	if (nPos.x > 0) {
		this->point.x = -nPos.x;
	}
	else {
		this->point.x = 0;
	}

	if (nPos.y > 0) {
		this->point.y = -nPos.y;
	}
	else {
		this->point.y = 0;
	}

	text.SetPoint(this->point.x + this->codeEditorForm->marginWidth, this->point.y);

	return text;
}

CPoint TextCoordinator::NumberPos(CPoint nPos){
	CPoint Number;

	this->point.x = 5;

	if (nPos.y > 0) {
		this->point.y = -nPos.y;
	}
	else {
		this->point.y = 0;
	}

	Number.SetPoint(this->point.x, this->point.y);

	return Number;
}

TextCoordinator & TextCoordinator::operator=(const TextCoordinator & source){
	this->codeEditorForm = source.codeEditorForm;
	this->point = source.point;

	return *this;
}
