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

#ifndef MCA_JSON_BASE_H
#define MCA_JSON_BASE_H

#include "opal_config.h"

#include "opal/mca/base/mca_base_framework.h"
#include "opal/mca/json/json.h"
#include "opal/mca/mca.h"

BEGIN_C_DECLS

OPAL_DECLSPEC extern mca_base_framework_t opal_json_base_framework;

/**
 * Select an json module
 */
OPAL_DECLSPEC int opal_json_base_select(void);

OPAL_DECLSPEC extern opal_json_base_component_t opal_json_base_selected_component;

END_C_DECLS

#endif
