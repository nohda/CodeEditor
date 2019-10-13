//BackspaceKeyAction.cpp
/*
파일명 : BackspaceKeyAction.cpp
작성일자 : 2019년 04월 17일
작성자 : 김영재
기능 : 백스페이스 키
수정 : 
*/

#include "BackspaceKeyAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"
#include "Glyph.h"
#include "Select.h"
#include "Cancellation.h"

BackspaceKeyAction::BackspaceKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

BackspaceKeyAction::~BackspaceKeyAction() {
}

void BackspaceKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long lineCurrent;
	Long memoCurrent;
	Long ret;
	Long cloneLength;
	Long i = 0;
	Glyph *previous;
	Glyph *letter;
	Long lineLength;
	CPoint start;
	CPoint end;
	CPoint temp;

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	memoCurrent = this->codeEditorForm->memo->GetCurrent();

	/*if (lineCurrent > 0 || memoCurrent > 0) {
		this->codeEditorForm->cancellation->UndoPush(3);
	}*/
	//선택영역을 구한다.
	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();

	if (start == end) { //선택영역이 없다면
		this->codeEditorForm->cancellation->UndoPush(3);
		this->codeEditorForm->nFlagUndo = TRUE;
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		lineLength = this->codeEditorForm->current->GetLength();

		if (lineCurrent > 0) { //처음이 아니라면
			if (this->codeEditorForm->current->GetCurrent() < this->codeEditorForm->current->GetLength()) {
				this->codeEditorForm->current->Previous();
			}
			this->codeEditorForm->current->Remove(lineCurrent - 1); //현재위치의 글자를 지운다

		}
		else {
			memoCurrent = this->codeEditorForm->memo->GetCurrent();
			previous = this->codeEditorForm->current;
			ret = this->codeEditorForm->memo->Previous();

			if (ret != memoCurrent) {
				this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(ret);
				lineLength = this->codeEditorForm->current->GetLength(); //로직추가 else후 current의 Length와 if후 current의 Length는 사용량이 다름 
				cloneLength = previous->GetLength();

				while (i < cloneLength) {
					letter = previous->GetAt(i);
					this->codeEditorForm->current->Add(letter->Clone());
					i++;
				}

				this->codeEditorForm->memo->Remove(ret + 1);
				this->codeEditorForm->current->Move(lineLength); // 로직추가 백스페이스로 현재줄을 지울 시 이전줄의 사용량으로 캐럿 이동
			}
		}
	}
	else { //선택영역이 있고 역항뱡이라면 기준점을 변경한다.
		if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
			temp = end;
			end = start;
			start = temp;

			this->codeEditorForm->memo->Move(end.y);
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(end.y);
			this->codeEditorForm->current->Move(end.x);
		}
		this->codeEditorForm->cancellation->UndoPush(3);

		while (start.y != end.y || start.x != end.x) {//선택영역동안 반복한다.
			lineCurrent = this->codeEditorForm->current->GetCurrent();
			lineLength = this->codeEditorForm->current->GetLength();
			if (end.x > 0) {
				if (this->codeEditorForm->current->GetCurrent() < this->codeEditorForm->current->GetLength()) {
				lineCurrent = this->codeEditorForm->current->Previous();
				}
				this->codeEditorForm->current->Remove(end.x - 1);
				end.x--;
			}
			else {
				previous = this->codeEditorForm->memo->GetAt(end.y);//end.y번째에 있는 줄 찾기
				lineCurrent = previous->GetLength();//end.y 줄의 length만큼 글자를 옮긴다.
				memoCurrent = this->codeEditorForm->memo->Previous();
				this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
				lineLength = this->codeEditorForm->current->GetLength();
				i = 0;
				while (i < lineCurrent) {
					letter = previous->GetAt(i);
					this->codeEditorForm->current->Add(letter->Clone());
					i++;
				}
				this->codeEditorForm->memo->Remove(end.y);
				end.y--;
				end.x = lineLength;
				this->codeEditorForm->current->Move(end.x);
			}
		}
	this->codeEditorForm->select->Reset();
	}
}