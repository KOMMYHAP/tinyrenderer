#pragma once

namespace Utils
{
	[[noreturn]] void OutOfRange(const char * msg);
	[[noreturn]] void OutOfRange(const string & msg);
}
