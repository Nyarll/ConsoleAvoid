//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Main.cpp
//!
//! @brief  �Q�[���v���O�����̃G���g���[�|�C���g�̃\�[�X�t�@�C��
//!
//! @date   2018/07/18
//!
//! @author GF1 26 �R������
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================

#include "Game.h"
#include "Console.h"
#include "GameMain.h"
#include "BufferedConsole.h"
#include "ScreenManager.h"
#include "Input.h"
#include "MathUtils.h"



// �O���[�o���ϐ���` ======================================================

// �Ō�̎���
static struct timespec last_clock;
// 1�t���[���̕b
float delta_time;
// �I�����N�G�X�g
static bool exit_request = false;



// �֐���` ================================================================

// 1�t���[��
static int ProcessMessage(void)
{
	struct timespec now;
	timespec_get(&now, TIME_UTC);
	delta_time = std::min(60.f, ((now.tv_sec - last_clock.tv_sec) + (now.tv_nsec - last_clock.tv_nsec)/1000.f/1000.f/1000.f) * 16);
	last_clock = now;

	InputManager::GetInstance().Update();

	Sleep(1000 / 100);

	return exit_request;
}

// ����ʐ؂�ւ�
static int ScreenFlip(void)
{
	auto& context = ScreenManager::GetInstance().GetContext();

	context.Flush();

	return true;
}

// �I�����N�G�X�g
void ExitGame(void)
{
	exit_request = true;
}

//----------------------------------------------------------------------
//! @brief �v���O�����̃G���g���[�|�C���g
//!
//! @retval  0 ����I��
//! @retval -1 �ُ�I��
//----------------------------------------------------------------------
int main(void)
{
	// ������Ԃ̉�ʃ��[�h�̐ݒ�
	SetFontSize(SCREEN_FONT_SIZE);
	SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetCursorVisibility(CURSOR_INVISIBLE);

	auto& context = ScreenManager::GetInstance().GetContext();

	/*
	// �X�s�[�h�e�X�g (�f�o�b�O)
	{
		TestSpeed();
		return 0;
	}
	/**/

	// �Q�[���̏���
	InitializeGame();			// �Q�[���̏���������

	while (!ProcessMessage())
	{
		UpdateGame();			// �Q�[���̍X�V����
		RenderGame();			// �Q�[���̕`�揈��

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
		context.Clear();		// ����ʂ̏���
	}

	FinalizeGame();				// �Q�[���̏I������

	return 0;					// ����I��
}
