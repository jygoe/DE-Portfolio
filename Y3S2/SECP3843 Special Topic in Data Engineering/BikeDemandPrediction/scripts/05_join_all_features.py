import os
from pyspark.sql import SparkSession
from pyspark.sql.functions import (
    col,
    when,
    dayofweek,
    month,
    dayofmonth,
    concat_ws,
    collect_list
)

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
    .appName("Join All Features")
    .master("local[*]")
    .config("spark.sql.shuffle.partitions", "8")
    .getOrCreate()
)

# =====================================================
# LOAD DATASETS
# =====================================================
print("Loading datasets...")
divvy = spark.read.parquet(
    "data/processed/divvy_daily/divvy_daily.parquet"
)
weather = spark.read.parquet(
    "data/processed/weather_daily/weather_daily.parquet"
)
holiday = spark.read.parquet(
    "data/processed/holiday_daily/holiday_daily.parquet"   # FIXED path
)
print("Datasets loaded.")

# =====================================================
# DEDUPE HOLIDAY (multiple holidays can share a date, e.g. Easter)
# =====================================================
holiday = (
    holiday
    .groupBy("date")
    .agg(
        concat_ws(", ", collect_list("holiday_name")).alias("holiday_name")
    )
    .withColumn("is_holiday", when(col("holiday_name").isNotNull(), 1).otherwise(0))
)

# =====================================================
# JOIN DIVVY + WEATHER
# =====================================================
df = divvy.join(
    weather,
    on="date",
    how="left"
)

# =====================================================
# JOIN HOLIDAY
# =====================================================
df = df.join(
    holiday,
    on="date",
    how="left"
)

# =====================================================
# FILL NULL HOLIDAY VALUES
# =====================================================
df = (
    df
    .withColumn(
        "holiday_name",
        when(col("holiday_name").isNull(), "None")
        .otherwise(col("holiday_name"))
    )
    .withColumn(
        "is_holiday",
        when(col("is_holiday").isNull(), 0)
        .otherwise(col("is_holiday"))
    )
)

# =====================================================
# CALENDAR FEATURES
# =====================================================
df = (
    df
    .withColumn("day_of_week", dayofweek("date"))
    .withColumn("month", month("date"))
    .withColumn("day", dayofmonth("date"))
)

# =====================================================
# SORT
# =====================================================
df = df.orderBy("date")

# =====================================================
# SHOW
# =====================================================
print()
print("Final Dataset Preview")
df.show(20, truncate=False)
print()

total_rows = df.count()
print("Rows:", total_rows)
print("Columns:")
print(df.columns)

# Sanity check: row count should match divvy's row count exactly
divvy_rows = divvy.count()
if total_rows != divvy_rows:
    print(f"WARNING: row count mismatch! divvy had {divvy_rows} rows, "
          f"final has {total_rows} rows. Check for duplicate join keys.")

# =====================================================
# SAVE
# =====================================================
output_dir = "data/processed/final"
os.makedirs(output_dir, exist_ok=True)
pdf = df.toPandas()
output_file = os.path.join(
    output_dir,
    "bike_demand_features.parquet"
)
pdf.to_parquet(output_file, index=False)

print()
print("Saved successfully!")
print(output_file)

spark.stop()