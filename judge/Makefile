ifndef TOPDIR
TOPDIR=..
endif
include $(TOPDIR)/Makefile.global

TARGETS = check_float check_boolfind runjury_boolfind compare runguard runpipe check_arith check_newyear check_sliding

judgehost: build

config: judgedaemon printdaemon

build: $(TARGETS)

check_sliding:
	chmod a+x check_sliding_puzzle

judgedaemon: judgedaemon.in $(TOPDIR)/paths.mk
	$(substconfigvars)
	chmod a+x $@

printdaemon: printdaemon.in $(TOPDIR)/paths.mk
	$(substconfigvars)
	chmod a+x $@

compare: $(LIBOBJECTS)
compare$(OBJEXT): $(LIBHEADERS)

check_float: -lm

runguard: -lm
runguard$(OBJEXT): $(TOPDIR)/etc/runguard-config.h

# FIXME: compile with diet libc to produce a static binary which is
# not 0.6 MB (!) in size?
runpipe: runpipe.c $(LIBHEADERS) $(LIBSOURCES)
	$(CC) $(CFLAGS) -static -o $@ $< $(LIBSOURCES)

runjury_boolfind: runjury_boolfind.c
	$(CC) $(CFLAGS) -static -o $@ $<

install-judgehost:
	$(INSTALL_PROG) -t $(DESTDIR)$(judgehost_libjudgedir) \
		compile*.sh testcase_run.sh chroot-startstop.sh \
		run run_wrapper run_boolfind runjury_boolfind \
		compare compare_wrapper compare_float compare_boolfind \
		check_diff.sh check_float check_boolfind sh-static \
                check_sliding_puzzle check_arith check_newyear \
                compare_sliding_puzzle compare_arith compare_newyear
	$(INSTALL_DATA) -t $(DESTDIR)$(judgehost_libjudgedir) parse_result.xslt \
		judgedaemon.main.php printdaemon.main.php
	$(INSTALL_PROG) -t $(DESTDIR)$(judgehost_bindir) judgedaemon printdaemon
	$(INSTALL_PROG) -t $(DESTDIR)$(judgehost_bindir) runguard runpipe
	#$(INSTALL_DATA) -t $(DESTDIR)$(judgehost_libjudgedir) \
		#libraries/*.c libraries/*.cpp libraries/*.h libraries/*.hpp \
		#libraries/*.java

clean-l:
	-rm -f $(TARGETS) $(TARGETS:%=%$(OBJEXT))

distclean-l:
	-rm -f judgedaemon
