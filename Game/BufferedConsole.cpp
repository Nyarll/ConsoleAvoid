#include "BufferedConsole.h"
#include "ConsoleCharacter.h"

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
	textAttributes = screenBufferInfo.wAttributes;

	buffer = std::vector<CHAR_INFO>(bufferSize.X * bufferSize.Y, default_pixel);
}

// ��ʂ�����������
void ScreenContext::Clear()
{
	// �I�t�X�N���[�����f�t�H���g�s�N�Z���ŏ�����
	int length = static_cast<int>(bufferSize.X * bufferSize.Y);
	for (int i = 0; i < length; i++)
		buffer[i] = default_pixel;
}

int ScreenContext::DrawCharacter(COORD dwWriteCoord, Color textColor, WORD wCharacter)
{
	int width = ConsoleCharacter::GetCharacterWidthCJK(wCharacter);
	if (bufferCoord.X <= dwWriteCoord.X && dwWriteCoord.X + width <= bufferSize.X)
	{
		auto pixel = &buffer[dwWriteCoord.X + dwWriteCoord.Y * bufferSize.X];
		pixel[0].Char.UnicodeChar = wCharacter;
		for (int j = 0; j < width; j++)
		{
			auto& npixel = pixel[j];
			npixel.Attributes = Attributes{ npixel.Attributes }.text(textColor);
			if (j != 0)
				npixel.Char.UnicodeChar = L' ';
		}
	}
	return width;
}

void ScreenContext::DrawString(COORD dwWriteCoord, Color textColor, LPCWSTR lpCharacter, DWORD nLength)
{
	int length = static_cast<int>(nLength);
	for (int i = 0, n = 0; length < 0 || i < length; i++)
	{
		auto& chr = lpCharacter[i];
		if (chr == L'\n' || chr == L'\0')
			break;
		int xCoord = n + dwWriteCoord.X;
		int width = DrawCharacter(COORD{ static_cast<SHORT>(xCoord), dwWriteCoord.Y }, textColor, chr);
		n += width;
	}
}

void ScreenContext::DrawStringLines(COORD dwWriteCoord, Color textColor, LPCWSTR lpCharacter)
{
	// �E����荶��Ȃ�
	if (dwWriteCoord.X < bufferSize.X && dwWriteCoord.Y < bufferSize.Y)
	{
		// Y���[�v
		SHORT iy;
		for (iy = dwWriteCoord.Y; iy < bufferSize.Y; iy++)
		{
			// ���s�܂ł̋���
			const WCHAR* enter = wcschr(lpCharacter, '\n');

			// ���Ə�ɃI�[�o�[�������Č����Ȃ��Ȃ��Ă��Ȃ����`�F�b�N
			if (iy >= bufferCoord.Y)
				DrawString(COORD{ dwWriteCoord.X, iy }, textColor, lpCharacter);

			// ���s���Ȃ���΂����ŏI��
			if (enter == nullptr)
				return;
			// ���s������Ή��s�̂��Ƃ܂ŃJ�[�\�������炵�đ��s
			else
				lpCharacter = enter + 1;
		}
	}
}

void ScreenContext::Flush()
{
	WriteConsoleOutput(hOutput, &buffer[0], bufferSize, bufferCoord, &screenRegion);
}
