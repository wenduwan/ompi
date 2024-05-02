/*
 * Copyright (c)           Amazon.com, Inc. or its affiliates.
 *                         All Rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */
/** @file:
 */
#ifndef OPAL_json_H
#define OPAL_json_H

#include "opal/class/opal_object.h"
#include "opal/mca/mca.h"

BEGIN_C_DECLS

typedef struct {
} opal_json_base_module_t;

typedef opal_json_base_module_t *(*mca_json_base_component_init_fn_t)(void);

typedef void (*mca_json_base_component_fini_fn_t)(void);
typedef struct {
    mca_base_component_t base_version;
    mca_base_component_data_t base_data;
    mca_json_base_component_init_fn_t json_init;
    mca_json_base_component_fini_fn_t json_finalize;
} opal_json_base_component_t;

#define OPAL_JSON_BASE_VERSION_1_0_0 OPAL_MCA_BASE_VERSION_2_1_0("json", 1, 0, 0)

OPAL_DECLSPEC extern opal_json_base_module_t opal_json;

END_C_DECLS

#endif