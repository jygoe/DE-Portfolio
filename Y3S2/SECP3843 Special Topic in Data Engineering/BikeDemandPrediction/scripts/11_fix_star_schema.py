# fix_star_schema.py
import pandas as pd

fact = pd.read_csv("data/warehouse/fact_bike_demand.csv")
dim_weather = pd.read_csv("data/warehouse/dim_weather.csv")
dim_holiday = pd.read_csv("data/warehouse/dim_holiday.csv")

fact = fact.merge(dim_weather[["date", "weather_key"]], on="date", how="left")
fact = fact.merge(dim_holiday[["date", "holiday_key"]], on="date", how="left")

fact_clean = fact[[
    "date_key", "weather_key", "holiday_key",
    "ride_count", "lag_1", "lag_7", "rolling_mean_7"
]]

# New filename — does not overwrite your existing fact table
fact_clean.to_csv("data/warehouse/fact_bike_demand_starschema.csv", index=False)
print(fact_clean.shape)
print(fact_clean.head())