# Automake input for strace tests.
#
# Copyright (c) 2011-2016 Dmitry V. Levin <ldv@altlinux.org>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

OS = linux
ARCH = @arch@
MPERS_NAME =
ARCH_MFLAGS =
AM_CFLAGS = $(WARN_CFLAGS)
AM_CPPFLAGS = $(ARCH_MFLAGS) \
	      -I$(builddir) \
	      -I$(top_builddir)/$(OS)/$(ARCH) \
	      -I$(top_srcdir)/$(OS)/$(ARCH) \
	      -I$(top_builddir)/$(OS) \
	      -I$(top_srcdir)/$(OS) \
	      -I$(top_builddir) \
	      -I$(top_srcdir)
AM_LDFLAGS = $(ARCH_MFLAGS)

libtests_a_SOURCES = \
	error_msg.c \
	get_page_size.c \
	hexdump_strdup.c \
	hexquote_strndup.c \
	inode_of_sockfd.c \
	print_quoted_string.c \
	tail_alloc.c \
	tests.h \
	tprintf.c \
	# end of libtests_a_SOURCES
libtests_a_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
check_LIBRARIES = libtests.a
LDADD = libtests.a

check_PROGRAMS = \
	_newselect \
	acct \
	adjtimex \
	aio \
	alarm \
	attach-f-p \
	attach-p-cmd-cmd \
	attach-p-cmd-p \
	bpf \
	caps \
	chmod \
	chroot \
	clock_nanosleep \
	clock_xettime \
	copy_file_range \
	count-f \
	creat \
	dup \
	dup2 \
	dup3 \
	epoll_create1 \
	eventfd \
	execve \
	execve-v \
	execveat \
	execveat-v \
	faccessat \
	fanotify_mark \
	fchmod \
	fchmodat \
	fchownat \
	fcntl \
	fcntl64 \
	fdatasync \
	file_handle \
	filter-unavailable \
	flock \
	fork-f \
	fstat \
	fstat64 \
	fstatat64 \
	fsync \
	ftruncate \
	ftruncate64 \
	getcwd \
	getdents \
	getdents64 \
	getrandom \
	getrusage \
	getxxid \
	inet-cmsg \
	ioctl \
	ip_mreq \
	ipc_msg \
	ipc_msgbuf \
	ipc_sem \
	ipc_shm \
	ksysent \
	linkat \
	llseek \
	lseek \
	lstat \
	lstat64 \
	membarrier \
	memfd_create \
	mincore \
	mkdirat \
	mknod \
	mlock2 \
	mmap \
	mmap64 \
	mmsg \
	mq \
	nanosleep \
	net-accept-connect \
	net-y-unix \
	net-yy-inet \
	net-yy-unix \
	netlink_inet_diag \
	netlink_unix_diag \
	newfstatat \
	oldselect \
	open \
	openat \
	pc \
	personality \
	pipe \
	poll \
	ppoll \
	pread64-pwrite64 \
	preadv \
	preadv-pwritev \
	pselect6 \
	pwritev \
	read-write \
	readdir \
	readlink \
	readlinkat \
	readv \
	recvmsg \
	rename \
	renameat\
	restart_syscall \
	rt_sigpending \
	rt_sigprocmask \
	rt_sigqueueinfo \
	rt_sigsuspend \
	rt_sigtimedwait \
	rt_tgsigqueueinfo \
	sched_get_priority_mxx \
	sched_xetaffinity \
	sched_xetattr \
	sched_xetparam \
	sched_xetscheduler \
	scm_rights \
	seccomp \
	select \
	sendfile \
	sendfile64 \
	set_ptracer_any \
	sethostname \
	sigaction \
	sigaltstack \
	signalfd \
	sigreturn \
	splice \
	stack-fcall \
	sleep \
	stat \
	stat64 \
	statfs \
	swap \
	sync_file_range \
	sync_file_range2 \
	sysinfo \
	syslog \
	tee \
	time \
	timer_create \
	timer_xettime \
	timerfd_xettime \
	times \
	times-fail \
	truncate \
	truncate64 \
	uid \
	uid16 \
	uid32 \
	uio \
	umask \
	umount \
	umount2 \
	umovestr \
	umovestr2 \
	uname \
	unlinkat \
	unix-pair-send-recv \
	userfaultfd \
	utime \
	utimensat \
	vfork-f \
	vmsplice \
	wait \
	xattr \
	xet_robust_list \
	xetitimer \
	xetpgid \
	xetpriority \
	xettimeofday \
	# end of check_PROGRAMS

