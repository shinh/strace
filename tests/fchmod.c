/*
 * Copyright (c) 2016 Fabien Siron <fabien.siron@epita.fr>
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
#include <sys/syscall.h>

#if defined __NR_fchmod

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int
main(void)
{
	static const char fname[] = "fchmod_test_file";

	int fd = open(fname, O_CREAT|O_RDONLY, 0400);

	if (fd == -1)
		perror_msg_and_fail("open");

	if (unlink(fname) == -1)
		perror_msg_and_fail("unlink");

	if (syscall(__NR_fchmod, fd, 0600) == 0) {
		close(fd);

		printf("fchmod(%d, 0600) = 0\n", fd);

		if (syscall(__NR_fchmod, fd, 0600) != -1)
			perror_msg_and_fail("fchmod");

		printf("fchmod(%d, 0600) = -1 EBADF (%m)\n", fd);
	} else {
		if (errno == ENOSYS) {
			printf("fchmod(%d, 0600) = -1 ENOSYS (%m)\n", fd);
		} else {
			perror_msg_and_fail("fchmod");
		}
	}

	puts("+++ exited with 0 +++");
	return 0;
}

#else

SKIP_MAIN_UNDEFINED("__NR_fchmod")

#endif
