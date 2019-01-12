//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  Pong Online! �I���W�i���ۑ�
//!
//! @date   2018/06/13
//!
//! @author GF1 26 �R������
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "Game.h"
#include "MathUtils.h"
#include "Input.h"
#include "CXLib.h"
#include "CXFont.h"
#include "Vec2.h"

// �萔�̒�` ==============================================================


// �O���[�o���ϐ��̒�` ====================================================

// <�t�H���g> ----------------------------------------------------------
CXFont g_font_pong;
CXFont g_font;

// <�|�[�Y> ------------------------------------------------------------
bool g_paused;
int g_pause_select;

Vec2 g_pos;

// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{
	g_font_pong = CreateFontToHandle(CXFontType::CXFONT_PONG, 12);
	g_font = CreateFontToHandle(CXFontType::CXFONT_DEFAULT, 1);
	g_pos = { 10, 10 };
}

//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	if (InputManager::GetInstance().key->GetButton('W') || InputManager::GetInstance().key->GetButton(VK_UP))
		g_pos += Vec2::up * delta_time;
	if (InputManager::GetInstance().key->GetButton('S') || InputManager::GetInstance().key->GetButton(VK_DOWN))
		g_pos += Vec2::down * delta_time;
	if (InputManager::GetInstance().key->GetButton('A') || InputManager::GetInstance().key->GetButton(VK_LEFT))
		g_pos += Vec2::left * delta_time;
	if (InputManager::GetInstance().key->GetButton('D') || InputManager::GetInstance().key->GetButton(VK_RIGHT))
		g_pos += Vec2::right * delta_time;
}

//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderGame(void)
{
	//DrawStringToHandle(10, 10, "Pong Game!", ATTR_WHITE, &g_font_pong);
	//for (int iy = 0; iy < 2; iy++)
	//	for (int ix = 0; ix < 10; ix++)
	//		DrawCircle(g_pos.x + ix * 10, g_pos.y + iy * 10, 5, ATTR_WHITE, true);

	//POINT point;
	//GetCursorPos(&point);
	//std::string str = "x=" + std::to_string(static_cast<int>(point.x)) + ", " + "y=" + std::to_string(static_cast<int>(point.y));
	//DrawStringToHandle(10, 25, str.c_str(), ATTR_WHITE, &g_font);

	//DrawBox(5, 5, 95, 95, ATTR_WHITE, false);

	DrawStringToHandle(g_pos.x, g_pos.y, L"��su\nshi����\nsus\nhi������������", ATTR_WHITE, &g_font);

	if (InputManager::GetInstance().key->GetButton('W') || InputManager::GetInstance().key->GetButton(VK_UP))
		DrawStringToHandle(15, 35, L"��", ATTR_WHITE, &g_font);
	if (InputManager::GetInstance().key->GetButton('S') || InputManager::GetInstance().key->GetButton(VK_DOWN))
		DrawStringToHandle(15, 45, L"��", ATTR_WHITE, &g_font);
	if (InputManager::GetInstance().key->GetButton('A') || InputManager::GetInstance().key->GetButton(VK_LEFT))
		DrawStringToHandle(10, 40, L"��", ATTR_WHITE, &g_font);
	if (InputManager::GetInstance().key->GetButton('D') || InputManager::GetInstance().key->GetButton(VK_RIGHT))
		DrawStringToHandle(20, 40, L"��", ATTR_WHITE, &g_font);

	//DrawBox(10, 10, 90, 90, ATTR_WHITE, false);
}

//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{
}
