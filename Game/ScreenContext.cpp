#include "ScreenContext.h"

ScreenContext::ScreenContext(const HANDLE& hOut, CHAR_INFO default_pixel)
	: hOutput(hOut)
	, bufferCoord(COORD{ 0, 0 })
	, default_pixel(default_pixel)
{
	// �X�N���[���o�b�t�@�Ɋւ�����
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

	// �X�N���[���o�b�t�@�Ɋւ�����̎擾
	GetConsoleScreenBufferInfo(hOutput, &screenBufferInfo);

	// �R���\�[����ʂɊւ�����̐ݒ�
	hOutput = hOutput;
	bufferSize = screenBufferInfo.dwSize;
	screenRegion = { bufferCoord.X, bufferCoord.Y, bufferSize.X - 1, bufferSize.Y - 1 };
	screenSize = { screenBufferInfo.srWindow.Right + 1, screenBufferInfo.srWindow.Bottom + 1 };
	attributes = screenBufferInfo.wAttributes;

	buffer = std::vector<CHAR_INFO>(bufferSize.X * bufferSize.Y, default_pixel);
	bufferPtr = &buffer[0];
}

// ��ʂ�����������
void ScreenContext::Clear()
{
	// �I�t�X�N���[�����f�t�H���g�s�N�Z���ŏ�����
	int length = static_cast<int>(bufferSize.X * bufferSize.Y);
	std::fill_n(buffer.begin(), length, default_pixel);
}

void ScreenContext::Flush()
{
	WriteConsoleOutput(hOutput, bufferPtr, bufferSize, bufferCoord, &screenRegion);
}
