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
	if (contents[0] != '\0') { //조합 중인 글자가 남아있다면

		//글자를 조립 중일때 current가 한칸 뒤로 이동되어서 -1번째에 추가
		if (lineCurrent < lineLength && this->codeEditorForm->isComposing == TRUE) {
			this->codeEditorForm->current->Add(letter, lineCurrent - 1);
		}
		//글자를 적을 위치에 앞 글자가 'ㅇ'이나 'ㅏ'와 같이 적혀있으면 조합이 끝난 글자로 인식하고 현재 위치에 추가
		else if (lineCurrent < lineLength && this->codeEditorForm->isComposing == FALSE) {
			this->codeEditorForm->current->Add(letter, lineCurrent);
		}
		this->codeEditorForm->isComposing = TRUE;
	}
	else { //조합 중 글자가 다 지워졌다면
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

	memoCurrent = this->codeEditorForm->memo->GetCurrent(); //몇 번째 줄인지 확인한다.
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //현재 줄을 끼운다.
	lineCurrent = this->codeEditorForm->current->GetCurrent(); //현재 줄에 글자의 위치를 확인한다.
	//lineLength = this->codeEditorForm->current->GetLength(); //현재 줄의 사용량을 확인한다.
	this->codeEditorForm->current->Remove(lineCurrent - 1); //조합중이던 글자를 지운다.
	
	this->codeEditorForm->current->Add(letter, lineCurrent - 1); //조합중이던 칸에 조합이 끝난 글자를 적는다.
	this->codeEditorForm->isComposing = FALSE;

	return 0;
}
