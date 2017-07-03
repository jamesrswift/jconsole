#include "public\accessor.h"
#include "public\console.hpp"

JCON_IMPL_ACCESSORFUNC(JCON_NAMESPACE::console, bool, m_Rebuilding, Rebuilding);
JCON_IMPL_ACCESSORFUNC(JCON_NAMESPACE::console, int, m_ScrollOffset, ScrollOffset);
JCON_IMPL_ACCESSORFUNC(JCON_NAMESPACE::console, bool, m_Scrolldown, ShouldScrollDown);
JCON_IMPL_ACCESSORFUNC(JCON_NAMESPACE::console, int, m_SideOffset, SideOffset);

JCON_NAMESPACE::console::console() {
	this->curX = 0;
	this->curY = 0;
	this->vPadding = 2;

	this->setRebuilding(false);
	this->setScrollOffset(0);
	this->setShouldScrollDown(false);
	this->setSideOffset(4);

	this->ContentBuffer.reserve(JCON_BUFFER_SIZE);
	this->ChildBuffer.reserve(JCON_BUFFER_SIZE);

	// Below is implied in declaration
	//this->SegmentBuffer.reserve(JCON_BUFFER_SIZE);
	//this->m_SegmentBuffer = JCON_NAMESPACE::segmentBuffer(JCON_BUFFER_SIZE);

	// Initialize default values
	defaultValues.Font.loadFromFile(JCON_DEFAULT_FONT);
}

void JCON_NAMESPACE::console::PerformLayout() {
	// All children will be rebuilt from content buffer
	this->ChildBuffer.clear();

	// Rebuild
	this->curX = 0;
	this->curY = 0;

	JCON_NAMESPACE::componentList ContentBufferCopy = this->ContentBuffer;
	this->ContentBuffer.clear();

	this->setRebuilding(true);
	for (JCON_NAMESPACE::component line : ContentBufferCopy) {
		this->AppendLine({ line });
	}
	// update scrollbar aswell
	this->setRebuilding(false);
}

void JCON_NAMESPACE::console::AppendLine(JCON_NAMESPACE::componentList insertion){
	for (JCON_NAMESPACE::component val : insertion) {
		ContentBuffer.push_back(val);
	}

	this->StartInsertion();

	for (JCON_NAMESPACE::component val : insertion) {
		switch (JCON_VARIANT_INDEX(val)) {
		case JCON_NAMESPACE::insertType::FONT:
			this->AppendFont(JCON_VARIANT_GET<JCON_NAMESPACE::fontType>(val));
			break;
		case JCON_NAMESPACE::insertType::COLOR:
			this->AppendColor(JCON_VARIANT_GET<JCON_NAMESPACE::colorType>(val));
			break;
		default:
		case JCON_NAMESPACE::insertType::TEXT:
			this->AppendText(JCON_VARIANT_GET<JCON_NAMESPACE::textType>(val));
			break;
		}
	}

	this->EndInsertion();

	if (this->ContentBuffer.size() > JCON_BUFFER_SIZE) {
		while (this->ContentBuffer.size() > JCON_BUFFER_SIZE) {
			this->ContentBuffer.erase(this->ContentBuffer.begin());
		}

		this->PerformLayout();
	}
}

void JCON_NAMESPACE::console::Paint() {

	for (std::function<JCON_NAMESPACE::ChildPaintType> child : this->ChildBuffer) {
		child(this->getScrollOffset());
	}
}

void JCON_NAMESPACE::console::setWindow(sf::RenderWindow* WindowContext) {
	this->m_WindowContext = WindowContext;
	this->Extent2D = this->m_WindowContext->getSize();
}

void JCON_NAMESPACE::console::StartInsertion() {
	this->curFont = this->defaultValues.Font;
	this->curColor = this->defaultValues.Color;
	this->curLineHeight = 0;

	this->setShouldScrollDown( /*this->ScrollBar->AtBottom() or*/ this->getRebuilding());
	this->m_SegmentBuffer.clear();
}

