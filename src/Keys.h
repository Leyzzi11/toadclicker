#include <string_view>

namespace toad
{
	inline static const char* keys[] = 
	{
		"Left mouse",
		"Right mouse",
		"Control-break",
		"mmb",
		"X1 mouse",
		"X2 mouse",
		"unknown",
		"BACKSPACE",
		"TAB",
		"unknown",
		"unknown",
		"CLEAR",
		"ENTER",
		"unknown",
		"unknown",
		"SHIFT",
		"CTRL",
		"ALT",
		"PAUSE",
		"CAPS LOCK",
		"IME Kana",
		"unknown",
		"IME Junja",
		"IME final",
		"IME Hanja kanji",
		"unknown",
		"ESC",
		"IME",
		"IME",
		"IME",
		"IME mode change",
		"Space bar",
		"PAGE UP",
		"PAGE DOWN",
		"END",
		"HOME",
		"LEFT ARROW",
		"UP ARROW",
		"RIGHT ARROW",
		"DOWN ARROW",
		"SELECT",
		"PRINT",
		"EXECUTE",
		"PRINT SCREEN",
		"INS",
		"DEL",
		"HELP",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"unknown",
		"unknown",
		"unknown",
		"unknown",
		"unknown",
		"unknown",
		"unknown",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Left Windows",
		"Right Windows",
		"Applications",
		"Reserved",
		"Computer Sleep",
		"Numeric keypad 0",
		"Numeric keypad 1",
		"Numeric keypad 2",
		"Numeric keypad 3",
		"Numeric keypad 4",
		"Numeric keypad 5",
		"Numeric keypad 6",
		"Numeric keypad 7",
		"Numeric keypad 8",
		"Numeric keypad 9",
		"Multiply",
		"ADD",
		"Separator",
		"Subtract",
		"Decimal",
		"Divide",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F13",
		"F14",
		"F15",
		"F16",
		"F17",
		"F18",
		"F19",
		"F20",
		"F21",
		"F22",
		"F23",
		"F24",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"NUM LOCK",
		"SCROLL LOCK",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"unassigned",
		"LSHIFT",
		"RSHIFT",
		"LCONTROL",
		"RCONTROL",
		"LMENU",
		"RMENU",
		"Back ",
		"Forward ",
		"Refresh ",
		"Stop ",
		"Search ",
		"Favorites ",
		"Start",
		"Volume Down" ,
		"Volume Mute" ,
		"Volume Up" ,
		"Next Track" ,
		"Previous Track" ,
		"Stop Media" ,
		"Play/Pause" ,
		"Start Mail" ,
		"Select Media" ,
		"Application 1" ,
		"Application 2" ,
		"reserved",
		"reserved",
		";" ,
		"=",
		",",
		"-",
		"'",
		"/" ,
		"`" ,
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Unassigned",
		"Unassigned",
		"Unassigned",
		"Unassigned",
		"[",
		"\\",
		"]",
		"'" ,
		"OEM8",
		"Reserved",
		"OEM specific",
		"\\",
		"OEM specific",
		"OEM specific",
		"PROCESS",
		"OEM specific",
		"packet",
		"Unassigned",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"OEM specific",
		"Attn",
		"CrSel",
		"ExSel",
		"Erase EOF",
		"Play",
		"Zoom",
		"reserved",
		"PA1 key",
		"clear"
	};

