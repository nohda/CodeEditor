#include "TextEdit.h"
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "Glyph.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "CaretCoordinator.h"
#include "TextAssort.h"
#include "TextIndent.h"
#include "Cancellation.h"

TextEdit::TextEdit(CodeEditorForm *codeEditorForm){
	this->codeEditorForm = codeEditorForm;
	this->textAssort = new TextAssort();
	this->textIndent = new TextIndent();
	this->start = 0;
	this->textNumber = 0;
	this->tapText = "";
}

TextEdit::TextEdit(CodeEditorForm *codeEditorForm,Long start, Long textNumber, string tapText){
	this->codeEditorForm = codeEditorForm;
	this->textAssort = new TextAssort();
	this->textIndent = new TextIndent();
	this->start = start;
	this->textNumber = textNumber;
	this->tapText = tapText;
}

TextEdit::TextEdit(const TextEdit & source){
	this->codeEditorForm = source.codeEditorForm;
	this->textAssort = source.textAssort;
	this->textIndent = source.textIndent;
	this->start = source.start;
	this->textNumber = source.textNumber;
	this->tapText = source.tapText;
}

TextEdit::~TextEdit(){
	delete this->textAssort;
	this->textAssort = NULL;
	delete this->textIndent;
	this->textIndent = NULL;
}

void TextEdit::isHighlight(CDC* memDC, Glyph* line, CPoint point, Long memoCurrent) {
	Long textCurrent;
	Long lineLength;
	Long height;
	Long number;
	Long colorPoint;
	Long xPos;
	Glyph* letter;
	char content[3] = { 0, };
	string contents;
	string texts = "";
	CString CText = "";

	height = this->codeEditorForm->fontMatrix->GetHeight();
	lineLength = line->GetLength();
	this->textNumber = 0;
	textCurrent = 0;
	this->start = textCurrent;

	while (textCurrent < lineLength) {
		if (lineLength > 0) {
			letter = line->GetAt(textCurrent);
			contents = letter->GetContents();
			texts += contents;
		}
		number = this->textAssort->GetNumber();
		if ((contents == " " || contents == "        " || contents == "{" || contents == "(" || contents == "=" || contents == ":") && number != 2 && number != 3 && number != 4) {
			if ((texts.at(0) != '\"' || texts.at(0) != '\'' || texts.at(0) != '<') && this->textNumber != 4) {
				texts = "";
				this->start = textCurrent + 1;
			}
		}
		number = this->textAssort->Assort(texts);
		CText = this->textAssort->TextColor(memDC);
		if (number == 4) {
			this->textNumber = number;
		}

		colorPoint = point.x;
		xPos = this->codeEditorForm->caretCoordinator->GetSelectXPos(this->codeEditorForm->fontMatrix, line, this->start);
		colorPoint += xPos;
		if (this->textAssort->GetText() != "" && this->textAssort->GetNumber() != 0) {
			memDC->TextOut(colorPoint - this->codeEditorForm->marginWidth, point.y + (memoCurrent * height), CText);
		}//130
		this->textAssort->Reset();
		textCurrent++;
	}
	this->textNumber = 0;
}

void TextEdit::AddParenthese(UINT nChar){
	Glyph *letter;
	char content = ' ';
	string text;

	this->textIndent->Parenthese(nChar);
	content=this->textIndent->GetContent();
	if (content != ' ') {
		letter= new SingleByteLetter(content);
		text = (char)content;
		this->codeEditorForm->current->Add(letter);
		this->codeEditorForm->cancellation->UndoPush(1);
		this->codeEditorForm->current->Previous();
		//if (content == '}') {
		//	//this->codeEditorForm->cancellation->UndoPush(1, "\r\n");
		//}
	}
}

void TextEdit::AddTap(){
	Glyph *line;
	Glyph *letter;
	Long memoCurrent;
	Long memoLength;
	Long i = 0;
	Long textSize;
	string text = "";
	char content = ' ';

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	memoLength = this->codeEditorForm->memo->GetLength();
	if (memoLength > 0 && memoCurrent >0) {
		line = this->codeEditorForm->memo->GetAt(memoCurrent - 1);
		text = line->GetContents();
		textSize = text.length();
		if (textSize >0 && text.at(0) != ' ') {
			this->tapText = "";
		}
		content = this->textIndent->lineAddTap(text);
		if (content != ' ') {
			text = (char)content;
			this->tapText.append(text);
			textSize = this->tapText.length();
			while (i < textSize) {
				letter = new SingleByteLetter(content);
				this->codeEditorForm->memo->Move(memoCurrent);
				line = this->codeEditorForm->memo->GetAt(memoCurrent);
				line->Add(letter);
				this->codeEditorForm->current = line;
				 this->codeEditorForm->cancellation->UndoPush(1);
				 this->codeEditorForm->current->Last();
				 if (i > 0) {
					 content = this->tapText.at(i);
					 letter = new SingleByteLetter(content);
					 this->codeEditorForm->memo->Move(memoCurrent + 1);
					 line = this->codeEditorForm->memo->GetAt(memoCurrent + 1);
					 line->Add(letter, 0);
					 this->codeEditorForm->current = line;
					 this->codeEditorForm->cancellation->UndoPush(1);
					 //this->codeEditorForm->current->Last();
				 }
				i++;
			}
			memoCurrent = this->codeEditorForm->memo->Move(memoCurrent);
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			this->codeEditorForm->current->Last();
		}
	}
}

TextEdit & TextEdit::operator=(const TextEdit & source){
	this->codeEditorForm = source.codeEditorForm;
	this->textAssort = source.textAssort;
	this->textIndent = source.textIndent;
	this->start = source.start;
	this->textNumber = source.textNumber;
	this->tapText = source.tapText;

	return *this;
}
