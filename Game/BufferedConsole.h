#pragma once

#include "Color.h"

class ScreenContext
{
public:
	HANDLE hOutput;					// �o�̓f�o�C�X�̃n���h��
	CHAR_INFO default_pixel;		// �f�t�H���g�s�N�Z��
	COORD bufferCoord;				// �o�b�t�@�[�̃I�t�Z�b�g
	COORD bufferSize;				// �o�b�t�@�T�C�Y
	SMALL_RECT screenRegion;		// �`��̈�
	COORD screenSize;				// ��ʃT�C�Y

private:
	WORD textAttributes;			// �����̑O�i�F�����Ɣw�i�F����
	std::vector<CHAR_INFO> buffer;	// �o�b�t�@

public:
	ScreenContext(const HANDLE& hOut, CHAR_INFO default_pixel = { ' ', Attributes{ Colors::Black, Colors::White } });

public:
	void Clear();
	int DrawCharacter(COORD dwWriteCoord, WORD wAttribute, WORD wCharacter);
	void DrawString(COORD dwWriteCoord, WORD wAttribute, LPCWSTR lpCharacter, DWORD nLength = -1);
	void DrawStringLines(COORD dwWriteCoord, WORD wAttribute, LPCWSTR lpCharacter);
	void Flush();
};
