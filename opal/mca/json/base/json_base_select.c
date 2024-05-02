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

#include <string.h>

#include "opal/class/opal_list.h"
#include "opal/constants.h"
#include "opal/mca/base/base.h"
#include "opal/mca/json/json.h"
#include "opal/mca/mca.h"
#include "opal/util/output.h"
#include "opal/util/proc.h"
#include "opal/util/show_help.h"

typedef struct json_list_item_t {
    opal_list_item_t super;
    opal_json_base_component_t *json_component;
    opal_json_base_module_t *json_module;
} json_list_item_t;

static void multiple_jsons_found_help_message(opal_list_t *components);

int opal_json_base_select(void)
{
    mca_base_component_list_item_t *cli = NULL;
    mca_base_component_t *skip = NULL;
    opal_json_base_component_t *component = NULL;
    opal_json_base_module_t *module = NULL;
    json_list_item_t *ali = NULL, *ali2 = NULL;
    opal_list_t ordered_list, initialized_list;
    opal_list_item_t *item = NULL;

    OBJ_CONSTRUCT(&ordered_list, opal_list_t);
    OBJ_CONSTRUCT(&initialized_list, opal_list_t);

    /* Traverse the list of available components and create a new ordered list with
       the NULL Component on the back of the new list */
    OPAL_LIST_FOREACH (cli, &opal_json_base_framework.framework_components,
                       mca_base_component_list_item_t) {
        ali = (json_list_item_t *) malloc(sizeof(json_list_item_t));
        if (NULL == ali) {
            return OPAL_ERR_OUT_OF_RESOURCE;
        }

        OBJ_CONSTRUCT(ali, opal_list_item_t);
        ali->json_component = (opal_json_base_component_t *) cli->cli_component;

        if (0 == strcmp(cli->cli_component->mca_component_name, "null")) {
            opal_list_append(&ordered_list, (opal_list_item_t *) ali);
        } else {
            opal_list_prepend(&ordered_list, (opal_list_item_t *) ali);
        }
    }

    /* Traverse the ordered list of available components and try and initialize every component.
     * Save all initialized components in initialized component list. */
    OPAL_LIST_FOREACH (ali, &ordered_list, json_list_item_t) {
        component = ali->json_component;
        if (NULL == component->json_init) {
            opal_output_verbose(10, opal_json_base_framework.framework_output,
                                "select: no init function; ignoring component %s",
                                component->base_version.mca_component_name);
            continue;
        }

        opal_output_verbose(10, opal_json_base_framework.framework_output,
                            "select: initializing %s component %s",
                            component->base_version.mca_type_name,
                            component->base_version.mca_component_name);

        module = component->json_init();

        if (NULL != module) {
            ali2 = (json_list_item_t *) malloc(sizeof(json_list_item_t));
            if (NULL == ali2) {
                return OPAL_ERR_OUT_OF_RESOURCE;
            }

            OBJ_CONSTRUCT(ali2, opal_list_item_t);

            ali2->json_component = ali->json_component;
            ali2->json_module = module;

            opal_list_append(&initialized_list, (opal_list_item_t *) ali2);
        }
    }

    /* There are four possible cases to handle:
     * 1. List empty, someone selected a component with --mca json <component> and it fails to
     * initialize
     * 2. There is 1 component in the list (NULL will always initialize, or someone selected a
     * component)
     * 3. There are 2 components in the list (User Defined, and NULL)
     * 4. There are 3+ components in the list (User Defined1, User Defined 2, ..., NULL)
     *
     * Case 1: Abort and show simple help message
     * Case 2 & 3 can be handled the same way by selecting the first component in the list
     * Case 4: Show help (with a string containing all initialized components) and abort
     */
    if (0 == initialized_list.opal_list_length) {
        opal_show_help("help-json-base.txt", "No jsons Found", true);
        /* leaks memory, but doesn't matter b/c ompi is aborting */
        return OPAL_ERR_FATAL;
    } else if (2 >= initialized_list.opal_list_length) {
        ali = (json_list_item_t *) opal_list_get_first(&initialized_list);
        opal_json_base_selected_component = *ali->json_component;
        skip = (mca_base_component_t *) ali->json_component;
        opal_json = *ali->json_module;
    } else {
        multiple_jsons_found_help_message(&initialized_list);
        /* leaks memory, but doesn't matter b/c ompi is aborting */
        return OPAL_ERR_FATAL;
    }

    opal_output_verbose(10, opal_json_base_framework.framework_output, "selected %s\n",
                        opal_json_base_selected_component.base_version.mca_component_name);

    /* This base function closes, unloads, and removes from the available list all
     * unselected components. The available list will contain only the selected component. */
    mca_base_framework_components_close(&opal_json_base_framework, skip);

    /* Cleanup Lists */
    for (item = opal_list_remove_first(&ordered_list); NULL != item;
         item = opal_list_remove_first(&ordered_list)) {
        OBJ_DESTRUCT(item);
        free(item);
    }

    for (item = opal_list_remove_first(&initialized_list); NULL != item;
         item = opal_list_remove_first(&initialized_list)) {
        OBJ_DESTRUCT(item);
        free(item);
    }

    OBJ_DESTRUCT(&ordered_list);
    OBJ_DESTRUCT(&initialized_list);

    return OPAL_SUCCESS;
}

static void multiple_jsons_found_help_message(opal_list_t *components)
{
    json_list_item_t *ali = NULL;
    int i = 0;
    int list_length = components->opal_list_length;
    /* NULL Terminator + Do not include NULL component in list */
    char *component_names = (char *) malloc(
        1 + ((list_length - 1) * MCA_BASE_MAX_COMPONENT_NAME_LEN));
    component_names[0] = '\0';

    OPAL_LIST_FOREACH (ali, components, json_list_item_t) {
        strcat(component_names, ali->json_component->base_version.mca_component_name);
        /* Do not include NULL component in list */
        if (++i == list_length - 1) {
            break;
        }
        strcat(component_names, ", ");
    }

    opal_show_help("help-json-base.txt", "Multiple jsons Found", true, component_names);
    free(component_names);
}
