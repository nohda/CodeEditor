#pragma once

#ifndef _FONT_H
#define _FONT_H

#include <afxwin.h>

class CodeEditorForm;
class CDC;
class Font {
public:

	Font();
	Font(CodeEditorForm* codeEditorForm);
	Font(const Font& source);
	~Font();
	void Make();
	Font& operator=(const Font& source);
	CFont *GetFont()const;
	CFont* GetOldFont()const;
	CDC* GetDC()const;

private:
	LOGFONT logFont;
	CFont *font;
	CFont *oldFont;
	CodeEditorForm *codeEditorForm;
	CDC* dc;
};

inline CFont* Font::GetFont()const {
	return this->font;
}
inline CFont* Font::GetOldFont()const {
	return this->oldFont;
}
inline CDC* Font::GetDC()const {
	return this->dc;
}

#endif //_FONT_H