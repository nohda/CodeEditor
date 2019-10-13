//PageDownKeyAction.cpp
#include "PageDownKeyAction.h"
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "CaretCoordinator.h"
#include "Glyph.h"
#include "Scroll.h"

PageDownKeyAction::PageDownKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm) {
}

PageDownKeyAction::~PageDownKeyAction() {
}

void PageDownKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long memoCurrent;  //���� �޸��� ��ġ
	Long memoLength;   // �޸��� ��뷮
	Long lineLength;  //���� ��뷮
	Long lineCurrent;  //���� ���� ��ġ
	Long previousWidth;  //���� ���� ���� ��ġ������ �ʺ�
	Long currentWidth;   //�ٲ� ���� ���� ��ġ������ �ʺ�
	//Long fontHeight;  //������ ����
	Long moveCurrent;  //�̵��Ÿ�
	Long i = 0;
	Long height;
	CRect rect;
	Long count = 0;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();  //�޸��� ����ġ�� ���Ѵ�.
	memoLength = this->codeEditorForm->memo->GetLength();  //�޸��� ��뷮�� ���Ѵ�,
	height = this->codeEditorForm->fontMatrix->GetHeight();
	this->codeEditorForm->GetClientRect(rect);
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
	moveCurrent = memoCurrent + count;
	if (memoLength - moveCurrent < count) { //���� �Ʒ��� ��������� ù�ٷ� �����Ѵ�.
		moveCurrent = memoLength;
	}
		previousWidth = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);  //���� ���� ������ġ������ �ʺ� ���Ѵ�,
		memoCurrent = this->codeEditorForm->memo->Move(moveCurrent);  //�޸��� ��ġ�� �̵���Ų��.

		if (moveCurrent == memoLength) {
			memoCurrent = this->codeEditorForm->memo->Last();
		}
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(moveCurrent-1);    //���� �̵��Ѵ�.
		this->codeEditorForm->current->First();    //���� ó������ �̵��Ѵ�.
		lineLength = this->codeEditorForm->current->GetLength();
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		currentWidth = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current); //�ٲ� ���� ���� ��ġ������ �ʺ� ���Ѵ�.

		while (currentWidth < previousWidth && lineCurrent < lineLength) {
			lineCurrent = this->codeEditorForm->current->Next();  
			currentWidth = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
		}
}
