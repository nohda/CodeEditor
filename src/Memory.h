#pragma once
//Memory.h

#ifndef _MEMORY_H
#define _MEMORY_H

#include "Cancellation.h"
#include <stdio.h>
#include <string>
using namespace std;

class CodeEditorForm;
class MemoryDelete;
class Memory /*:public Cancellation*/ {
public:
	Memory(CodeEditorForm *codeEditorForm);
	Memory(CodeEditorForm *codeEditorForm, Long action ,Long startX,Long startY,Long endX,Long endY,string text,bool status);
	Memory(const Memory& source);
	~Memory();
	bool SelectText();//push
	bool SelectMemory();//�迭���� �������� ������ ������ ��,������� ��������
	void CopyString(Long actionNumber);
	void CopyText(Long actionNumber);
	void CopyString(Long actionNumber,string contents);
	void CopyStrings(Long actionNumber, string contents);
	void CopyCurrent(Long actionNumber, string contents,Long current);
	Memory& operator=(const Memory& source);

public:
	CodeEditorForm *codeEditorForm;
	MemoryDelete *MemoryDelete;
	Long action ;
	Long startX ;
	Long startY ;
	Long endX ;
	Long endY ;
	string text ;
	bool status ;
};
//enum { None, Insert, Delete, Backsapce };
#endif //_MEMORY_H
