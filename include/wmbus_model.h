#ifndef WMBUS_MODEL_H
#define WMBUS_MODEL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_DEVICES        4
#define MAX_DATA_POINTS    8
typedef struct {
    char timestamp[17];          // "YYYY-MM-DD HH:MM"
    char meter_datetime[17];     // "YYYY-MM-DD HH:MM"
    double total_m3;
    char status[8];              // "OK", "ERR"
} wmbus_data_point_t;

typedef struct {
    char media[16];
    char meter[16];
    char deviceId[32];
    char unit[8];

    uint8_t data_count;
    wmbus_data_point_t data[MAX_DATA_POINTS];
} wmbus_device_t;

typedef struct {
    uint8_t device_count;
    wmbus_device_t devices[MAX_DEVICES];
} wmbus_values_t;

typedef struct {
    char gatewayId[32];
    char date[11];               // YYYY-MM-DD
    char deviceType[16];
    uint16_t interval_minutes;
    uint16_t total_readings;

    wmbus_values_t values;
} wmbus_payload_t;

#ifdef __cplusplus
}
#endif

#endif
