## Process this file with automake to create Makefile.in
include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

## Add bugs to this line as they are fixed so that they can be used as test problems
## At least we should not reintroduce these fixed bugs again later.
# TESTCODES = \
#      test2001_11.C \
#      test2001_01.C \
#      test2001_02.C \
#      test2001_03.C \
#      test2001_04.C \
#      test2001_05.C \
#      test2001_06.C \
#      test2001_07.C \
#      test2001_08.C \
#      test2001_09.C \
#      test2001_10.C \
#      test2001_14.C \
#      test2001_15.C \
#      test2001_17.C \
#      test2001_18.C \
#      test2001_19.C \
#      test2001_20.C \
#      test2001_21.C \
#      test2001_22.C \
#      test_treeTrav_MK_01.C \
#      test_treeTrav_MK_02.C

TESTCODES = \
13.3.3.1.4.cc\
13.3.3.2d.cc\
7.3.3g.cc\
7.3.3j.cc\
13.3.3.2a.cc\
13.3.3b.cc\
3.4.5.cc\
7.3.1.cc\
7.3.3e.cc\
7.3.3h.cc\
7.3.4c.cc\
13.3.3.2b.cc\
13.cc\
7.3.3i.cc\
7.3.4a.cc

# DQ (9/4/2005): Generated code with name qualification 
# "namespace std { template<> struct std::X < int > }" 
# not allowed in g++ 3.4.3 (test commented out for now).
# There are still several cases like this so that the 
# code generation within ROSE will not pass with 3.4.x
# at present.
#    test2005_81.C
#    test2005_93.C

# DQ (7/27/2005): Example generates instanatiations for template static data members (redifinition error)
#    test2005_69.C

# DQ (9/10/2005): This code fails with 3.4.x, but passes with 3.3.x
#    test2005_98.C

# DQ (7/25/2005): Example which breaks g++ 3.4.3 (from Peter), also breaks ROSE :-)
#    test2005_115.C

# This demonstrates a bug in g++ (ROSE can't handle it until g++ can handle it)
#    test2005_151.C

# DQ (6/30/2005): Removed to compile Kull (submitted by Jeremiah Willcock)
#    test2005_85.C (Duff's Device)

# Moved to explicit rule below so that we could include -I<pythonDir>
#     test2005_18.C
#     test2005_54.C
#     test2005_24.C
#     test2004_62.C 
#     test2004_63.C 
#     test2004_41.C

# This is now an explicit makefile rule (so that we can use the -rose:C_only option)
#     test2004_21.C
#     test2004_21.c 

# This fails since it uses old style C and must be compiled in a file with *.c (instead of *.C)
#      test2004_20.C

# These require special options and have specific makefile rules
#     test2004_22.C
#     test2004_30.C
#     test2004_41.C

# DQ (8/8/2005): requires use od Python.h not included in ROSE distribution
#     test2004_92.C

# Build the list of object files
TEST_Objects = ${TESTCODES:.cc=.o}

# Restrict to level 6 testing for the moment
#ROSE_FLAGS = -rose:test 6
ROSE_FLAGS = 

ROSE_VERBOSE = -rose:verbose
# ROSE_VERBOSE =

C_ONLY = -rose:C_only
# C_ONLY =

TRANSLATOR_EXECUTABLE = $(top_builddir)/tests/nonsmoke/functional/testTranslator 
TEST_TRANSLATOR = $(TRANSLATOR_EXECUTABLE) $(ROSE_FLAGS)

## Include the path to A++ and the transformation specification
TESTCODE_INCLUDES = -I$(top_srcdir)/tests/nonsmoke/functional/CompileTests/A++Code -I$(srcdir) 
# check-local:
#	@echo "ROSE Test Codes."
#  Run this test explicitly since it has to be run using a specific rule and can't be lumped with the rest
#	@$(MAKE) test2004_21.o
#	@$(MAKE) test2004_22.o
#	@$(MAKE) test2004_30.o
#	@$(MAKE) test2004_41.o
#	@$(MAKE) $(TEST_Objects)

$(TEST_Objects): $(TESTCODES)
	$(TEST_TRANSLATOR) $(AM_CPPFLAGS) $(TESTCODE_INCLUDES) -c $(srcdir)/$(@:.o=.cc)

EXTRA_DIST = \
      $(TESTCODES)

clean-local:
	rm -f C/*.o *.o C/rose_*.c rose_*.C rose_*.c rose_*.cc *.sage.C test2001_??.C.show *.dot *.ps \
              *.C.pdf *.C.edg.pdf *.pdf *.int.C core test2005_56
	rm -rf ti_files *.ti *.et

check-local: $(TRANSLATOR_EXECUTABLE) 
	@$(MAKE) $(TEST_Objects)
	@$(MAKE) $(TEST2_Objects)
	@echo "*********************************************************************************************"
	@echo "****** ROSE/tests/nonsmoke/functional/CompileTests/C++Code: make check rule complete (terminated normally) ******"
	@echo "*********************************************************************************************"



