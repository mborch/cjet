/*
 *The MIT License (MIT)
 *
 * Copyright (c) <2017> <Stephan Gatzka and Mathieu Borchardt>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stddef.h>
#include <string.h>

#include "compiler.h"
#include "jet_string.h"

const char *jet_strcasestr(const char *haystack, const char *needle)
{
	char* p1 = (char*)haystack;
	const char* p2 = needle;
	char* r = *p2 == 0 ? (char*)haystack : 0;

	while (*p1 != 0 && *p2 != 0)
	{
		if (tolower(*p1) == tolower(*p2))
		{
			if (r == 0)
			{
				r = p1;
			}

			p2++;
		}
		else
		{
			p2 = needle;
			if (tolower(*p1) == tolower(*p2))
			{
				r = p1;
				p2++;
			}
			else
			{
				r = 0;
			}
		}

		p1++;
	}

	return *p2 == 0 ? r : 0;
}

void *jet_memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen)
{
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

int jet_strcasecmp(const char *s1, const char *s2)
{
	return _stricmp(s1, s2);
}

int jet_strncasecmp(const char *s1, const char *s2, size_t n)
{
	return _strnicmp(s1, s2, n);
}

char *duplicate_string(const char *s)
{
	char *ptr = cjet_malloc(strlen(s) + 1);
	if (unlikely(ptr == NULL)) {
		return NULL;
	}

	strcpy(ptr, s);
	return ptr;
}
