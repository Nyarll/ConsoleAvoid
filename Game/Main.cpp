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
#include "Screen.h"
#include "ScreenManager.h"
#include "Input.h"
#include "MathUtils.h"



// �O���[�o���ϐ���` ======================================================

// �Ō�̎���
static std::chrono::time_point<std::chrono::high_resolution_clock> last_time;
// 1�t���[���̊Ԋu
static std::chrono::nanoseconds delta_clock;
// 1�t���[���̕b
float delta_time;
// �I�����N�G�X�g
static bool exit_request = false;
// FPS
static const int FPS = 60;



// �֐���` ================================================================

// 1�t���[��
static int ProcessMessage(void)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
	delta_clock = now - last_time;
	last_time = now;

	delta_time = delta_clock.count() * 1e-9f;

	static auto interval = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)) / FPS;
	auto sleeptime = interval - delta_clock;
	Sleep(static_cast<DWORD>(std::max(0LL, std::chrono::duration_cast<std::chrono::milliseconds>(sleeptime).count())));

	InputManager::GetInstance().Update();

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
	ScreenManager::GetInstance().SetFontSize(SCREEN_FONT_SIZE/2, SCREEN_FONT_SIZE);
	ScreenManager::GetInstance().SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	ScreenManager::GetInstance().SetCursorVisibility(CURSOR_INVISIBLE);

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
