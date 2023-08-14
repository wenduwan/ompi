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

#include "ompi/communicator/communicator.h"
#include "ompi/mca/pml/base/base.h"
#include "ompi/mca/pml/base/pml_base_bsend.h"
#include "ompi/mca/pml/base/pml_base_request.h"

#include "ompi/mca/pml/cm/pml_cm.h"
#include "ompi/mca/pml/ob1/pml_ob1.h"
#include "pml_topo.h"
#include "pml_topo_component.h"

static int pml_topo_enable(bool enable)
{
    int ret;

    ret = ompi_pml_cm.super.pml_enable(enable);
    ret = mca_pml_ob1.super.pml_enable(enable);

    return ret;
}

static int pml_topo_add_comm(ompi_communicator_t *comm)
{
    int ret;

    ret = ompi_pml_cm.super.pml_add_comm(comm);
    ret = mca_pml_ob1.super.pml_add_comm(comm);

    return ret;
}

static int pml_topo_del_comm(ompi_communicator_t *comm)
{
    /* notify the MTL about the deleted communicator */
    int ret;

    ret = ompi_pml_cm.super.pml_del_comm(comm);
    ret = mca_pml_ob1.super.pml_del_comm(comm);

    return ret;
}

static int pml_topo_add_procs(struct ompi_proc_t **procs, size_t nprocs)
{
    int ret;

    ret = ompi_pml_cm.super.pml_add_procs(procs, nprocs);
    ret = mca_pml_ob1.super.pml_add_procs(procs, nprocs);

    return ret;
}

static int pml_topo_del_procs(struct ompi_proc_t **procs, size_t nprocs)
{
    int ret;

    ret = ompi_pml_cm.super.pml_del_procs(procs, nprocs);
    ret = mca_pml_ob1.super.pml_del_procs(procs, nprocs);

    return ret;
}

/* print any available useful information from this communicator */
static int pml_topo_dump(struct ompi_communicator_t *comm, int verbose)
{
    return OMPI_ERR_NOT_IMPLEMENTED;
}

static inline bool is_local_peer(struct ompi_communicator_t *comm, int peer_id)
{
    ompi_proc_t *proc = ompi_comm_peer_lookup(comm, peer_id);
    if (!proc) {
        return false;
    }

    return OPAL_PROC_ON_LOCAL_NODE(proc->super.proc_flags);
}

static inline mca_pml_base_module_t *get_module(struct ompi_communicator_t *comm, int peer_id)
{
    if (is_local_peer(comm, peer_id)) {
        return &mca_pml_ob1.super;
    }

    return &ompi_pml_cm.super;
}

static int pml_topo_irecv_init(void *addr, size_t count, ompi_datatype_t *datatype, int src,
                               int tag, struct ompi_communicator_t *comm,
                               struct ompi_request_t **request)
{
    return get_module(comm, src)->pml_irecv_init(addr, count, datatype, src, tag, comm, request);
}

static int pml_topo_irecv(void *addr, size_t count, ompi_datatype_t *datatype, int src, int tag,
                          struct ompi_communicator_t *comm, struct ompi_request_t **request)
{
    return get_module(comm, src)->pml_irecv(addr, count, datatype, src, tag, comm, request);
}

static int pml_topo_imrecv(void *buf, size_t count, ompi_datatype_t *datatype,
                           struct ompi_message_t **message, struct ompi_request_t **request)
{
    return get_module((*message)->comm, (*message)->peer)
        ->pml_imrecv(buf, count, datatype, message, request);
}

static int pml_topo_mrecv(void *buf, size_t count, ompi_datatype_t *datatype,
                          struct ompi_message_t **message, ompi_status_public_t *status)
{
    return get_module((*message)->comm, (*message)->peer)
        ->pml_mrecv(buf, count, datatype, message, status);
}

static int pml_topo_recv(void *addr, size_t count, ompi_datatype_t *datatype, int src, int tag,
                         struct ompi_communicator_t *comm, ompi_status_public_t *status)
{
    return get_module(comm, src)->pml_recv(addr, count, datatype, src, tag, comm, status);
}

static int pml_topo_isend_init(const void *buf, size_t count, ompi_datatype_t *datatype, int dst,
                               int tag, mca_pml_base_send_mode_t sendmode,
                               ompi_communicator_t *comm, ompi_request_t **request)
{
    return get_module(comm, dst)->pml_isend_init(buf, count, datatype, dst, tag, sendmode, comm,
                                                 request);
}

static int pml_topo_isend(const void *buf, size_t count, ompi_datatype_t *datatype, int dst,
                          int tag, mca_pml_base_send_mode_t sendmode, ompi_communicator_t *comm,
                          ompi_request_t **request)
{
    return get_module(comm, dst)->pml_isend(buf, count, datatype, dst, tag, sendmode, comm,
                                            request);
}

static int pml_topo_send(const void *buf, size_t count, ompi_datatype_t *datatype, int dst, int tag,
                         mca_pml_base_send_mode_t sendmode, ompi_communicator_t *comm)
{
    return get_module(comm, dst)->pml_send(buf, count, datatype, dst, tag, sendmode, comm);
}

static int pml_topo_iprobe(int src, int tag, struct ompi_communicator_t *comm, int *matched,
                           ompi_status_public_t *status)
{
    return get_module(comm, src)->pml_iprobe(src, tag, comm, matched, status);
}

static int pml_topo_probe(int src, int tag, struct ompi_communicator_t *comm,
                          ompi_status_public_t *status)
{
    return get_module(comm, src)->pml_probe(src, tag, comm, status);
}

static int pml_topo_start(size_t count, ompi_request_t **requests)
{
    /* TODO */
    return OMPI_ERR_NOT_IMPLEMENTED;
}

static int pml_topo_improbe(int src, int tag, struct ompi_communicator_t *comm, int *matched,
                            struct ompi_message_t **message, ompi_status_public_t *status)
{
    return get_module(comm, src)->pml_improbe(src, tag, comm, matched, message, status);
}

static int pml_topo_mprobe(int src, int tag, struct ompi_communicator_t *comm,
                           struct ompi_message_t **message, ompi_status_public_t *status)
{
    return get_module(comm, src)->pml_mprobe(src, tag, comm, message, status);
}

ompi_pml_topo_t ompi_pml_topo = {{
    .pml_add_procs = pml_topo_add_procs,
    .pml_del_procs = pml_topo_del_procs,
    .pml_enable = pml_topo_enable,
    .pml_progress = NULL, /* No progress function. The MTL register their own */
    .pml_add_comm = pml_topo_add_comm,
    .pml_del_comm = pml_topo_del_comm,
    .pml_irecv_init = pml_topo_irecv_init,
    .pml_irecv = pml_topo_irecv,
    .pml_recv = pml_topo_recv,
    .pml_isend_init = pml_topo_isend_init,
    .pml_isend = pml_topo_isend,
    .pml_send = pml_topo_send,
    .pml_iprobe = pml_topo_iprobe,
    .pml_probe = pml_topo_probe,
    .pml_start = pml_topo_start,
    .pml_improbe = pml_topo_improbe,
    .pml_mprobe = pml_topo_mprobe,
    .pml_imrecv = pml_topo_imrecv,
    .pml_mrecv = pml_topo_mrecv,
    .pml_dump = pml_topo_dump,
    .pml_max_contextid = 65535,
    .pml_max_tag = INT_MAX,
    .pml_flags = 0 /* flags */
}};
