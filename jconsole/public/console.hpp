#pragma once

#include "public\accessor.h"
#include "public\types.hpp"
#include "public\segment.hpp"
#include "public\component.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>


namespace JCON_NAMESPACE {

	class console {
		JCON_DEF_ACCESSORFUNC(bool, m_Rebuilding,	Rebuilding);
		JCON_DEF_ACCESSORFUNC(int, m_ScrollOffset, ScrollOffset);
		JCON_DEF_ACCESSORFUNC(bool,	m_Scrolldown,	ShouldScrollDown);
		JCON_DEF_ACCESSORFUNC(int, m_SideOffset,	SideOffset);

	public:
		console();
		void PerformLayout();
		void AppendLine(componentList insertion);
		void Paint();

		void setWindow(sf::RenderWindow* WindowContext);
		void HandleWindowOnResize(sf::Event* Event);

	private:
		JCON_NAMESPACE::componentList ContentBuffer;
		std::vector<std::function<ChildPaintType>> ChildBuffer;
		//std::vector<JCON_NAMESPACE::segment> SegmentBuffer;
		JCON_NAMESPACE::segmentBuffer m_SegmentBuffer;

		extent2DType Extent2D;
		float curX = 0;
		float curY = 0;
		float vPadding = 2;

		JCON_NAMESPACE::fontType curFont;
		JCON_NAMESPACE::colorType curColor;
		float curLineHeight;

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
		} defaultValues;

		sf::RenderWindow* m_WindowContext;

	};

}