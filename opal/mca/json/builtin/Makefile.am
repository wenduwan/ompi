#
# Copyright (c)           Amazon.com, Inc. or its affiliates.
#                         All Rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#


AM_CPPFLAGS = $(common_json_CPPFLAGS)
sources = \
        json.c \
        json.h \
        json_builtin.h \
        json_builtin_component.c

# Make the output library in this directory, and name it either
# mca_<type>_<name>.la (for DSO builds) or libmca_<type>_<name>.la
# (for static builds).

if MCA_BUILD_opal_json_builtin_DSO
component_noinst =
component_install = mca_json_builtin.la
else
component_noinst = libmca_json_builtin.la
component_install =
endif

mcacomponentdir = $(opallibdir)
mcacomponent_LTLIBRARIES = $(component_install)

mca_json_builtin_la_SOURCES = $(sources)
mca_json_builtin_la_LDFLAGS = -module -avoid-version $(json_builtin_LDFLAGS)
mca_json_builtin_la_LIBADD = $(top_builddir)/opal/lib@OPAL_LIB_NAME@.la \
        $(json_builtin_LIBS)

noinst_LTLIBRARIES = $(component_noinst)
libmca_json_builtin_la_SOURCES =$(sources)
libmca_json_builtin_la_LDFLAGS = -module -avoid-version $(json_builtin_LDFLAGS)
libmca_json_builtin_la_LIBADD = $(json_builtin_LIBS)
