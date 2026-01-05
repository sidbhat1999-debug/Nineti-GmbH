# JSON Serialization Library for w-M-Bus–Related Firmware

## Project Overview
This project implements an embedded-friendly C library that serializes structured
meter data into a predefined JSON format suitable for smart-meter and w-M-Bus
gateway backends.

The focus is on clean architecture, deterministic memory usage, and strict
compliance with a fixed JSON schema. Radio communication, OMS, encryption,
and real meter interaction are intentionally out of scope.

---

## Platform & Programming Language

### Platform: Arduino Framework  
### Language: C (C99-compatible)

The Arduino framework is used as a lightweight build and execution environment.
The core serialization library itself contains no Arduino-specific dependencies
and can be reused without modification in STM32CubeIDE, ESP-IDF, or bare-metal
projects.

Arduino was selected to:
- Reduce platform-specific boilerplate
- Enable fast verification of JSON output
- Keep the example application minimal and portable

---

## Design Principles
- No dynamic memory allocation
- Fixed-size buffers and structures
- No external JSON libraries
- Transport-agnostic core logic
- Explicit error handling
- Buffer overflow prevention

Arduino `String` is deliberately avoided.

---

## Public API

```c
wmbus_json_status_t wmbus_serialize_json(
    const wmbus_payload_t *payload,
    char *out_buffer,
    size_t buffer_size,
    size_t *bytes_written
);
