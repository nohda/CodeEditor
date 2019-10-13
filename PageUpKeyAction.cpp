//PageUpKeyAction.cpp
#include "PageUpKeyAction.h"
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "CaretCoordinator.h"
#include "Glyph.h"
#include "Scroll.h"

PageUpKeyAction::PageUpKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm) {
}

PageUpKeyAction::~PageUpKeyAction() {
}

void PageUpKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long memoCurrent;
	Long lineLength;
	Long lineCurrent;
	Long previousWidth;
	Long currentWidth;
	Long moveCurrent;
	Long i = 0;
	CRect rect;
	Long height;
	Long memoLength;
	Long count = 0;

	memoCurrent = this->codeEditorForm->memo->GetCurrent() + 1;
	this->codeEditorForm->GetClientRect(rect);
	height = this->codeEditorForm->fontMatrix->GetHeight();
	memoLength = this->codeEditorForm->memo->GetLength();

	//ȭ�鿡 ��� �ٱ��� ǥ���� �� �ִ��� ���Ѵ�.
	while (i * height < rect.bottom && i < memoLength) {
		if ((i + 1) * height < rect.bottom) {
			count++;
			i++;
		}
		else {
			break;
		}
	}
	moveCurrent = memoCurrent - count;
	if (moveCurrent < count - 1) { //���� ���� ��������� ù�ٷ� �����Ѵ�.
		moveCurrent = 0;
	}
		previousWidth = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
		memoCurrent = this->codeEditorForm->memo->Move(moveCurrent);

		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent + 1);
		this->codeEditorForm->current->First();
		lineLength = this->codeEditorForm->current->GetLength();
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		currentWidth = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);

		while (currentWidth < previousWidth && lineCurrent < lineLength) {
			lineCurrent = this->codeEditorForm->current->Next();
			currentWidth = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
		}
}
