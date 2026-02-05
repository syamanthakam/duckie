# Infrastructure Notes

This folder documents how Duckie connects to the cloud.

Initial version keeps things simple:

- ESP32 posts JSON measurements to the backend `/api/measurements` endpoint over HTTP.
- Backend stores recent data in memory and exposes it via `GET /api/measurements`.

Next steps (not implemented yet, but planned):

- Use AWS IoT Core MQTT topics instead of raw HTTP from the ESP32.
- Forward MQTT messages into AWS Lambda.
- Store measurements in Amazon S3 (or DynamoDB) for long-term analysis.

These steps match the architecture described in the project summary and can be implemented iteratively.
