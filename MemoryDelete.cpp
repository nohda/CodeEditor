#include "MemoryDelete.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Line.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "Memory.h"
#include "Select.h"

MemoryDelete::MemoryDelete() {
	this->codeEditorForm = 0;
}

MemoryDelete::MemoryDelete(CodeEditorForm * codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

MemoryDelete::MemoryDelete(const MemoryDelete & source) {
	this->codeEditorForm = source.codeEditorForm;
}

MemoryDelete::~MemoryDelete() {
}


Memory * MemoryDelete::UndoDelete(Memory *memory) {
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

	start.SetPoint(memory->startX, memory->startY);
	end.SetPoint(memory->endX, memory->endY);

	memoCurrent = this->codeEditorForm->memo->Move(end.y);
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	if (end.x > 0) {
		this->codeEditorForm->current->Move(end.x);
	}
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent > 0 && lineLength > 0) { //처음이 아니라면
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

	return memory;
}

Memory * MemoryDelete::RedoBack(Memory * memory) {
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

	//선택영역을 구한다.

	start.SetPoint(memory->startX, memory->startY);
	end.SetPoint(memory->endX, memory->endY);

	memoCurrent = this->codeEditorForm->memo->Move(end.y);
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	this->codeEditorForm->current->Move(end.x);

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

	return memory;
}

Memory * MemoryDelete::RedoDelete(Memory * memory) {
	Long i = 0;
	Glyph *letter;
	Glyph *next;
	Long lineCurrent;
	Long lineLength;
	Long lineCurrentx;// REMOVE  수정후 삭제
	Long lineLengthx;
	Long memoCurrent;
	Long memoLength;
	Long nextLength;
	CPoint start;
	CPoint end;
	CPoint temp;

	start.SetPoint(memory->startX, memory->startY);
	end.SetPoint(memory->endX, memory->endY);

	memoCurrent = this->codeEditorForm->memo->Move(end.y);
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	this->codeEditorForm->current->Move(end.x);


	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent < lineLength) {
		this->codeEditorForm->current->Remove(lineCurrent);
		lineCurrentx = this->codeEditorForm->current->GetCurrent();// REMOVE  수정후 삭제
		lineLengthx = this->codeEditorForm->current->GetLength();// REMOVE  수정후 삭제

		if (lineCurrent == lineLength - 1 && lineCurrentx == lineLengthx - 1) {// REMOVE  수정후 삭제
			this->codeEditorForm->current->Last();
		}
	}
	else {
		memoCurrent = this->codeEditorForm->memo->GetCurrent();
		memoLength = this->codeEditorForm->memo->GetLength();

		if (memoCurrent < memoLength - 1) {
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

	return memory;
}


Memory * MemoryDelete::SelectDelete(Memory * memory) {//선택영역 지우기
	Long lineCurrent;
	Long lineLength;
	Long memoCurrent;
	Long i = 0;
	Glyph *previous;
	Glyph *letter;
	CPoint start;
	CPoint end;
	CPoint temp;

	//선택영역을 구한다.
	start.SetPoint(memory->startX, memory->startY);
	end.SetPoint(memory->endX, memory->endY);

	if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
		temp = end;
		end = start;
		start = temp;

	}

	memoCurrent = this->codeEditorForm->memo->Move(end.y);
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	if (end.x != 0) {
		this->codeEditorForm->current->Move(end.x);
	}

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
			memoCurrent = this->codeEditorForm->memo->Move(end.y);
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			this->codeEditorForm->current->Move(end.x);
		}
	}

	this->codeEditorForm->select->Reset();

	return memory;
}

MemoryDelete & MemoryDelete::operator=(const MemoryDelete & source) {
	this->codeEditorForm = source.codeEditorForm;

	return *this;
}
