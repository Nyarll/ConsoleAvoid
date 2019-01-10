#include "InputManager.h"
#include "Console.h"
#include <time.h>

// �萔�̒�` ==============================================================

#define KEY_DURATION 475

// �O���[�o���ϐ��̒�` ====================================================

// �����͏��
static int g_raw_input_state;
// �O��̐����͏��
static int g_raw_input_state_last;

// ���͏��
static int g_input_state;
// �O��̓��͏��
static int g_input_state_last;

// �ҋ@���̃L�[
static int g_pending_key;
// �Ō�ɓ��͂��ꂽ����
static time_t g_pending_last;

// �֐��̒�` ==============================================================

// �L�[�X�V
void UpdateInputManager(void)
{
	// �Ō�ɓ��͂��ꂽ�L�[���X�V
	g_raw_input_state_last = g_raw_input_state;
	g_input_state_last = g_input_state;
	// ���ݓ��͂��ꂽ�L�[���X�V
	g_input_state = g_raw_input_state = GetKeyInput();

	// ���͂���������
	if (g_input_state != 0)
	{
		// �ҋ@���̃L�[���X�V
		g_pending_key = g_input_state;
		g_pending_last = clock();
	}
	else
	{
		// �ҋ@���̃L�[����莞�ԉ��������Ƃɂ���
		if (clock() - g_pending_last < KEY_DURATION)
			g_input_state = g_pending_key;
	}
}

// ���L�[��������Ă��邩
bool IsRawKeyDown(int key)
{
	return g_raw_input_state == key;
}

// ���L�[��������Ă��邩
bool IsRawKeyUp(int key)
{
	return !IsKeyDown(key);
}

// ���L�[�����������ォ
bool IsRawKeyPressed(int key)
{
	return (g_raw_input_state_last != key) && (g_raw_input_state == key);
}

// ���L�[�𗣂������ォ
bool IsRawKeyReleased(int key)
{
	return (g_raw_input_state_last == key) && (g_raw_input_state != key);
}

// �L�[��������Ă��邩
bool IsKeyDown(int key)
{
	return g_input_state == key;
}

// �L�[��������Ă��邩
bool IsKeyUp(int key)
{
	return !IsKeyDown(key);
}

// �L�[�����������ォ
bool IsKeyPressed(int key)
{
	return (g_input_state_last != key) && (g_input_state == key);
}

// �L�[�𗣂������ォ
bool IsKeyReleased(int key)
{
	return (g_input_state_last == key) && (g_input_state != key);
}