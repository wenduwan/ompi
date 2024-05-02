/*
 * Copyright (c) 2014      Intel, Inc.  All rights reserved.
 * Copyright (c) 2017-2022 Amazon.com, Inc. or its affiliates.
 *                         All Rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#ifndef MCA_JSON_BUILTIN_H
#define MCA_JSON_BUILTIN_H

#include "opal_config.h"

#include "opal/mca/json/json.h"

BEGIN_C_DECLS

typedef struct {
    opal_json_base_component_t super;
} opal_json_builtin_component_t;


OPAL_DECLSPEC extern opal_json_builtin_component_t mca_json_builtin_component;
OPAL_DECLSPEC extern opal_json_base_module_t opal_json_builtin_module;

END_C_DECLS

#endif /* MCA_JSON_BUILTIN_H */
