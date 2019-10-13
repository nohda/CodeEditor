#include "WriteState.h"
#include "Memo.h"
#include "Line.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "WriteStateAppend.h"
#include "WriteStateInsert.h"


WriteState::WriteState(CodeEditorForm* codeEditorForm)
{
	this->codeEditorForm = codeEditorForm;
}

WriteState::~WriteState()
{
}

void WriteState::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
#if 0
	Long lineCurrent;
	Long lineLength;

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent == lineLength || lineCurrent == -1) {
		this->codeEditorForm->writeStateAppend->OnChar(nChar, nRepCnt, nFlags);
	}
	else if (lineCurrent < lineLength) {
		
	}
#endif
}

LRESULT WriteState::OnImeStartComposition(WPARAM wParam, LPARAM lParam)
{
#if 0
	Long lineCurrent;
	Long lineLength;

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent == lineLength || lineCurrent == -1) {
		this->codeEditorForm->writeStateAppend->OnImeStartComposition(wParam, lParam);
	}
	else if (lineCurrent < lineLength) {
		this->codeEditorForm->writeStateInsert->OnImeStartComposition(wParam, lParam);
	}
#endif
	return 0;
}

LRESULT WriteState::OnImeComposition(WPARAM wParam, LPARAM lParam)
{
#if 0
	Long lineCurrent;
	Long lineLength;

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent == lineLength || lineCurrent == -1) {
		this->codeEditorForm->writeStateAppend->OnImeComposition(wParam, lParam);
	}
	else if (lineCurrent < lineLength) {
		this->codeEditorForm->writeStateInsert->OnImeComposition(wParam, lParam);
	}
#endif
	return 0;
}

LRESULT WriteState::OnImeChar(WPARAM wParam, LPARAM lParam)
{
#if 0
	Long lineCurrent;
	Long lineLength;

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent == lineLength || lineCurrent == -1) {
		this->codeEditorForm->writeStateAppend->OnImeChar(wParam, lParam);
	}
	else if (lineCurrent < lineLength) {
		this->codeEditorForm->writeStateInsert->OnImeChar(wParam, lParam);
	}
#endif 
	return 0;
}

void WriteState::ChangeState() {
	Long lineCurrent;
	Long lineLength;

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent == lineLength || lineCurrent == -1) {
		this->codeEditorForm->state = this->codeEditorForm->states[0];
	}
	else if (lineCurrent < lineLength) {
		this->codeEditorForm->state = this->codeEditorForm->states[1];
	}
}
