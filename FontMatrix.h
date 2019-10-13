/*
파일명 : FontMatrix.h
작성일자 : 2019년 03월 29일
작성자 : 김영재
기능 : 폰트의 너비와 높이를 구한다.
수정 :
*/

#pragma once
#ifndef _FONTMATRIX_H
#define _FONTMATRIX_H

#include <afxwin.h>
#pragma warning (disable:4996)

typedef signed long int Long;

class Glyph;
class FontMatrix {
public:
	FontMatrix(CDC *dc);
	FontMatrix(const FontMatrix& source);
	~FontMatrix();
	Long GetSingleByteWidth(Long code);
	Long GetDoubleByteWidth();
	Long GetWidth(Glyph *letter);
	FontMatrix& operator=(const FontMatrix& source);
	Long GetHeight() const;
private:
	Long widths[129];
	Long height;
};

inline Long FontMatrix::GetHeight() const {
	return this->height;
}

#endif //_FONTMATRIX_H