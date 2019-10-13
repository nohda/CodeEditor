/*
���ϸ� : File.cpp
�ۼ����� : 2019�� 04�� 02��
�ۼ��� : �迵��
��� : ���� Ŭ���� (������)
���� :20190403 OpenDialog ��� ����
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
�Լ���: File
���: ����Ʈ ������
���� : 20190404 fileName ����
*/
File::File() {
	this->pathName = "";
	this->fileName = "";
}

/*
�Լ���: File
���: �Ű����� ������
*/
File::File(CodeEditorForm * codeEditorForm,string pathName, string fileName) {
	this->codeEditorForm = codeEditorForm;
	this->pathName = pathName;
	this->fileName = fileName;
}

/*
�Լ���: File
���: ���� ������
*/
File::File(const File& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->pathName = source.pathName;
	this->fileName = source.fileName;
}

/*
�Լ���: ~File
���: �Ҹ���
*/
File::~File() {
}

/*
�Լ���: Save
���: �����ϴ�
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
�Լ���: Load
���: �ҷ�����
*/
string File::Load(string pathName) {
	fstream fs;
	string text = "";
	Long lineLength = 0;
	Long i = 0;
	char line[256];
	fs.open(pathName, ios::in);

	if (fs.is_open()) { //������ ���������� ������

		while (fs.getline(line, 256)) { //������ ����.
			lineLength++;
		}

		fs.clear(); //�ʱ�ȭ
		fs.seekg(0); //������ �̵�

		while (fs.getline(line, 256)) { //ù�ٺ��� �ٽ� �д´�.
			text += (line);

			if (i < lineLength - 1) { //���������� �ƴҶ� ���๮�� ���δ�.
				text += '\n';
				i++;
			}
		}
	
	}
	text += '\0'; //�ι��ڸ� ���δ�.
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
		content[0] = LOBYTE(LOWORD(text[i])); //�����ڵ�� 1BYTE�̹Ƿ� LOBYTE���

		if (content[0] != '\r') {

			if (content[0] != '\n' && content[0] != '\0') {

				if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) { //���� �����ڵ��Ͻ�
					letter = new SingleByteLetter(content[0]);
				}
				else { // �ѱ� �����ڵ��Ͻ�

					content[1] = LOBYTE(LOWORD(text[i + 1])); // �ѱ��� �������� 2BYTE��ŭ�� �ʿ��ϹǷ� ������° �����ڵ带 �ѹ� �� ����
					letter = new DoubleByteLetter(content);
					i++; //�������ڸ� �о���ϹǷ� i����
				}
				line->Add(letter);
			}
			else {

				if (content[0] != '\0') { // ���������ڴ� �ι����̰� ������ ���̹Ƿ� ������ �߰����� �ʾƾ� �Ѵ�.
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
�Լ���: OpenDialog
���: Load, Save�� ���������� FileName, PathName�� �����´�
���� : Load, Save ���� 20190404 cFileDialog 3��° �Ű����� ����
*/
bool File::OpenDialog(bool isOpen) {
	char szFilter[] = "�ؽ�Ʈ ����(*.txt)|*.txt|��� ����||";
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
�Լ���: operator=
���: ġȯ ������
*/
File& File::operator=(const File& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->pathName = source.pathName;
	this->fileName = source.fileName;

	return *this;
}