#pragma once
#include <SFML/Graphics.hpp>
#include "public\accessor.h"
#include <string>
#include <vector>
#include <functional>

#ifndef JCON_NAMESPACE
#define JCON_NAMESPACE jconsole
#endif

#ifndef JCON_BUFFER_SIZE
#define JCON_BUFFER_SIZE 255
#endif

#ifndef JCON_DEFAULT_FONT
#define JCON_DEFAULT_FONT "Consolas.ttf"
#endif

#if __cplusplus == 201703L
#include <variant>
#define JCON_VARIANT std::variant
#define JCON_VARIANT_GET std::get
#define JCON_VARIANT_INDEX(x) x.index()
#else
#include <boost/variant.hpp>
#define JCON_VARIANT boost::variant
#define JCON_VARIANT_GET boost::get
#define JCON_VARIANT_INDEX(x) x.which()
#endif // __cplusplus == 201703L

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

	struct segment {
		float x;
		float y;
		JCON_NAMESPACE::textType text;
		JCON_NAMESPACE::fontType font;
		JCON_NAMESPACE::colorType color;
		float lineHeight;
	};

	typedef JCON_VARIANT<JCON_NAMESPACE::textType, JCON_NAMESPACE::fontType, JCON_NAMESPACE::colorType> component;
	typedef std::vector<JCON_NAMESPACE::component> componentList;

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

	private:
		JCON_NAMESPACE::componentList ContentBuffer;
		std::vector<std::function<ChildPaintType>> ChildBuffer;
		std::vector<JCON_NAMESPACE::segment> SegmentBuffer;

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

		void HandleWindowOnResize();
		JCON_NAMESPACE::segment newSegment();

	protected:
		struct defaultValuesStruct {
			sf::Font Font;
			sf::Color Color = sf::Color::White;
			int characterSize = 14;
		} defaultValues;

		sf::RenderWindow* m_WindowContext;

	};

}