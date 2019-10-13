//Scroll.cpp
/*
파일명 : Scroll.cpp
작성일자 : 2019년 04월 24일
작성자 : 김영재
기능 : 스크롤에 대한 생성,이동,보여주기
수정 :
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
함수명 : Scroll
기능 : 매개변수 생성자
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
함수명 : Scroll
기능 : 복사 생성자
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
함수명 : Scroll
기능 : 소멸자
*/
Scroll::~Scroll() {
	this->codeEditorForm->SubjectDetach(this);
	delete this->cscrollBar;
}

void Scroll::MakeScroll() {
	this->cscrollBar->Create(SBS_VERT | SBS_TOPALIGN | SBS_HORZ | SBS_LEFTALIGN, this->codeEditorForm->clientRect, this->codeEditorForm, 0);
}

/*
함수명 : Show
기능 : 스크롤을 보여준다
*/
void Scroll::ShowScroll() {
	Long memoLength;
	Glyph* memo;

	memoLength = this->codeEditorForm->memo->GetLength();
	memo = this->codeEditorForm->memo;
	this->codeEditorForm->ShowScrollBar(SB_VERT | SB_HORZ); //가로, 세로 스크롤을 보여준다.

	if (this->longestHeight < this->codeEditorForm->clientRect.bottom) {
		this->codeEditorForm->EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH); //가장 긴 높이가 클라이언트의 높이보다 낮으면 비활성화
	}
	else {
		this->codeEditorForm->EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);
	}

	if (this->longestWidth < this->codeEditorForm->clientRect.right) {
		this->codeEditorForm->EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH); //가장 긴 너비가 클라이언트의 너비보다 좁으면 비활성화
	}
	else {
		this->codeEditorForm->EnableScrollBar(SB_HORZ, ESB_ENABLE_BOTH);
	}
}

void Scroll::UpdateHScroll(Long cx) {
	SCROLLINFO si;

	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_ALL);//세로 스크롤 설정
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;

	if (this->longestWidth - this->codeEditorForm->marginWidth < cx - this->codeEditorForm->marginWidth) {//줄의 갯수가 화면보다 길지 않다면
		si.nMax = cx - this->codeEditorForm->marginWidth; //스크롤바의 크기를 화면크기로 설정
	}

	si.nPage = cx - this->codeEditorForm->marginWidth; //페이지의 크기는 한 화면에 보이는 크기로 설정
	this->codeEditorForm->SetScrollInfo(SB_HORZ, &si, TRUE); //세로 스크롤바에 설정값 세팅
}

void Scroll::UpdateVScroll(Long cy) {
	SCROLLINFO si;

	this->codeEditorForm->GetScrollInfo(SB_VERT, &si, SIF_ALL);//세로 스크롤 설정
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;

	if (this->longestHeight > cy) {//줄의 갯수가 화면보다 길면
		si.nMax = this->longestHeight; //스크롤바의 크기를 줄의 갯수 크기로 설정
	}
	else { //길지 않다면
		si.nMax = cy; //스크롤바의 크기를 화면크기로 설정
	}
	si.nPage = cy; //페이지의 크기는 한 화면에 보이는 크기로 설정
	this->codeEditorForm->SetScrollInfo(SB_VERT, &si, TRUE); //세로 스크롤바에 설정값 세팅
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

	//컨트롤키가 안눌렸거나 컨트롤키 + HOME, END, LEFT, RIGHT, UP, DOWN, A, V키라면
	if (!(GetAsyncKeyState(VK_CONTROL) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_HOME) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_END) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_LEFT) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_UP) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_DOWN) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x41) & 0x8000) ||
		(GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x56) & 0x8000)) {

		//줄의 위치가 화면을 넘었다면
		if (this->longestWidth >= this->codeEditorForm->clientRect.right) {
			//현재 줄의 위치가 마지막 위치라면
			if (xPosX == this->longestWidth) {
				nSBCode = SB_RIGHT; //가장 오른쪽으로 스크롤한다.
			}
			//현재 줄의 위치가 화면 오른쪽이면
			else if (viewXPos >= (this->codeEditorForm->clientRect.right) - this->codeEditorForm->marginWidth) {
				nSBCode = SB_LINERIGHT; //오른쪽으로 한단어만큼 스크롤한다.
			}
			//현재 위치가 처음 이라면
			else if (this->codeEditorForm->current->GetCurrent() == 0) {
				nSBCode = SB_LEFT; //가장 왼쪽으로 스크롤한다.
			}
			//현재 줄의 위치가 화면 왼쪽이라면
			else if (viewReversXPos > this->codeEditorForm->clientRect.right - this->codeEditorForm->marginWidth) {
				nSBCode = SB_LINELEFT;//왼쪽으로 한 단어만큼 스크롤한다.
			}
		}
		else {
			nSBCode = SB_LEFT; //가장 왼쪽으로 스크롤한다.
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

	//모든줄의 높이가 화면을 넘었다면
	if (this->longestHeight > this->codeEditorForm->clientRect.bottom) {
		//현재 줄이 마지막 줄 이라면
		if (yPosX == this->longestHeight) {
			nSBCode = SB_BOTTOM; //가장 아래로 스크롤한다.
		}
		//페이지 아래로 이동햇다면
		else if (GetAsyncKeyState(VK_NEXT) & 0x8000) {
			nSBCode = SB_PAGEDOWN;
		}
		//현재 줄이 화면 아래라면
		else if (viewYPos > this->codeEditorForm->clientRect.bottom) {
			nSBCode = SB_LINEDOWN; //아래로 한줄만큼 스크롤한다.
		}
		//현재 줄이 처음 줄 이라면
		else if (yPosX == fontHeight) {
			nSBCode = SB_TOP; //가장 위로 스크롤한다.
		}
		//페이지 위로 이동했다면
		else if (GetAsyncKeyState(VK_PRIOR) & 0x8000) {
			nSBCode = SB_PAGEUP;
		}
		//현재 줄이 화면 위라면
		else if (viewReversYPos > this->codeEditorForm->clientRect.bottom) {
			nSBCode = SB_LINEUP; //위로 한줄만큼 스크롤한다.
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
함수명 : operator=
기능 : 치환 연산자
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