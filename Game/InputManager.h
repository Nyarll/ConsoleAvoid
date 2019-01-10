#pragma once
#include "Game.h"

// �֐��̒�` ==============================================================

// �L�[�X�V
void UpdateInputManager(void);

// ���L�[��������Ă��邩
bool IsRawKeyDown(int key);

// ���L�[��������Ă��邩
bool IsRawKeyUp(int key);

// ���L�[�����������ォ
bool IsRawKeyPressed(int key);

// ���L�[�𗣂������ォ
bool IsRawKeyReleased(int key);

// �L�[��������Ă��邩
bool IsKeyDown(int key);

// �L�[��������Ă��邩
bool IsKeyUp(int key);

// �L�[�����������ォ
bool IsKeyPressed(int key);

// �L�[�𗣂������ォ
bool IsKeyReleased(int key);
