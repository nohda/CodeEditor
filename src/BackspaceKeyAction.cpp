//BackspaceKeyAction.cpp
/*
���ϸ� : BackspaceKeyAction.cpp
�ۼ����� : 2019�� 04�� 17��
�ۼ��� : �迵��
��� : �齺���̽� Ű
���� : 
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
	//���ÿ����� ���Ѵ�.
	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();

	if (start == end) { //���ÿ����� ���ٸ�
		this->codeEditorForm->cancellation->UndoPush(3);
		this->codeEditorForm->nFlagUndo = TRUE;
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		lineLength = this->codeEditorForm->current->GetLength();

		if (lineCurrent > 0) { //ó���� �ƴ϶��
			if (this->codeEditorForm->current->GetCurrent() < this->codeEditorForm->current->GetLength()) {
				this->codeEditorForm->current->Previous();
			}
			this->codeEditorForm->current->Remove(lineCurrent - 1); //������ġ�� ���ڸ� �����

		}
		else {
			memoCurrent = this->codeEditorForm->memo->GetCurrent();
			previous = this->codeEditorForm->current;
			ret = this->codeEditorForm->memo->Previous();

			if (ret != memoCurrent) {
				this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(ret);
				lineLength = this->codeEditorForm->current->GetLength(); //�����߰� else�� current�� Length�� if�� current�� Length�� ��뷮�� �ٸ� 
				cloneLength = previous->GetLength();

				while (i < cloneLength) {
					letter = previous->GetAt(i);
					this->codeEditorForm->current->Add(letter->Clone());
					i++;
				}

				this->codeEditorForm->memo->Remove(ret + 1);
				this->codeEditorForm->current->Move(lineLength); // �����߰� �齺���̽��� �������� ���� �� �������� ��뷮���� ĳ�� �̵�
			}
		}
	}
	else { //���ÿ����� �ְ� ���ד��̶�� �������� �����Ѵ�.
		if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
			temp = end;
			end = start;
			start = temp;

			this->codeEditorForm->memo->Move(end.y);
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(end.y);
			this->codeEditorForm->current->Move(end.x);
		}
		this->codeEditorForm->cancellation->UndoPush(3);

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
	this->codeEditorForm->select->Reset();
	}
}