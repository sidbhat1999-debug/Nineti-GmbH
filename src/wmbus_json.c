#include <stdio.h>
#include "wmbus_json.h"

#define APPEND(fmt, ...)                                                      \
    do {                                                                      \
        int n = snprintf(out + pos, size - pos, fmt, ##__VA_ARGS__);           \
        if (n < 0 || (size_t)n >= size - pos)                                 \
            return WMBUS_JSON_ERR_BUFFER_TOO_SMALL;                            \
        pos += (size_t)n;                                                     \
    } while (0)

wmbus_json_status_t wmbus_serialize_json(
    const wmbus_payload_t *p,
    char *out,
    size_t size,
    size_t *written)
{
    if (!p || !out || size == 0)
        return WMBUS_JSON_ERR_INVALID_ARG;

    size_t pos = 0;

    APPEND("[{");
    APPEND("\"gatewayId\":\"%s\",", p->gatewayId);
    APPEND("\"date\":\"%s\",", p->date);
    APPEND("\"deviceType\":\"%s\",", p->deviceType);
    APPEND("\"interval_minutes\":%u,", p->interval_minutes);
    APPEND("\"total_readings\":%u,", p->total_readings);

    APPEND("\"values\":{");
    APPEND("\"device_count\":%u,", p->values.device_count);
    APPEND("\"readings\":[");

    for (uint8_t i = 0; i < p->values.device_count; i++) {
        wmbus_device_t *d = &p->values.devices[i];

        APPEND("{");
        APPEND("\"media\":\"%s\",", d->media);
        APPEND("\"meter\":\"%s\",", d->meter);
        APPEND("\"deviceId\":\"%s\",", d->deviceId);
        APPEND("\"unit\":\"%s\",", d->unit);
        APPEND("\"data\":[");

        for (uint8_t j = 0; j < d->data_count; j++) {
            wmbus_data_point_t *dp = &d->data[j];
            APPEND("{");
            APPEND("\"timestamp\":\"%s\",", dp->timestamp);
            APPEND("\"meter_datetime\":\"%s\",", dp->meter_datetime);
            APPEND("\"total_m3\":%.3f,", dp->total_m3);
            APPEND("\"status\":\"%s\"}", dp->status);
            if (j + 1 < d->data_count) APPEND(",");
        }

        APPEND("]}");
        if (i + 1 < p->values.device_count) APPEND(",");
    }

    APPEND("]}}]");
    if (written) *written = pos;

    return WMBUS_JSON_OK;
}
