#ifndef KEYBOARD_H
#define KEYBOARD_H

namespace KillerbyteGameEngine
{
	class Keyboard
	{
		friend class Platform;

	public:
		// At the moment, only the letter keys, enter, shift, escape and the arrow keys
		enum Key
		{
			KEY_NONE = 0,
			KEY_CAP_A = 'A',
			KEY_CAP_B = 'B',
			KEY_CAP_C = 'C',
			KEY_CAP_D = 'D',
			KEY_CAP_E = 'E',
			KEY_CAP_F = 'F',
			KEY_CAP_G = 'G',
			KEY_CAP_H = 'H',
			KEY_CAP_I = 'I',
			KEY_CAP_J = 'J',
			KEY_CAP_K = 'K',
			KEY_CAP_L = 'L',
			KEY_CAP_M = 'M',
			KEY_CAP_N = 'N',
			KEY_CAP_O = 'O',
			KEY_CAP_P = 'P',
			KEY_CAP_Q = 'Q',
			KEY_CAP_R = 'R',
			KEY_CAP_S = 'S',
			KEY_CAP_T = 'T',
			KEY_CAP_U = 'U',
			KEY_CAP_V = 'V',
			KEY_CAP_W = 'W',
			KEY_CAP_X = 'X',
			KEY_CAP_Y = 'Y',
			KEY_CAP_Z = 'Z',
			KEY_A = 'a',
			KEY_B = 'b',
			KEY_C = 'c',
			KEY_D = 'd',
			KEY_E = 'e',
			KEY_F = 'f',
			KEY_G = 'g',
			KEY_H = 'h',
			KEY_I = 'i',
			KEY_J = 'j',
			KEY_K = 'k',
			KEY_L = 'l',
			KEY_M = 'm',
			KEY_N = 'n',
			KEY_O = 'o',
			KEY_P = 'p',
			KEY_Q = 'q',
			KEY_R = 'r',
			KEY_S = 's',
			KEY_T = 't',
			KEY_U = 'u',
			KEY_V = 'v',
			KEY_W = 'w',
			KEY_X = 'x',
			KEY_Y = 'y',
			KEY_Z = 'z',
			KEY_ESCAPE = 0x001B,
			KEY_RETURN = 0x000D,
			KEY_SHIFT = 0x00E1,
			KEY_LEFTARROW = 0x1051,
			KEY_UPARROW = 0x1052,
			KEY_RIGHTARROW = 0x1053,
			KEY_DOWNARROW = 0x1054
		};

		enum KeyEvent // We have the key char to show that it is a character and not a special character
		{
			KEY_DOWN,
			KEY_UP,
			KEY_CHAR
		};
	private:
		Keyboard() { }
	};
}

#endif