#pragma once
//GlyphFactory.h
#ifndef _GLHPHFACTORY_H
#define _GLHPHFACTORY_H
#include <afxwin.h>

class CodeEditorForm;
class Glyph;
class GlyphFactory {
public:
	GlyphFactory(CodeEditorForm *codeEditorForm = 0);
	GlyphFactory(const GlyphFactory& source);
	~GlyphFactory();
	Glyph* Make();
	Glyph* Make(UINT nChar, UINT nRepCnt, UINT nFlags);
	Glyph* Make(WPARAM wParam, LPARAM lParam);
private:
	CodeEditorForm *codeEditorForm;
};

#endif //_GLHPHFACTORY_H