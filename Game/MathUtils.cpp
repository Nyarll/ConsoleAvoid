#include "MathUtils.h"

namespace MathUtils
{
	std::random_device rnd;		// �񌈒�I�ȗ���������
	std::mt19937 mt(rnd());		// �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
									   
	// 0.0��x��1.0 �̏��������_������
	float GetRandScale()
	{
		return static_cast<float>(GetRand(RAND_MAX)) / RAND_MAX;
	}

	// 0.0��x��max �̐��������_������
	int GetRand(int max)
	{
		return mt() % (max + 1);
	}

	// 0.0��x��max �̏��������_������
	float GetRand(float max)
	{
		return GetRandScale() * max;
	}

	// min��x��max �̐��������_������
	int GetRandRange(int min, int max)
	{
		if (max < min)
			std::swap(min, max);
		return GetRand(max - min) + min;
	}

	// min��x��max �̏��������_������
	float GetRandRange(float min, float max)
	{
		if (max < min)
			std::swap(min, max);
		return GetRand(max - min) + min;
	}

	// 0�`w �̐������[�v
	int GetLoop(int x, int w)
	{
		return ((x % w) + w) % w;
	}

	// 0�`w �̏������[�v
	float GetLoop(float x, float w)
	{
		return std::fmodf((std::fmodf(x, w) + w), w);
	}

	// min�`max �̐������[�v
	int GetLoopRange(int x, int min, int max)
	{
		if (max < min)
			std::swap(min, max);
		return GetLoop(x - min, max - min) + min;
	}

	// min�`max �̏������[�v
	float GetLoopRange(float x, float min, float max)
	{
		if (max < min)
			std::swap(min, max);
		return GetLoop(x - min, max - min) + min;
	}

	// ���������_���^�̌덷���l���ɓ��ꂽ��r
	bool FloatEquals(float a, float b)
	{
		return std::abs(a - b) <= std::numeric_limits<float>::epsilon();
	}

	// �p�x�̒P�ʕϊ�([�x]��[���W�A��])
	float ToRadians(float degree)
	{
		return degree * static_cast<float>(M_PI) / 180.0f;
	}

	// �p�x�̒P�ʕϊ�([���W�A��]��[�x])
	float ToDegrees(float radian)
	{
		return radian * 180.0f / static_cast<float>(M_PI);
	}

	// 0�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
	// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
	float GetPercentage(float x, float max)
	{
		float n = GetClamp(x, 0.f, max);
		return n / max;
	}

	// min�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
	// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
	float GetPercentageRange(float x, float min, float max)
	{
		if (max < min)
		{
			x = max - x + min;
			std::swap(min, max);
		}
		return GetPercentage(x - min, max - min);
	}

	// 0�`max�͈̔͂ł�percent%�̈ʒu
	float GetPercentValue(float percent, float max)
	{
		return max * percent;
	}

	// min�`max�͈̔͂ł�percent%�̈ʒu
	float GetPercentValueRange(float percent, float min, float max)
	{
		if (max < min)
		{
			percent = 1 - percent;
			std::swap(min, max);
		}
		return GetPercentValue(percent, max - min) + min;
	}
}