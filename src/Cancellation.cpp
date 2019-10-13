#include "Cancellation.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Memo.h"
#include "Line.h"
#include "MemoryInsert.h"
#include "MemoryDelete.h"
#include "Memory.h"
#include "Select.h"

Cancellation::Cancellation(CodeEditorForm * codeEditorForm, Long capacity) :memories() {
	this->codeEditorForm = codeEditorForm;
	this->memoryInsert = this->codeEditorForm->memoryInsert;
	this->memoryDelete = this->codeEditorForm->memoryDelete;
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
	this->composing = -1;
}

Cancellation::Cancellation(const Cancellation & source) :memories(source.memories) {
	this->codeEditorForm = source.codeEditorForm; 
	this->memoryInsert = source.memoryInsert;
	this->memoryDelete = source.memoryDelete;
	Long i = 0;
	while (i < this->GetLength()) {
		Memory *memory = this->memories.GetAt(i);
		this->memories.Modify(i, memory);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
	this->composing = source.composing;
}

Cancellation::~Cancellation() {
	Long i = 0;
	while (i < this->GetLength()) {
		delete this->memories[i];
		i++;
	}
}

Long Cancellation::UndoPush(Long action) {
	Long i = 0;
	Memory *memory;
	bool selectText = false;
	Long index = 0;

	while (i < this->GetLength()) {
		memory = this->memories.GetAt(i);
		if (memory->status == false && memory->action != 0) {
			this->current = i;
		}
		else {
			if (this->memories[i] != 0) {
				delete this->memories[i];
			}

			this->memories.Delete(i);
			this->capacity--;
			this->length--;
			this->current--;
		}
		i++;
	}
	memory = new Memory(this->codeEditorForm);
	selectText = memory->SelectText();//선택영역이 있는지 확인

	if (selectText == true) {
		memory->CopyString(action);
	}
	else {
		memory->CopyText(action);
	}
	if (memory->status == true) {
		if (memory != 0) {
			delete memory;
		}
	}
	else {
		if (this->capacity > this->length) {
			this->current = memories.Store(this->length, memory);

		}
		else {
			this->current = memories.AppendFromRear(memory);
			this->capacity++;
		}
		this->length++;
	}
	return this->current;
}

Long Cancellation::UndoPush(Long action, string contents) {
	Long i = 0;
	Memory *memory;
	bool selectText = false;
	Long index = 0;

	while (i < this->GetLength()) {
		memory = this->memories.GetAt(i);
		if (memory->status == false && memory->action != 0) {
			this->current = i;
		}
		else {
			if (this->memories[i] != 0) {
				delete this->memories[i];
			}

			this->memories.Delete(i);
			this->capacity--;
			this->length--;
			this->current--;
		}
		i++;
	}

	memory = new Memory(this->codeEditorForm);

	selectText = memory->SelectText();//선택영역이 있는지 확인

	if (selectText == true) {//선택영역이 있으면
		memory->CopyStrings(action, contents);
	}
	else {
		memory->CopyString(action, contents);
	}

	if (memory->status == true) {
		if (memory != 0) {
			delete memory;
		}
	}
	else {
		if (this->capacity > this->length) {
			this->current = memories.Store(this->length, memory);

		}
		else {
			this->current = memories.AppendFromRear(memory);
			this->capacity++;
		}
		this->length++;
	}
	return this->current;
}

Long Cancellation::UndoPush(Long action, string contents, Long lineCurrent){
	Long i = 0;
	Memory *memory;
	bool selectText = false;
	Long index = 0;

	while (i < this->GetLength()) {
		memory = this->memories.GetAt(i);
		if (memory->status == false && memory->action != 0) {
			this->current = i;
		}
		else {
			if (this->memories[i] != 0) {
				delete this->memories[i];
			}

			this->memories.Delete(i);
			this->capacity--;
			this->length--;
			this->current--;
		}
		i++;
	}

	memory = new Memory(this->codeEditorForm);
	//입력된 글자들로 기억하기
	memory->CopyCurrent(action, contents, lineCurrent);

	if (memory->status == true) {
		if (memory != 0) {
			delete memory;
		}
	}
	else {
		if (this->capacity > this->length) {
			this->current = memories.Store(this->length, memory);

		}
		else {
			this->current = memories.AppendFromRear(memory);
			this->capacity++;
		}
		this->length++;
	}
	return this->current;
}

void Cancellation::UndoPop() {
	Long i = 0;
	Memory *temp = NULL;
	bool out = false;
	bool selectText = false;

	i = this->GetLength();
	while (i > 0 && out != true) {
		temp = this->GetAt(i - 1);
		if (temp->status == false) {
			out = true;
		}
		i--;
	}
	if (out == true) {
		if (temp->status == false) {
			selectText = temp->SelectMemory();//선택영역이 있는지 확인
			if (temp->action == 1) {
				if (selectText == true) {
					this->memoryDelete->SelectDelete(temp);
				}
				else {
					this->memoryDelete->UndoDelete(temp);
				}
			}
			else if(temp->action == 2) {
				if (selectText == true) {
						this->memoryInsert->SelectInsert(temp);
				}
				else {
					this->memoryInsert->RedoDelete(temp);
				}
			}
			else if (temp->action == 3) {
				if (selectText == true) {
					this->memoryInsert->SelectInsert(temp);
				}
				else {
					this->memoryInsert->RedoBack(temp);
				}
			}
		temp->status = true;
		}
		this->codeEditorForm->select->Reset();
	}
}

void Cancellation::RedoPop() {
	Long i = 0;
	Memory *temp = NULL;
	bool out = false;
	bool selectText = false;

	while (i < this->GetLength() && out != true) {
		temp = this->GetAt(i);
		if (temp->status == true) {
			this->current = i;
			out = true;
		}
		i++;
	}
	if (out == true) {
		selectText = temp->SelectMemory();//선택영역이 있는지 확인

		if (temp->status == true) {
			if (temp->action == 1) {
				if (selectText == true) {
					this->memoryInsert->SelectInsert(temp);
				}
				else {
					this->memoryInsert->RedoBack(temp);
				}

			}
			else if (temp->action == 2) {
				if (selectText == true) {
					this->memoryDelete->SelectDelete(temp);
				}
				else {
					this->memoryDelete->RedoDelete(temp);
				}

			}
			else if (temp->action == 3) {
				if (selectText == true) {
					this->memoryDelete->SelectDelete(temp);
				}
				else {
					this->memoryDelete->RedoBack(temp);
				}
			}
		temp->status = false;
		}
	}
}

Cancellation & Cancellation::operator=(const Cancellation & source) {
	this->codeEditorForm = source.codeEditorForm;
	this->memoryInsert = source.memoryInsert;
	this->memoryDelete = source.memoryDelete;
	Long i = 0;
	while (i < this->GetLength()) {
		if (this->memories[i] != 0) {
			delete this->memories[i];
		}
		this->capacity--;
		this->length--;
		this->current--;
		i++;
	}
	i = 0;
	while (i < source.length) {
		this->memories = source.memories;
		Memory *memory = this->memories.GetAt(i);
		this->memories.Modify(i, memory);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
	this->composing = source.composing;

	return *this;
}

Memory* Cancellation::GetAt(Long index) {
	return this->memories.GetAt(index);
}

Memory* Cancellation::operator[](Long index) {
	return this->memories[index];
}

