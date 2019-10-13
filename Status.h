#ifndef STATUS_H
#define STATUS_H
#include "resource.h"
#include "Observer.h"
#include <afxwin.h>

typedef signed long int Long;

class CodeEditorForm;
class CStatusBar;
class Status:public Observer {
public:
	Status();
	Status(CodeEditorForm *codeEditorForm);
	~Status();
	void Create();
	void Delete();
	void Update();
	CStatusBar* GetStatusBar()const;

private:
	CodeEditorForm* codeEditorForm;
	CStatusBar* status;
	Long current;
	Long memoCurrent;
};
inline CStatusBar* Status::GetStatusBar()const {
	return this->status;
}
#endif //_STATUS_H