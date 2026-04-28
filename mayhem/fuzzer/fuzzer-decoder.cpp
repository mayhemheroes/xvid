#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cstdio>

extern "C" {
#include "xvid.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    xvid_gbl_init_t xvid_gbl_init;
    memset(&xvid_gbl_init, 0, sizeof(xvid_gbl_init));
    xvid_gbl_init.version = XVID_VERSION;
    xvid_global(NULL, XVID_GBL_INIT, &xvid_gbl_init, NULL);

    xvid_dec_create_t create;
    memset(&create, 0, sizeof(create));
    create.version = XVID_VERSION;
    create.width = 0;
    create.height = 0;

    void *handle = NULL;
    if (xvid_decore(NULL, XVID_DEC_CREATE, &create, NULL) != 0) {
        return 0;
    }
    handle = create.handle;

    xvid_dec_frame_t frame;
    xvid_dec_stats_t stats;
    memset(&frame, 0, sizeof(frame));
    memset(&stats, 0, sizeof(stats));
    frame.version = XVID_VERSION;
    stats.version = XVID_VERSION;
    frame.bitstream = (void*)data;
    frame.length = (int)size;
    frame.output.csp = XVID_CSP_NULL;

    xvid_decore(handle, XVID_DEC_DECODE, &frame, &stats);

    xvid_decore(handle, XVID_DEC_DESTROY, NULL, NULL);
    return 0;
}
