#include <bitset>
#include <iostream>
#include "Cup/Object/Color.hpp"

using namespace Cup::Object;

// Constructs

Color::Color(UInt32 r, UInt32 g, UInt32 b) : Color(r, g, b, 255)
{

}

Color::Color(UInt32 r, UInt32 g, UInt32 b, UInt32 a)
{
	value += r << 24;
	value += g << 16;
	value += b << 8;
	value += a << 0;
}

// Getters

Color::UInt8 Color::getRed() const
{
	return static_cast<UInt8>(value >> 24);
}

Color::UInt8 Color::getGreen() const
{
	return static_cast<UInt8>(value >> 16);
}

Color::UInt8 Color::getBlue() const
{
	return static_cast<UInt8>(value >> 8);
}

Color::UInt8 Color::getAlpha() const
{
	return static_cast<UInt8>(value >> 0);
}

// Setters

void Color::setRed(Color::UInt32 r)
{
	// Remember, the component red is
	// localize in the side left,
	// The schema is - R G B A -
	// In the parameter r the schema
	// is - 0 0 0 R -
	// Need move R to left (aka: - R 0 0 0 -)
	// Each position (of 4 possibles)
	// in the schema have a size of 8.
	// As we need move 3 position the total
	// of bits to move is of
	// 24 = 8 bits * 3 positions
	r <<= 24;
	// Clear the old value of component
	// in r for that we can store a new
	// value of component r.
	// The schema is actual is - G B A 0 -
	value <<= 8;
	// However, with the above operation
	// the schema is unordered, we have
	// order tha schema.
	// It will be like that again
	// as - 0 G B A -
	value >>= 8;
	// The operator "bitwise XOR (exclusive
	// OR)" allow interchange the values of
	// component r without affect the
	// another components ( G B and A).
	// See:
	// - 0 G B A - The schema of value
	// - R 0 0 0 - The schema of parameter r
	// Apply the operation xor the result is:
	// - R G B A -
	value ^= r;
}

void Color::setGreen(Color::UInt32 g)
{
	// Schema r is : - R 0 0 0 -
	UInt32 r = getRed() << 24;
	// Schema value: - B A 0 0 -
	value <<= 16;
	// Schema value: - 0 0 B A -
	value >>= 16;
	// Schema parameter g is : - 0 G 0 0 -
	g <<= 16;

	// - 0 0 B A - Schema value
	// - 0 G 0 0 - Schema parameter g
	// Result of operation
	// - 0 G B A -
	value ^= g;

	// - 0 G B A - Schema value
	// - R G B A - Schema r
	// Result of operation
	// - R G B A -
	value ^= r;
}

void Color::setBlue(Color::UInt32 b)
{
	UInt32 a = getAlpha();
	value >>= 16;
	value <<= 16;
	b <<= 8;
	value ^= b;
	value ^= a;
}

void Color::setAlpha(Color::UInt32 a)
{
	value += a << 0;
}
