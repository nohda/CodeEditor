//CodeEditorForm.cpp
/*
파일명 : CodeEditorForm.cpp
작성일자 : 2019년 03월 27일
작성자 : 김영재
기능 : CodeEditorForm (View)
수정 : Line 의 GetContents 를 이용한 글 출력
		20190402 OnFontMenuClicked 기능구현 , OnClose에 저장기능 구현
		20190403 OnSaveMenuClicked 기능구현, OnSaveAsMenuClicked 기능 구현
		20190411 OnPaint 글자 높이수정
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

	if (this->nFlagUndo == FALSE ) {//입력된 키가 글자이고, 조합이 끝났다면
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

	if (this->status->GetStatusBar() != NULL) { //상태바가 없다면
		status = 20;
	}

	if (nType != SIZE_MINIMIZED || nType != SIZE_MAXIMIZED) {
		
		//((CodeEditorFormFrame *)GetParent())->GetClientRect(&this->clientRect);
		((CodeEditorFormFrame*)GetParent())->GetClientRect(&parentRect);
		parentRect.left = this->marginWidth;//마진영역
		parentRect.bottom -= (status /*+ si.cbSize*/);
		this->SetWindowPos(NULL, parentRect.left, parentRect.top, parentRect.right, parentRect.bottom, SWP_NOMOVE);//상태바없으면 뺴기
		this->GetClientRect(&this->clientRect);
		this->clientRect.left = this->marginWidth;
	}
	this->scroll->UpdateHScroll(cx);
	this->scroll->UpdateVScroll(cy);

	if (this->memoryDC->GetBuffer() != NULL) {
		this->memoryDC->Resize(); //변경된 작업영역 크기의 비트맵을 새로 만들어야하므로 삭제한다.
	}

	if (this->status->GetStatusBar() != NULL) {
		this->status->Delete(); //변경된 윈도우 크기에 맞춰서 상태바의 크기도 재설정한다.
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
		scrollAction->Move(nSBCode, nPos); //NULL이 아니면 Move 호출
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

		scrollAction->Move(nSBCode, nPos); //NULL이 아니면 Move 호출
		delete scrollAction;
	}

	this->Notify();
	this->Invalidate();
}

void CodeEditorForm::OnLButtonDown(UINT nFlags, CPoint point) {
	
	if (GetKeyState(VK_SHIFT) < 0) { //쉬프트키가 눌렸다면
		this->select->EndArea(this->mouseAction->LButton(point)); //끝점을 설정한다.
	}
	else { //아니라면
		this->select->Reset(); //선택영역을 초기화한다.
		this->select->StartArea(this->mouseAction->LButton(point)); //시작점과 끝점을 설정한다.
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

	findDialog = CFindReplaceDialog::GetNotifier(lParam); // 찾기 모달리스의 포인터를 얻는다.
	
	if (findDialog->FindNext() && findDialog->SearchDown()) { //찾기를 눌렀고 찾는방향이 아래라면
		this->find->FindDown((LPCTSTR)findDialog->GetFindString(), findDialog->MatchCase());
	}
	else if(findDialog->FindNext() && !findDialog->SearchDown()) { //찾기를 눌렀고 찾는방향이 위라면
		this->find->FindUp((LPCTSTR)findDialog->GetFindString(), findDialog->MatchCase());
	}
	else if (findDialog->ReplaceCurrent()) { //바꾸기를 눌렀다면
		this->find->Correct((LPCTSTR)findDialog->GetFindString(), (LPCTSTR)findDialog->GetReplaceString(), findDialog->MatchCase());
	}
	else if (findDialog->ReplaceAll()) { //모두바꾸기를 눌렀다면
		this->find->AllCorrect((LPCTSTR)findDialog->GetFindString(), (LPCTSTR)findDialog->GetReplaceString(), findDialog->MatchCase());
	}
	else { //다이얼로그가 종료 됬다면
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

	if (this->memoryDC->GetBuffer() == NULL) { //버퍼가 없다면 만든다.
		this->memoryDC->Make(&dc);
	}

	this->memoryDC->Draw(&dc); //버퍼에 작업한다.
	dc.BitBlt(0, 0, this->clientRect.right, this->clientRect.bottom, this->memoryDC->GetMemDC(), 0, 0, SRCCOPY); //버퍼DC의 작업내용을 화면에 복사한다.
	this->memoryDC->SetOfDelete();
}

/*
함수명: TakeIn
기능: 텍스트를 기존메모에 끼운다
수정 :
*/
void CodeEditorForm::TakeIn(string text) {
	this->select->Reset();
	this->memo = this->file->TakeInMemo(text);
	this->memo->First(); //모든줄에서 첫번째 줄로 이동 커런트를 첫번째로 맞춰야 한다.
	this->current = this->memo->GetAt(0); //현재줄을 첫번째 줄로 설정한다.
	this->current->First(); //첫번째줄의 첫칸으로 이동한다.
}

/*
함수명: OnClose
기능: 창을 닫는다
수정 : Cancle 수정 필요
*/
void CodeEditorForm::OnClose() {
	int messageBox;

	messageBox = MessageBox((LPCTSTR)"저장하시겠습니까?", (LPCTSTR)"저장", MB_YESNOCANCEL);
	
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