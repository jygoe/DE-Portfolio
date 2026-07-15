import os
from pyspark.sql import SparkSession
from pyspark.sql.functions import col, to_date, lit

# =========================
# ENV
# =========================
os.environ["PYSPARK_PYTHON"] = r"C:\Users\User\Downloads\BikeDemandPrediction\.venv\Scripts\python.exe"
os.environ["PYSPARK_DRIVER_PYTHON"] = os.environ["PYSPARK_PYTHON"]
os.environ["SPARK_LOCAL_IP"] = "127.0.0.1"

# =========================
# SPARK
# =========================
spark = SparkSession.builder \
    .appName("Holiday Load Clean") \
    .master("local[*]") \
    .config("spark.sql.shuffle.partitions", "8") \
    .getOrCreate()

# =========================
# LOAD FILE
# =========================
file_path = "data/holiday/US Holiday Dates (2004-2021).csv"

df = spark.read.option("header", True).option("inferSchema", True).csv(file_path)

print("Raw holiday loaded")

# =========================
# CLEAN COLUMN NAMES
# =========================
df = df.withColumnRenamed("Date", "date") \
       .withColumnRenamed("Holiday", "holiday_name")

# =========================
# CONVERT DATE FORMAT
# =========================
df = df.withColumn("date", to_date(col("date"), "M/d/yyyy"))

# =========================
# CREATE HOLIDAY FLAG
# =========================
df = df.withColumn("is_holiday", lit(1))

# =========================
# KEEP ONLY USEFUL COLUMNS
# =========================
holiday_df = df.select(
    "date",
    "holiday_name",
    "is_holiday"
)

# =========================
# REMOVE NULLS
# =========================
holiday_df = holiday_df.filter(col("date").isNotNull())

# =========================
# SORT
# =========================
holiday_df = holiday_df.orderBy("date")

# =========================
# SHOW SAMPLE
# =========================
holiday_df.show(10)

total_rows = holiday_df.count()
print("Holiday rows:", total_rows)

# =========================
# SAVE — VIA PANDAS (bypasses Hadoop FileOutputCommitter)
# =========================
output_dir = "data/processed/holiday_daily"
os.makedirs(output_dir, exist_ok=True)

holiday_pd = holiday_df.toPandas()
output_file = os.path.join(output_dir, "holiday_daily.parquet")
holiday_pd.to_parquet(output_file, index=False)

print("Saved to:", output_file)

spark.stop()