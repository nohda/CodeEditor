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

	//���ÿ����� ���Ѵ�.
	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();
	contents = "\r\n";
	this->codeEditorForm->cancellation->UndoPush(1, contents);

	//���ÿ����� �ְ� ���ד��̶�� �������� �����Ѵ�.
	if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
		temp = end;
		end = start;
		start = temp;

		this->codeEditorForm->memo->Move(end.y);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(end.y);
		this->codeEditorForm->current->Move(end.x);
	}

	while (start.y != end.y || start.x != end.x) {//���ÿ������� �ݺ��Ͽ� �����.
		if (end.x > 0) {
			if (this->codeEditorForm->current->GetCurrent() < this->codeEditorForm->current->GetLength()) {
				this->codeEditorForm->current->Previous();
			}
			this->codeEditorForm->current->Remove(end.x - 1);
			end.x--;
		}
		else {
			memoCurrent = this->codeEditorForm->memo->Previous();//end.y��°�� �ִ� �� ã��
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

	//���� ��ġ�� �ڿ� ���ڰ� �ִٸ� 
	if (lineCurrent != -1 && lineCurrent != lineLength) { //�������� ����
		i = lineCurrent;

		while (i < lineLength) { //���ٿ� ���� ���� ����
			letter = this->codeEditorForm->current->GetAt(i);
			if (i == lineCurrent) {
				text = letter->GetContents();
			}
			line->Add(letter->Clone());
			i++;
		}

		i = lineLength;

		while (i > lineCurrent) { //���� �� ���� ���� ����
			this->codeEditorForm->current->Remove(lineCurrent);
			i--;
		}
	}
	//�������� �����̶��
	else if (memoCurrent == memoLength - 1) {
		this->codeEditorForm->memo->Add(line); //���� ���δ�.
	}
	else {
		this->codeEditorForm->memo->Add(line, memoCurrent + 1); //���� �����.
	}
	this->codeEditorForm->current = line;
	this->codeEditorForm->current->First(); //���� ó������ �̵��Ѵ�.
	
	if (text == "}" ) {
		line = new Line;
		this->codeEditorForm->memo->Add(line, memoCurrent + 1);
		this->codeEditorForm->cancellation->UndoPush(1, contents);
		//this->codeEditorForm->textEdit->AddTap();
	}

}