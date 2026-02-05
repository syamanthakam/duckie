from fastapi import FastAPI
from pydantic import BaseModel
from typing import List
from datetime import datetime

app = FastAPI(title="Duckie Backend API")


class MeasurementIn(BaseModel):
    device_id: str
    temperature: float
    turbidity: float
    ph: float


class Measurement(MeasurementIn):
    timestamp: datetime


_db: List[Measurement] = []


@app.get("/health")
async def health():
    return {"status": "ok"}


@app.post("/api/measurements")
async def create_measurement(m: MeasurementIn):
    measurement = Measurement(**m.model_dump(), timestamp=datetime.utcnow())
    _db.append(measurement)
    return {"ok": True, "count": len(_db)}


@app.get("/api/measurements")
async def list_measurements(limit: int = 50):
    return _db[-limit:]
