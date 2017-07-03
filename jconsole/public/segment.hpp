#pragma once

#include "public\types.hpp"

namespace JCON_NAMESPACE {

	struct segment {
		float x;
		float y;
		JCON_NAMESPACE::textType text;
		JCON_NAMESPACE::fontType font;
		JCON_NAMESPACE::colorType color;
		float lineHeight;
	};

	class segmentBuffer {
	private:
		JCON_NAMESPACE::segment* m_Buffer;
		size_t m_BufferSize;

	public:
		segmentBuffer(size_t bufferSize = JCON_BUFFER_SIZE);
		~segmentBuffer();

		JCON_NAMESPACE::segment* push_back(JCON_NAMESPACE::segment &copyInsert);

	};

}