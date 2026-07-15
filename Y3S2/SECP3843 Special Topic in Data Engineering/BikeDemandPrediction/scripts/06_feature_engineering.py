import os
from pyspark.sql import SparkSession
from pyspark.sql.functions import (
    col,
    when,
    month,
    weekofyear,
    dayofweek,
    lag,
    avg
)
from pyspark.sql.window import Window

# =====================================================
# ENVIRONMENT
# =====================================================
os.environ["HADOOP_HOME"] = "C:\\hadoop"
os.environ["hadoop.home.dir"] = "C:\\hadoop"
os.environ["PYSPARK_PYTHON"] = (
    r"C:\Users\User\Downloads\BikeDemandPrediction\.venv\Scripts\python.exe"
)
os.environ["PYSPARK_DRIVER_PYTHON"] = os.environ["PYSPARK_PYTHON"]
os.environ["SPARK_LOCAL_IP"] = "127.0.0.1"

# =====================================================
# SPARK
# =====================================================
spark = (
    SparkSession.builder
    .appName("Feature Engineering")
    .master("local[*]")
    .config("spark.sql.shuffle.partitions", "8")
    .getOrCreate()
)

# =====================================================
# LOAD JOINED DATASET
# =====================================================
print("Loading joined dataset...")
df = spark.read.parquet(
    "data/processed/final/bike_demand_features.parquet"
)
print("Loaded.")

# =====================================================
# DEDUPE FIRST (before any window computation)
# =====================================================
rows_before = df.count()
df = df.dropDuplicates(["date"])
rows_after = df.count()
if rows_before != rows_after:
    print(f"WARNING: dropped {rows_before - rows_after} duplicate date rows before feature engineering")

# =====================================================
# CALENDAR FEATURES
# =====================================================
df = (
    df
    .withColumn("month", month("date"))
    .withColumn("week_of_year", weekofyear("date"))
    .withColumn("day_of_week", dayofweek("date"))
)

# Weekend
# Spark:
# Sunday = 1
# Saturday = 7
df = df.withColumn(
    "is_weekend",
    when(
        (col("day_of_week") == 1) |
        (col("day_of_week") == 7),
        1
    ).otherwise(0)
)

# =====================================================
# SEASON
# =====================================================
df = df.withColumn(
    "season",
    when(col("month").isin([12, 1, 2]), "Winter")
    .when(col("month").isin([3, 4, 5]), "Spring")
    .when(col("month").isin([6, 7, 8]), "Summer")
    .otherwise("Autumn")
)

# =====================================================
# LAG FEATURES
# =====================================================
window = Window.orderBy("date")
df = df.withColumn(
    "lag_1",
    lag("ride_count", 1).over(window)
)
df = df.withColumn(
    "lag_7",
    lag("ride_count", 7).over(window)
)

# =====================================================
# ROLLING MEAN (7 DAYS)
# =====================================================
rolling_window = (
    Window.orderBy("date")
    .rowsBetween(-6, 0)
)
df = df.withColumn(
    "rolling_mean_7",
    avg("ride_count").over(rolling_window)
)

# =====================================================
# HANDLE NULLS
# =====================================================
df = (
    df
    .fillna({
        "lag_1": 0,
        "lag_7": 0,
        "rolling_mean_7": 0
    })
)

# =====================================================
# SORT
# =====================================================
df = df.orderBy("date")

# =====================================================
# SHOW RESULT
# =====================================================
print("\nFinal Feature Dataset")
df.show(20, truncate=False)
print("\nTotal rows:", df.count())
print("\nColumns:")
for c in df.columns:
    print(c)

# =====================================================
# SAVE
# =====================================================
output_dir = "data/processed/ml_ready"
os.makedirs(output_dir, exist_ok=True)
pdf = df.toPandas()
output_file = os.path.join(
    output_dir,
    "bike_demand_ml.parquet"
)
pdf.to_parquet(output_file, index=False)
print("\nSaved successfully!")
print(output_file)

spark.stop()