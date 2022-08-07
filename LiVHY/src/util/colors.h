#pragma once
#include "types.h"
inline constexpr RGB intToRGB(int red, int green, int blue)
{
	return RGB(1.0 * red / 255, 1.0 * green / 255, 1.0 * blue / 255);
}

inline constexpr int charToHex(char c)
{
	if(c <= '9' && c >= '0')
	{
		return c - '0';
	}
	else if(c >= 'a' && c <= 'f')
	{
		return c - 'a' + 10;
	}
	else if(c >= 'A' && c <= 'F')
	{
		return c - 'A' + 10;
	}
	assert(!"Character isn't hex.");
}

inline constexpr RGB stringToRGB(const char str[8])
{
#ifdef _DEBUG
	assert(str[0] == '#');
#endif
	int red = (charToHex(str[1]) << 4) + charToHex(str[2]);
	int green = (charToHex(str[3]) << 4) + charToHex(str[4]);
	int blue = (charToHex(str[5]) << 4) + charToHex(str[6]);
	return intToRGB(red, green, blue);
}

namespace Colors
{
	inline constexpr RGB cyan = stringToRGB("#00ffff");
	inline constexpr RGB beige = stringToRGB("#f5f5dc");
	inline constexpr RGB black = stringToRGB("#000000");
	inline constexpr RGB blue = stringToRGB("#0000ff");
	inline constexpr RGB blueviolet = stringToRGB("#8a2be2");
	inline constexpr RGB brown = stringToRGB("#a52a2a");
	inline constexpr RGB crimson = stringToRGB("#dc143c");
	inline constexpr RGB darkblue = stringToRGB("#00008b");
	inline constexpr RGB darkcyan = stringToRGB("#008b8b");
	inline constexpr RGB darkgray = stringToRGB("#3a3a3a");
	inline constexpr RGB darkgreen = stringToRGB("#006400");
	inline constexpr RGB darkmagenta = stringToRGB("#8b008b");
	inline constexpr RGB darkred = stringToRGB("#8b0000");
	inline constexpr RGB deeppink = stringToRGB("#ff1493");
	inline constexpr RGB deepskyblue = stringToRGB("#00bfff");
	inline constexpr RGB forestgreen = stringToRGB("#228b22");
	inline constexpr RGB magenta = stringToRGB("#ff00ff");
	inline constexpr RGB gold = stringToRGB("#ffd700");
	inline constexpr RGB gray = stringToRGB("#808080");
	inline constexpr RGB green = stringToRGB("#008000");
	inline constexpr RGB hotpink = stringToRGB("#ff69b4");
	inline constexpr RGB indigo = stringToRGB("#4b0082");
	inline constexpr RGB ivory = stringToRGB("#fffff0");
	inline constexpr RGB lavender = stringToRGB("#e6e6fa");
	inline constexpr RGB lightblue = stringToRGB("#add8e6");
	inline constexpr RGB lightgray = stringToRGB("#d3d3d3");
	inline constexpr RGB lightgreen = stringToRGB("#90ee90");
	inline constexpr RGB lightskyblue = stringToRGB("#87cefa");
	inline constexpr RGB lime = stringToRGB("#00ff00");
	inline constexpr RGB limegreen = stringToRGB("#32cd32");
	inline constexpr RGB maroon = stringToRGB("#800000");
	inline constexpr RGB mediumblue = stringToRGB("#0000cd");
	inline constexpr RGB mediumpurple = stringToRGB("#9370db");
	inline constexpr RGB midnightblue = stringToRGB("#191970");
	inline constexpr RGB navy = stringToRGB("#000080");
	inline constexpr RGB olive = stringToRGB("#808000");
	inline constexpr RGB orange = stringToRGB("#ffa500");
	inline constexpr RGB orangered = stringToRGB("#ff4500");
	inline constexpr RGB pink = stringToRGB("#ffc0cb");
	inline constexpr RGB purple = stringToRGB("#800080");
	inline constexpr RGB red = stringToRGB("#ff0000");
	inline constexpr RGB royalblue = stringToRGB("#4169e1");
	inline constexpr RGB silver = stringToRGB("#c0c0c0");
	inline constexpr RGB skyblue = stringToRGB("#87ceeb");
	inline constexpr RGB tomato = stringToRGB("#ff6347");
	inline constexpr RGB turquoise = stringToRGB("#40e0d0");
	inline constexpr RGB violet = stringToRGB("#ee82ee");
	inline constexpr RGB white = stringToRGB("#ffffff");
	inline constexpr RGB yellow = stringToRGB("#ffff00");
}
