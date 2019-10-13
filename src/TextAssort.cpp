#include "TextAssort.h"

TextAssort::TextAssort(){
	this->number = 0;
	this->text = "";
	this->start = 0;
	this->end = 0;
}

TextAssort::TextAssort(Long number, string text,Long start, Long end) {
	this->number = number;
	this->text = text;
	this->start = start;
	this->end = end;
}

TextAssort::TextAssort(const TextAssort & source){
	this->number = source.number;
	this->text = source.text;
	this->start = source.start;
	this->end = source.end;
}

TextAssort::~TextAssort(){
}

Long TextAssort::Assort(string text){
	int i = 0;
	int stringLast = 0;

	this->text.append(text);//글자 이어 붙임

	string one[] = {"public","protected","private","class","while","while ","for","for ","if","if ","else","else ","return","new","delete","void","char","int","bool"
					,"sizeof","true","false","double","short","switch","default","break","continue","dynamic_cast","case","struct"
					,"virtual" ,"const" ,"friend" ,"catch" ,"const_cast" ,"inline" ,"long" ,"namespace" ,"operator" ,"signed" ,"sizeof" 
					,"static" ,"template" ,"this" ,"typedef" ,"unsigned" ,"using"};
	string two[] = {"CString","TCHAR","LRESULT","BYTE","CWnd","DWORD","CFrameWnd","CDC",
					"string","BOOL","CPoint","UINT" ,"WPARAM" ,"LPARAM" ,"CScrollBar","LPCTSTR" };
	string three[] = {"''","<>"};
	string five[] = { "TRUE","FALSE","NULL","afx_msg","TextOut"}; 

	while (i < sizeof(one) / sizeof(string) && this->number ==0) {
		if (((this->text.compare(one[i])) == 0 )&& this->text.length() == one[i].length()) {
			this->number = 1;
		}
		i++;
	}
	i = 0;
	while (i < sizeof(two) / sizeof(string) && this->number == 0) {
		if ((this->text.compare(two[i])) == 0 && this->text.length() == two[i].length()) {
			this->number = 2;
		}
		i++;
	}
	if (this->text.length() > 1) {//주황색
		stringLast = this->text.length();
		if (this->text.at(0) == '\"' && this->text.at(stringLast-1) == '\"') {
			this->number = 3;
		}
		i = 0;
		while (i < sizeof(three) / sizeof(string)) {
			if (this->text.at(0) == three[i].at(0) && this->text.at(stringLast - 1) == three[i].at(1)) {
				this->number = 3;
			}
			i++;
		}
	}
	if (this->text.length() > 1) {//초록색 주석
		if (this->text.at(0) =='/' && this->text.at(1)=='/' ) {
			this->number = 4;
		}
	}
	i = 0;
	while (i < sizeof(five) / sizeof(string)) {
		if (((this->text.compare(five[i])) == 0) && this->text.length() == five[i].length()) {
			this->number = 5;
		}
		i++;
	}
	return this->number;
}

CString TextAssort::TextColor(CDC * memDC){
	CString CText = "";

	if (this->text != "" && this->number != 0) {
		if (this->number == 1) {//파란색
			memDC->SetTextColor(RGB(77, 106, 255));
		}
		else if (this->number == 2) {//하늘색
			memDC->SetTextColor(RGB(40, 173, 173));
		}
		else if (this->number == 3) {//주황색
			memDC->SetTextColor(RGB(255, 153, 51));
		}
		else if (this->number == 4) {//초록색
			memDC->SetTextColor(RGB(30, 179, 0));
		}
		else if (this->number == 5) {//보라색
			memDC->SetTextColor(RGB(148, 48, 173));
		}
	}
	CText = CString(this->text.c_str());

	return CText;
}

void TextAssort::Reset(){
	this->number = 0;
	this->text = "";
	//if () {

	//}
}
TextAssort & TextAssort::operator=(const TextAssort & source){
	this->number = source.number;
	this->text = source.text;
	this->start = source.start;
	this->end = source.end;

	return *this;
}
