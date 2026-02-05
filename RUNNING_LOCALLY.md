# Running Duckie Locally

This guide shows how to run the backend locally and interact with it without any hardware.

## 1. Start the FastAPI backend

```bash
cd backend
python -m venv .venv
source .venv/bin/activate  # Windows: .venv\\Scripts\\activate
pip install -r requirements.txt
uvicorn app:app --reload --host 0.0.0.0 --port 8000
```

The API will now be available at `http://localhost:8000`.

## 2. Post a sample measurement (no ESP32 required)

Open a new terminal in the `duckie` repo root and run:

```bash
curl -X POST "http://localhost:8000/api/measurements" \
  -H "Content-Type: application/json" \
  -d '{
    "device_id": "duckie-sim-001",
    "temperature": 23.5,
    "turbidity": 2.8,
    "ph": 7.0
  }'
```

You should see a small JSON response confirming it was stored.

## 3. List recent measurements

```bash
curl "http://localhost:8000/api/measurements?limit=10" | jq
```

If you don't have `jq` installed, you can omit the pipe and just see the raw JSON.

## 4. Use the simple dashboard script

There is a tiny Python script that acts as a CLI-style dashboard.

```bash
cd backend
source .venv/bin/activate  # if not already active
python dashboard.py
```

You should see human-readable lines like:

```text
[2026-02-05T18:05:00Z] device=duckie-sim-001 T=23.5C turbidity=2.8 NTU pH=7.0
```

This gives reviewers a quick way to see how the system behaves without needing real hardware or AWS.
