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
������
1. ���� ����Ǵ� �� ó�� ���̴°� ���� ������ �ִ� logfont�� ���� �Ⱦ��־��� ����
2. logfont�� CFont�� �Ȳ�ģ��.
3. �������ü�� ���������� ���ڸ� �� ���󰣴�.
*/