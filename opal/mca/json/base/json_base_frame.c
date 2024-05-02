/*
 * Copyright (c)           Amazon.com, Inc. or its affiliates.
 *                         All Rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#include "opal_config.h"

#include "opal/constants.h"
#include "opal/mca/base/base.h"
#include "opal/mca/json/base/base.h"
#include "opal/mca/mca.h"

/*
 * The following file was created by configure.  It contains extern
 * components and the definition of an array of pointers to each
 * module's public mca_base_module_t struct.
 */
#include "opal/mca/json/base/static-components.h"

opal_json_base_module_t opal_json = {0};
opal_json_base_component_t opal_json_base_selected_component = {{0}};

static int opal_json_base_frame_register(mca_base_register_flag_t flags)
{
    return OPAL_SUCCESS;
}

static int opal_json_base_frame_close(void)
{
    return mca_base_framework_components_close(&opal_json_base_framework, NULL);
}

static int opal_json_base_frame_open(mca_base_open_flag_t flags)
{
    return mca_base_framework_components_open(&opal_json_base_framework, flags);
}

OBJ_CLASS_INSTANCE(, opal_object_t, NULL, NULL);

MCA_BASE_FRAMEWORK_DECLARE(opal, json, "OPAL JSON Framework", opal_json_base_frame_register,
                           opal_json_base_frame_open, opal_json_base_frame_close,
                           mca_json_base_static_components, 0);
