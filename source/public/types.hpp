#pragma once

#include "public\defines.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

namespace JCON_NAMESPACE {

	typedef sf::RenderWindow windowType;
	typedef sf::Event eventType;

	typedef std::string textType;
	typedef sf::Font fontType;
	typedef sf::Color colorType;
	typedef sf::Vector2u extent2DType;

	typedef void(ChildPaintType)(int yOffset);
	typedef std::vector<std::function<JCON_NAMESPACE::ChildPaintType>> ChildBufferType;

	enum JCON_API insertType {
		TEXT = 0,
		FONT = 1,
		COLOR = 2
	};

	// FORWARDS
	struct JCON_API segment;
	typedef void(segmentBufferIter)(JCON_NAMESPACE::segment *member);
	class JCON_API segmentBuffer;

	class JCON_API console;

}
