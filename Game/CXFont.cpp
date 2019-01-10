//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   CXFont.cpp
//!
//! @brief  �R���\�[���E�t�H���g
//!
//! @date   2018/07/29
//!
//! @author GF1 26 �R������
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================

#include "CXFont.h"
#include "CXLib.h"
#include "MathUtils.h"
#include <string.h>

// �񋓌^�̒�` ============================================================

// �X�v���C�g
typedef struct
{
	char name;
	int x;
	int y;
	int w;
	int h;
} Sprite;

// �萔�̒�` ==============================================================

#define TEXTURE_ATLAS_WIDTH		60		// �e�N�X�`���A�g���X�̕�
#define TEXTURE_ATLAS_HEIGHT	27		// �e�N�X�`���A�g���X�̍���
#define NUM_FONTS				27		// �t�H���g�̐�
#define FONT_SPAN_WIDTH			2.f		// �������m�̉��̋�
#define FONT_SPAN_HEIGHT		2.f		// �������m�̏c�̋�

// �O���[�o���ϐ���` ======================================================

// �e�N�X�`���A�g���X
static char* texture_atlas[TEXTURE_ATLAS_HEIGHT] = {
	"11   1111  1111  1  1  1111  11111 11111  11111 11111  11111",
	"11   1111  1111  1  1  1111  11111 11111  11111 11111  11111",
	" 1   1  1     1  1  1  1     1        11  1  11 1  11  11  1",
	" 1     11   111  1111  1111  11111    11  11111 11111  111 1",
	" 1    11      1  1111     1  11111    11  11111 11111  1 1 1",
	" 1   11       1     1     1  1  11    11  1  11    11  1  11",
	"111  1111  1111     1  1111  11111    11  11111    11  11111",
	"                                                            ",
	"11111                        11111                          ",
	"11111                        11111                          ",
	"1   1  1111  1111  1111      1     111  1111111  111        ",
	"11111  1  1  1  1  1  1      1 111   1  1  1  1  1 1        ",
	"11111  1  1  1  1  1  1      1 111 111  1  1  1  111        ",
	"1      1  1  1  1  1  1      1  11 1 1  1  1  1  1          ",
	"1      1111  1  1  1111      11111 111  1  1  1  111        ",
	"                      1                                     ",
	"                   1111                                     ",
	"                   1111                                     ",
	"                                                            ",
	"11111 1                1         11  11                     ",
	"11111 1                1         11 11              1       ",
	"  1   1111             1 11       111         1  1  1       ",
	"  1   1  1             111         11         1  1  1       ",
	"  1   1  1             11          1          1  1  1       ",
	"  1   1  1             1 1         1          1  1          ",
	"  1   1  1             1 11        1          1111  1       ",
	"                                                    1       "
};

// �t�H���g�E�X�v���C�g
static Sprite fonts[NUM_FONTS] = {
	{ '1', 0, 0, 3, 7 },
	{ '2', 5, 0, 4, 7 },
	{ '3', 11, 0, 4, 7 },
	{ '4', 17, 0, 4, 7 },
	{ '5', 23, 0, 4, 7 },
	{ '6', 29, 0, 5, 7 },
	{ '7', 35, 0, 5, 7 },
	{ '8', 42, 0, 5, 7 },
	{ '9', 48, 0, 5, 7 },
	{ '0', 55, 0, 5, 7 },
	{ 'P', 0, 8, 5, 7 },
	{ 'o', 7, 8, 4, 7 },
	{ 'n', 13, 8, 4, 7 },
	{ 'g', 19, 8, 4, 10 },
	{ ' ', 24, 8, 4, 7 },
	{ 'G', 29, 8, 5, 7 },
	{ 'a', 35, 8, 3, 7 },
	{ 'm', 40, 8, 7, 7 },
	{ 'e', 49, 8, 3, 7 },
	{ 'T', 0, 19, 5, 7 },
	{ 'h', 6, 19, 4, 7 },
	{ 'k', 23, 19, 4, 7 },
	{ 'Y', 33, 19, 6, 7 },
	{ 'u', 46, 19, 4, 7 },
	{ '!', 52, 19, 1, 8 }
};

// �t�H���g�n���h�����쐬����
CXFont CreateFontToHandle(CXFontType Font, int Size)
{
	return{ Font, (float)Size };
}

