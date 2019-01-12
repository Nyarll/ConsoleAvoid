#pragma once
#include "Color.h"

class ScreenContext
{
private:
	HANDLE hOutput;				  	// �o�̓f�o�C�X�̃n���h��
	CHAR_INFO default_pixel;	  	// �f�t�H���g�s�N�Z��
	COORD bufferCoord;			  	// �o�b�t�@�[�̃I�t�Z�b�g
	COORD bufferSize;			  	// �o�b�t�@�T�C�Y
	SMALL_RECT screenRegion;	  	// �`��̈�
	COORD screenSize;			  	// ��ʃT�C�Y
	std::vector<CHAR_INFO> buffer;	// �o�b�t�@
	CHAR_INFO* bufferPtr;		  	// �o�b�t�@
	WORD attributes;			  	// ����

public:
	ScreenContext(const HANDLE& hOut, CHAR_INFO default_pixel = { ' ', Attributes{ Colors::Black, Colors::White } });

public:
	void Clear();
	void Flush();

public:
	inline CHAR_INFO& Pixel(COORD dwWriteCoord) { return bufferPtr[dwWriteCoord.X + dwWriteCoord.Y * bufferSize.X]; }
	inline CHAR_INFO& DefaultPixel() { return default_pixel; };

public:
	constexpr inline const HANDLE& GetHandle() const { return hOutput; }
	constexpr inline const COORD& GetBoundsMin() const { return bufferCoord; };
	constexpr inline const COORD& GetBoundsMax() const { return bufferSize; };
	constexpr inline const COORD& GetSize() const { return bufferSize; };
	constexpr inline const WORD& GetAttributes() const { return attributes; };
};
