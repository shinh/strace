/*
 * Check decoding of recvmsg and sendmsg syscalls.
 *
 * Copyright (c) 2016 Dmitry V. Levin <ldv@altlinux.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "tests.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/uio.h>

int
main(void)
{
	tprintf("%s", "");

	int fds[2];
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds))
		perror_msg_and_skip("socketpair");
	assert(0 == fds[0]);
	assert(1 == fds[1]);

	static const char w0_c[] = "012";
	const char *w0_d = hexdump_strdup(w0_c);
	void *w0 = tail_memdup(w0_c, LENGTH_OF(w0_c));

	static const char w1_c[] = "34567";
	const char *w1_d = hexdump_strdup(w1_c);
	void *w1 = tail_memdup(w1_c, LENGTH_OF(w1_c));

	static const char w2_c[] = "89abcde";
	const char *w2_d = hexdump_strdup(w2_c);
	void *w2 = tail_memdup(w2_c, LENGTH_OF(w2_c));

	static const char r0_c[] = "01234567";
	const char *r0_d = hexdump_strdup(r0_c);
	static const char r1_c[] = "89abcde";
	const char *r1_d = hexdump_strdup(r1_c);

	const struct iovec w_iov_[] = {
		{
			.iov_base = w0,
			.iov_len = LENGTH_OF(w0_c)
		}, {
			.iov_base = w1,
			.iov_len = LENGTH_OF(w1_c)
		}, {
			.iov_base = w2,
			.iov_len = LENGTH_OF(w2_c)
		}
	};
	struct iovec *w_iov = tail_memdup(w_iov_, sizeof(w_iov_));
	const unsigned int w_len =
		LENGTH_OF(w0_c) + LENGTH_OF(w1_c) + LENGTH_OF(w2_c);

	const struct msghdr w_mh_ = {
		.msg_iov = w_iov,
		.msg_iovlen = ARRAY_SIZE(w_iov_)
	};
	const struct msghdr *w_mh = tail_memdup(&w_mh_, sizeof(w_mh_));

	assert(sendmsg(1, w_mh, 0) == (int) w_len);
	close(1);
	tprintf("sendmsg(1, {msg_name(0)=NULL, msg_iov(%u)="
		"[{\"%s\", %u}, {\"%s\", %u}, {\"%s\", %u}]"
		", msg_controllen=0, msg_flags=0}, 0) = %u\n"
		" * %u bytes in buffer 0\n"
		" | 00000 %-49s  %-16s |\n"
		" * %u bytes in buffer 1\n"
		" | 00000 %-49s  %-16s |\n"
		" * %u bytes in buffer 2\n"
		" | 00000 %-49s  %-16s |\n",
		ARRAY_SIZE(w_iov_), w0_c, LENGTH_OF(w0_c),
		w1_c, LENGTH_OF(w1_c), w2_c, LENGTH_OF(w2_c), w_len,
		LENGTH_OF(w0_c), w0_d, w0_c, LENGTH_OF(w1_c), w1_d, w1_c,
		LENGTH_OF(w2_c), w2_d, w2_c);

	const unsigned int r_len = (w_len + 1) / 2;
	void *r0 = tail_alloc(r_len);
	const struct iovec r0_iov_[] = {
		{
			.iov_base = r0,
			.iov_len = r_len
		}
	};
	struct iovec *r_iov = tail_memdup(r0_iov_, sizeof(r0_iov_));

	const struct msghdr r_mh_ = {
		.msg_iov = r_iov,
		.msg_iovlen = ARRAY_SIZE(r0_iov_)
	};
	struct msghdr *r_mh = tail_memdup(&r_mh_, sizeof(r_mh_));

	assert(recvmsg(0, r_mh, 0) == (int) r_len);
	tprintf("recvmsg(0, {msg_name(0)=NULL, msg_iov(%u)="
		"[{\"%s\", %u}], msg_controllen=0, msg_flags=0}, 0) = %u\n"
		" * %u bytes in buffer 0\n"
		" | 00000 %-49s  %-16s |\n",
		ARRAY_SIZE(r0_iov_), r0_c, r_len, r_len, r_len, r0_d, r0_c);

	void *r1 = tail_alloc(r_len);
	void *r2 = tail_alloc(w_len);
	const struct iovec r1_iov_[] = {
		{
			.iov_base = r1,
			.iov_len = r_len
		},
		{
			.iov_base = r2,
			.iov_len = w_len
		}
	};
	r_iov = tail_memdup(r1_iov_, sizeof(r1_iov_));
	r_mh->msg_iov = r_iov;
	r_mh->msg_iovlen = ARRAY_SIZE(r1_iov_);

	assert(recvmsg(0, r_mh, 0) == (int) w_len - r_len);
	tprintf("recvmsg(0, {msg_name(0)=NULL, msg_iov(%u)="
		"[{\"%s\", %u}, {\"\", %u}], msg_controllen=0"
		", msg_flags=0}, 0) = %u\n"
		" * %u bytes in buffer 0\n"
		" | 00000 %-49s  %-16s |\n",
		ARRAY_SIZE(r1_iov_), r1_c, r_len, w_len, w_len - r_len,
		w_len - r_len, r1_d, r1_c);
	close(0);

	tprintf("+++ exited with 0 +++\n");
	return 0;
}