// �s�N�Z�����擾
static char GetPixel(int x, int y)
{
	return texture_atlas[y][x];
}

// ������`��֐�
void DrawString(float x, float y, const WCHAR* String, Attributes Color)
{
	Print({ WorldToConsoleX(x), WorldToConsoleY(y) }, Color, String);
}

// �t�H���g�n���h�����g�p����������̕`�敝(���[���h���W)���擾����
float GetDrawStringWidthToHandle(const WCHAR* String, const CXFont* FontHandle)
{
	switch (FontHandle->type)
	{
	default:
	case CXFONT_DEFAULT:
		// ������=��
		return ConsoleToWorldX((SHORT)wcslen(String));
		break;
	case CXFONT_PONG:
		// �T�C�Y�̔�
		float size = 7 / FontHandle->size;
		// �t�H���g�̕�
		float font_w = 0;
		// �t�H���g�����X���W
		float font_x = 0;
		// �������[�v
		const WCHAR* c;
		for (c = String; *c != '\0'; c++)
		{
			// �X�v���C�g
			Sprite* sprite = NULL;

			// ���s��������
			if (*c == '\n')
			{
				// �����擾
				font_w = std::max(font_w, font_x);
				// X���W��߂�
				font_x = 0;
				continue;
			}

			// �X�v���C�g���擾
			{
				int i;
				for (i = 0; i < NUM_FONTS; i++)
				{
					// ��v���Ă�����擾
					if (fonts[i].name == *c)
					{
						sprite = &fonts[i];
						break;
					}
				}
			}

			// �X�v���C�g������Ε������Z
			if (sprite != NULL)
			{
				font_x += sprite->w + FONT_SPAN_WIDTH;
			}
		}
		// �t�H���g�̕��̍ő�
		font_w = std::max(font_w, font_x);
		return font_w;
		break;
	}
}

// �t�H���g�n���h�����g�p���ĕ������`�悷��
void DrawStringToHandle(float x, float y, const WCHAR* String, Attributes Color, const CXFont* FontHandle, const WCHAR* Str)
{
	switch (FontHandle->type)
	{
	default:
	case CXFONT_DEFAULT:
		// ����������̂܂ܕ`��
		DrawString(x, y, String, Color);
		break;
	case CXFONT_PONG:
		// �T�C�Y�̔�
		float size = 7 / FontHandle->size;
		// �t�H���g�����X���W
		float font_x = 0;
		// �t�H���g�����Y���W
		float font_y = 0;
		// �t�H���g�̍ő卂��
		float font_h = 0;
		// �������[�v
		const WCHAR* c;
		for (c = String; *c != '\0'; c++)
		{
			// �X�v���C�g
			Sprite* sprite = NULL;

			// ���s��������
			if (*c == '\n')
			{
				// �t�H���g�����X���W�����Z�b�g
				font_x = 0;
				// X���W��߂�
				font_y += font_h + FONT_SPAN_HEIGHT;
				// �ő卂���̃��Z�b�g
				font_h = 0;
				continue;
			}

			// �X�v���C�g���擾
			{
				int i;
				for (i = 0; i < NUM_FONTS; i++)
				{
					// ��v���Ă�����擾
					if (fonts[i].name == *c)
					{
						sprite = &fonts[i];
						break;
					}
				}
			}
			// �X�v���C�g�������
			if (sprite != NULL)
			{
				// �����̕�
				int str_len = std::max(1, (int)wcslen(Str));

				// Y���[�v
				SHORT ix, iy;
				for (iy = 0; ConsoleToWorldYF(iy) < sprite->h / size; iy += 1)
				{
					// X���[�v
					for (ix = 0; ConsoleToWorldXF(ix) < sprite->w / size; ix += str_len)
					{
						// �s�N�Z����1��������`��
						if (GetPixel(sprite->x + (int)(ConsoleToWorldX(ix) * size), sprite->y + (int)(ConsoleToWorldY(iy) * size)) == '1')
							Print({ WorldToConsoleX(font_x / size + x) + ix, WorldToConsoleY(font_y / size + y) + iy }, Color, Str);
					}
				}
				// �t�H���g�����X���W��i�߂�
				font_x += sprite->w + FONT_SPAN_WIDTH;
				// �t�H���g�̍ő卂�����X�V
				font_h = std::max(font_y, ConsoleToWorldY(sprite->h));
			}
		}
		break;
	}
}