//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   CXFont.h
//!
//! @brief  �R���\�[���E�t�H���g
//!
//! @date   2018/07/29
//!
//! @author GF1 26 �R������
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ================================================

#include "CXLib.h"

// �񋓌^�̒�` ============================================================

// �t�H���g�̎��
typedef enum {
	CXFONT_DEFAULT,
	CXFONT_PONG
} CXFontType;

// �\���̂̒�` ============================================================

// �t�H���g
typedef struct {
	CXFontType type;
	float size;
} CXFont;

// �֐��̐錾 ==============================================================

// �t�H���g�n���h�����쐬����
CXFont CreateFontToHandle(CXFontType Font, int Size);

// ������`��֐�
void DrawString(float x, float y, const WCHAR* String, Attributes Color = DEFAULT_ATTR);

// �t�H���g�n���h�����g�p����������̕`�敝(���[���h���W)���擾����
float GetDrawStringWidthToHandle(const WCHAR* String, const CXFont* FontHandle);

// �t�H���g�n���h�����g�p���ĕ������`�悷��
void DrawStringToHandle(float x, float y, const WCHAR* String, Attributes Color, const CXFont* FontHandle, const WCHAR* Str = L" ");
