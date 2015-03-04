ifndef TOPDIR
TOPDIR=..
endif
include $(TOPDIR)/Makefile.global

TARGETS = check_float check_boolfind check_loan check_yesno check_ncmp check_hcmp check_sync3 check_lcmp yesno_checker ncmp_checker hcmp_checker sync3_checker lcmp_checker polynomial_checker runjury_fanfour2 runjury_fanfour3 runjury_fanfour4 runjury_boolfind runjury_spy runjury_spytwo compare runguard runpipe run_spy run_spytwo run_fanfour2 run_fanfour3 run_fanfour4 check_commonr

judgehost: build

config: judgedaemon printdaemon

build: $(TARGETS)

judgedaemon: judgedaemon.in $(TOPDIR)/paths.mk
	$(substconfigvars)
	chmod a+x $@

printdaemon: printdaemon.in $(TOPDIR)/paths.mk
	$(substconfigvars)
	chmod a+x $@

compare: $(LIBOBJECTS)
compare$(OBJEXT): $(LIBHEADERS)

check_float: -lm $(LIBOBJECTS)
check_float$(OBJEXT): -lm $(LIBHEADERS)

runguard: -lm $(LIBCGROUP)
runguard: CFLAGS += -std=c99
runguard$(OBJEXT): $(TOPDIR)/etc/runguard-config.h

# FIXME: compile with diet libc to produce a static binary which is
# not 0.6 MB (!) in size?
runpipe: runpipe.c $(LIBHEADERS) $(LIBSOURCES)
	$(CC) $(CFLAGS) -static -o $@ $< $(LIBSOURCES)

runjury_boolfind: runjury_boolfind.c
	$(CC) $(CFLAGS) -static -o $@ $<

polynomial_checker: polynomial_checker.cpp
	$(CXX) $(CXXFLAGS) -static -o $@ $<

yesno_checker: yesno_checker.cpp
	$(CXX) $(CXXFLAGS) -static -o $@ $<

ncmp_checker: ncmp_checker.cpp
	$(CXX) $(CXXFLAGS) -static -o $@ $<

hcmp_checker: hcmp_checker.cpp
	$(CXX) $(CXXFLAGS) -static -o $@ $<

lcmp_checker: lcmp_checker.cpp
	$(CXX) $(CXXFLAGS) -static -o $@ $<

sync3_checker: sync3_checker.cpp
	$(CXX) $(CXXFLAGS) -static -o $@ $<

runjury_fanfour2: runjury_fanfour2.cpp
	$(CXX) $(CXXFLAGS) -static -o $@ $<

runjury_fanfour3: runjury_fanfour3.cpp
	$(CXX) $(CXXFLAGS) -static -o $@ $<

runjury_fanfour4: runjury_fanfour4.cpp
	$(CXX) $(CXXFLAGS) -static -o $@ $<

install-judgehost:
	$(INSTALL_PROG) -t $(DESTDIR)$(judgehost_libjudgedir) \
		compile*.sh testcase_run.sh chroot-startstop.sh \
		run run_fanfour2 run_fanfour3 run_fanfour4 run_wrapper run_boolfind run_spy run_spytwo runjury_boolfind runjury_fanfour2 runjury_fanfour3 runjury_fanfour4 runjury_spytwo runjury_spy \
		compare compare_commonr compare_wrapper compare_loan compare_float compare_boolfind compare_yesno compare_ncmp compare_hcmp compare_sync3 compare_lcmp \
		check_diff.sh check_float check_loan check_commonr polynomial_checker check_boolfind sh-static \
                check_yesno check_ncmp check_hcmp check_lcmp check_sync3 yesno_checker ncmp_checker hcmp_checker lcmp_checker sync3_checker
	$(INSTALL_DATA) -t $(DESTDIR)$(judgehost_libjudgedir) parse_result.xslt \
		judgedaemon.main.php printdaemon.main.php
	$(INSTALL_PROG) -t $(DESTDIR)$(judgehost_bindir) judgedaemon printdaemon
	$(INSTALL_PROG) -t $(DESTDIR)$(judgehost_bindir) runguard runpipe

clean-l:
	-rm -f $(TARGETS) $(TARGETS:%=%$(OBJEXT))

distclean-l:
	-rm -f judgedaemon
	-rm -f printdaemon
