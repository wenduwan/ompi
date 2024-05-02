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

#include "opal_config.h"

#include "json_builtin.h"
#include "opal/mca/dl/base/base.h"
#include "opal/mca/json/base/base.h"
#include "opal/runtime/opal_params.h"
#include "opal/sys/atomic.h"
#include "opal/util/argv.h"
#include "opal/util/printf.h"
#include "opal/util/proc.h"
#include "opal/util/show_help.h"

const char *opal_json_builtin_component_version_string
    = "OPAL builtin JSON MCA component version " OPAL_VERSION;

/*
 * Local function
 */
static int json_builtin_open(void);
static int json_builtin_close(void);
static int json_builtin_component_register(void);
static opal_json_base_module_t *json_builtin_init(void);
static void json_builtin_finalize(opal_json_base_module_t *module);
/*
 * Instantiate the public struct with all of our public information
 * and pointers to our public functions in it
 */

opal_json_builtin_component_t mca_json_builtin_component = {{

    /* First, the mca_component_t struct containing meta information
     * about the component itself */

    .base_version =
        {
            /* Indicate that we are a json v1.1.0 component (which also
             * implies a specific MCA version) */

            OPAL_JSON_BASE_VERSION_1_0_0,

            /* Component name and version */

            .mca_component_name = "builtin",
            MCA_BASE_MAKE_VERSION(component, OPAL_MAJOR_VERSION, OPAL_MINOR_VERSION,
                                  OPAL_RELEASE_VERSION),

            /* Component open and close functions */

            .mca_open_component = json_builtin_open,
            .mca_close_component = json_builtin_close,
            .mca_register_component_params = json_builtin_component_register,

        },
    /* Next the MCA v1.0.0 component meta data */
    .base_data =
        { /* The component is checkpoint ready */
         MCA_BASE_METADATA_PARAM_CHECKPOINT},
    .json_init = json_builtin_init,
    .json_finalize = json_builtin_finalize,
}};

static int json_builtin_open(void)
{
    /* construct the component fields */
    return OPAL_SUCCESS;
}

static int json_builtin_close(void)
{
    return OPAL_SUCCESS;
}

static int json_builtin_component_register(void)
{
    return OPAL_SUCCESS;
}

static opal_json_base_module_t *json_builtin_init(void)
{
    return &opal_json_builtin_module;
}

static void json_builtin_finalize(opal_json_base_module_t *module)
{
    return;
}
