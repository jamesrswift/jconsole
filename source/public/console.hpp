#pragma once
#pragma warning( disable : 4251 )  // all members having no dll-interface are private

#include "public\accessor.h"
#include "public\types.hpp"
#include "public\segment.hpp"
#include "public\component.hpp"

namespace JCON_NAMESPACE {

	class JCON_API console {
		JCON_DEF_ACCESSORFUNC(bool, m_Rebuilding,	Rebuilding);
		JCON_DEF_ACCESSORFUNC(int, m_ScrollOffset, ScrollOffset);
		JCON_DEF_ACCESSORFUNC(bool,	m_Scrolldown,	ShouldScrollDown);
		JCON_DEF_ACCESSORFUNC(int, m_SideOffset,	SideOffset);

	public:
		console();
		void PerformLayout();
		void AppendLine(componentList insertion);
		void Paint();

		void setWindow(JCON_NAMESPACE::windowType* WindowContext);
		void HandleWindowOnResize(sf::Event* Event);

	private:
		JCON_NAMESPACE::componentList m_ContentBuffer;
		JCON_NAMESPACE::ChildBufferType m_ChildBuffer;
		JCON_NAMESPACE::segmentBuffer m_SegmentBuffer;

		JCON_NAMESPACE::extent2DType m_Extent2D;
		float m_curX = 0;
		float m_curY = 0;
		float m_vPadding = 2;

		JCON_NAMESPACE::fontType m_curFont;
		JCON_NAMESPACE::colorType m_curColor;
		float m_curLineHeight;

		void StartInsertion();
		void EndInsertion();

		void AppendColor(JCON_NAMESPACE::colorType color);
		void AppendFont(JCON_NAMESPACE::fontType font);
		void AppendText(JCON_NAMESPACE::textType text);

		JCON_NAMESPACE::segment* newSegment();

	protected:
		struct defaultValuesStruct {
			sf::Font Font;
			sf::Color Color = sf::Color::White;
			int characterSize = 14;
		} m_defaultValues;

		JCON_NAMESPACE::windowType* m_WindowContext;

	};

}
