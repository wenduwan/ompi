/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) Amazon.com, Inc. or its affiliates. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#ifndef PML_TOPO_H
#define PML_TOPO_H

#include "ompi_config.h"
#include "ompi/communicator/communicator.h"
#include "ompi/datatype/ompi_datatype.h"
#include "ompi/mca/pml/base/base.h"
#include "ompi/mca/pml/pml.h"
#include "ompi/request/request.h"

#include "ompi/mca/pml/base/pml_base_recvreq.h"
#include "ompi/message/message.h"

BEGIN_C_DECLS

struct ompi_pml_topo_t {
    mca_pml_base_module_t super;
};
typedef struct ompi_pml_topo_t ompi_pml_topo_t;
extern ompi_pml_topo_t ompi_pml_topo;

END_C_DECLS

#endif /* PML_topo_H_HAS_BEEN_INCLUDED */
