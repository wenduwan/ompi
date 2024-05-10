#
# Copyright (c) 2024      Amazon.com, Inc. or its affiliates.
#                         All Rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#

SUBDIRS = 3rd-party

noinst_LTLIBRARIES = libopalutil_json.la

libopalutil_json_la_SOURCES = \
	opal_json.h \
	opal_json.c

libopalutil_json_la_LIBADD = \
        3rd-party/libopalutil_json_3p.la

libopalutil_json_la_DEPENDENCIES = \
        3rd-party/libopalutil_json_3p.la
