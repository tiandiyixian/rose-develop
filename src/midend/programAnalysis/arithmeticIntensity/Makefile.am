# where to find rose and boost libraries 
include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

#DEBUG_LEVEL     = -g -O0
#EXTRA_CCFLAGS   = -Wall
#CXXFLAGS        = $(DEBUG_LEVEL) $(EXTRA_CCFLAGS)
#CCFLAGS         = $(CXXFLAGS)
# search path for .m4 macros
#ACLOCAL_AMFLAGS = -I ./config

AM_CPPFLAGS =  $(ROSE_INCLUDES) $(BOOST_CPPFLAGS)

noinst_LIBRARIES = libarithmeticMeasurement.a #libinstrumentor.a
libarithmeticMeasurement_la_SOURCES = ai_measurement.cpp
#libinstrumentor_a_SOURCES = instrumentor_lib.c

#include_HEADERS = ai_measurement.h

pkginclude_HEADERS = ai_measurement.h

EXTRA_DIST = CMakeLists.txt
