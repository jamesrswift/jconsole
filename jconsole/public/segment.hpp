#pragma once

#include "public\types.hpp"

#include <functional>

#define JCON_SEGMENTBUFFER_ERROR_RANGE "Attempt to reference segment at location outside array"
#define JCON_SEGMENTBUFFER_ERROR_UNINT "Attempt to reference segment at bad location"
#define JCON_SEGMENTBUFFER_ERROR_OVERFLOW "Attempt to exceed buffer capacity"

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
		size_t m_BufferContent = 0;

	public:
		segmentBuffer(size_t bufferSize = JCON_BUFFER_SIZE);
		~segmentBuffer();

		JCON_NAMESPACE::segment* get(size_t Index);
		JCON_NAMESPACE::segment* push_back(JCON_NAMESPACE::segment Insert);
		void clear();
		//void reserve(size_t size);
		void Iterate(std::function<segmentBufferIter> It);


	};

}
