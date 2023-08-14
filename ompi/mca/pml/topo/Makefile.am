#
# Copyright (c) Amazon.com, Inc. or its affiliates. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#

# Make the output library in this directory, and name it either
# mca_<type>_<name>.la (for DSO builds) or libmca_<type>_<name>.la
# (for static builds).

EXTRA_DIST = post_configure.sh

if MCA_BUILD_ompi_pml_topo_DSO
component_noinst =
component_install = mca_pml_topo.la
else
component_noinst = libmca_pml_topo.la
component_install =
endif

local_sources = \
	pml_topo.c \
	pml_topo.h \
	pml_topo_component.c \
	pml_topo_component.h

mcacomponentdir = $(ompilibdir)
mcacomponent_LTLIBRARIES = $(component_install)
mca_pml_topo_la_SOURCES = $(local_sources)
mca_pml_topo_la_LIBADD = $(top_builddir)/ompi/lib@OMPI_LIBMPI_NAME@.la \
	$(pml_topo_LIBS)
mca_pml_topo_la_LDFLAGS = -module -avoid-version $(pml_topo_LDFLAGS)

noinst_LTLIBRARIES = $(component_noinst)
libmca_pml_topo_la_SOURCES = $(local_sources)
libmca_pml_topo_la_LIBADD = $(pml_topo_LIBS)
libmca_pml_topo_la_LDFLAGS = -module -avoid-version $(pml_topo_LDFLAGS)
