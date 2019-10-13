#include "CtrlCKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"

CtrlCKeyAction::CtrlCKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm) {
}

CtrlCKeyAction::~CtrlCKeyAction() {
}

void CtrlCKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CPoint start;
	CPoint end;
	CPoint temp;
	CPoint currentPoint;
	Glyph *line;
	Glyph *letter;
	string contents="";
	Long memoCurrent;
	Long memoLength;
	Long lineCurrent;
	Long lineLength;
	Long i = 0;
	HANDLE h_data;
	const char * content;
	char *p_data;

	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();
	currentPoint = end;

	if (start != end) {
		if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
			temp = end;
			end = start;
			start = temp;
		}
		this->codeEditorForm->memo->Move(end.y);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(end.y);
		this->codeEditorForm->current->Move(end.x);

		this->codeEditorForm->OpenClipboard();
		EmptyClipboard();

		memoCurrent = start.y;
		memoLength = end.y;

		while (memoCurrent <= memoLength) {
			line = this->codeEditorForm->memo->GetAt(memoCurrent);

			if (i == 0 && memoCurrent == memoLength) {
				lineCurrent = start.x;
				lineLength = end.x;
			}
			else if (i == 0 && memoCurrent != memoLength) {
				lineCurrent = start.x;
				lineLength = line->GetLength();
			}
			else if (memoCurrent == memoLength) {
				lineCurrent = 0;
				lineLength = end.x;
			}
			else {
				lineCurrent = 0;
				lineLength = line->GetLength();
			}

			while (lineCurrent < lineLength) {
				letter = line->GetAt(lineCurrent);
				contents += letter->GetContents();
				lineCurrent++;
			}
			if (memoCurrent != memoLength) {
				contents += "\r\n";
			}
			i++;
			memoCurrent++;
		}
		
		content = contents.c_str();
		int string_length = strlen(content) + 1;
		h_data = ::GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, string_length);
		p_data = (char *)::GlobalLock(h_data);
		if (NULL != p_data) {
			memcpy(p_data, content, string_length);
			::GlobalUnlock(h_data);
		}
		::SetClipboardData(CF_TEXT, h_data);
		::CloseClipboard();

		this->codeEditorForm->memo->Move(currentPoint.y);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(currentPoint.y);
		this->codeEditorForm->current->Move(currentPoint.x);
	}
}
