/// @file util/colors.h
#pragma once
#include "types.h"
#include "glm/common.hpp"

/// @brief Helper function that converts 3 ints into a RGB.
/// @param[in] red Red value of the RGB
/// @param[in] green Green value of the RGB
/// @param[in] blue Blue value of the RGB
/// @return Returns an RGB type of the 
constexpr RGB intToRGB(uint8_t red, uint8_t green, uint8_t blue)
{
	return RGB(1.0 * red / 255, 1.0 * green / 255, 1.0 * blue / 255); 
}

/// @brief Helper function converting a character into a hex value.
/// @param[in] c Input character. 
/// @return uint8_t representing a hex Value
constexpr uint8_t charToHex(char c)
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
	return 0;
}

/// @brief Helper function converting a string into RGB.
/// @param str 7 character long string representing a hex value (e.g. "#000000")
/// @return Returns the equivalent RGB value of the string.
constexpr RGB stringToRGB(const char str[8])
{
#ifdef _DEBUG
	assert(str[0] == '#');
#endif
	int red = (charToHex(str[1]) << 4) + charToHex(str[2]);
	int green = (charToHex(str[3]) << 4) + charToHex(str[4]);
	int blue = (charToHex(str[5]) << 4) + charToHex(str[6]);
	return intToRGB(red, green, blue);
}

/// @brief Namespace containing color constants.
namespace Colors
{
	constexpr RGB cyan = stringToRGB("#00ffff");
	constexpr RGB beige = stringToRGB("#f5f5dc");
	constexpr RGB black = stringToRGB("#000000");
	constexpr RGB blue = stringToRGB("#0000ff");
	constexpr RGB blueviolet = stringToRGB("#8a2be2");
	constexpr RGB brown = stringToRGB("#a52a2a");
	constexpr RGB crimson = stringToRGB("#dc143c");
	constexpr RGB darkblue = stringToRGB("#00008b");
	constexpr RGB darkcyan = stringToRGB("#008b8b");
	constexpr RGB darkgray = stringToRGB("#3a3a3a");
	constexpr RGB darkgreen = stringToRGB("#006400");
	constexpr RGB darkmagenta = stringToRGB("#8b008b");
	constexpr RGB darkred = stringToRGB("#8b0000");
	constexpr RGB deeppink = stringToRGB("#ff1493");
	constexpr RGB deepskyblue = stringToRGB("#00bfff");
	constexpr RGB forestgreen = stringToRGB("#228b22");
	constexpr RGB magenta = stringToRGB("#ff00ff");
	constexpr RGB gold = stringToRGB("#ffd700");
	constexpr RGB gray = stringToRGB("#808080");
	constexpr RGB green = stringToRGB("#008000");
	constexpr RGB hotpink = stringToRGB("#ff69b4");
	constexpr RGB indigo = stringToRGB("#4b0082");
	constexpr RGB ivory = stringToRGB("#fffff0");
	constexpr RGB lavender = stringToRGB("#e6e6fa");
	constexpr RGB lightblue = stringToRGB("#add8e6");
	constexpr RGB lightgray = stringToRGB("#d3d3d3");
	constexpr RGB lightgreen = stringToRGB("#90ee90");
	constexpr RGB lightskyblue = stringToRGB("#87cefa");
	constexpr RGB lime = stringToRGB("#00ff00");
	constexpr RGB limegreen = stringToRGB("#32cd32");
	constexpr RGB maroon = stringToRGB("#800000");
	constexpr RGB mediumblue = stringToRGB("#0000cd");
	constexpr RGB mediumpurple = stringToRGB("#9370db");
	constexpr RGB midnightblue = stringToRGB("#191970");
	constexpr RGB navy = stringToRGB("#000080");
	constexpr RGB olive = stringToRGB("#808000");
	constexpr RGB orange = stringToRGB("#ffa500");
	constexpr RGB orangered = stringToRGB("#ff4500");
	constexpr RGB pink = stringToRGB("#ffc0cb");
	constexpr RGB purple = stringToRGB("#800080");
	constexpr RGB red = stringToRGB("#ff0000");
	constexpr RGB royalblue = stringToRGB("#4169e1");
	constexpr RGB silver = stringToRGB("#c0c0c0");
	constexpr RGB skyblue = stringToRGB("#87ceeb");
	constexpr RGB tomato = stringToRGB("#ff6347");
	constexpr RGB turquoise = stringToRGB("#40e0d0");
	constexpr RGB violet = stringToRGB("#ee82ee");
	constexpr RGB white = stringToRGB("#ffffff");
	constexpr RGB yellow = stringToRGB("#ffff00");
}
