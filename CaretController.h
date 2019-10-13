/*���ϸ� : CaretController.h
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : ���α�
��� : ĳ������ Ŭ�������� �����ϴ� Ŭ����
���� : 20190410 GetXPosCaret �����߰�
*/

#pragma once

#ifndef _CARETCONTROLLER_H
#define _CARETCONTROLLER_H
#include "Observer.h"

typedef signed long int Long;

class CodeEditorForm;
//class CaretCoordinator;
class Caret;
class Glyph;
class CaretController : public Observer {
public:
	CaretController();
	CaretController(CodeEditorForm *codeEditorForm, Glyph *line, Long row);
	CaretController(const CaretController& source);
	~CaretController();
	void MakeCaret();
	void MoveCaret();
	void ShowCaret(bool isShow);
	void DeleteCaret();
	void Update();
	CaretController& operator=(const CaretController& source);
	Glyph* GetLine() const;
	Long GetRow() const;

private:
	CodeEditorForm *codeEditorForm;
	//CaretCoordinator *caretCoordinator;
	Caret *caret;
	Glyph *line;
	Long row;
};

inline Glyph* CaretController::GetLine() const {
	return this->line;
}
inline Long CaretController::GetRow() const {
	return this->row;
}


#endif //_CARETCONTROLLER_H