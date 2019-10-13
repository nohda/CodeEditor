//CodeEditorForm.cpp
/*
���ϸ� : CodeEditorForm.cpp
�ۼ����� : 2019�� 03�� 27��
�ۼ��� : �迵��
��� : CodeEditorForm (View)
���� : Line �� GetContents �� �̿��� �� ���
		20190402 OnFontMenuClicked ��ɱ��� , OnClose�� ������ ����
		20190403 OnSaveMenuClicked ��ɱ���, OnSaveAsMenuClicked ��� ����
		20190411 OnPaint ���� ���̼���
*/

#include "CodeEditorForm.h"
#include "Memo.h"
#include "Line.h"
#include "resource.h"
#include "File.h"
#include "Font.h"
#include "CaretController.h"
#include "CaretCoordinator.h"
#include "FontMatrix.h"
#include "KeyActionFactory.h"
#include "KeyAction.h"
#include "GlyphFactory.h"
#include "WriteState.h"
#include "WriteStateAppend.h"
#include "WriteStateInsert.h"
#include "CommandFactory.h"
#include "Command.h"
#include "ScrollActionFactory.h"
#include "ScrollAction.h"
#include "Scroll.h"
#include "TextCoordinator.h"
#include "textEdit.h"
#include "MemoryDC.h"
#include "Select.h"
#include "MouseAction.h"
#include "MenuUpdate.h"
#include "Cancellation.h"
#include "Memory.h"
#include "MemoryInsert.h"
#include "MemoryDelete.h"
#include "Find.h"
#include "Status.h"
#include "CodeEditorFormFrame.h"

static const UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

BEGIN_MESSAGE_MAP(CodeEditorForm, CWnd)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnImeStartComposition)
	ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	ON_MESSAGE(WM_IME_CHAR, OnImeChar)
	ON_MESSAGE(WM_MOUSEWHEEL, OnMouseWheel)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_COMMAND(IDM_FILE_EXIT, OnClose) //01
	ON_UPDATE_COMMAND_UI_RANGE(IDM_EDIT_UNDO, IDM_STATE_STATUSBAR, OnMenuButtonUpdate) //02 ~ 10
	ON_COMMAND_RANGE(IDM_EDIT_UNDO, IDM_HELP_ABOUT, OnMenuButtonClicked) //02 ~ 20
	ON_REGISTERED_MESSAGE(WM_FINDREPLACE, OnFind)
	ON_WM_CLOSE()

END_MESSAGE_MAP()

CodeEditorForm::CodeEditorForm() {
	this->memo = NULL;
	this->current = NULL;
	this->isComposing = FALSE;
	this->file = NULL;
	this->font = NULL;
	this->fontMatrix = NULL;
	this->scroll = NULL;
	this->nSBCode = FALSE;
	this->memoryDC = NULL;
	this->caretController = NULL;
	this->textCoordinator = NULL;
	this->textEdit = NULL;
	this->caretCoordinator = NULL;
	this->select = NULL;
	this->mouseAction = NULL;
	this->nFlagUndo = FALSE;
	this->cancellation = NULL;
	this->memory = NULL;
	this->memoryInsert = NULL;
	this->memoryDelete = NULL;
	this->find = NULL;
	this->clientRect = { 0, };
	this->marginWidth = 60;
	this->status = NULL;
}

int CodeEditorForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	
	CWnd::OnCreate(lpCreateStruct);

	this->memo = new Memo;
	this->current = new Line;
	this->memo->Add(this->current);
	this->file = new File;
	this->font = new Font(this);
	this->fontMatrix = new FontMatrix(this->font->GetDC());
	this->ReleaseDC(this->font->GetDC());
	this->scroll = new Scroll(this);
	this->scroll->MakeScroll();
	this->memoryDC = new MemoryDC(this);
	this->caretController = new CaretController(this, this->current, this->memo->GetCurrent());
	this->textCoordinator = new TextCoordinator(this);
	this->textEdit = new TextEdit(this);
	this->caretCoordinator = new CaretCoordinator(this);
	this->states[0] = WriteStateAppend::WriteAppendInstance(this);
	this->states[1] = WriteStateInsert::WriteInsertInstance(this);
	this->state = this->states[0];
	this->mouseAction = new MouseAction(this);
	this->select = new Select(this);
	this->memoryInsert = new MemoryInsert(this);
	this->memoryDelete = new MemoryDelete(this);
	this->cancellation = new Cancellation(this);
	this->memory = new Memory(this);
	this->find = new Find(this);
	this->status = new Status(this);
	this->Notify();

	return 0;
}

void CodeEditorForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//this->textEdit->AddTap();
	state->ChangeState();
	state->OnChar(nChar, nRepCnt, nFlags);

	if (this->nFlagUndo == FALSE && nChar !=8) {
		this->cancellation->UndoPush(1);
	}
	this->textEdit->AddParenthese(nChar);
	if (nChar == 13) {
		this->textEdit->AddTap();
	}
	this->nFlagUndo = FALSE;
	this->Notify();
	this->Invalidate();
}

LRESULT CodeEditorForm::OnImeStartComposition(WPARAM wParam, LPARAM lParam) {
	return 0;
}


LRESULT CodeEditorForm::OnImeComposition(WPARAM wParam, LPARAM lParam) {
	state->ChangeState();
	state->OnImeComposition(wParam, lParam);
	
	this->nFlagUndo = FALSE;
	this->Notify();
	this->Invalidate();
	return 0;
}

LRESULT CodeEditorForm::OnImeChar(WPARAM wParam, LPARAM lParam) {
	state->ChangeState();
	state->OnImeChar(wParam, lParam);

	if (this->nFlagUndo == FALSE ) {//�Էµ� Ű�� �����̰�, ������ �����ٸ�
		this->cancellation->UndoPush(1);
	}

	this->nFlagUndo = FALSE;
	this->Notify();
	this->Invalidate();

	return 0;
}

void CodeEditorForm::OnSize(UINT nType, int cx, int cy) {
	CodeEditorFormFrame *pFrame = (CodeEditorFormFrame*)AfxGetMainWnd();
	Long status = 0;
	CRect parentRect;
	CRect childRect;

	if (this->status->GetStatusBar() != NULL) { //���¹ٰ� ���ٸ�
		status = 20;
	}

	if (nType != SIZE_MINIMIZED || nType != SIZE_MAXIMIZED) {
		
		//((CodeEditorFormFrame *)GetParent())->GetClientRect(&this->clientRect);
		((CodeEditorFormFrame*)GetParent())->GetClientRect(&parentRect);
		parentRect.left = this->marginWidth;//��������
		parentRect.bottom -= (status /*+ si.cbSize*/);
		this->SetWindowPos(NULL, parentRect.left, parentRect.top, parentRect.right, parentRect.bottom, SWP_NOMOVE);//���¹پ����� ����
		this->GetClientRect(&this->clientRect);
		this->clientRect.left = this->marginWidth;
	}
	this->scroll->UpdateHScroll(cx);
	this->scroll->UpdateVScroll(cy);

	if (this->memoryDC->GetBuffer() != NULL) {
		this->memoryDC->Resize(); //����� �۾����� ũ���� ��Ʈ���� ���� �������ϹǷ� �����Ѵ�.
	}

	if (this->status->GetStatusBar() != NULL) {
		this->status->Delete(); //����� ������ ũ�⿡ ���缭 ���¹��� ũ�⵵ �缳���Ѵ�.
		this->status->Create();
	}
	this->Notify();
}

void CodeEditorForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * cScrollBar) {
	ScrollActionFactory scrollActionFactory(this);
	ScrollAction *scrollAction;
	
	this->nSBCode = TRUE;
	scrollAction = scrollActionFactory.Make(nSBCode, TRUE);
	
	if (scrollAction != NULL) {
		scrollAction->Move(nSBCode, nPos); //NULL�� �ƴϸ� Move ȣ��
		delete scrollAction;
	}

	this->Notify();
	this->Invalidate();
}

void CodeEditorForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar * cScrollBar) {
	ScrollActionFactory scrollActionFactory(this);
	ScrollAction *scrollAction;

	this->nSBCode = TRUE;
	scrollAction = scrollActionFactory.Make(nSBCode, FALSE);

	if (scrollAction != NULL) {

		scrollAction->Move(nSBCode, nPos); //NULL�� �ƴϸ� Move ȣ��
		delete scrollAction;
	}

	this->Notify();
	this->Invalidate();
}

