#pragma once
//TextEdit.h
#ifndef _TEXTEDIT_H
#define _TEXTEDIT_H

#include "CodeEditorForm.h"
#include <string>

typedef signed long int Long;

class CPoint;
class TextIndent;
class TextAssort;
class TextEdit {
public:
	TextEdit(CodeEditorForm *codeEditorForm);
	TextEdit(CodeEditorForm *codeEditorForm,Long start, Long textNumber, string tapText);
	TextEdit(const TextEdit& source);
	~TextEdit();
	void isHighlight(CDC *memDC,Glyph *line, CPoint nPos,Long memoCurrent);
	void AddParenthese(UINT nChar);
	void AddTap();
	TextEdit& operator=(const TextEdit& source);
	string GetTapText()const;


private:
	CodeEditorForm *codeEditorForm;
	TextAssort *textAssort;
	TextIndent *textIndent;
	Long start;
	Long textNumber;
	string tapText;
};
inline string TextEdit::GetTapText() const {
	return this->tapText;
}

#endif //_TEXTEDIT_H