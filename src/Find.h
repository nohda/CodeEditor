//Find.h

#ifndef _FIND_H
#define _FIND_H
#include <afxwin.h>
#include <string>

using namespace std;

class CFindReplaceDialog;
class CodeEditorForm;
class Find {

public:
	Find();
	Find(CodeEditorForm *codeEditorForm);
	Find(const Find& source);
	~Find();
	void Create(BOOL find);
	void Delete();
	void FindUp(string findcontents, BOOL match);
	BOOL FindDown(string findContents, BOOL match, BOOL allCorrect = FALSE);
	BOOL Correct(string findContents, string correctcontents, BOOL match, BOOL allCorrect = FALSE);
	void AllCorrect(string contents, string correctContents, BOOL match);
	string GetFindStr()const;
	string GetCorrectStr()const;
	BOOL GetSearchDown()const;
	BOOL GetMatchCase()const;
	Find& operator=(const Find& source);

private:
	CodeEditorForm *codeEditorForm;
	CFindReplaceDialog *findDialog;
	string findStr;
	string correctStr;
	BOOL searchDown;
	BOOL matchCase;
	BOOL sw;
};

inline string Find::GetFindStr()const {
	return this->findStr;
}
inline string Find::GetCorrectStr()const {
	return this->correctStr;
}
inline BOOL Find::GetSearchDown()const {
	return this->searchDown;
}
inline BOOL Find::GetMatchCase()const {
	return this->matchCase;
}

#endif //_FIND_H