/*
 * Copyright (c) 2015-2016 Dmitry V. Levin <ldv@altlinux.org>
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
#include <fcntl.h>

#ifdef MAX_HANDLE_SZ

# include <alloca.h>
# include <assert.h>
# include <errno.h>
# include <stdio.h>

int
main(void)
{
	struct file_handle *handle =
		alloca(sizeof(struct file_handle) + MAX_HANDLE_SZ);
	const int dirfd = AT_FDCWD;
	const int flags = AT_SYMLINK_FOLLOW;
	int mount_id;
	unsigned int i;

	handle->handle_bytes = 0;

	assert(name_to_handle_at(dirfd, ".", handle, &mount_id, flags | 1) == -1);
	if (EINVAL != errno)
		perror_msg_and_skip("name_to_handle_at");
	printf("name_to_handle_at(AT_FDCWD, \".\", {handle_bytes=0}, %p"
	       ", AT_SYMLINK_FOLLOW|0x1) = -1 EINVAL (%m)\n", &mount_id);

	assert(name_to_handle_at(dirfd, ".", handle, &mount_id, flags) == -1);
	if (EOVERFLOW != errno)
		perror_msg_and_skip("name_to_handle_at");
	printf("name_to_handle_at(AT_FDCWD, \".\", {handle_bytes=0 => %u}"
	       ", %p, AT_SYMLINK_FOLLOW) = -1 EOVERFLOW (%m)\n",
	       handle->handle_bytes, &mount_id);

	assert(name_to_handle_at(dirfd, ".", handle, &mount_id, flags) == 0);
	printf("name_to_handle_at(AT_FDCWD, \".\", {handle_bytes=%u"
	       ", handle_type=%d, f_handle=0x",
	       handle->handle_bytes, handle->handle_type);
	for (i = 0; i < handle->handle_bytes; ++i)
		printf("%02x", handle->f_handle[i]);
	printf("}, [%d], AT_SYMLINK_FOLLOW) = 0\n", mount_id);

	printf("open_by_handle_at(-1, {handle_bytes=%u, handle_type=%d"
	       ", f_handle=0x", handle->handle_bytes, handle->handle_type);
	for (i = 0; i < handle->handle_bytes; ++i)
		printf("%02x", handle->f_handle[i]);
	printf("}, O_RDONLY|O_DIRECTORY) = -1 ");
	assert(open_by_handle_at(-1, handle, O_RDONLY | O_DIRECTORY) == -1);
	const char *errno_text;
	switch (errno) {
		case EPERM:
			errno_text = "EPERM";
			break;
		case EINVAL:
			errno_text = "EINVAL";
			break;
		default:
			errno_text = "EBADF";
	}
	printf("%s (%m)\n", errno_text);

	puts("+++ exited with 0 +++");
	return 0;
}

#else

SKIP_MAIN_UNDEFINED("MAX_HANDLE_SZ")

#endif
