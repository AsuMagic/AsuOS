#ifndef HTERMINAL
#define HTERMINAL

#include <stdint.h>
#include "../module/module.hpp"
#include "../common/vec.hpp"

// Generic terminal driver class
template<typename pixT>
class TerminalDriver : public Module
{
public:
	void putString(const char* cstring)
	{
		int i = -1; // @TODO : avoid doing this, use size_t too
		while (cstring[++i] != 0) // != end of string character.
			putChar(cstring[i]);

		updateCursor();
	}

	virtual void putChar(char character) = 0;

	virtual void setCursorPosition(vec2u newposition) = 0;
	virtual void updateCursor() = 0; // Not done by setCursorPosition.
	virtual vec2u getCursorPosition() const = 0;

	virtual pixT* getFramebuffer() const = 0;
};

#endif