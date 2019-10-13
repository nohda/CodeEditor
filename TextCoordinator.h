#pragma once
//TextCoordinator.h
#ifndef _TEXTCOODINATOR_H
#define _TEXTCOODINATOR_H

#include <afxwin.h>
#pragma warning (disable:4996)

typedef signed long int Long;

class CPoint;
class CodeEditorForm;
class TextCoordinator {
public:
	TextCoordinator(CodeEditorForm *codeEditorForm);
	TextCoordinator(const TextCoordinator& source);
	~TextCoordinator();
	CPoint TextPos(CPoint nPos);
	CPoint NumberPos(CPoint nPos);
	TextCoordinator& operator=(const TextCoordinator& source);
	CPoint GetPoint()const;

private:
	CodeEditorForm *codeEditorForm;
	CPoint point;
};

inline CPoint TextCoordinator::GetPoint() const {
	return this->point;
}

#endif //_TEXTCOODINATOR_H