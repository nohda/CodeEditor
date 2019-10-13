//Scroll.cpp
/*
���ϸ� : Scroll.cpp
�ۼ����� : 2019�� 04�� 24��
�ۼ��� : �迵��
��� : ��ũ�ѿ� ���� ����,�̵�,�����ֱ�
���� :
*/

#include "Scroll.h"
#include "CodeEditorForm.h"
#include "CaretCoordinator.h"
#include "Glyph.h"
#include "ScrollActionFactory.h"
#include "ScrollAction.h"
#include "FontMatrix.h"
#include "Status.h"

/*
�Լ��� : Scroll
��� : �Ű����� ������
*/

Scroll::Scroll(CodeEditorForm* codeEditorForm, Long longestWidth, Long longestHeight, Long xPos, Long yPos, Long memoCurrentbool) {
	this->codeEditorForm = codeEditorForm;
	this->cscrollBar = new CScrollBar;
	this->longestWidth = longestWidth;
	this->longestHeight = longestHeight;
	this->xPos = xPos;
	this->yPos = yPos;
	this->memoCurrent = memoCurrent;
	this->codeEditorForm->SubjectAttach(this);
}

/*
�Լ��� : Scroll
��� : ���� ������
*/
Scroll::Scroll(const Scroll& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->cscrollBar = source.cscrollBar;
	this->longestWidth = source.longestWidth;
	this->longestHeight = source.longestHeight;
	this->xPos = source.xPos;
	this->yPos = source.yPos;
	this->memoCurrent = source.memoCurrent;
}

/*
�Լ��� : Scroll
��� : �Ҹ���
*/
Scroll::~Scroll() {
	this->codeEditorForm->SubjectDetach(this);
	delete this->cscrollBar;
}

void Scroll::MakeScroll() {
	this->cscrollBar->Create(SBS_VERT | SBS_TOPALIGN | SBS_HORZ | SBS_LEFTALIGN, this->codeEditorForm->clientRect, this->codeEditorForm, 0);
}

/*
�Լ��� : Show
��� : ��ũ���� �����ش�
*/
void Scroll::ShowScroll() {
	Long memoLength;
	Glyph* memo;

	memoLength = this->codeEditorForm->memo->GetLength();
	memo = this->codeEditorForm->memo;
	this->codeEditorForm->ShowScrollBar(SB_VERT | SB_HORZ); //����, ���� ��ũ���� �����ش�.

	if (this->longestHeight < this->codeEditorForm->clientRect.bottom) {
		this->codeEditorForm->EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH); //���� �� ���̰� Ŭ���̾�Ʈ�� ���̺��� ������ ��Ȱ��ȭ
	}
	else {
		this->codeEditorForm->EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);
	}

	if (this->longestWidth < this->codeEditorForm->clientRect.right) {
		this->codeEditorForm->EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH); //���� �� �ʺ� Ŭ���̾�Ʈ�� �ʺ񺸴� ������ ��Ȱ��ȭ
	}
	else {
		this->codeEditorForm->EnableScrollBar(SB_HORZ, ESB_ENABLE_BOTH);
	}
}

void Scroll::UpdateHScroll(Long cx) {
	SCROLLINFO si;

	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_ALL);//���� ��ũ�� ����
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;

	if (this->longestWidth - this->codeEditorForm->marginWidth < cx - this->codeEditorForm->marginWidth) {//���� ������ ȭ�麸�� ���� �ʴٸ�
		si.nMax = cx - this->codeEditorForm->marginWidth; //��ũ�ѹ��� ũ�⸦ ȭ��ũ��� ����
	}

	si.nPage = cx - this->codeEditorForm->marginWidth; //�������� ũ��� �� ȭ�鿡 ���̴� ũ��� ����
	this->codeEditorForm->SetScrollInfo(SB_HORZ, &si, TRUE); //���� ��ũ�ѹٿ� ������ ����
}

void Scroll::UpdateVScroll(Long cy) {
	SCROLLINFO si;

	this->codeEditorForm->GetScrollInfo(SB_VERT, &si, SIF_ALL);//���� ��ũ�� ����
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;

	if (this->longestHeight > cy) {//���� ������ ȭ�麸�� ���
		si.nMax = this->longestHeight; //��ũ�ѹ��� ũ�⸦ ���� ���� ũ��� ����
	}
	else { //���� �ʴٸ�
		si.nMax = cy; //��ũ�ѹ��� ũ�⸦ ȭ��ũ��� ����
	}
	si.nPage = cy; //�������� ũ��� �� ȭ�鿡 ���̴� ũ��� ����
	this->codeEditorForm->SetScrollInfo(SB_VERT, &si, TRUE); //���� ��ũ�ѹٿ� ������ ����
}

