//Scroll.h
#ifndef _SCROLL_H
#define _SCROLL_H

#include "Observer.h"
#include <afxwin.h>

typedef signed long int Long;

class CodeEditorForm;
class Scroll :public Observer  {
public:
	Scroll(CodeEditorForm *codeEditorForm,Long longestWidth=0, Long longestHeight=0, Long xPos=0, Long yPos=0, Long memoCurrent=0);
	Scroll(const Scroll& source);
	~Scroll();
	void MakeScroll();
	void ShowScroll();
	void UpdateHScroll(Long cx);
	void UpdateVScroll(Long cy);
	void MoveHScroll();
	void MoveVScroll();
	void Update();
	Scroll& operator=(const Scroll& source);
	CScrollBar* GetScrollBar()const;
	Long GetXPos()const;
	Long GetYPos()const;
	Long GetLongestHeight()const;

private:
	CodeEditorForm *codeEditorForm;
	CScrollBar *cscrollBar;
	Long longestWidth;
	Long longestHeight;
	Long xPos;
	Long yPos;
	Long memoCurrent;
};
inline CScrollBar* Scroll::GetScrollBar()const {
	return this->cscrollBar;
}
inline Long Scroll::GetXPos()const {
	return this->xPos;
}
inline Long Scroll::GetYPos()const {
	return this->yPos;
}
inline Long Scroll::GetLongestHeight()const {
	return this->longestHeight;
}
#endif _SCROLL_H