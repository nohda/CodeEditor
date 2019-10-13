#include "WriteStateInsert.h"
#include "CodeEditorForm.h"
#include "GlyphFactory.h"
#include "Glyph.h"

WriteStateInsert::WriteStateInsert(CodeEditorForm * codeEditorForm): WriteState(codeEditorForm)
{
	this->codeEditorForm = codeEditorForm;
}

WriteStateInsert::~WriteStateInsert()
{
}

WriteStateInsert* WriteStateInsert::instance = 0;

WriteStateInsert* WriteStateInsert::WriteInsertInstance(CodeEditorForm * codeEditorForm)
{
	if (instance == 0)
	{
		instance = new WriteStateInsert(codeEditorForm);
	}

	return instance;
}

void WriteStateInsert::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags){
	Glyph *letter;
	GlyphFactory *glyphFactory = new GlyphFactory(this->codeEditorForm);
	Long lineCurrent;

	lineCurrent = this->codeEditorForm->current->GetCurrent();

	letter = glyphFactory->Make(nChar, nRepCnt, nFlags);
	if (letter != NULL) {
		this->codeEditorForm->current->Add(letter, lineCurrent);
	}
	
}

LRESULT WriteStateInsert::OnImeStartComposition(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT WriteStateInsert::OnImeComposition(WPARAM wParam, LPARAM lParam) {
	GlyphFactory glyphFactory(this->codeEditorForm);
	Glyph *letter;
	string contents;
	Long lineCurrent;
	Long lineLength;

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();
	letter = glyphFactory.Make(wParam, lParam);

	if (lineCurrent >= 0 && this->codeEditorForm->isComposing == TRUE) {
		this->codeEditorForm->current->Remove(lineCurrent - 1);
	}

	contents = letter->GetContents();
	if (contents[0] != '\0') { //���� ���� ���ڰ� �����ִٸ�

		//���ڸ� ���� ���϶� current�� ��ĭ �ڷ� �̵��Ǿ -1��°�� �߰�
		if (lineCurrent < lineLength && this->codeEditorForm->isComposing == TRUE) {
			this->codeEditorForm->current->Add(letter, lineCurrent - 1);
		}
		//���ڸ� ���� ��ġ�� �� ���ڰ� '��'�̳� '��'�� ���� ���������� ������ ���� ���ڷ� �ν��ϰ� ���� ��ġ�� �߰�
		else if (lineCurrent < lineLength && this->codeEditorForm->isComposing == FALSE) {
			this->codeEditorForm->current->Add(letter, lineCurrent);
		}
		this->codeEditorForm->isComposing = TRUE;
	}
	else { //���� �� ���ڰ� �� �������ٸ�
		this->codeEditorForm->isComposing = FALSE;
		this->codeEditorForm->current->Move(lineCurrent - 1);
	}

	return ::DefWindowProc(this->codeEditorForm->m_hWnd, WM_IME_COMPOSITION, wParam, lParam);
}

LRESULT WriteStateInsert::OnImeChar(WPARAM wParam, LPARAM lParam) {
	GlyphFactory glyphFactory(this->codeEditorForm);
	Glyph *letter;
	Long memoCurrent;
	Long lineCurrent;
	//Long lineLength;
	
	letter = glyphFactory.Make(wParam, lParam);

	memoCurrent = this->codeEditorForm->memo->GetCurrent(); //�� ��° ������ Ȯ���Ѵ�.
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //���� ���� �����.
	lineCurrent = this->codeEditorForm->current->GetCurrent(); //���� �ٿ� ������ ��ġ�� Ȯ���Ѵ�.
	//lineLength = this->codeEditorForm->current->GetLength(); //���� ���� ��뷮�� Ȯ���Ѵ�.
	this->codeEditorForm->current->Remove(lineCurrent - 1); //�������̴� ���ڸ� �����.
	
	this->codeEditorForm->current->Add(letter, lineCurrent - 1); //�������̴� ĭ�� ������ ���� ���ڸ� ���´�.
	this->codeEditorForm->isComposing = FALSE;

	return 0;
}
