#include "EnterKeyAction.h"
#include "CodeEditorForm.h"
#include "CaretCoordinator.h"
#include "Scroll.h"
#include "Glyph.h"
#include "Line.h"
#include "Letter.h"
#include "Cancellation.h"
#include "TextEdit.h"
#include "Select.h"

EnterKeyAction::EnterKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm) {
}

EnterKeyAction::~EnterKeyAction() {
}

void EnterKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph *line;
	Glyph *letter;
	Long lineCurrent;
	Long lineLength;
	Long memoCurrent;
	Long memoLength;
	Long i;
	string contents;
	string text="";
	CPoint start;
	CPoint end;
	CPoint temp;

	//선택영역을 구한다.
	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();
	contents = "\r\n";
	this->codeEditorForm->cancellation->UndoPush(1, contents);

	//선택영역이 있고 역항뱡이라면 기준점을 변경한다.
	if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
		temp = end;
		end = start;
		start = temp;

		this->codeEditorForm->memo->Move(end.y);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(end.y);
		this->codeEditorForm->current->Move(end.x);
	}

	while (start.y != end.y || start.x != end.x) {//선택영역동안 반복하여 지운다.
		if (end.x > 0) {
			if (this->codeEditorForm->current->GetCurrent() < this->codeEditorForm->current->GetLength()) {
				this->codeEditorForm->current->Previous();
			}
			this->codeEditorForm->current->Remove(end.x - 1);
			end.x--;
		}
		else {
			memoCurrent = this->codeEditorForm->memo->Previous();//end.y번째에 있는 줄 찾기
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			lineLength = this->codeEditorForm->current->GetLength();
			this->codeEditorForm->memo->Remove(end.y);
			end.y--;
			end.x = lineLength;
			this->codeEditorForm->current->Move(end.x);

		}
	}

	line = new Line;
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();
	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	memoLength = this->codeEditorForm->memo->GetLength();

	//현재 위치의 뒤에 글자가 있다면 
	if (lineCurrent != -1 && lineCurrent != lineLength) { //끼워쓰기 로직
		i = lineCurrent;

		while (i < lineLength) { //새줄에 글자 복사 로직
			letter = this->codeEditorForm->current->GetAt(i);
			if (i == lineCurrent) {
				text = letter->GetContents();
			}
			line->Add(letter->Clone());
			i++;
		}

		i = lineLength;

		while (i > lineCurrent) { //기존 줄 글자 삭제 로직
			this->codeEditorForm->current->Remove(lineCurrent);
			i--;
		}
	}
	//현재줄이 끝줄이라면
	else if (memoCurrent == memoLength - 1) {
		this->codeEditorForm->memo->Add(line); //줄을 붙인다.
	}
	else {
		this->codeEditorForm->memo->Add(line, memoCurrent + 1); //줄을 끼운다.
	}
	this->codeEditorForm->current = line;
	this->codeEditorForm->current->First(); //줄의 처음으로 이동한다.
	
	if (text == "}" ) {
		line = new Line;
		this->codeEditorForm->memo->Add(line, memoCurrent + 1);
		this->codeEditorForm->cancellation->UndoPush(1, contents);
		//this->codeEditorForm->textEdit->AddTap();
	}

}