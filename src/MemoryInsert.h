//MemoryInsert.h
#ifndef _MEMORYINSERT_H
#define _MEMORYINSERT_H

#include <string>
#include "CodeEditorForm.h"

class CodeEditorForm;
class Glyph;
class Memory;
class MemoryInsert {
public:
	MemoryInsert();
	MemoryInsert(CodeEditorForm *codeEditorForm);
	MemoryInsert(const MemoryInsert& source);
	~MemoryInsert();
	Glyph* selectLetter(string text);
	Memory* SelectInsert(Memory *temp);
	Memory* RedoBack(Memory *temp);
	Memory* RedoDelete(Memory *temp);
	MemoryInsert & operator=(const MemoryInsert & source);

private:
	CodeEditorForm *codeEditorForm;
	Long letterByte;//영문1,한글2

};
#endif //_MEMORYINSERT_H
