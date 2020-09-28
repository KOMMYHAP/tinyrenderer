#include "Utils.h"

namespace Utils
{
	[[noreturn]] void OutOfRange(const char * msg)
	{
		Wusiko::Internal::DebugBreak();
		throw std::out_of_range(msg);
	}
	
	[[noreturn]] void OutOfRange(const string & msg)
	{
		Wusiko::Internal::DebugBreak();
		throw std::out_of_range(msg);
	}
}