void Scroll::MoveHScroll() {
	ScrollActionFactory scrollActionFactory(this->codeEditorForm);
	ScrollAction* scrollAction;
	SCROLLINFO si;
	Long nSBCode = -1;
	Long xPosX;
	Long viewXPos;
	Long viewReversXPos;
	Long lineWidth;
	Long nPos = 0;

	xPosX = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	lineWidth = this->codeEditorForm->caretCoordinator->GetLineWidth(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	
	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_ALL);
	si.nMax = max(this->codeEditorForm->clientRect.right - this->codeEditorForm->marginWidth, longestWidth - this->codeEditorForm->marginWidth);
	this->codeEditorForm->SetScrollInfo(SB_HORZ, &si, TRUE);

	viewXPos = xPosX - this->codeEditorForm->marginWidth;
	viewXPos -= si.nPos;

	viewReversXPos = this->codeEditorForm->clientRect.right - viewXPos;
	viewReversXPos -= this->codeEditorForm->marginWidth;

	//��Ʈ��Ű�� �ȴ��Ȱų� ��Ʈ��Ű + HOME, END, LEFT, RIGHT, UP, DOWN, A, VŰ���
	if (!(GetAsyncKeyState(VK_CONTROL) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_HOME) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_END) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_LEFT) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_UP) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_DOWN) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x41) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x56) & 0x8000)) {

		//���� ��ġ�� ȭ���� �Ѿ��ٸ�
		if (this->longestWidth >= this->codeEditorForm->clientRect.right) {
			//���� ���� ��ġ�� ������ ��ġ���
			if (xPosX == this->longestWidth) {
				nSBCode = SB_RIGHT; //���� ���������� ��ũ���Ѵ�.
			}
			//���� ���� ��ġ�� ȭ�� �������̸�
			else if (viewXPos >= (this->codeEditorForm->clientRect.right) - this->codeEditorForm->marginWidth) {
				nSBCode = SB_LINERIGHT; //���������� �Ѵܾŭ ��ũ���Ѵ�.
			}
			//���� ��ġ�� ó�� �̶��
			else if (this->codeEditorForm->current->GetCurrent() == 0) {
				nSBCode = SB_LEFT; //���� �������� ��ũ���Ѵ�.
			}
			//���� ���� ��ġ�� ȭ�� �����̶��
			else if (viewReversXPos > this->codeEditorForm->clientRect.right - this->codeEditorForm->marginWidth) {
				nSBCode = SB_LINELEFT;//�������� �� �ܾŭ ��ũ���Ѵ�.
			}
		}
		else {
			nSBCode = SB_LEFT; //���� �������� ��ũ���Ѵ�.
		}
	}

	scrollAction = scrollActionFactory.Make(nSBCode, false);

	this->xPos = xPosX;

	if (scrollAction != NULL) {
		scrollAction->Move(nSBCode, nPos);
		delete scrollAction;
	}
}

void Scroll::MoveVScroll() {
	ScrollActionFactory scrollActionFactory(this->codeEditorForm);
	ScrollAction* scrollAction;
	SCROLLINFO si;
	Long nSBCode = -1;
	Long yPosX;
	Long memoCurrentX;
	Long fontHeight;
	Long viewYPos;
	Long viewReversYPos;

	yPosX = this->codeEditorForm->caretCoordinator->GetYPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->memo->GetCurrent() + 1);
	memoCurrentX = this->codeEditorForm->memo->GetCurrent();
	fontHeight = this->codeEditorForm->fontMatrix->GetHeight();

	this->codeEditorForm->GetScrollInfo(SB_VERT, &si, SIF_ALL);
	si.nMax = max(this->codeEditorForm->clientRect.bottom, this->longestHeight);
	this->codeEditorForm->SetScrollInfo(SB_VERT, &si, TRUE);

	viewYPos = yPosX - si.nPos;
	viewReversYPos = this->codeEditorForm->clientRect.bottom + fontHeight - viewYPos;

	//������� ���̰� ȭ���� �Ѿ��ٸ�
	if (this->longestHeight > this->codeEditorForm->clientRect.bottom) {
		//���� ���� ������ �� �̶��
		if (yPosX == this->longestHeight) {
			nSBCode = SB_BOTTOM; //���� �Ʒ��� ��ũ���Ѵ�.
		}
		//������ �Ʒ��� �̵��޴ٸ�
		else if (GetAsyncKeyState(VK_NEXT) & 0x8000) {
			nSBCode = SB_PAGEDOWN;
		}
		//���� ���� ȭ�� �Ʒ����
		else if (viewYPos > this->codeEditorForm->clientRect.bottom) {
			nSBCode = SB_LINEDOWN; //�Ʒ��� ���ٸ�ŭ ��ũ���Ѵ�.
		}
		//���� ���� ó�� �� �̶��
		else if (yPosX == fontHeight) {
			nSBCode = SB_TOP; //���� ���� ��ũ���Ѵ�.
		}
		//������ ���� �̵��ߴٸ�
		else if (GetAsyncKeyState(VK_PRIOR) & 0x8000) {
			nSBCode = SB_PAGEUP;
		}
		//���� ���� ȭ�� �����
		else if (viewReversYPos > this->codeEditorForm->clientRect.bottom) {
			nSBCode = SB_LINEUP; //���� ���ٸ�ŭ ��ũ���Ѵ�.
		}
	}

	this->yPos = yPosX;

	scrollAction = scrollActionFactory.Make(nSBCode, true);

	if (scrollAction != NULL) {
		scrollAction->Move(nSBCode, 0);
		delete scrollAction;
	}
	this->memoCurrent = memoCurrentX;
}

void Scroll::Update() {
	this->longestWidth = this->codeEditorForm->caretCoordinator->GetLongestWidth(this->codeEditorForm->fontMatrix, this->codeEditorForm->memo);
	
	if (this->codeEditorForm->status->GetStatusBar() == NULL) {
		this->longestHeight = this->codeEditorForm->memo->GetLength() * this->codeEditorForm->fontMatrix->GetHeight();
	}
	else {
		this->longestHeight = (this->codeEditorForm->memo->GetLength() - 1) * this->codeEditorForm->fontMatrix->GetHeight();
	}
	if (this->codeEditorForm->nSBCode == false) {
		this->MoveVScroll();
		this->MoveHScroll();
	}
	this->ShowScroll();
	this->codeEditorForm->nSBCode = false;
}

/*
�Լ��� : operator=
��� : ġȯ ������
*/
Scroll& Scroll::operator=(const Scroll& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->longestWidth = source.longestWidth;
	this->longestHeight = source.longestHeight;
	this->xPos = source.xPos;
	this->yPos = source.yPos;
	this->memoCurrent = source.memoCurrent;

	return *this;
}