//KeyActionFactory.cpp

/*
파일명 : KeyActionFactory.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 키액션팩토리
수정 :
*/

#include "KeyActionFactory.h"
#include "LeftKeyAction.h"
#include "RightKeyAction.h"
#include "CtrlLeftKeyAction.h"
#include "CtrlRightKeyAction.h"
#include "HomeKeyAction.h"
#include "EndKeyAction.h"
#include "CtrlHomeKeyAction.h"
#include "CtrlEndKeyAction.h"
#include "UpKeyAction.h"
#include "DownKeyAction.h"
#include "BackspaceKeyAction.h"
#include "DeleteKeyAction.h"
#include "EnterKeyAction.h"
#include "PageUpKeyAction.h"
#include "PageDownKeyAction.h"
#include "CtrlAKeyAction.h"
#include "CtrlCKeyAction.h"
#include "CtrlVKeyAction.h"
#include "CtrlXKeyAction.h"
#include "CtrlFKeyAction.h"
#include "CtrlZKeyAction.h"
#include "CtrlYKeyAction.h"
#include "CtrlHKeyAction.h"
#include "CtrlGKeyAction.h"
#include "CtrlSKeyAction.h"
#include "CodeEditorForm.h"
#include "F3KeyAction.h"
#include "F5KeyAction.h"
#include "F1KeyAction.h"
#include "Select.h"
#include "Glyph.h"

KeyActionFactory::KeyActionFactory(CodeEditorForm* codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

KeyActionFactory::~KeyActionFactory() {
}

KeyAction * KeyActionFactory::Make(UINT nChar) {
	KeyAction *keyAction = NULL;

	if ((GetKeyState(VK_CONTROL) < 0) && nChar == VK_LEFT) {
		keyAction = new CtrlLeftKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == VK_RIGHT) {
		keyAction = new CtrlRightKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == VK_HOME) {
		keyAction = new CtrlHomeKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == VK_END) {
		keyAction = new CtrlEndKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar =='A') {
		keyAction = new CtrlAKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == 'C') {
		keyAction = new CtrlCKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == 'V') {
		keyAction = new CtrlVKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == 'X') {
		keyAction = new CtrlXKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == 'F') {
		keyAction = new CtrlFKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == 'Z') {
		keyAction = new CtrlZKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == 'Y') {
		keyAction = new CtrlYKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == 'H') {
		keyAction = new CtrlHKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == 'G') {
		keyAction = new CtrlGKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == 'S') {
		keyAction = new CtrlSKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if (nChar == VK_F1) {
		keyAction = new F1KeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_F3) {
		keyAction = new F3KeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_F5) {
		keyAction = new F5KeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if (nChar == VK_LEFT) { 
		keyAction = new LeftKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_RIGHT) {
		keyAction = new RightKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_UP) {
		keyAction = new UpKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_DOWN) {
		keyAction = new DownKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_HOME) {
		keyAction = new HomeKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_END){
		keyAction = new EndKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_PRIOR) {
		keyAction = new PageUpKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_NEXT) {
		keyAction = new PageDownKeyAction(this->codeEditorForm);
	}
	//백스페이스키가 눌렸거나 문자키이고 선택영역이 있다면
	else if (nChar == VK_BACK || (nChar >= 32 || nChar == VK_TAB) && this->codeEditorForm->select->GetStartPoint() != this->codeEditorForm->select->GetEndPoint()) {
		keyAction = new BackspaceKeyAction(this->codeEditorForm);
		//this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if (nChar == VK_DELETE) {
		keyAction = new DeleteKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	else if (nChar == VK_RETURN) {
		keyAction = new EnterKeyAction(this->codeEditorForm);
		this->codeEditorForm->nFlagUndo = TRUE;
	}
	return keyAction;
}