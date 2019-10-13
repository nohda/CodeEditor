//CaretCoordinator.h
/*
파일명 : CaretCoordinator.h
작성일자 : 2019년 03월 29일
작성자 : 김영재
기능 : 캐럿의 위치를 지정한다
수정 : 20190410 GetXPos 연산추가
*/

#ifndef _CARETCOORDINATOR_H
#define _CARETCOORDINATOR_H

typedef signed long int Long;

class CodeEditorForm;
class Glyph;
class FontMatrix;
class CaretCoordinator {

public:
	CaretCoordinator();
	CaretCoordinator(CodeEditorForm *codeEditorForm);
	CaretCoordinator(const CaretCoordinator& source);
	~CaretCoordinator();
	Long GetLineWidth(FontMatrix *fontMatrix, Glyph *line);
	Long GetLongestWidth(FontMatrix *fontMatrix, Glyph *memo);
	Long GetXPos(FontMatrix *fontMatrix, Glyph *line);
	Long GetYPos(FontMatrix *fontMatrix, Long row);
	Long GetSelectXPos(FontMatrix *fontMatrix, Glyph *line, Long current);
	CaretCoordinator& operator=(const CaretCoordinator& source);
	Long GetX() const;
	Long GetY() const;
	Long GetAveWidth() const;

private:
	CodeEditorForm *codeEditorForm;
	Long x;
	Long y;
	Long aveWidth;
};

inline Long CaretCoordinator::GetX()const {
	return this->x;
}

inline Long CaretCoordinator::GetY()const {
	return this->y;
}
inline Long CaretCoordinator::GetAveWidth()const {
	return this->aveWidth;
}

#endif //_CARETCOORDINATOR_H