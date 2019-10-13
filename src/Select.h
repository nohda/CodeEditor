//Select.h
#ifndef _SELECT_H
#define _SELECT_H

#include <afxwin.h>

typedef signed long int Long;

class CodeEditorForm;
class CPoint;
class Select {
public:
	Select();
	Select(CodeEditorForm *codeEditorForm);
	Select(const Select& source);
	~Select();
	void StartArea(CPoint point);
	void EndArea(CPoint point);
	void WordArea(CPoint dblClkStart, CPoint dblClkEnd);
	void Reset();
	void Draw(CDC *memDC, CPoint point);//선택하는 연산
	CPoint GetStartPoint()const;
	CPoint GetEndPoint()const;
	Select & operator=(const Select & source);

private:
	CodeEditorForm *codeEditorForm;
	CPoint start;
	CPoint end;
};

inline CPoint Select::GetStartPoint()const {
	return this->start;
}
inline CPoint Select::GetEndPoint()const {
	return this->end;
}
#endif //_SELECT_H