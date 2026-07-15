import os
from pyspark.sql import SparkSession
from pyspark.sql.functions import col, to_timestamp, to_date

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
spark = SparkSession.builder \
    .appName("Divvy Load Fixed") \
    .master("local[*]") \
    .config("spark.sql.shuffle.partitions", "8") \
    .getOrCreate()

# =========================
# LOAD CSV FILES
# =========================
folder = "data/trip/csv"

files = [
    os.path.join(folder, f)
    for f in os.listdir(folder)
    if f.endswith(".csv")
]

print(f"Found {len(files)} CSV files")

df = spark.read.option("header", True).csv(files)

# =========================
# CLEAN + CONVERT TIMESTAMP
# =========================
df = df.withColumn("started_at", to_timestamp(col("started_at")))
df = df.filter(col("started_at").isNotNull())

# =========================
# FILTER DATE RANGE
# =========================
df = df.filter(
    (col("started_at") >= "2020-01-01") &
    (col("started_at") <= "2021-12-31")
)

print("Filtered 2020–2021 done")

# =========================
# CREATE DATE COLUMN
# =========================
df = df.withColumn("date", to_date(col("started_at")))

# =========================
# DAILY AGGREGATION
# =========================
daily_df = df.groupBy("date").count()
daily_df = daily_df.withColumnRenamed("count", "ride_count")
daily_df = daily_df.orderBy("date")

print("Daily aggregation done")

# =========================
# SHOW RESULT
# =========================
daily_df.show(10)
total_rows = daily_df.count()
print("Total daily rows:", total_rows)

# =========================
# SAVE OUTPUT — VIA PANDAS (bypasses Hadoop FileOutputCommitter entirely)
# =========================
output_dir = "data/processed/divvy_daily"
os.makedirs(output_dir, exist_ok=True)

daily_pd = daily_df.toPandas()
output_file = os.path.join(output_dir, "divvy_daily.parquet")
daily_pd.to_parquet(output_file, index=False)

print(f"Saved {len(daily_pd)} rows to: {output_file}")

spark.stop()