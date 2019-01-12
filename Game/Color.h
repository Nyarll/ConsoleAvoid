#pragma once

// �F
using Color = int;

// �F�Z�b�g
namespace Colors
{
	enum : Color
	{
		Black,
		Dark_blue,
		Dark_green,
		Dark_cyan,
		Dark_red,
		Dark_magenta,
		Dark_yellow,
		Gray,
		Dark_gray,
		Blue,
		Green,
		Cyan,
		Red,
		Magenta,
		Yellow,
		White,
	};
}

// ����(�F)
class Attributes
{
public:
	Color background;	// �w�i�J���[
	Color foreground;	// �e�L�X�g�J���[

public:
	// ����(�F)���쐬
	Attributes(Color background, Color foreground = Colors::White);
	Attributes(const WORD& word);
	operator WORD() const;
};
