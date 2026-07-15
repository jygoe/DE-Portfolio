import os
import requests
import pandas as pd

# ==========================================
# CONFIGURATION
# ==========================================

LATITUDE = 41.8781      # Chicago
LONGITUDE = -87.6298

START_DATE = "2020-04-01"
END_DATE = "2021-12-31"

OUTPUT_FOLDER = "data/weather"
OUTPUT_FILE = os.path.join(OUTPUT_FOLDER, "weather_daily.csv")

os.makedirs(OUTPUT_FOLDER, exist_ok=True)

# ==========================================
# OPEN-METEO API
# ==========================================

url = "https://archive-api.open-meteo.com/v1/archive"

params = {
    "latitude": LATITUDE,
    "longitude": LONGITUDE,
    "start_date": START_DATE,
    "end_date": END_DATE,
    "daily": ",".join([
        "temperature_2m_max",
        "temperature_2m_min",
        "temperature_2m_mean",
        "precipitation_sum",
        "rain_sum",
        "snowfall_sum",
        "precipitation_hours",
        "windspeed_10m_max"
    ]),
    "timezone": "America/Chicago"
}

print("Downloading weather data...")

response = requests.get(url, params=params)

response.raise_for_status()

weather_json = response.json()

print("Download completed.")

# ==========================================
# CONVERT JSON TO DATAFRAME
# ==========================================

daily = weather_json["daily"]

weather_df = pd.DataFrame(daily)

# ==========================================
# SAVE CSV
# ==========================================

weather_df.to_csv(OUTPUT_FILE, index=False)

print(f"\nSaved weather data to:\n{OUTPUT_FILE}")

print("\nDataset Preview:")

print(weather_df.head())

print(f"\nTotal days: {len(weather_df)}")