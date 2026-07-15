import pandas as pd
import os
from pyspark.sql import SparkSession
from pyspark.sql.functions import col

from pyspark.ml.feature import VectorAssembler
from pyspark.ml.regression import RandomForestRegressor
from pyspark.ml.evaluation import RegressionEvaluator

# =========================
# ENV SETUP (matches rest of pipeline)
# =========================
os.environ["HADOOP_HOME"] = "C:\\hadoop"
os.environ["hadoop.home.dir"] = "C:\\hadoop"
os.environ["PYSPARK_PYTHON"] = r"C:\Users\User\Downloads\BikeDemandPrediction\.venv\Scripts\python.exe"
os.environ["PYSPARK_DRIVER_PYTHON"] = os.environ["PYSPARK_PYTHON"]
os.environ["SPARK_LOCAL_IP"] = "127.0.0.1"

# =========================
# SPARK SESSION
# =========================
spark = SparkSession.builder \
    .appName("Bike Demand RF Model") \
    .master("local[*]") \
    .getOrCreate()

# =========================
# LOAD DATA (FIXED PATH)
# =========================
df = spark.read.parquet("data/processed/ml_ready/bike_demand_ml.parquet")

print("Dataset loaded")
df.show(5)

# =========================
# FEATURE SELECTION
# =========================
feature_cols = [
    "temperature_2m_mean",
    "precipitation_sum",
    "windspeed_10m_max"
]

# Optional features (only if they exist)
optional_cols = ["is_holiday", "day_of_week", "is_weekend", "month",
                  "lag_1", "lag_7", "rolling_mean_7"]

for c in optional_cols:
    if c in df.columns:
        feature_cols.append(c)

print("Features used:", feature_cols)

# =========================
# HANDLE MISSING VALUES
# =========================
rows_before = df.count()
df = df.dropna(subset=feature_cols + ["ride_count"])
rows_after = df.count()
if rows_before != rows_after:
    print(f"Dropped {rows_before - rows_after} rows with nulls in features/label "
          f"(likely early-2020 rows missing weather data)")

# =========================
# CHRONOLOGICAL TRAIN/TEST SPLIT
# (avoids leaking future info into training for a time-series problem)
# =========================
df = df.orderBy("date")
total_rows = df.count()
split_point = int(total_rows * 0.8)

df_indexed = df.rdd.zipWithIndex().toDF(["data", "idx"]).select(
    col("data.*"), col("idx")
)

train_data_raw = df_indexed.filter(col("idx") < split_point).drop("idx")
test_data_raw = df_indexed.filter(col("idx") >= split_point).drop("idx")

# =========================
# VECTOR ASSEMBLER
# =========================
assembler = VectorAssembler(
    inputCols=feature_cols,
    outputCol="features"
)

train_data = assembler.transform(train_data_raw).select(
    "date",
    "features",
    col("ride_count").alias("label")
)

test_data = assembler.transform(test_data_raw).select(
    "date",
    "features",
    col("ride_count").alias("label")
)

print("Train size:", train_data.count())
print("Test size:", test_data.count())

# =========================
# RANDOM FOREST MODEL
# =========================
rf = RandomForestRegressor(
    featuresCol="features",
    labelCol="label",
    numTrees=100,
    maxDepth=10,
    seed=42
)

model = rf.fit(train_data)

# =========================
# PREDICTIONS
# =========================
predictions = model.transform(test_data)
predictions.select("features", "label", "prediction").show(10)

prediction_pd = predictions.select(
    "date",
    "label",
    "prediction"
).toPandas()

prediction_pd.to_csv(
    "data/models/random_forest_predictions.csv",
    index=False
)

# =========================
# EVALUATION
# =========================
evaluator_rmse = RegressionEvaluator(
    labelCol="label", predictionCol="prediction", metricName="rmse"
)
evaluator_r2 = RegressionEvaluator(
    labelCol="label", predictionCol="prediction", metricName="r2"
)

rmse = evaluator_rmse.evaluate(predictions)
r2 = evaluator_r2.evaluate(predictions)

print("===================================")
print(f"RMSE: {rmse}")
print(f"R2: {r2}")
print("===================================")

metrics = pd.DataFrame({
    "Metric": ["RMSE", "R2"],
    "Value": [rmse, r2]
})

metrics.to_csv(
    "data/models/random_forest_metrics.csv",
    index=False
)

# =========================
# FEATURE IMPORTANCE
# =========================

importances = model.featureImportances.toArray()

print("Feature Importance:")

for i, col_name in enumerate(feature_cols):
    print(f"{col_name}: {importances[i]}")


# =========================
# SAVE FEATURE IMPORTANCE
# =========================

importance_df = pd.DataFrame({
    "Feature": feature_cols,
    "Importance": importances
})

importance_df["Importance_Percentage"] = (
    importance_df["Importance"] * 100
)

importance_df = importance_df.sort_values(
    by="Importance",
    ascending=False
)


importance_df.to_csv(
    "data/models/random_forest_feature_importance.csv",
    index=False
)

print("Feature importance saved")

spark.stop()