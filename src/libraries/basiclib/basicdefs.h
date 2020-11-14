#pragma once

#include "stdheaders.h"

namespace Wusiko::Internal
{
	void DebugBreak();
	void Assert(const char * file, unsigned line, const string & msg = {});
}

#ifndef WUSIKO_IS_PRODUCTION
	#define WUSIKO_ASSERT(x) \
		x ? ((void)0) : Wusiko::Internal::Assert(__FILE__, __LINE__, #x);

	#define WUSIKO_ASSERT_MSG(x, msg) \
		x ? ((void)0) : Wusiko::Internal::Assert(__FILE__, __LINE__, msg);
#else
	#define WUSIKO_ASSERT(x) ((void)0)

	#define WUSIKO_ASSERT_MSG(x, msg) ((void)0)
#endif
