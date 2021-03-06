//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   CXFont.h
//!
//! @brief  コンソール・フォント
//!
//! @date   2018/07/29
//!
//! @author GF1 26 山口寛雅
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once
#include "CXLib.h"

namespace CXLib
{
	// フォントの種類
	typedef enum {
		CXFONT_DEFAULT,
		CXFONT_PONG
	} CXFontType;

	// フォント
	typedef struct {
		CXFontType type;
		float size;
	} CXFont;

	// フォントハンドルを作成する
	CXFont CreateFontToHandle(CXFontType Font, int Size);

	// 文字列描画関数
	void DrawString(Vector2 pos, LPCWSTR String, Color Color);

	// フォントハンドルを使用した文字列の描画幅(ワールド座標)を取得する
	float GetDrawStringWidthToHandle(LPCWSTR String, const CXFont* FontHandle);

	// フォントハンドルを使用して文字列を描画する
	void DrawStringToHandle(Vector2 pos, LPCWSTR String, Color Color, const CXFont* FontHandle);
}