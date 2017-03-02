/* *****************************************************************
*
* Copyright 2016 Microsoft
*
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************/

#include <stddef.h>
#include <memory.h>

#include "memmem.h"


void *memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen)
{
	/*
	if (needleLen == 0)
	{
	return (void *)haystack;
	}

	if (haystackLen >= needleLen)
	{
	for (size_t i = 0; i <= haystackLen - needleLen; i++)
	{
	if (memcmp(needle, ((char *)haystack) + i, needleLen) == 0)
	{
	return ((char *)haystack) + i;
	}
	}
	}

	return NULL;
	*/

	// Sanity check
	if (needlelen > haystacklen) return NULL;

	// Void is useless -- we must treat our data as bytes (== unsigned chars)
	typedef const unsigned char* p;

	// We'll stop searching at the last possible position for a match, 
	// which is haystack[ haystacklen - needlelen + 1 ]
	haystacklen -= needlelen - 1;

	while (haystacklen)
	{
		// Find the first byte in a potential match
		p z = memchr((p)haystack, *(p)needle, haystacklen);
		if (!z) return NULL;

		// Is there enough space for there to actually be a match?
		ptrdiff_t delta = z - (p)haystack;
		ptrdiff_t remaining = (ptrdiff_t)haystacklen - delta;
		if (remaining < 1) return NULL;

		// Advance our pointer and update the amount of haystack remaining
		haystacklen -= delta;
		haystack = z;

		// Did we find a match?
		if (!memcmp(haystack, needle, needlelen))
			return (void*)haystack;

		// Ready for next loop
		haystack = (p)haystack + 1;
		haystacklen -= 1;
	}
	return NULL;
}