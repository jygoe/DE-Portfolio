import os
from pyspark.sql import SparkSession
from pyspark.sql.functions import col, to_date

# =========================
# ENV (Windows safe setup)
# =========================
os.environ["PYSPARK_PYTHON"] = r"C:\Users\User\Downloads\BikeDemandPrediction\.venv\Scripts\python.exe"
os.environ["PYSPARK_DRIVER_PYTHON"] = os.environ["PYSPARK_PYTHON"]
os.environ["SPARK_LOCAL_IP"] = "127.0.0.1"

# =========================
# SPARK SESSION
# =========================
spark = SparkSession.builder \
    .appName("Weather Load Clean") \
    .master("local[*]") \
    .config("spark.sql.shuffle.partitions", "8") \
    .getOrCreate()

# =========================
# LOAD WEATHER CSV
# (from Open-Meteo export)
# =========================
file_path = "data/weather/weather_daily.csv"

df = spark.read.option("header", True).csv(file_path)

print("Weather raw schema loaded")

# =========================
# CLEAN + FORMAT DATE
# =========================
df = df.withColumn("date", to_date(col("time")))

# =========================
# SELECT ONLY USEFUL COLUMNS
# =========================
weather_df = df.select(
    "date",
    col("temperature_2m_mean").cast("double"),
    col("temperature_2m_max").cast("double"),
    col("temperature_2m_min").cast("double"),
    col("precipitation_sum").cast("double"),
    col("windspeed_10m_max").cast("double")
)

# =========================
# REMOVE NULL DATES
# =========================
weather_df = weather_df.filter(col("date").isNotNull())

# =========================
# SORT
# =========================
weather_df = weather_df.orderBy("date")

# =========================
# SHOW SAMPLE
# =========================
weather_df.show(10)

total_rows = weather_df.count()
print("Weather rows:", total_rows)

# =========================
# SAVE CLEAN OUTPUT — VIA PANDAS (bypasses Hadoop FileOutputCommitter)
# =========================
output_dir = "data/processed/weather_daily"
os.makedirs(output_dir, exist_ok=True)

weather_pd = weather_df.toPandas()
output_file = os.path.join(output_dir, "weather_daily.parquet")
weather_pd.to_parquet(output_file, index=False)

print("Saved clean weather dataset to:", output_file)

spark.stop()