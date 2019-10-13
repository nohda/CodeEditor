#include "FontCommand.h"
#include <afxdlgs.h>
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "Font.h"

FontCommand::FontCommand(CodeEditorForm* codeEditorForm) :Command(codeEditorForm){
	this->codeEditorForm = codeEditorForm;
}

FontCommand::~FontCommand() {
}

void FontCommand::Execute() {
	this->codeEditorForm->font->Make();

	if (this->codeEditorForm->fontMatrix != NULL) {
		delete this->codeEditorForm->fontMatrix;
	}

	this->codeEditorForm->fontMatrix = new FontMatrix(this->codeEditorForm->font->GetDC());
	this->codeEditorForm->ReleaseDC(this->codeEditorForm->font->GetDC());
}
/*
문제점
1. 현재 적용되는 것 처럼 보이는건 폼이 가지고 있는 logfont에 직접 꽂아주었기 때문
2. logfont를 CFont에 안꽂친다.
3. 맑은고딕체를 적용했을때 글자를 못 따라간다.
*/