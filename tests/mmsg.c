/*
 * Copyright (c) 2014 Masatake YAMATO <yamato@redhat.com>
 * Copyright (c) 2014-2016 Dmitry V. Levin <ldv@altlinux.org>
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
# include <sys/syscall.h>

#if (defined __NR_sendmmsg || defined HAVE_SENDMMSG) \
 && (defined __NR_recvmmsg || defined HAVE_RECVMMSG)

# include <assert.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/socket.h>

# ifndef HAVE_STRUCT_MMSGHDR
struct mmsghdr {
	struct msghdr msg_hdr;
	unsigned msg_len;
};
# endif

static int
send_mmsg(int fd, struct mmsghdr *vec, unsigned int vlen, unsigned int flags)
{
	int rc;
#ifdef __NR_sendmmsg
	rc = syscall(__NR_sendmmsg, (long) fd, vec, (unsigned long) vlen,
		     (unsigned long) flags);
	if (rc >= 0 || ENOSYS != errno)
		return rc;
	tprintf("sendmmsg(%d, %p, %u, MSG_DONTROUTE|MSG_NOSIGNAL)"
		" = -1 ENOSYS (%m)\n", fd, vec, vlen);
#endif
#ifdef HAVE_SENDMMSG
	rc = sendmmsg(fd, vec, vlen, flags);
#endif
	return rc;
}

static int
recv_mmsg(int fd, struct mmsghdr *vec, unsigned int vlen, unsigned int flags,
	  struct timespec *timeout)
{
	int rc;
#ifdef __NR_recvmmsg
	rc = syscall(__NR_recvmmsg, (long) fd, vec, (unsigned long) vlen,
		     (unsigned long) flags, timeout);
	if (rc >= 0 || ENOSYS != errno)
		return rc;
	tprintf("recvmmsg(%d, %p, %u, MSG_DONTWAIT, NULL)"
		" = -1 ENOSYS (%m)\n", fd, vec, vlen);
#endif
#ifdef HAVE_RECVMMSG
	rc = recvmmsg(fd, vec, vlen, flags, timeout);
#endif
	return rc;
}

int
main(void)
{
	tprintf("%s", "");

	int fds[2];
	if (socketpair(AF_UNIX, SOCK_DGRAM, 0, fds))
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

	const struct iovec w0_iov_[] = {
		{
			.iov_base = w0,
			.iov_len = LENGTH_OF(w0_c)
		}, {
			.iov_base = w1,
			.iov_len = LENGTH_OF(w1_c)
		}
	};
	struct iovec *w0_iov = tail_memdup(w0_iov_, sizeof(w0_iov_));

	const struct iovec w1_iov_[] = {
		{
			.iov_base = w2,
			.iov_len = LENGTH_OF(w2_c)
		}
	};
	struct iovec *w1_iov = tail_memdup(w1_iov_, sizeof(w1_iov_));

	const struct mmsghdr w_mmh_[] = {
		{
			.msg_hdr = {
				.msg_iov = w0_iov,
				.msg_iovlen = ARRAY_SIZE(w0_iov_),
			}
		}, {
			.msg_hdr = {
				.msg_iov = w1_iov,
				.msg_iovlen = ARRAY_SIZE(w1_iov_),
			}
		}
	};
	void *w_mmh = tail_memdup(w_mmh_, sizeof(w_mmh_));
	const unsigned int n_w_mmh = ARRAY_SIZE(w_mmh_);

	int r = send_mmsg(1, w_mmh, n_w_mmh, MSG_DONTROUTE | MSG_NOSIGNAL);
	if (r < 0 && errno == ENOSYS)
		perror_msg_and_skip("sendmmsg");
	assert(r == (int) n_w_mmh);
	assert(close(1) == 0);
	tprintf("sendmmsg(1, {{{msg_name(0)=NULL, msg_iov(%u)=[{\"%s\", %u}"
		", {\"%s\", %u}], msg_controllen=0, msg_flags=0}, %u}"
		", {{msg_name(0)=NULL, msg_iov(%u)=[{\"%s\", %u}]"
		", msg_controllen=0, msg_flags=0}, %u}}, %u"
		", MSG_DONTROUTE|MSG_NOSIGNAL) = %d\n"
		" = %u buffers in vector 0\n"
		" * %u bytes in buffer 0\n"
		" | 00000 %-49s  %-16s |\n"
		" * %u bytes in buffer 1\n"
		" | 00000 %-49s  %-16s |\n"
		" = %u buffers in vector 1\n"
		" * %u bytes in buffer 0\n"
		" | 00000 %-49s  %-16s |\n",
		ARRAY_SIZE(w0_iov_), w0_c, LENGTH_OF(w0_c),
		w1_c, LENGTH_OF(w1_c),
		LENGTH_OF(w0_c) + LENGTH_OF(w1_c),
		ARRAY_SIZE(w1_iov_), w2_c, LENGTH_OF(w2_c), LENGTH_OF(w2_c),
		n_w_mmh, r,
		ARRAY_SIZE(w0_iov_), LENGTH_OF(w0_c), w0_d, w0_c,
		LENGTH_OF(w1_c), w1_d, w1_c,
		ARRAY_SIZE(w1_iov_), LENGTH_OF(w2_c), w2_d, w2_c);

	const unsigned int w_len =
		LENGTH_OF(w0_c) + LENGTH_OF(w1_c) + LENGTH_OF(w2_c);
	const unsigned int r_len = (w_len + 1) / 2;
	void *r0 = tail_alloc(r_len);
	void *r1 = tail_alloc(r_len);
	void *r2 = tail_alloc(r_len);
	const struct iovec r0_iov_[] = {
		{
			.iov_base = r0,
			.iov_len = r_len
		}
	};
	struct iovec *r0_iov = tail_memdup(r0_iov_, sizeof(r0_iov_));
	const struct iovec r1_iov_[] = {
		{
			.iov_base = r1,
			.iov_len = r_len
		},
		{
			.iov_base = r2,
			.iov_len = r_len
		}
	};
	struct iovec *r1_iov = tail_memdup(r1_iov_, sizeof(r1_iov_));

	const struct mmsghdr r_mmh_[] = {
		{
			.msg_hdr = {
				.msg_iov = r0_iov,
				.msg_iovlen = ARRAY_SIZE(r0_iov_),
			}
		}, {
			.msg_hdr = {
				.msg_iov = r1_iov,
				.msg_iovlen = ARRAY_SIZE(r1_iov_),
			}
		}
	};
	void *r_mmh = tail_memdup(r_mmh_, sizeof(r_mmh_));
	const unsigned int n_r_mmh = ARRAY_SIZE(r_mmh_);

	static const char r0_c[] = "01234567";
	const char *r0_d = hexdump_strdup(r0_c);
	static const char r1_c[] = "89abcde";
	const char *r1_d = hexdump_strdup(r1_c);

	assert(recv_mmsg(0, r_mmh, n_r_mmh, MSG_DONTWAIT, NULL) == (int) n_r_mmh);
	assert(close(0) == 0);
	tprintf("recvmmsg(0, {{{msg_name(0)=NULL, msg_iov(%u)=[{\"%s\", %u}]"
		", msg_controllen=0, msg_flags=0}, %u}"
		", {{msg_name(0)=NULL, msg_iov(%u)=[{\"%s\", %u}, {\"\", %u}]"
		", msg_controllen=0, msg_flags=0}, %u}}, %u"
		", MSG_DONTWAIT, NULL) = %d (left NULL)\n"
		" = %u buffers in vector 0\n"
		" * %u bytes in buffer 0\n"
		" | 00000 %-49s  %-16s |\n"
		" = %u buffers in vector 1\n"
		" * %u bytes in buffer 0\n"
		" | 00000 %-49s  %-16s |\n",
		ARRAY_SIZE(r0_iov_), r0_c, r_len, LENGTH_OF(r0_c),
		ARRAY_SIZE(r1_iov_), r1_c, r_len, r_len, LENGTH_OF(r1_c),
		n_r_mmh, r,
		ARRAY_SIZE(r0_iov_), LENGTH_OF(r0_c), r0_d, r0_c,
		ARRAY_SIZE(r1_iov_), LENGTH_OF(r1_c), r1_d, r1_c);

	tprintf("+++ exited with 0 +++\n");
	return 0;
}

#else

SKIP_MAIN_UNDEFINED("(__NR_sendmmsg || HAVE_SENDMMSG) && (__NR_recvmmsg || HAVE_RECVMMSG)")

#endif
