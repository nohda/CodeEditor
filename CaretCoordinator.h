//CaretCoordinator.h
/*
���ϸ� : CaretCoordinator.h
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : �迵��
��� : ĳ���� ��ġ�� �����Ѵ�
���� : 20190410 GetXPos �����߰�
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