void CodeEditorForm::OnLButtonDown(UINT nFlags, CPoint point) {
	
	if (GetKeyState(VK_SHIFT) < 0) { //����ƮŰ�� ���ȴٸ�
		this->select->EndArea(this->mouseAction->LButton(point)); //������ �����Ѵ�.
	}
	else { //�ƴ϶��
		this->select->Reset(); //���ÿ����� �ʱ�ȭ�Ѵ�.
		this->select->StartArea(this->mouseAction->LButton(point)); //�������� ������ �����Ѵ�.
	}

	this->SetCapture();
	this->Notify();
	this->Invalidate();
}

void CodeEditorForm::OnLButtonUp(UINT nFlags, CPoint point) {
	ReleaseCapture();
	this->Notify();
	this->Invalidate();
}

void CodeEditorForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CPoint give;

	give = this->mouseAction->LButton(point);
	if (give.x != 0) {
		give.x -= 1;
	}

	this->mouseAction->DblClk(give);
	this->select->WordArea(this->mouseAction->GetDblClkStart(), this->mouseAction->GetDblClkEnd());
	this->Notify();
	this->Invalidate();
}

void CodeEditorForm::OnRButtonUp(UINT nFlags, CPoint point) {
	CMenu menu;
	CMenu *contextMenu;
	CPoint menuPoint;
	CRect rect;

	menu.LoadMenu(IDR_MENU1);
	contextMenu = menu.GetSubMenu(1);
	this->GetClientRect(rect);
	GetCursorPos(&menuPoint);
	contextMenu->TrackPopupMenu(TPM_LEFTALIGN, menuPoint.x, menuPoint.y, this);
}

LRESULT CodeEditorForm::OnMouseWheel(WPARAM wParam, LPARAM lParam) {
	this->mouseAction->Wheel(wParam, lParam);
	this->Notify();
	this->Invalidate();

	return ::DefWindowProc(this->m_hWnd, WM_MOUSEWHEEL, wParam, lParam);
}

void CodeEditorForm::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {
		this->select->EndArea(this->mouseAction->LButton(point));
		this->Notify();
		this->Invalidate();
	}
}

void CodeEditorForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	KeyActionFactory keyActionFactory(this);
	KeyAction *keyAction;
	
	keyAction = keyActionFactory.Make(nChar);
	
	if (keyAction != NULL) {
		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
		delete keyAction;
	}
	this->Notify();
	this->Invalidate();
}

void CodeEditorForm::OnMenuButtonClicked(UINT id) {
	CommandFactory* commandFactory = new CommandFactory(this);
	Command* command = commandFactory->Make(id);

	if (command != NULL) {
		command->Execute();
		delete command;
	}
	this->Notify();
	this->Invalidate();
}

void CodeEditorForm::OnMenuButtonUpdate(CCmdUI *pCmdUI) {
	MenuUpdate menuUpdate(this);

	menuUpdate.Update(pCmdUI);

}

LRESULT CodeEditorForm::OnFind(WPARAM wParam, LPARAM lParam){
	CFindReplaceDialog* findDialog;

	findDialog = CFindReplaceDialog::GetNotifier(lParam); // ã�� ��޸����� �����͸� ��´�.
	
	if (findDialog->FindNext() && findDialog->SearchDown()) { //ã�⸦ ������ ã�¹����� �Ʒ����
		this->find->FindDown((LPCTSTR)findDialog->GetFindString(), findDialog->MatchCase());
	}
	else if(findDialog->FindNext() && !findDialog->SearchDown()) { //ã�⸦ ������ ã�¹����� �����
		this->find->FindUp((LPCTSTR)findDialog->GetFindString(), findDialog->MatchCase());
	}
	else if (findDialog->ReplaceCurrent()) { //�ٲٱ⸦ �����ٸ�
		this->find->Correct((LPCTSTR)findDialog->GetFindString(), (LPCTSTR)findDialog->GetReplaceString(), findDialog->MatchCase());
	}
	else if (findDialog->ReplaceAll()) { //��ιٲٱ⸦ �����ٸ�
		this->find->AllCorrect((LPCTSTR)findDialog->GetFindString(), (LPCTSTR)findDialog->GetReplaceString(), findDialog->MatchCase());
	}
	else { //���̾�αװ� ���� ��ٸ�
		this->find->Delete();
	}
	this->Notify();
	this->Invalidate();

	return 0;
}

