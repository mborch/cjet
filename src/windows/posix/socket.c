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

#include <io.h>
#include <errno.h>
#include <winsock2.h>
#include <malloc.h>

#include "compiler.h"
#include "socket.h"


ssize_t socket_read(socket_type sock, void *buf, size_t count)
{
	ssize_t recv_len = SOCKET_ERROR;

	if (likely(count > 0))
	{
		recv_len = recv(sock, buf, count, 0);
		if (recv_len == SOCKET_ERROR && (WSAGetLastError() == WSAEWOULDBLOCK))
		{
			errno = EWOULDBLOCK;
		}
	}

	return recv_len;
}


ssize_t socket_writev(socket_type sock, struct socket_io_vector *io_vec, size_t count)
{
	DWORD send_len = -1;

	if (likely(count > 0))
	{
		WSABUF *buf = alloca(count * sizeof(WSABUF));
		for (unsigned int i = 0; i < count; i++)
		{
			buf[i].buf = (CHAR *)io_vec[i].iov_base;
			buf[i].len = io_vec[i].iov_len;
		}

		if (WSASend(sock, buf, sizeof(buf) / sizeof(WSABUF), &send_len, 0, NULL, NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				errno = EWOULDBLOCK;
			}

			send_len = -1;
		}
	}

	printf("\n");
	printf("%d", send_len);
	printf("\n");
	
	return send_len;
}


int socket_close(socket_type sock)
{
	return closesocket(sock);
}
