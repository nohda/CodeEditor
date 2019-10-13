/*파일명 : CaretController.h
작성일자 : 2019년 03월 29일
작성자 : 진민국
기능 : 캐럿관련 클래스들을 관리하는 클래스
수정 : 20190410 GetXPosCaret 연산추가
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