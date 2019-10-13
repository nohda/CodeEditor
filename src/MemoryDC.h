#pragma once

#ifndef _MEMORYDC_H
#define _MEMORYDC_H

#include <string>
using namespace std;
typedef signed long int Long;

class CodeEditorForm;
class CPaintDC;
class CDC;
class CBitmap;
class MemoryDC {
public:
	MemoryDC();
	MemoryDC(CodeEditorForm* codeEditorForm);
	MemoryDC(const MemoryDC& source);
	~MemoryDC();
	void Make(CPaintDC *dc);
	void Draw(CPaintDC *dc);
	void Resize();
	void SetOfDelete();
	MemoryDC& operator=(const MemoryDC& source);
	CBitmap* GetBuffer()const;
	CDC *GetMemDC()const;

private:
	CBitmap* buffer;
	CBitmap* oldBuffer;
	CDC *memDC;
	CodeEditorForm* codeEditorForm;
};

inline CBitmap* MemoryDC::GetBuffer()const {
	return this->buffer;
}
inline CDC* MemoryDC::GetMemDC()const {
	return this->memDC;
}
#endif //_MEMORYDC_H