	inline static const std::unordered_map<int, int> mc_as_vkc
	{
		{ 1, VK_ESCAPE },	// Escape
		{ 2, VK_1 },		// 1
		{ 3, VK_2 },		// 2
		{ 4, VK_3 },		// 3
		{ 5, VK_4 },		// 4
		{ 6, VK_5 },		// 5
		{ 7, VK_6 },		// 6
		{ 8, VK_7 },		// 7
		{ 9, VK_8 },		// 8
		{ 10, VK_9 },		// 9
		{ 11, VK_0 },		// 0
		{ 12, VK_OEM_MINUS },	// -
		{ 13, VK_OEM_PLUS },	// =
		{ 14, VK_BACK },	// Backspace
		{ 15, VK_TAB },		// Tab
		{ 16, 'Q' },		// Q
		{ 17, 'W' },		// W
		{ 18, 'E' },		// E
		{ 19, 'R' },		// R
		{ 20, 'T' },		// T
		{ 21, 'Y' },		// Y
		{ 22, 'U' },		// U
		{ 23, 'I' },		// I
		{ 24, 'O' },		// O
		{ 25, 'P' },		// P
		{ 26, VK_OEM_4 },	// [
		{ 27, VK_OEM_6 },	// ]
		{ 28, VK_RETURN },	// Enter
		{ 29, VK_CONTROL },	// Left Ctrl
		{ 30, 'A' },		// A
		{ 31, 'S' },		// S
		{ 32, 'D' },		// D
		{ 33, 'F' },		// F
		{ 34, 'G' },		// G
		{ 35, 'H' },		// H
		{ 36, 'J' },		// J
		{ 37, 'K' },		// K
		{ 38, 'L' },		// L
		{ 39, VK_OEM_1 },	// ;
		{ 40, VK_OEM_7 },	// '
		{ 41, VK_OEM_3 },	// `
		{ 42, VK_SHIFT },	// Left Shift
		{ 43, VK_OEM_5 },	// \
		{ 44, 'Z' },		// Z
		{ 45, 'X' },		// X
		{ 46, 'C' },		// C
		{ 47, 'V' },		// V
		{ 48, 'B' },		// B
		{ 49, 'N' },		// N
		{ 50, 'M' },		// M
		{ 51, VK_OEM_COMMA },	// ,
		{ 52, VK_OEM_PERIOD },	// .
		{ 53, VK_OEM_2 },	// /
		{ 54, VK_SHIFT },	// Right Shift
		{ 55, VK_SNAPSHOT },	// Print Screen
		{ 56, VK_MENU },	// Left Alt
		{ 57, VK_SPACE },	// Space
		{ 58, VK_CAPITAL },	// Caps Lock
		{ 59, VK_F1 },		// F1
		{ 60, VK_F2 },		// F2
		{ 61, VK_F3 },		// F3
		{ 62, VK_F4 },		// F4
		{ 63, VK_F5 },		// F5
		{ 64, VK_F6 },		// F6
		{ 65, VK_F7 },		// F7
		{ 66, VK_F8 },		// F8
		{ 67, VK_F9 },		// F9
		{ 68, VK_F10 },		// F10
		{ 69, VK_F11 },		// F11
		{ 70, VK_F12 },		// F12
		{ 71, VK_SCROLL },	// Scroll Lock
		{ 72, VK_PAUSE },	// Pause
		{ 73, VK_INSERT },	// Insert
		{ 74, VK_HOME },	// Home
		{ 75, VK_PRIOR },	// Page Up
		{ 76, VK_DELETE },	// Delete
		{ 77, VK_END },		// End
		{ 78, VK_NEXT },	// Page Down
		{ 79, VK_RIGHT },	// Right Arrow
		{ 80, VK_LEFT },	// Left Arrow
		{ 81, VK_DOWN },	// Down Arrow
		{ 82, VK_UP },		// Up Arrow
		{ 83, VK_NUMLOCK },	// Num Lock
		{ 84, VK_DIVIDE },	// Numpad /
		{ 85, VK_MULTIPLY },	// Numpad *
		{ 86, VK_SUBTRACT },	// Numpad -
		{ 87, VK_ADD },		// Numpad +
		{ 88, VK_RETURN },	// Numpad Enter
		{ 89, VK_DECIMAL },	// Numpad .
		{ 90, VK_NUMPAD0 },	// Numpad 0
		{ 91, VK_NUMPAD1 },	// Numpad 1
		{ 92, VK_NUMPAD2 },	// Numpad 2
		{ 93, VK_NUMPAD3 },	// Numpad 3
		{ 94, VK_NUMPAD4 },	// Numpad 4
		{ 95, VK_NUMPAD5 },	// Numpad 5
		{ 96, VK_NUMPAD6 },	// Numpad 6
		{ 97, VK_NUMPAD7 },	// Numpad 7
		{ 98, VK_NUMPAD8 },	// Numpad 8
		{ 99, VK_NUMPAD9 },	// Numpad 9
	};
}
