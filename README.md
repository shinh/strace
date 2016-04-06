This strace runs faster when you use it with some syscall filters.

    $ time sh -c "find . -name '*.mk' | xargs grep foobar > /dev/null"
    sh -c "find . -name '*.mk' | xargs grep foobar > /dev/null"  0.66s user 1.22s system 101% cpu 1.847 total
    $ time strace -f -of -efile sh -c "find . -name '*.mk' | xargs grep foobar > /dev/null"
    strace -f -of -efile sh -c   7.36s user 56.84s system 117% cpu 54.548 total
    $ time ~/wrk/strace/strace -f -of -efile sh -c "find . -name '*.mk' | xargs grep foobar > /dev/null"
    ~/wrk/strace/strace -f -of -efile sh -c   6.33s user 37.47s system 115% cpu 37.891 total

TODO:

* strace without -f is broken (tests/dumpio.test).
* create a testcase which takes forever with vanila strace.
* handle non-x86_64 cases.
* autotoolize

The original README.md follows:

This is [strace](http://strace.io) -- a diagnostic, debugging and instructional userspace utility for Linux.  It is used to monitor interactions between processes and the Linux kernel, which include system calls, signal deliveries, and changes of process state.  The operation of strace is made possible by the kernel feature known as [ptrace](http://man7.org/linux/man-pages/man2/ptrace.2.html).

strace is released under a Berkeley-style license at the request of Paul Kranenburg; see the file [COPYING](https://raw.githubusercontent.com/strace/strace/master/COPYING) for details.

See the file [NEWS](https://raw.githubusercontent.com/strace/strace/master/NEWS) for information on what has changed in recent versions.

Please send bug reports and enhancements to [the strace mailing list](https://lists.sourceforge.net/lists/listinfo/strace-devel).

[![Build Status](https://travis-ci.org/strace/strace.svg?branch=master)](https://travis-ci.org/strace/strace) [![Code Coverage](https://codecov.io/github/strace/strace/coverage.svg?branch=master)](https://codecov.io/github/strace/strace?branch=master)
