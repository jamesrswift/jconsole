#include "public\defines.h"
#include "public\types.hpp"
#include "public\segment.hpp"

#include <functional>
#include <stdexcept>

namespace JCON_NAMESPACE {

	segmentBuffer::segmentBuffer(size_t bufferSize) {
		this->m_Buffer = new JCON_NAMESPACE::segment[bufferSize];
		this->m_BufferSize = bufferSize;
	}

	segmentBuffer::~segmentBuffer() {
		delete[] this->m_Buffer;
	}

	JCON_NAMESPACE::segment* segmentBuffer::get(size_t Index) {
		if (Index > m_BufferSize)
			throw std::out_of_range(JCON_SEGMENTBUFFER_ERROR_RANGE);

		if (Index > m_BufferContent)
			throw std::out_of_range(JCON_SEGMENTBUFFER_ERROR_UNINT);

		return &(this->m_Buffer[Index]);
	}

	JCON_NAMESPACE::segment* segmentBuffer::push_back(JCON_NAMESPACE::segment copyInsert){

		if (m_BufferContent == ( m_BufferSize - 1) )
			throw std::out_of_range(JCON_SEGMENTBUFFER_ERROR_OVERFLOW);

		this->m_Buffer[m_BufferContent] = copyInsert;
		m_BufferContent++;

		return &(this->m_Buffer[m_BufferContent-1]);
	}

	void segmentBuffer::clear() {
		// Harmless way of clearing segment buffer without dereferencing immediately
		this->m_BufferContent = 0;
	}

	void segmentBuffer::Iterate(std::function<JCON_NAMESPACE::segmentBufferIter> It)
	{
		for (size_t position = 0; position < m_BufferContent; position++)
			It(this->get(position));
	}


}
