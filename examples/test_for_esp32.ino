#include <Arduino.h>
#include "wmbus_json.h"

static char json_buffer[1024];

void setup() {
    Serial.begin(115200);
    delay(1000);

    wmbus_payload_t payload = {
        .gatewayId = "gateway_1234",
        .date = "1970-01-01",
        .deviceType = "stromleser",
        .interval_minutes = 15,
        .total_readings = 1,
        .values.device_count = 1
    };

    wmbus_device_t *dev = &payload.values.devices[0];
    snprintf(dev->media, sizeof(dev->media), "water");
    snprintf(dev->meter, sizeof(dev->meter), "waterstarm");
    snprintf(dev->deviceId, sizeof(dev->deviceId), "stromleser_50898527");
    snprintf(dev->unit, sizeof(dev->unit), "m3");

    dev->data_count = 1;
    snprintf(dev->data[0].timestamp, 17, "1970-01-01 00:00");
    snprintf(dev->data[0].meter_datetime, 17, "1970-01-01 00:00");
    dev->data[0].total_m3 = 107.752;
    snprintf(dev->data[0].status, 8, "OK");

    size_t written;
    wmbus_json_status_t status =
        wmbus_serialize_json(&payload, json_buffer, sizeof(json_buffer), &written);

    if (status == WMBUS_JSON_OK) {
        Serial.println(json_buffer);
    } else {
        Serial.println("JSON serialization failed");
    }
}

void loop() {
    // One-shot demo
}
