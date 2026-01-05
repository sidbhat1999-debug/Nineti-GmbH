#ifndef WMBUS_JSON_H
#define WMBUS_JSON_H

#include <stddef.h>
#include "wmbus_model.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WMBUS_JSON_OK = 0,
    WMBUS_JSON_ERR_BUFFER_TOO_SMALL,
    WMBUS_JSON_ERR_INVALID_ARG
} wmbus_json_status_t;

wmbus_json_status_t wmbus_serialize_json(
    const wmbus_payload_t *payload,
    char *out_buffer,
    size_t buffer_size,
    size_t *bytes_written
);

#ifdef __cplusplus
}
#endif

#endif
