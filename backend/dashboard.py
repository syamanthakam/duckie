import requests
from pprint import pprint

BASE_URL = "http://localhost:8000"

"""
Very small CLI-style dashboard for Duckie measurements.

Run the FastAPI app first, for example:

    uvicorn app:app --reload --host 0.0.0.0 --port 8000

Then run this script:

    python dashboard.py

It will fetch the latest measurements and print them in a readable format.
"""


def fetch_measurements(limit: int = 10):
    resp = requests.get(f"{BASE_URL}/api/measurements", params={"limit": limit})
    resp.raise_for_status()
    return resp.json()


def main():
    try:
        data = fetch_measurements(limit=10)
    except Exception as e:
        print("Failed to fetch measurements:", e)
        return

    if not data:
        print("No measurements yet. Start the ESP32 device or post sample data.")
        return

    print("Latest Duckie measurements:\n")
    for m in data[::-1]:  # newest last
        ts = m.get("timestamp", "?")
        print(f"[{ts}] device={m['device_id']} T={m['temperature']}C turbidity={m['turbidity']} NTU pH={m['ph']}")


if __name__ == "__main__":
    main()
