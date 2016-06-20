#include "logger.hpp"

Logger::Logger(vga::VGATerminal& term) : term(term) {}

Logger& Logger::operator()(enum Levels loglevel)
{
	if (term.getCursorPosition().y == 0) // @TODO : Avoid needing skipFirst?
		skipFirst = !skipFirst;
	
	if (skipFirst)
		term.putChar('\n');

	currentLevel = loglevel;
	size_t n = static_cast<size_t>(loglevel);
	
	uint8_t prevcolor = term.getColor();
	term.setColor(levelcolors[n]);
	term.putString(levelstrings[n]);
	
	term.setColor(prevcolor);
	term.putChar(' ');

	return *this;
}

Logger& Logger::operator<<(const char* cstring)
{
	term.putString(cstring);
	return *this;
}

const uint8_t Logger::levelcolors[] = {
	vga::VGATerminal::makeColor(vga::COLOR_LIGHT_GREEN),
	vga::VGATerminal::makeColor(vga::COLOR_GREEN),
	vga::VGATerminal::makeColor(vga::COLOR_RED),
	vga::VGATerminal::makeColor(vga::COLOR_LIGHT_BROWN),
	vga::VGATerminal::makeColor(vga::COLOR_DARK_GREY)};

const char* const Logger::levelstrings[] = {
	"[ ** ]",
	"[ OK ]",
	"[FAIL]",
	"[WARN]",
	"[INFO]"};
