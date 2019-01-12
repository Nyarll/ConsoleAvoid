#pragma once
#include "Color.h"

// ��
#define CX_PI_F (3.1415926535897932384626433832795f)

// ���[���h���W���R���\�[�����W�ɕϊ�
float WorldToConsoleXF(float world_x, float size = 1);

// ���[���h���W���R���\�[�����W�ɕϊ�
float WorldToConsoleYF(float world_y, float size = 1);

// ���[���h���W���R���\�[�����W�ɕϊ�
SHORT WorldToConsoleX(float world_x, float size = 1);

// ���[���h���W���R���\�[�����W�ɕϊ�
SHORT WorldToConsoleY(float world_y, float size = 1);

// �R���\�[�����W�����[���h���W�ɕϊ�
float ConsoleToWorldXF(float screen_x, float size = 1);

// �R���\�[�����W�����[���h���W�ɕϊ�
float ConsoleToWorldYF(float screen_y, float size = 1);

// �R���\�[�����W�����[���h���W�ɕϊ�
float ConsoleToWorldX(SHORT screen_x, float size = 1);

// �R���\�[�����W�����[���h���W�ɕϊ�
float ConsoleToWorldY(SHORT screen_y, float size = 1);

// ��`�`��֐�
void DrawBox(float x1, float y1, float x2, float y2, Color Color, int FillFlag);

// �ȉ~�`��֐�
void DrawOval(float x, float y, float rx, float ry, Color Color, int FillFlag);

// �~�`��֐�
void DrawCircle(float x, float y, float r, Color Color, int FillFlag);

// ���`��֐�
void DrawLine(float x1, float y1, float x2, float y2, Color Color);

// �j����`��
void DrawDashedLine(float x1, float y1, float x2, float y2, Color color, float length);