void CodeEditorForm::OnSetFocus(CWnd * pOldWnd) {
	this->caretController->ShowCaret(TRUE);
}

void CodeEditorForm::OnKillFocus(CWnd * pNewWnd) {
	this->caretController->ShowCaret(FALSE);

}

BOOL CodeEditorForm::OnEraseBkgnd(CDC * pDC){
	return FALSE;
}

void CodeEditorForm::OnPaint() {
	CPaintDC dc(this);

	if (this->memoryDC->GetBuffer() == NULL) { //���۰� ���ٸ� �����.
		this->memoryDC->Make(&dc);
	}

	this->memoryDC->Draw(&dc); //���ۿ� �۾��Ѵ�.
	dc.BitBlt(0, 0, this->clientRect.right, this->clientRect.bottom, this->memoryDC->GetMemDC(), 0, 0, SRCCOPY); //����DC�� �۾������� ȭ�鿡 �����Ѵ�.
	this->memoryDC->SetOfDelete();
}

/*
�Լ���: TakeIn
���: �ؽ�Ʈ�� �����޸� �����
���� :
*/
void CodeEditorForm::TakeIn(string text) {
	this->select->Reset();
	this->memo = this->file->TakeInMemo(text);
	this->memo->First(); //����ٿ��� ù��° �ٷ� �̵� Ŀ��Ʈ�� ù��°�� ����� �Ѵ�.
	this->current = this->memo->GetAt(0); //�������� ù��° �ٷ� �����Ѵ�.
	this->current->First(); //ù��°���� ùĭ���� �̵��Ѵ�.
}

/*
�Լ���: OnClose
���: â�� �ݴ´�
���� : Cancle ���� �ʿ�
*/
void CodeEditorForm::OnClose() {
	int messageBox;

	messageBox = MessageBox((LPCTSTR)"�����Ͻðڽ��ϱ�?", (LPCTSTR)"����", MB_YESNOCANCEL);
	
	if (messageBox == IDYES || messageBox == IDNO) {

		if (messageBox == IDYES) {
			this->OnMenuButtonClicked(IDM_FILE_SAVE);
		}
		if (this->status != NULL) {
			delete this->status;
			this->status = NULL;
		}
		if (this->find != NULL) {
			delete this->find;
			this->find = NULL;
		}
		if (this->memory != NULL) {
			delete this->memory;
			this->memory = NULL;
		}
		if (this->cancellation != NULL) {
			delete this->cancellation;
			this->cancellation = NULL;
		}
		if (this->memoryInsert != NULL) {
			delete this->memoryInsert;
			this->memoryInsert = NULL;
		}
		if (this->memoryDelete != NULL) {
			delete this->memoryDelete;
			this->memoryDelete = NULL;
		}
		if (this->select != NULL) {
			delete this->select;
			this->select = NULL;
		}
		if (this->mouseAction != NULL) {
			delete this->mouseAction;
			this->mouseAction = NULL;
		}
		if (this->caretCoordinator != NULL) {
			delete this->caretCoordinator;
			this->caretCoordinator = NULL;
		}
		if (this->textCoordinator != NULL) {
			delete this->textCoordinator;
			this->textCoordinator = NULL;
		}
		if (this->caretController != NULL) {
			delete this->caretController;
			this->caretController = NULL;
		}
		if (this->memoryDC != NULL) {
			delete this->memoryDC;
			this->memoryDC = NULL;
		}
		if (this->scroll != NULL) {
			delete this->scroll;
			this->scroll = NULL;
		}
		if (this->fontMatrix != NULL) {
			delete this->fontMatrix;
			this->fontMatrix = NULL;
		}
		if (this->font != NULL) {
			delete this->font;
			this->font = NULL;
		}
		if (this->file != NULL) {
			delete this->file;
			this->file = NULL;
		}
		if (this->memo != NULL) {
			delete this->memo;
			this->memo = NULL;
		}
		
		CWnd::OnClose();
	}
}