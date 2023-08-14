/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) Amazon.com, Inc. or its affiliates. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#include "ompi_config.h"

#include "opal/util/event.h"
#include "pml_topo.h"

#include "ompi/mca/pml/cm/pml_cm_component.h"
#include "ompi/mca/pml/ob1/pml_ob1_component.h"
#include "pml_topo_component.h"

static int mca_pml_topo_component_register(void);
static int mca_pml_topo_component_open(void);
static int mca_pml_topo_component_close(void);
static mca_pml_base_module_t* mca_pml_topo_component_init( int* priority,
                            bool enable_progress_threads, bool enable_mpi_threads);
static int mca_pml_topo_component_fini(void);

mca_pml_base_component_2_1_0_t mca_pml_topo_component = {
    /* First, the mca_base_component_t struct containing meta
     * information about the component itself */

    .pmlm_version = {
        MCA_PML_BASE_VERSION_2_1_0,

        .mca_component_name = "topo",
        MCA_BASE_MAKE_VERSION(component, OMPI_MAJOR_VERSION, OMPI_MINOR_VERSION,
                              OMPI_RELEASE_VERSION),
        .mca_open_component = mca_pml_topo_component_open,
        .mca_close_component = mca_pml_topo_component_close,
        .mca_register_component_params = mca_pml_topo_component_register,
    },
    .pmlm_data = {
        /* This component is not checkpoint ready */
        MCA_BASE_METADATA_PARAM_NONE
    },

    .pmlm_init = mca_pml_topo_component_init,
    .pmlm_finalize = mca_pml_topo_component_fini,
};

static int
mca_pml_topo_component_register(void)
{
    return OMPI_SUCCESS;
}

static int
mca_pml_topo_component_open(void)
{
    return OMPI_SUCCESS;
}


static int
mca_pml_topo_component_close(void)
{
    int ret;

    ret = mca_pml_cm_component.pmlm_version.mca_close_component();
    ret = mca_pml_ob1_component.pmlm_version.mca_close_component();

    return ret;
}


static mca_pml_base_module_t*
mca_pml_topo_component_init(int* priority,
                          bool enable_progress_threads,
                          bool enable_mpi_threads)
{
    *priority = 100;

    return &ompi_pml_topo.super;
}


static int
mca_pml_topo_component_fini(void)
{
    mca_pml_cm_component.pmlm_finalize();
    mca_pml_ob1_component.pmlm_finalize();
    return OMPI_SUCCESS;
}
