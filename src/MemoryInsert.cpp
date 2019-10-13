#include "MemoryInsert.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Line.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "Memory.h"
#include "select.h"

MemoryInsert::MemoryInsert() {
	this->codeEditorForm = 0;
	this->letterByte = 0;
}

MemoryInsert::MemoryInsert(CodeEditorForm * codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
	this->letterByte = 0;
}

MemoryInsert::MemoryInsert(const MemoryInsert & source) {
	this->codeEditorForm = source.codeEditorForm;
	this->letterByte = source.letterByte;
}

MemoryInsert::~MemoryInsert() {
}

Glyph * MemoryInsert::selectLetter(string text){
	Glyph *letter=NULL;
	Long textSize = 0;
	Long i = 0;
	char content[3] = { 0, };
	this->letterByte = 0;

	content[0] = LOBYTE(LOWORD(text[i])); //유니코드는 1BYTE이므로 LOBYTE사용
	if (content[0] != '\r') {
		if (content[0] != '\n' && content[0] != '\0') {
			if (Long(content[0]) >= 32 && Long(content[0]) <= 126 && text != "        ") { //문자 유니코드일시
				letter = new SingleByteLetter(content[0]);
				this->letterByte = 1;
			}
			else if (text == "        ") {
				//text = (char)content;
				letter = new SingleByteLetter('\t');
				this->letterByte = 1;
			}
			else { // 한글 유니코드일시
				content[1] = LOBYTE(LOWORD(text[i + 1])); // 한글의 사이즈인 2BYTE만큼이 필요하므로 다음번째 유니코드를 한번 더 추출
				letter = new DoubleByteLetter(content);
				this->letterByte = 2;
			}
		}
	}
	return letter;
}

Memory * MemoryInsert::SelectInsert(Memory * memory){
	Glyph *line;
	Glyph *letter;
	Long textSize = 0;
	Long i = 0;
	Long j = 0;
	Long lineCurrent;
	Long lineLength;
	Long memoCurrent;
	Long memoLength;
	Long previousCurrent;
	Glyph *previous;
	string contents;
	string newText;
	char content[3] = { 0, };

	contents = memory->text;
	textSize = contents.length();

	memoCurrent=this->codeEditorForm->memo->Move(memory->startY);
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	lineCurrent = this->codeEditorForm->current->Move(memory->startX);

	while (i < textSize) {
		content[0] = LOBYTE(LOWORD(contents[i]));
		if (content[0] != '\r') {
			if (content[0] != '\n' && content[0] != '\0') {
				if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) { 
					letter = new SingleByteLetter(content[0]);
				}
				else { 
					content[1] = LOBYTE(LOWORD(contents[i + 1])); 
					letter = new DoubleByteLetter(content);
					i++; //다음문자를 읽어야하므로 i증가
				}
				this->codeEditorForm->current->Add(letter, lineCurrent);
				lineCurrent++;
			}
		}
		else {//다른줄에서 끼워넣기
				memoCurrent = this->codeEditorForm->memo->GetCurrent();
				memoLength = this->codeEditorForm->memo->GetLength();
				lineCurrent = this->codeEditorForm->current->GetCurrent();
				lineLength = this->codeEditorForm->current->GetLength();
				previous = this->codeEditorForm->current;
				//현재줄이 끝줄이라면
				line = new Line;

				if (memoCurrent == memoLength - 1) {
					if (memoCurrent == memory->endY) {
						memoCurrent = this->codeEditorForm->memo->Move(memory->endY);
						this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
						this->codeEditorForm->memo->Add(line, memory->endY);
					}
					else {
						this->codeEditorForm->memo->Add(line); //줄을 붙인다.
					}
				}
				else {
					if (memoCurrent == memory->endY) {
						this->codeEditorForm->memo->Add(line, memoCurrent + 1);
					}
					else {
						memoCurrent = this->codeEditorForm->memo->Move(memory->endY);
						this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
						this->codeEditorForm->memo->Add(line, memory->endY);
					}
				}
				memoCurrent = this->codeEditorForm->memo->GetCurrent();
				this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
				previousCurrent = this->codeEditorForm->current->GetCurrent();

				////현재 위치의 뒤에 글자가 있다면 
				if (lineCurrent != lineLength) {
					if (lineCurrent != -1 && lineCurrent != lineLength) { //끼워쓰기 로직
						j = lineCurrent;

						while (j < lineLength) { //새줄에 글자 복사 로직
							letter = previous->GetAt(j);
							this->codeEditorForm->current->Add(letter->Clone());
							j++;
						}
						j = lineLength;

						while (j > lineCurrent) { //기존 줄 글자 삭제 로직
							previous->Remove(lineCurrent);
							j--;
						}
					}
					else {
						j = 0;

						while (j < lineLength) { //새줄에 글자 복사 로직
							letter = previous->GetAt(j);
						this->codeEditorForm->current->Add(letter->Clone());
						j++;
					}
					j = lineLength;
					while (j > 0) { //기존 줄 글자 삭제 로직
						previous->Remove(j - 1);
						j--;
					}
				}
			}
			lineCurrent=this->codeEditorForm->current->Move(0);
		}
		i++;
	}
	this->codeEditorForm->select->Reset();

	return memory;
}

Memory * MemoryInsert::RedoBack(Memory * memory){
	Glyph *letter;
	Long i = 0;
	Long lineCurrent;
	Long memoCurrent;

	letter = this->selectLetter(memory->text);
	memoCurrent = this->codeEditorForm->memo->Move(memory->startY);
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	this->codeEditorForm->current->Move(memory->startX-1);
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	this->codeEditorForm->current->Add(letter, lineCurrent);

	return memory;
}

Memory * MemoryInsert::RedoDelete(Memory * memory){
	Glyph *letter;
	Long i = 0;
	Long lineCurrent;
	Long memoCurrent;

	letter = this->selectLetter(memory->text);
	memoCurrent = this->codeEditorForm->memo->Move(memory->startY);
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	this->codeEditorForm->current->Move(memory->startX);
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	this->codeEditorForm->current->Add(letter, lineCurrent);

	return memory;
}

MemoryInsert & MemoryInsert::operator=(const MemoryInsert & source){
	this->codeEditorForm = source.codeEditorForm;
	this->letterByte = source.letterByte;

	return *this;
}