attach_f_p_LDADD = -lrt -lpthread $(LDADD)
clock_xettime_LDADD = -lrt $(LDADD)
count_f_LDADD = -lpthread $(LDADD)
filter_unavailable_LDADD = -lpthread $(LDADD)
fstat64_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
fstatat64_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
ftruncate64_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
lstat64_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
mmap64_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
mq_LDADD = -lrt $(LDADD)
newfstatat_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
pc_LDADD = $(dl_LIBS) $(LDADD)
pread64_pwrite64_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
preadv_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
preadv_pwritev_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
pwritev_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
stat64_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
statfs_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
times_LDADD = -lrt $(LDADD)
truncate64_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64
uio_CPPFLAGS = $(AM_CPPFLAGS) -D_FILE_OFFSET_BITS=64

stack_fcall_SOURCES = stack-fcall.c \
	stack-fcall-0.c stack-fcall-1.c stack-fcall-2.c stack-fcall-3.c

if USE_LIBUNWIND
LIBUNWIND_TESTS = strace-k.test
else
LIBUNWIND_TESTS =
endif

DECODER_TESTS = \
	_newselect.test \
	acct.test \
	adjtimex.test \
	aio.test \
	alarm.test \
	bpf.test \
	caps.test \
	chmod.test \
	chroot.test \
	clock_nanosleep.test \
	clock_xettime.test \
	copy_file_range.test \
	creat.test \
	dup.test \
	dup2.test \
	dup3.test \
	epoll_create1.test \
	eventfd.test \
	execve.test \
	execve-v.test \
	execveat.test \
	execveat-v.test \
	faccessat.test \
	fanotify_mark.test \
	fchmod.test \
	fchmodat.test \
	fchownat.test \
	fcntl.test \
	fcntl64.test \
	fdatasync.test \
	file_handle.test \
	flock.test \
	fstat.test \
	fstat64.test \
	fstatat64.test \
	fsync.test \
	ftruncate.test \
	ftruncate64.test \
	getcwd.test \
	getdents.test \
	getdents64.test \
	getrandom.test \
	getrusage.test \
	getxxid.test \
	inet-cmsg.test \
	ioctl.test \
	ip_mreq.test \
	ipc_msg.test \
	ipc_msgbuf.test \
	ipc_sem.test \
	ipc_shm.test \
	linkat.test \
	llseek.test \
	lseek.test \
	lstat.test \
	lstat64.test \
	membarrier.test \
	memfd_create.test \
	mincore.test \
	mkdirat.test \
	mknod.test \
	mlock2.test \
	mmap.test \
	mmap64.test \
	mmsg.test \
	mq.test \
	nanosleep.test \
	net-y-unix.test \
	net-yy-inet.test \
	net-yy-unix.test \
	net.test \
	newfstatat.test \
	oldselect.test \
	open.test \
	openat.test \
	personality.test \
	pipe.test \
	poll.test \
	ppoll.test \
	pread64-pwrite64.test \
	preadv.test \
	preadv-pwritev.test \
	pselect6.test \
	pwritev.test \
	read-write.test \
	readdir.test \
	readlink.test \
	readlinkat.test \
	readv.test \
	recvmsg.test \
	rename.test \
	renameat.test \
	rt_sigpending.test \
	rt_sigprocmask.test \
	rt_sigqueueinfo.test \
	rt_sigsuspend.test \
	rt_sigtimedwait.test \
	rt_tgsigqueueinfo.test \
	sched_get_priority_mxx.test \
	sched_xetaffinity.test \
	sched_xetattr.test \
	sched_xetparam.test \
	sched_xetscheduler.test \
	scm_rights-fd.test \
	seccomp.test \
	select.test \
	sendfile.test \
	sendfile64.test \
	sethostname.test \
	sigaction.test \
	sigaltstack.test \
	signalfd.test \
	sigreturn.test \
	splice.test \
	stat.test \
	stat64.test \
	statfs.test \
	sun_path.test \
	swap.test \
	sync_file_range.test \
	sync_file_range2.test \
	sysinfo.test \
	syslog.test \
	tee.test \
	time.test \
	timer_create.test \
	timer_xettime.test \
	timerfd_xettime.test \
	times-fail.test \
	times.test \
	truncate.test \
	truncate64.test \
	uid.test \
	uid16.test \
	uid32.test \
	uio.test \
	umask.test \
	umount.test \
	umount2.test \
	umovestr.test \
	umovestr2.test \
	uname.test \
	unlinkat.test \
	userfaultfd.test \
	utime.test \
	utimensat.test \
	vmsplice.test \
	wait.test \
	xattr.test \
	xet_robust_list.test \
	xetitimer.test \
	xetpgid.test \
	xetpriority.test \
	xettimeofday.test \
	# end of DECODER_TESTS