void JCON_NAMESPACE::console::EndInsertion() {

	int side_x_offset = this->getSideOffset();

	/*for (JCON_NAMESPACE::segment segment : this->SegmentBuffer) {*/

	this->m_SegmentBuffer.Iterate([=](JCON_NAMESPACE::segment* segment){

		// Paint function
		this->ChildBuffer.push_back([=](int yOffset){

			sf::Text text(segment->text, segment->font, this->defaultValues.characterSize);
			text.setFillColor(segment->color);
			text.setPosition(segment->x + side_x_offset, segment->y + yOffset);
			this->m_WindowContext->draw(text);
		});

	});

}

void JCON_NAMESPACE::console::AppendColor(JCON_NAMESPACE::colorType color) {
	this->curColor = color;
}

void JCON_NAMESPACE::console::AppendFont(JCON_NAMESPACE::fontType font) {
	this->curFont = font;
}

void JCON_NAMESPACE::console::AppendText(JCON_NAMESPACE::textType text) {
	if (text.length() == 0) return;
	
	/*
	unsigned int w = this->Extent2D.x;
	unsigned int h = this->Extent2D.y;

	// Adjust for scrollbar TODO

	sf::Text sizeTester;
	sizeTester.setFont(this->curFont);

	size_t lastSpace = 0;

	JCON_NAMESPACE::segment* newSegment = this->newSegment();

	for (auto character : text) {

		sizeTester.setString(character);
		sf::FloatRect characterSize = sizeTester.getLocalBounds();

		if ((this->curX + characterSize.width > w) | (character == '\n')) {

			if (character == '\n') {
				lastSpace = NULL;
				characterSize.height = characterSize.height / 2;
			}

			std::string carryOver;

			if (lastSpace > 0) {

				for (size_t i = lastSpace; i < newSegment->text.length(); i++) {
					carryOver += newSegment->text.at(i);
					newSegment->text.erase(i, 1);
				}

				lastSpace = 0;

			}

			this->curX = 0;
			this->curY += this->curLineHeight;

			JCON_NAMESPACE::segment* newSegmentSecond = this->newSegment();

			for (auto carryOverChar : carryOver) {

				sizeTester.setString(character);
				sf::FloatRect characterSize = sizeTester.getLocalBounds();
				characterSize.height += this->vPadding;

				if (characterSize.height > this->curLineHeight) {
					this->curLineHeight = characterSize.height;
				}

				this->curX += characterSize.width;

				newSegmentSecond->text += carryOverChar;
			}

		}

		if (character == ' ') {
			lastSpace = newSegment->text.length() + 1;
		}

		if ((character == '\n') | (character == '\r')) {
			continue;
		}

		if (characterSize.height > this->curLineHeight) {
			this->curLineHeight = characterSize.height;
		}

		this->curX += characterSize.width;

		newSegment->text += character;

	}
	*/
	sf::Text sizeTester( text, this->curFont, this->defaultValues.characterSize);
	sf::FloatRect characterSize = sizeTester.getLocalBounds();

	if (characterSize.height > this->curLineHeight) {
		this->curLineHeight = characterSize.height;
	}

	JCON_NAMESPACE::segment* newSegment = this->newSegment();
	newSegment->text = text;

	this->curX += characterSize.width;

	if (this->curX > this->Extent2D.x) {
		this->curX = 0;
		this->curY += this->curLineHeight;
	}

	//this->SegmentBufferpush_back(newSegment);
	
}

void JCON_NAMESPACE::console::HandleWindowOnResize(sf::Event* Event) {
	this->m_WindowContext->setView(sf::View(sf::FloatRect(0, 0, Event->size.width, Event->size.height)));
	this->Extent2D = this->m_WindowContext->getSize();
}

JCON_NAMESPACE::segment* JCON_NAMESPACE::console::newSegment(){
	
	JCON_NAMESPACE::segment newSegment;
	newSegment.x = this->curX;
	newSegment.y = this->curY;
	newSegment.text = "";
	newSegment.font = this->curFont;
	newSegment.color = this->curColor;
	newSegment.lineHeight = this->curLineHeight;

	//this->SegmentBuffer.push_back(newSegment);

	//return &this->SegmentBuffer.back();
	//return &(*(this->m_SegmentBuffer.end()));

	return this->m_SegmentBuffer.push_back(newSegment);
}