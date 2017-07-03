#pragma once

#include "public\defines.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace JCON_NAMESPACE {

	typedef std::string textType;
	typedef sf::Font fontType;
	typedef sf::Color colorType;
	typedef sf::Vector2u extent2DType;

	typedef void(ChildPaintType)(int yOffset);

	enum insertType {
		TEXT = 0,
		FONT = 1,
		COLOR = 2
	};

	// FORWARDS
	struct segment;
	typedef void(segmentBufferIter)(JCON_NAMESPACE::segment *member);
	class segmentBuffer;

	class console;

}