#include "ContentsEdit.h"
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "Glyph.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "Status.h"

ContentsEdit::ContentsEdit(){
	this->codeEditorForm = 0;
	this->firstLine = 0;
	this->lastLine = 0;
	this->firstContents = 0;
	this->lastContents = 0;
	this->singleCount = 0;
	this->doubleCount = 0;
	this->interval = 0;
}

ContentsEdit::ContentsEdit(CodeEditorForm* codeEditorForm){
	this->codeEditorForm = codeEditorForm;
	this->firstLine = 0;
	this->lastLine = 0;
	this->firstContents = 0;
	this->lastContents = 0;
	this->singleCount = 0;
	this->doubleCount = 0;
	this->interval = 0;
}

ContentsEdit::ContentsEdit(const ContentsEdit& source){
	this->codeEditorForm = source.codeEditorForm;
	this->firstLine = source.firstLine;
	this->lastLine = source.lastLine;
	this->firstContents = source.firstContents;
	this->lastContents = source.lastContents;
	this->singleCount = source.singleCount;
	this->doubleCount = source.doubleCount;
	this->interval = source.interval;
}

ContentsEdit::~ContentsEdit(){
}

Long ContentsEdit::FirstLineNumber(Long pointY, Long height){
	this->firstLine = 0;

	while (pointY < 0) {
		if (pointY + height < 0) {
			this->firstLine++;
		}
		pointY += height;
	}

	return this->firstLine;
}

Long ContentsEdit::LastLineNumber(Long height, Long clientBottom, Long memoLength){
	Long i = 0;
	BOOL state = TRUE;
	this->lastLine = 0;

	while (i * height < clientBottom && i < memoLength && state == TRUE) {
		if ((i + 0) * height < clientBottom) {
			this->lastLine++;
			i++;
		}
		else {
			this->lastLine++;
			state = FALSE;
		}
	}

	return this->lastLine;
}

Long ContentsEdit::FirstContentNumber(Long nPos, string contents){
	Long firstContentNumber = 0;
	Long fontWidth;
	char content[3] = { 0, };
	Glyph* letter = NULL;
	BOOL state = FALSE;
	BOOL stop = FALSE;
	this ->firstContents = 0;
	this->singleCount = 0;
	this->doubleCount = 0;
	this->interval = 0;

		while (nPos < 0 && stop == FALSE) {
			if (this->firstContents < (Long)contents.length()) {
				content[0] = LOBYTE(LOWORD(contents[this->firstContents]));

				if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) {
					letter = new SingleByteLetter(content[0]);
					state = FALSE;
				}
				else {
					content[1] = LOBYTE(LOWORD(contents[this->firstContents + 1]));
					letter = new DoubleByteLetter(content);
					this->firstContents++;
					state = TRUE;
				}

				fontWidth = this->codeEditorForm->fontMatrix->GetWidth(letter);

				if (nPos + fontWidth <= 0) {
					if (state == FALSE) {
						firstContentNumber++;
						this->singleCount++;
					}
					else {
						firstContentNumber += 2;
						this->doubleCount++;
					}
					this->interval += fontWidth;
					nPos += fontWidth;
				}
				else {
					stop = TRUE;
				}
			}
			else {
				stop = TRUE;
			}

			this->firstContents++;
		}

	return firstContentNumber;
}

Long ContentsEdit::LastContentsNumber(Glyph *line, Long clientRight){
	Glyph* letter;
	Long width = 0;
	char content[3] = { 0, };
	string contents;
	Long j = 0;

	contents = line->GetContents();
	this->lastContents = this->firstContents;

	while (this->lastContents < (Long)contents.length() && width < clientRight) {
		content[0] = LOBYTE(LOWORD(contents[lastContents]));

		if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) {
			letter = new SingleByteLetter(content[0]);
		}
		else {
			content[1] = LOBYTE(LOWORD(content[lastContents + 1])); // 한글의 사이즈인 2BYTE만큼이 필요하므로 다음번째 유니코드를 한번 더 추출
			letter = new DoubleByteLetter(content);
			this->lastContents++; //다음문자를 읽어야하므로 i증가
		}
		width += this->codeEditorForm->fontMatrix->GetWidth(letter);
		this->lastContents++;
	}

	if (this->lastContents < (Long)contents.length()) {
		while (j < this->doubleCount) {
			this->lastContents -= 2;
			j++;
		}
		j = 0;
		while (j < this->singleCount) {
			this->lastContents--;
			j++;
		}
	}

	return lastContents;
}

ContentsEdit& ContentsEdit::operator=(const ContentsEdit& source){
	this->codeEditorForm = source.codeEditorForm;
	this->firstLine = source.firstLine;
	this->lastLine = source.lastLine;
	this->firstContents = source.firstContents;
	this->lastContents = source.lastContents;
	this->singleCount = source.singleCount;
	this->doubleCount = source.doubleCount;
	this->interval = source.interval;

	return *this;
}
