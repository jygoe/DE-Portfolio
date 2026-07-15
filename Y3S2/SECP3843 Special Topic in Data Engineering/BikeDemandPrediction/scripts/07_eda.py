import os
from pyspark.sql import SparkSession
from pyspark.sql.functions import col, avg, min, max, isnan, count as spark_count, when

# =========================
# ENV SETUP
# =========================
os.environ["HADOOP_HOME"] = "C:\\hadoop"
os.environ["hadoop.home.dir"] = "C:\\hadoop"
os.environ["PYSPARK_PYTHON"] = r"C:\Users\User\Downloads\BikeDemandPrediction\.venv\Scripts\python.exe"
os.environ["PYSPARK_DRIVER_PYTHON"] = os.environ["PYSPARK_PYTHON"]
os.environ["SPARK_LOCAL_IP"] = "127.0.0.1"

# =========================
# SPARK SESSION
# =========================
spark = (
    SparkSession.builder
    .appName("EDA Bike Demand")
    .master("local[*]")
    .config("spark.sql.shuffle.partitions", "8")
    .getOrCreate()
)

# =========================
# LOAD DATA
# =========================
df = spark.read.parquet(
    "data/processed/ml_ready/bike_demand_ml.parquet"
)
df.printSchema()

# =========================
# BASIC STATISTICS
# =========================
print("\n===== BASIC STATISTICS =====")
df.select(
    avg("ride_count").alias("avg_rides"),
    min("ride_count").alias("min_rides"),
    max("ride_count").alias("max_rides")
).show()
print("Total rows:", df.count())

# =========================
# NULL AUDIT (important — weather data starts 2020-04-01,
# so early-2020 Divvy dates may have null weather columns)
# =========================
print("\n===== NULL COUNTS PER COLUMN =====")
null_check_cols = [
    "temperature_2m_mean", "temperature_2m_max", "temperature_2m_min",
    "precipitation_sum", "windspeed_10m_max"
]
df.select([
    spark_count(when(col(c).isNull(), c)).alias(c) for c in null_check_cols
]).show()

# =========================
# RIDE BY WEEKDAY
# =========================
print("\n===== RIDES BY DAY OF WEEK =====")
df.groupBy("day_of_week") \
    .agg(avg("ride_count").alias("avg_rides")) \
    .orderBy("day_of_week") \
    .show()

# =========================
# RIDE BY MONTH
# =========================
print("\n===== RIDES BY MONTH =====")
df.groupBy("month") \
    .agg(avg("ride_count").alias("avg_rides")) \
    .orderBy("month") \
    .show()

# =========================
# WEEKEND VS WEEKDAY
# =========================
print("\n===== WEEKEND VS WEEKDAY =====")
df.groupBy("is_weekend") \
    .agg(avg("ride_count").alias("avg_rides")) \
    .show()

# =========================
# HOLIDAY VS NON-HOLIDAY
# =========================
print("\n===== HOLIDAY VS NON-HOLIDAY =====")
df.groupBy("is_holiday") \
    .agg(avg("ride_count").alias("avg_rides")) \
    .show()

# =========================
# WEATHER IMPACT
# =========================
print("\n===== TEMPERATURE IMPACT =====")
df.select("temperature_2m_mean", "ride_count") \
    .orderBy("temperature_2m_mean") \
    .show(20)

print("\n===== RAINFALL IMPACT =====")
df.select("precipitation_sum", "ride_count") \
    .orderBy("precipitation_sum", ascending=False) \
    .show(20)

# =========================
# CORRELATION (IMPORTANT FOR REPORT)
# =========================
print("\n===== CORRELATION WITH RIDES (full dataset, nulls dropped pairwise) =====")
numeric_cols = [
    "temperature_2m_mean",
    "precipitation_sum",
    "windspeed_10m_max",
    "lag_1",
    "lag_7",
    "rolling_mean_7"
]
for c in numeric_cols:
    corr = df.stat.corr(c, "ride_count")
    print(f"Correlation {c} vs ride_count = {corr}")

# Optional: correlation excluding the first 7 rows, where lag/rolling
# values are artificial 0-fills rather than real history
print("\n===== CORRELATION excluding first 7 rows (lag warm-up period) =====")
df_trimmed = df.orderBy("date").limit(df.count()).subtract(
    df.orderBy("date").limit(7)
)
for c in ["lag_1", "lag_7", "rolling_mean_7"]:
    corr = df_trimmed.stat.corr(c, "ride_count")
    print(f"Correlation {c} vs ride_count (trimmed) = {corr}")

# =========================
# SAMPLE DATA CHECK
# =========================
print("\n===== SAMPLE DATA =====")
df.orderBy("date").show(10, truncate=False)

spark.stop()