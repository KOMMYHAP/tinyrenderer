#include "basicdefs.h"

namespace Wusiko::Internal
{
	// You can use link below to implement portable __debugbreak() analog:
	// https://stackoverflow.com/questions/173618/is-there-a-portable-equivalent-to-debugbreak-debugbreak
#pragma optimize("", off)
	void DebugBreak()
	{
#ifdef _DEBUG
		__debugbreak();
#else
		// set breakpoint on next line:
		int _a = 42;
#endif
	}
#pragma optimize("", on)
	
	void Assert(
		[[maybe_unused]] const bool value,
		[[maybe_unused]] const char * file,
		[[maybe_unused]] const unsigned line,
		[[maybe_unused]] const string & msg)
	{
#ifndef WUSIKO_IS_PRODUCTION
		if (!value)
		{
			DebugBreak();
			if (msg.empty())
			{
				std::cerr << "Assertion failed!" << std::endl;
			}
			else
			{
				std::cerr << file << ":" << line << " " << msg << std::endl;
			}
		}
#endif
	}
}
