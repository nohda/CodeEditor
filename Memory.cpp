#include "Memory.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Memo.h"
#include "Line.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "Select.h"

Memory::Memory(CodeEditorForm *codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
	this-> action = 0;
	this->startX = 0;
	this->startY = 0;
	this-> endX = 0;
	this->endY = 0;
	this->text = "";
	this->status = false;
}

Memory::Memory(CodeEditorForm *codeEditorForm, Long action, Long startX, Long startY, Long endX, Long endY, string text, bool status) {
	this->codeEditorForm = codeEditorForm;
	this->action = action;
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	this->text = text;
	this-> status = status;
}

Memory::Memory(const Memory & source) {
	this->codeEditorForm = source.codeEditorForm;
	this->action = action;
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	this->text = text;
	this->status = status;
}

Memory::~Memory() {
}

bool Memory::SelectText() {//선택영역이 있는지 여부 확인
	CPoint start;
	CPoint end;
	bool selectText = false;

	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();

	if (start != end) {
		selectText = true;
	}
	return selectText;
}

bool Memory::SelectMemory(){//메모리에서 선택영역이 있는지 확인
	CPoint start;
	CPoint end;
	bool selectText = false;

	start.SetPoint(this->startX, this->startY);
	end.SetPoint(this->endX, this->endY);

	if (start != end) {
		selectText = true;
	}
	return selectText;
}

void Memory::CopyString(Long actionNumber) {
	
	CPoint start;
	CPoint end;
	CPoint temp;
	Glyph *line;
	Glyph *letter;
	string contents = "";
	Long memoCurrent;
	Long memoLength;
	Long lineCurrent;
	Long lineLength;
	Long i = 0;

	this->action = actionNumber;
	this->status = false;

	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();

	if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
		temp = end;
		end = start;
		start = temp;

		this->codeEditorForm->memo->Move(end.y);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(end.y);
		this->codeEditorForm->current->Move(end.x);
	}

		memoCurrent = start.y;
		memoLength = end.y;

		while (memoCurrent <= memoLength) {
			line = this->codeEditorForm->memo->GetAt(memoCurrent);

			if (i == 0 && memoCurrent == memoLength) {
				lineCurrent = start.x;
				lineLength = end.x;
			}
			else if (i == 0 && memoCurrent != memoLength) {
				lineCurrent = start.x;
				lineLength = line->GetLength();
			}
			else if (memoCurrent == memoLength) {
				lineCurrent = 0;
				lineLength = end.x;
			}
			else {
				lineCurrent = 0;
				lineLength = line->GetLength();
			}

			while (lineCurrent < lineLength) {
				letter = line->GetAt(lineCurrent);
				contents += letter->GetContents();
				lineCurrent++;
			}
			if (memoCurrent != memoLength) {
				contents += "\r\n";
			}
			i++;
			memoCurrent++;
		}

		this->text = contents;
		this->startX = start.x;
		this->startY = start.y;
		this->endX = end.x;
		this->endY = end.y;
}

