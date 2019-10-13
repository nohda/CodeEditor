/*
파일명 : File.h
작성일자 : 2019년 04월 02일
작성자 : 김영재
기능 : 파일 클래스 (저장기능)
수정 :
*/

#pragma once

#ifndef _FILE_H
#define _FILE_H

#include <string>

using namespace std;
typedef signed long int Long;

class CodeEditorForm;
class Glyph;
class File {
public:
	File();
	File(CodeEditorForm *codeEditorForm,string pathName, string fileName);
	File(const File& source);
	~File();
	void Save(string constents, string pathName);
	string Load(string pathName);
	Glyph* TakeInMemo(string text);
	bool OpenDialog(bool isOpen);
	File& operator=(const File& source);
	string GetPathName() const;
	string GetFileName() const;

private:
	CodeEditorForm *codeEditorForm;
	string pathName;
	string fileName;
};

inline string File::GetPathName() const {
	return this->pathName;
}

inline string File::GetFileName() const {
	return this->fileName;
}

#endif //_FILE_H