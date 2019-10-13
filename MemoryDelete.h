//MemoryDelete.h
#ifndef _DELETEMEMORY_H
#define _DELETEMEMORY_H

typedef signed long int Long;

class CodeEditorForm;
class Memory;
class MemoryDelete {
public:
	MemoryDelete();
	MemoryDelete(CodeEditorForm *codeEditorForm);
	MemoryDelete(const MemoryDelete& source);
	~MemoryDelete();
	//Memory* Insert(Memory *temp);
	Memory* UndoDelete(Memory *temp);
	Memory* RedoBack(Memory *temp);
	Memory* RedoDelete(Memory *temp);
	Memory* SelectDelete(Memory *temp);
	MemoryDelete & operator=(const MemoryDelete & source);

private:
	CodeEditorForm *codeEditorForm;
	
};
#endif //_DELETEMEMORY_H