void Memory::CopyText(Long actionNumber){
	Glyph *line;
	Glyph *letter;
	string contents = "";
	Long memoCurrent;
	Long memoLength;
	Long lineCurrent;
	Long lineLength;

	this->action = actionNumber;
	this->status = false;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	memoLength = this->codeEditorForm->memo->GetLength();
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();
	//enum { None, Insert, Delete, Backsapce };
	if (this->action == 1) {
		if (lineCurrent >= 1) {
			letter = this->codeEditorForm->current->GetAt(lineCurrent - 1);
			contents = letter->GetContents();
			this->startX = lineCurrent;
			this->startY = memoCurrent;
		}
		else if(lineCurrent < 0) {
			this->status = true;
		}
		else {			
			contents += "\r\n";
			this->startX = 0;
			this->startY = memoCurrent + 1;
		}
	}
	else if (this->action == 2) {
		if (lineLength == lineCurrent && memoLength != memoCurrent + 1) {
			contents += "\r\n";
			this->startX = lineLength;
			this->startY = memoCurrent;
		}
		else if (lineLength > lineCurrent) {
			letter = this->codeEditorForm->current->GetAt(lineCurrent);
			contents = letter->GetContents();
			this->startX = lineCurrent;
			this->startY = memoCurrent;
		}
		else {
			this->status = true;
		}
	}
	else if (this->action == 3) {//BackSpaceKey
		if (memoCurrent > 0 && lineCurrent < 1) {//맨 앞 칸
			contents += "\r\n";
			this->startY = memoCurrent-1;
			line = this->codeEditorForm->memo->GetAt(memoCurrent - 1);
			lineLength = line->GetLength();
			this->startX = lineLength;
		}
		else if (memoCurrent == 0 && lineCurrent < 1) {//맨 앞줄에서 맨 앞칸
			this->status = true;
		}
		else {//중간 칸
			letter = this->codeEditorForm->current->GetAt(lineCurrent-1);
			contents = letter->GetContents();
			this->startX = lineCurrent;
			this->startY = memoCurrent;
		}
	}
	this->endX = startX;
	this->endY = startY;

	this->text = contents;
}

void Memory::CopyString(Long actionNumber,string contents){
	char content[3] = { 0, };
	Long textSize = 0;
	Long i = 0;

	this->action = actionNumber;
	this->status = false;

	this->startX = this->codeEditorForm->current->GetCurrent();
	if (this->startX < 0) {
		this->startX = 0;
	}
	this->startY = this->codeEditorForm->memo->GetCurrent();
	this->endX = this->startX;
	this->endY = this->startY;
	
	textSize = contents.length();
	while (i < textSize) {
		content[0] = LOBYTE(LOWORD(contents[i])); //유니코드는 1BYTE이므로 LOBYTE사용
		if (content[0] != '\r') {
			if (content[0] != '\n' && content[0] != '\0') {

				if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) { //문자 유니코드일시
					this->endX++;
				}
				else {
					this->endX++;
					i++; //다음문자를 읽어야하므로 i증가
				}
			}
		}
		else {
			if (content[0] != '\0') {
				this->endY++;
				this->endX = 0;
			}
			}
		
		i++;
	}

	this->text = contents;
}

void Memory::CopyStrings(Long actionNumber, string contents){
	CPoint start;
	CPoint end;
	CPoint temp;
	char content[3] = { 0, };
	Long textSize = 0;
	Long i = 0;

	this->action = actionNumber;
	this->status = false;

	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();

	if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
		temp = end;
		end = start;
		start = temp;
	}
	this->codeEditorForm->select->Reset();
	this->startX = start.x;
	this->startY = start.y;
	this->endX = end.x;
	this->endY = end.y;
	this->text = contents;
}

void Memory::CopyCurrent(Long actionNumber, string contents, Long current){
	char content[3] = { 0, };
	Long textSize = 0;
	Long i = 0;

	this->action = actionNumber;
	this->status = false;

	this->startX = current;
	this->startY = this->codeEditorForm->memo->GetCurrent();
	this->endX = this->startX;
	this->endY = this->startY;

	textSize = contents.length();
	while (i < textSize) {
		content[0] = LOBYTE(LOWORD(contents[i])); //유니코드는 1BYTE이므로 LOBYTE사용
		if (content[0] != '\r') {
			if (content[0] != '\n' && content[0] != '\0') {

				if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) { //문자 유니코드일시
					this->endX++;
				}
				else {
					this->endX++;
					i++; //다음문자를 읽어야하므로 i증가
				}
			}
		}
		else {
			if (content[0] != '\0') {
				this->endY++;
				this->endX = 0;
			}
		}

		i++;
	}

	this->text = contents;
}

Memory & Memory::operator=(const Memory & source) {
	this->codeEditorForm = source.codeEditorForm;
	this->action = action;
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	this->text = text;
	this->status = status;

	return *this;
}
