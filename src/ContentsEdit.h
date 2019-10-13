#pragma once

#ifndef _CONTENTSEDIT_H
#define _CONTENTSEDIT_H
#include <string>
using namespace std;

typedef signed long int Long;

class CodeEditorForm;
class Glyph;
class ContentsEdit {
public:
	ContentsEdit();
	ContentsEdit(CodeEditorForm* codeEditorForm);
	ContentsEdit(const ContentsEdit& source);
	~ContentsEdit();
	Long FirstLineNumber(Long pointY, Long height);
	Long LastLineNumber(Long height, Long clientBottom, Long memoLength);
	Long FirstContentNumber(Long nPos, string contents);
	Long LastContentsNumber(Glyph* line, Long clientRight);
	ContentsEdit& operator=(const ContentsEdit& source);
	Long GetFirstLineNumber()const;
	Long GetLastLineNumber()const;
	Long GetInterval()const;

private:
	CodeEditorForm* codeEditorForm;
	Long firstLine;
	Long lastLine;
	Long firstContents;
	Long lastContents;
	Long singleCount;
	Long doubleCount;
	Long interval;
};

inline Long ContentsEdit::GetFirstLineNumber()const {
	return this->firstLine;
}
inline Long ContentsEdit::GetLastLineNumber()const {
	return this->lastLine;
}
inline Long ContentsEdit::GetInterval()const {
	return this->interval;
}
#endif //_CONTENTSEDIT_H