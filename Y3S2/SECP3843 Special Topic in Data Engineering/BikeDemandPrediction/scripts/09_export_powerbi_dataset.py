import pandas as pd
import os

# =========================
# PATHS
# =========================
input_path = r"C:\Users\User\Downloads\BikeDemandPrediction\data\processed\ml_ready\bike_demand_ml.parquet"
output_path = r"C:\Users\User\Downloads\BikeDemandPrediction\data\processed\ml_ready\bike_demand_ml.csv"

# =========================
# LOAD PARQUET
# =========================
df = pd.read_parquet(input_path)

print("Loaded parquet with shape:", df.shape)

# =========================
# EXPORT TO CSV
# =========================
df.to_csv(output_path, index=False)

print("Saved CSV to:", output_path)