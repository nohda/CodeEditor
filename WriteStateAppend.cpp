#include "WriteStateAppend.h"
#include "CodeEditorForm.h"
#include "GlyphFactory.h"
#include "Glyph.h"
#include "CaretCoordinator.h"
#include "FontMatrix.h"

WriteStateAppend::WriteStateAppend(CodeEditorForm *codeEditorForm) :WriteState(codeEditorForm){
	this->codeEditorForm = codeEditorForm;
}

WriteStateAppend::~WriteStateAppend(){
}

WriteStateAppend* WriteStateAppend::instance = 0;

WriteStateAppend* WriteStateAppend::WriteAppendInstance(CodeEditorForm* codeEditorForm){
	if (instance == 0){
		instance = new WriteStateAppend(codeEditorForm);
	}

	return instance;
}

void WriteStateAppend::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags){
	Glyph *letter;
	GlyphFactory *glyphFactory = new GlyphFactory(this->codeEditorForm);
	

	letter = glyphFactory->Make(nChar, nRepCnt, nFlags);
	
	if (letter != NULL) {
		this->codeEditorForm->current->Add(letter);
	}
	
}

LRESULT WriteStateAppend::OnImeStartComposition(WPARAM wParam, LPARAM lParam) {
	return 0;
}

LRESULT WriteStateAppend::OnImeComposition(WPARAM wParam, LPARAM lParam) {
	GlyphFactory glyphFactory(this->codeEditorForm);
	Glyph *letter;
	string contents;
	Long lineCurrent;
	Long lineLength;
	
	letter = glyphFactory.Make(wParam, lParam);

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent >= 0 && this->codeEditorForm->isComposing == TRUE) {
		this->codeEditorForm->current->Remove(lineCurrent - 1);
	}
	contents = letter->GetContents();
	if (contents[0] != '\0') {//���� ���� ���ڰ� �����ִٸ�
		letter = glyphFactory.Make(wParam, lParam); //���� ���ڸ� �ٽ� Ȯ�� �� �����.

		if (lineCurrent == lineLength || lineCurrent == -1) {
			this->codeEditorForm->current->Add(letter);
		}
		this->codeEditorForm->isComposing = TRUE;
	}
	else
	{ //���� �� ���ڰ� �� ����������
		this->codeEditorForm->isComposing = FALSE;
		this->codeEditorForm->current->Move(lineCurrent - 1);
	}
	return ::DefWindowProc(this->codeEditorForm->m_hWnd, WM_IME_COMPOSITION, wParam, lParam);
}

LRESULT WriteStateAppend::OnImeChar(WPARAM wParam, LPARAM lParam) {
	GlyphFactory glyphFactory(this->codeEditorForm);
	Glyph *letter;
	Long memoCurrent;
	Long lineCurrent;
	//Long lineLength;

	letter = glyphFactory.Make(wParam, lParam);

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	//lineLength = this->codeEditorForm->current->GetLength();
	this->codeEditorForm->current->Remove(lineCurrent - 1);

	this->codeEditorForm->current->Add(letter);
	this->codeEditorForm->isComposing = FALSE;

	return 0;
}
