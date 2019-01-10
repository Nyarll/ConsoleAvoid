//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   BufferedConsole.h
//!
//! @brief  �\�t�g�E�F�A�E�R���\�[���o�b�t�@
//!
//! @date   2018/07/29
//!
//! @author GF1 26 �R������
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ================================================

#include "Console.h"

// �^�̒�` ================================================================

// �R���\�[�����W�̗v�f
typedef short SHORT;

// �\���̂̒�` ============================================================

// ����(�F)
class Attributes
{
public:
	ConsoleColor foreground;
	ConsoleColor background;

public:
	// ����(�F)���쐬
	Attributes(ConsoleColor foreground, ConsoleColor background);
	Attributes(const WORD& word);
	operator WORD() const;
};

class ScreenInfo
{
public:
	HANDLE hOutput;					// �o�̓f�o�C�X�̃n���h��
	CHAR_INFO default_pixel;		// �f�t�H���g�s�N�Z��
	COORD bufferCoord;				// �o�b�t�@�[�̃I�t�Z�b�g
	COORD bufferSize;				// �o�b�t�@�T�C�Y
	SMALL_RECT screenRegion;		// �`��̈�
	COORD  screenSize;				// ��ʃT�C�Y

private:
	WORD   textAttributes;			// �����̑O�i�F�����Ɣw�i�F����
	std::vector<CHAR_INFO> buffer;	// �o�b�t�@

public:
	ScreenInfo(const HANDLE& hOut, CHAR_INFO default_pixel = { ' ', Attributes{ ConsoleColor::COLOR_WHITE, ConsoleColor::COLOR_BLACK } });

public:
	void Clear();
	void Draw(COORD dwWriteCoord, WORD wAttribute, LPCWSTR lpCharacter, DWORD nLength);
	//void DrawA(COORD dwWriteCoord, WORD wAttribute, LPCSTR lpCharacter, DWORD nLength);
	void Flush();
};

// �O���[�o���ϐ��錾 ======================================================

// �f�t�H���g����(�F)
extern const Attributes DEFAULT_ATTR;

// �֐��̐錾 ==============================================================


// �\�t�g�E�F�A�E�R���\�[���o�b�t�@������������
void BufferedConsole_Initialize(void);

// ��ʂ�����������
void Clear(void);

// �w����W�Ɏw�蕶�����w�葮��(�F)�ŕ\��
void Print(COORD coord, Attributes attributes, const WCHAR* format);

// �X�N���[���𔽉f
void BufferedConsole_Flush(void);
