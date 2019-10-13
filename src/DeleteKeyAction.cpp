//DeleteKeyAction.cpp


#include "DeleteKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"
#include "Cancellation.h"

DeleteKeyAction::DeleteKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

DeleteKeyAction::~DeleteKeyAction() {
}

void DeleteKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph *next;
	Glyph *letter;
	Glyph *previous;
	Long lineCurrent;
	Long lineLength;
	Long memoCurrent;
	Long memoLength;
	Long nextLength;
	Long i = 0;
	Long lineCurrentx;// REMOVE  ������ ����
	Long lineLengthx;// REMOVE  ������ ����.
	CPoint start;
	CPoint end;
	CPoint temp;


	//���ÿ����� ���Ѵ�.
	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();

	if (start == end) { //���ÿ����� ���ٸ�
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		lineLength = this->codeEditorForm->current->GetLength();

		if (lineCurrent < lineLength) {
			this->codeEditorForm->cancellation->UndoPush(2);
			this->codeEditorForm->current->Remove(lineCurrent);
			lineCurrentx = this->codeEditorForm->current->GetCurrent();// REMOVE  ������ ����
			lineLengthx = this->codeEditorForm->current->GetLength();// REMOVE  ������ ����

			if (lineCurrent == lineLength - 1 && lineCurrentx == lineLengthx - 1) {// REMOVE  ������ ����
				this->codeEditorForm->current->Last();
			}
		}
		else {
			memoCurrent = this->codeEditorForm->memo->GetCurrent();
			memoLength = this->codeEditorForm->memo->GetLength();

			if (memoCurrent < memoLength - 1) {
				this->codeEditorForm->cancellation->UndoPush(2);
				next = this->codeEditorForm->memo->GetAt(memoCurrent + 1);
				nextLength = next->GetLength();

				while (i < nextLength) {
					letter = next->GetAt(i);
					this->codeEditorForm->current->Add(letter->Clone());
					i++;
				}
				this->codeEditorForm->memo->Remove(memoCurrent + 1);
				this->codeEditorForm->current->Move(lineCurrent);
			}
		}
	}
	else {
		this->codeEditorForm->cancellation->UndoPush(2);
		if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
			temp = end;
			end = start;
			start = temp;

			this->codeEditorForm->memo->Move(end.y);
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(end.y);
			this->codeEditorForm->current->Move(end.x);
		}

		while (start.y != end.y || start.x != end.x) {//���ÿ������� �ݺ��Ѵ�.
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
				previous = this->codeEditorForm->memo->GetAt(end.y);//end.y��°�� �ִ� �� ã��
				lineCurrent = previous->GetLength();//end.y ���� length��ŭ ���ڸ� �ű��.
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
		this->codeEditorForm->current->Move(start.x);
		this->codeEditorForm->select->Reset();
	}
}