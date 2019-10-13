#include "GlyphFactory.h"
#include "Memo.h"
#include "Line.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"

GlyphFactory::GlyphFactory(CodeEditorForm *codeEditorForm) {

	this->codeEditorForm = codeEditorForm;
}

GlyphFactory::GlyphFactory(const GlyphFactory& source) {

	this->codeEditorForm = source.codeEditorForm;
}

GlyphFactory::~GlyphFactory() {
	  
}	  
	  
Glyph* GlyphFactory::Make() {
	Glyph *glyph = NULL;

	glyph = new Memo;

	return glyph;
}

Glyph* GlyphFactory::Make(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph *glyph = NULL;

	if (nChar >= 32 || nChar == VK_TAB) {
		glyph = new SingleByteLetter(nChar);
	}

	/*else if (nChar == VK_RETURN) {
		glyph = new Line;
	}*/

	return glyph;
}

Glyph* GlyphFactory::Make(WPARAM wParam, LPARAM lParam) {
	Glyph *glyph = NULL;

	TCHAR str[2];

	if (lParam & GCS_COMPSTR) {
		str[0] = HIBYTE(LOWORD(wParam));
		str[1] = LOBYTE(LOWORD(wParam));

 	}

	if (IsDBCSLeadByte((BYTE)(wParam >> 8)) == TRUE) {
		str[0] = HIBYTE(LOWORD(wParam));
		str[1] = LOBYTE(LOWORD(wParam));
	}

	glyph = new DoubleByteLetter(str);

	return glyph;
}