MISC_TESTS = \
	attach-f-p.test \
	attach-p-cmd.test \
	bexecve.test \
	count-f.test \
	count.test \
	detach-running.test \
	detach-sleeping.test \
	detach-stopped.test \
	dumpio.test \
	filter-unavailable.test \
	fork-f.test \
	ksysent.test \
	opipe.test \
	pc.test \
	qual_syscall.test \
	redirect.test \
	restart_syscall.test \
	strace-T.test \
	strace-f.test \
	strace-r.test \
	strace-t.test \
	strace-tt.test \
	strace-ttt.test \
	vfork-f.test \
	# end of MISC_TESTS

TESTS = $(DECODER_TESTS) $(MISC_TESTS) $(LIBUNWIND_TESTS)

XFAIL_TESTS_ =
XFAIL_TESTS_m32 = $(LIBUNWIND_TESTS)
XFAIL_TESTS_mx32 = $(LIBUNWIND_TESTS)
XFAIL_TESTS = $(XFAIL_TESTS_$(MPERS_NAME))

TEST_LOG_COMPILER = env
AM_TEST_LOG_FLAGS = STRACE_ARCH=$(ARCH) $(srcdir)/run.sh

EXTRA_DIST = init.sh run.sh match.awk \
	     caps.awk \
	     count-f.expected \
	     dumpio.expected \
	     eventfd.expected \
	     fanotify_mark.expected \
	     filter-unavailable.expected \
	     fstatat.c \
	     fstatx.c \
	     ip_mreq.expected \
	     ipc.sh \
	     ipc_msgbuf.expected \
	     ksysent.sed \
	     lstatx.c \
	     memfd_create.expected \
	     mq.expected \
	     net.expected \
	     oldselect.expected \
	     pipe.expected \
	     ppoll.expected \
	     ppoll-v.expected \
	     sigaction.awk \
	     sigaltstack.expected \
	     signalfd.expected \
	     statfs.expected \
	     statx.sh \
	     strace-T.expected \
	     strace-r.expected \
	     struct_flock.c \
	     sun_path.expected \
	     uid.awk \
	     uio.expected \
	     umovestr.expected \
	     wait.expected \
	     xattr.expected \
	     xselect.c \
	     xstatx.c \
	     $(TESTS)

ksysent.h: $(srcdir)/ksysent.sed
	echo '#include <asm/unistd.h>' | \
		$(CPP) $(AM_CPPFLAGS) $(CPPFLAGS) -dM - > $@.t1
	LC_COLLATE=C sed -n -f $(srcdir)/ksysent.sed < $@.t1 > $@.t2
	mv -f $@.t2 $@
	rm -f $@.t1

BUILT_SOURCES = ksysent.h
CLEANFILES = ksysent.h $(TESTS:=.tmp)
