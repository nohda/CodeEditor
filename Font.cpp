#include "Font.h"
#include "CodeEditorForm.h"

Font::Font() {
	this->codeEditorForm = 0;
	this->dc = 0;
	this->logFont = { 0, };
	this->font = 0;
	this->oldFont = 0;
}

Font::Font(CodeEditorForm* codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
	(this->dc = new CDC) = this->codeEditorForm->GetDC();
	this->logFont = { -17,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("����ü") };
	(this->font = new CFont)->CreateFontIndirect(&this->logFont);
	this->oldFont = this->dc->SelectObject(this->font);
}

Font::Font(const Font& source) {
	this->dc = source.dc;
	this->codeEditorForm = source.codeEditorForm;
	this->logFont = source.logFont;
	this->font = source.font;
	this->oldFont = source.oldFont;
}

Font::~Font() {
	if (this->font != NULL) {
		delete this->font;
		this->font = NULL;
	}
}

void Font::Make() {
	CFontDialog fontdlg(&this->logFont);
	
	(this->dc = new CDC) = this->codeEditorForm->GetDC();
	
	if (fontdlg.DoModal() == IDOK) {
		
		if (this->font != NULL) {
			delete this->font;
			this->font = NULL;

			(this->font = new CFont)->CreateFontIndirect(&this->logFont); //���� �α���Ʈ ������� ��Ʈ�� �����.
		}
	}
	this->oldFont = dc->SelectObject(this->font); //���� ��Ʈ�� dc�� �����Ѵ�.
}

Font& Font::operator=(const Font& source) {
	this->dc = source.dc;
	this->codeEditorForm = source.codeEditorForm;
	this->logFont = source.logFont;
	this->font = source.font;
	this->oldFont = source.oldFont;

	return *this;
}