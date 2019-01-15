#include "GameMain.h"
#include "Screen.h"
#include "ScreenManager.h"
#include "Input.h"
#include "Time.h"
#include "SystemUtils.h"

// 1�t���[��
static int ProcessMessage(void)
{
	auto& time = Time::GetInstance();
	time.Update();
	time.WaitFrame();
	InputManager::GetInstance().Update();
	return !SystemUtils::running;
}

// ����ʐ؂�ւ�
static int ScreenFlip(void)
{
	static auto& context = ScreenManager::GetInstance().GetContext();

	context.Flush();

	return true;
}

// �v���O�����̃G���g���[�|�C���g
int main(void)
{
	// ������Ԃ̉�ʃ��[�h�̐ݒ�
	//ScreenManager::GetInstance().SetFontSize(SCREEN_FONT_SIZE);
	//ScreenManager::GetInstance().SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//ScreenManager::GetInstance().SetPixelSize(14);
	ScreenManager::GetInstance().SetFontSize(7);
	ScreenManager::GetInstance().SetWindowSize(640, 480);
	ScreenManager::GetInstance().SetCursorVisibility(false);
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	static auto& context = ScreenManager::GetInstance().GetContext();

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
