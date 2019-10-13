/*
파일명 : File.cpp
작성일자 : 2019년 04월 02일
작성자 : 김영재
기능 : 파일 클래스 (저장기능)
수정 :20190403 OpenDialog 기능 구현
*/

//File.cpp

#include "File.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Memo.h"
#include "Line.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "Select.h"
#include <iostream>
#include <fstream>
#include <afxdlgs.h>


/*
함수명: File
기능: 디폴트 생성자
수정 : 20190404 fileName 수정
*/
File::File() {
	this->pathName = "";
	this->fileName = "";
}

/*
함수명: File
기능: 매개변수 생성자
*/
File::File(CodeEditorForm * codeEditorForm,string pathName, string fileName) {
	this->codeEditorForm = codeEditorForm;
	this->pathName = pathName;
	this->fileName = fileName;
}

/*
함수명: File
기능: 복사 생성자
*/
File::File(const File& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->pathName = source.pathName;
	this->fileName = source.fileName;
}

/*
함수명: ~File
기능: 소멸자
*/
File::~File() {
}

/*
함수명: Save
기능: 저장하다
*/
void File::Save(string contents, string pathName) {
	fstream fs;

	fs.open(pathName, ios::out);

	if (!fs.bad()) {
		fs << contents;
		fs.flush();
		fs.close();
	}
}

/*
함수명: Load
기능: 불러오다
*/
string File::Load(string pathName) {
	fstream fs;
	string text = "";
	Long lineLength = 0;
	Long i = 0;
	char line[256];
	fs.open(pathName, ios::in);

	if (fs.is_open()) { //파일이 정상적으로 열리면

		while (fs.getline(line, 256)) { //라인을 센다.
			lineLength++;
		}

		fs.clear(); //초기화
		fs.seekg(0); //포인터 이동

		while (fs.getline(line, 256)) { //첫줄부터 다시 읽는다.
			text += (line);

			if (i < lineLength - 1) { //마지막줄이 아닐때 개행문자 붙인다.
				text += '\n';
				i++;
			}
		}
	
	}
	text += '\0'; //널문자를 붙인다.
	fs.close();

	return text;
}

Glyph* File::TakeInMemo(string text){
	Glyph *memo;
	Glyph *line;
	Glyph *letter;
	char content[3] = { 0, };
	Long textSize = 0;
	Long i = 0;

	memo = new Memo;
	line = new Line;
	memo->Add(line);

	textSize = text.length();

	while (i < textSize) {
		content[0] = LOBYTE(LOWORD(text[i])); //유니코드는 1BYTE이므로 LOBYTE사용

		if (content[0] != '\r') {

			if (content[0] != '\n' && content[0] != '\0') {

				if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) { //문자 유니코드일시
					letter = new SingleByteLetter(content[0]);
				}
				else { // 한글 유니코드일시

					content[1] = LOBYTE(LOWORD(text[i + 1])); // 한글의 사이즈인 2BYTE만큼이 필요하므로 다음번째 유니코드를 한번 더 추출
					letter = new DoubleByteLetter(content);
					i++; //다음문자를 읽어야하므로 i증가
				}
				line->Add(letter);
			}
			else {

				if (content[0] != '\0') { // 마지막문자는 널문자이고 문자의 끝이므로 라인을 추가하지 않아야 한다.
					line = new Line;
					memo->Add(line);
				}
			}
		}
		i++;
	}
	return memo;
}

/*
함수명: OpenDialog
기능: Load, Save를 선택적으로 FileName, PathName을 가져온다
수정 : Load, Save 통합 20190404 cFileDialog 3번째 매개변수 수정
*/
bool File::OpenDialog(bool isOpen) {
	char szFilter[] = "텍스트 문서(*.txt)|*.txt|모든 파일||";
	CString fileName;
	bool state = TRUE;

	if (isOpen == TRUE) {
		fileName = "";
	}
	else {
		if (this->fileName == "") {
			fileName = "*.txt";
		}
		else {
			fileName = this->fileName.c_str();
		}
	}

	CFileDialog cFileDialog(isOpen, ".txt", fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL, 0, NULL);
	if (cFileDialog.DoModal() == IDOK) {
		this->fileName = cFileDialog.GetFileName();
		this->pathName = cFileDialog.GetPathName();
	}
	else {
		state = false;
	}
	return state;
}

/*
함수명: operator=
기능: 치환 연산자
*/
File& File::operator=(const File& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->pathName = source.pathName;
	this->fileName = source.fileName;

	return *this;
}