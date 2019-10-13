//Cancellation.h
#ifndef _CANCELLATION_H
#define _CANCELLATION_H

#include "Array.h"
#include "Memory.h"
#include <string>

using namespace std;
typedef signed long int Long;

class CodeEditorForm;
class MemoryInsert;
class MemoryDelete;
class Memory;
class Cancellation {
public:
	Cancellation(CodeEditorForm *codeEditorForm, Long capacity = 256);
	Cancellation(const Cancellation& source);
	~Cancellation();
	Long UndoPush(Long action);
	Long UndoPush(Long action,string contents);
	Long UndoPush(Long action, string contents,Long Current);
	void UndoPop();
	void RedoPop();
	Cancellation& operator=(const Cancellation& source);
	Memory* GetAt(Long index);
	Memory* operator[](Long index);
	Long GetCapacity()const;
	Long GetLength()const;
	Long GetCurrent()const;

public:
	CodeEditorForm *codeEditorForm;
	MemoryInsert *memoryInsert;
	MemoryDelete *memoryDelete;
private:
	Array<Memory*>memories;
	Long capacity;
	Long length;
	Long current;
	Long composing;

};
inline Long Cancellation::GetCapacity()const {
	return this->capacity;
}
inline Long Cancellation::GetLength()const {
	return this->length;
}
inline Long Cancellation::GetCurrent()const {
	return this->current;
}
#endif //_CANCELLATION_H
