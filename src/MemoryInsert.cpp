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

	content[0] = LOBYTE(LOWORD(text[i])); //�����ڵ�� 1BYTE�̹Ƿ� LOBYTE���
	if (content[0] != '\r') {
		if (content[0] != '\n' && content[0] != '\0') {
			if (Long(content[0]) >= 32 && Long(content[0]) <= 126 && text != "        ") { //���� �����ڵ��Ͻ�
				letter = new SingleByteLetter(content[0]);
				this->letterByte = 1;
			}
			else if (text == "        ") {
				//text = (char)content;
				letter = new SingleByteLetter('\t');
				this->letterByte = 1;
			}
			else { // �ѱ� �����ڵ��Ͻ�
				content[1] = LOBYTE(LOWORD(text[i + 1])); // �ѱ��� �������� 2BYTE��ŭ�� �ʿ��ϹǷ� ������° �����ڵ带 �ѹ� �� ����
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
					i++; //�������ڸ� �о���ϹǷ� i����
				}
				this->codeEditorForm->current->Add(letter, lineCurrent);
				lineCurrent++;
			}
		}
		else {//�ٸ��ٿ��� �����ֱ�
				memoCurrent = this->codeEditorForm->memo->GetCurrent();
				memoLength = this->codeEditorForm->memo->GetLength();
				lineCurrent = this->codeEditorForm->current->GetCurrent();
				lineLength = this->codeEditorForm->current->GetLength();
				previous = this->codeEditorForm->current;
				//�������� �����̶��
				line = new Line;

				if (memoCurrent == memoLength - 1) {
					if (memoCurrent == memory->endY) {
						memoCurrent = this->codeEditorForm->memo->Move(memory->endY);
						this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
						this->codeEditorForm->memo->Add(line, memory->endY);
					}
					else {
						this->codeEditorForm->memo->Add(line); //���� ���δ�.
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

				////���� ��ġ�� �ڿ� ���ڰ� �ִٸ� 
				if (lineCurrent != lineLength) {
					if (lineCurrent != -1 && lineCurrent != lineLength) { //�������� ����
						j = lineCurrent;

						while (j < lineLength) { //���ٿ� ���� ���� ����
							letter = previous->GetAt(j);
							this->codeEditorForm->current->Add(letter->Clone());
							j++;
						}
						j = lineLength;

						while (j > lineCurrent) { //���� �� ���� ���� ����
							previous->Remove(lineCurrent);
							j--;
						}
					}
					else {
						j = 0;

						while (j < lineLength) { //���ٿ� ���� ���� ����
							letter = previous->GetAt(j);
						this->codeEditorForm->current->Add(letter->Clone());
						j++;
					}
					j = lineLength;
					while (j > 0) { //���� �� ���� ���� ����
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

