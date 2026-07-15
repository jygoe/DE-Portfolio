import os
from pyspark.sql import SparkSession
from pyspark.sql.functions import (
    col,
    year,
    month,
    dayofmonth,
    dayofweek,
    weekofyear,
    date_format,
    when,
    monotonically_increasing_id
)


# =========================
# ENV SETUP
# =========================

os.environ["HADOOP_HOME"] = "C:\\hadoop"
os.environ["hadoop.home.dir"] = "C:\\hadoop"

os.environ["PYSPARK_PYTHON"] = (
    r"C:\Users\User\Downloads\BikeDemandPrediction\.venv\Scripts\python.exe"
)

os.environ["PYSPARK_DRIVER_PYTHON"] = os.environ["PYSPARK_PYTHON"]

os.environ["SPARK_LOCAL_IP"] = "127.0.0.1"


# =========================
# SPARK SESSION
# =========================

spark = SparkSession.builder \
    .appName("Build Bike Demand Star Schema") \
    .master("local[*]") \
    .getOrCreate()


# =========================
# LOAD GOLD DATASET
# =========================

input_path = (
    "data/processed/ml_ready/bike_demand_ml.parquet"
)

df = spark.read.parquet(input_path)


print("Original Dataset")
df.show(5)


# =====================================================
# DIM DATE
# =====================================================

print("Creating DimDate...")


dim_date = df.select(
    "date"
).distinct()


dim_date = dim_date \
    .withColumn(
        "date_key",
        date_format(col("date"), "yyyyMMdd").cast("int")
    ) \
    .withColumn(
        "year",
        year(col("date"))
    ) \
    .withColumn(
        "month",
        month(col("date"))
    ) \
    .withColumn(
        "day",
        dayofmonth(col("date"))
    ) \
    .withColumn(
        "day_of_week",
        dayofweek(col("date"))
    ) \
    .withColumn(
        "week_of_year",
        weekofyear(col("date"))
    ) \
    .withColumn(
        "month_name",
        date_format(col("date"), "MMMM")
    )


# weekend flag

dim_date = dim_date.withColumn(
    "is_weekend",
    when(
        col("day_of_week").isin([1,7]),
        1
    ).otherwise(0)
)


# season

dim_date = dim_date.withColumn(
    "season",
    when(col("month").isin([12,1,2]),"Winter")
    .when(col("month").isin([3,4,5]),"Spring")
    .when(col("month").isin([6,7,8]),"Summer")
    .otherwise("Fall")
)


dim_date.show(5)


# =====================================================
# DIM WEATHER
# =====================================================

print("Creating DimWeather...")


dim_weather = df.select(
    "date",
    "temperature_2m_mean",
    "temperature_2m_max",
    "temperature_2m_min",
    "precipitation_sum",
    "windspeed_10m_max"
).distinct()


dim_weather = dim_weather.withColumn(
    "weather_key",
    monotonically_increasing_id()
)


dim_weather.show(5)



# =====================================================
# DIM HOLIDAY
# =====================================================

print("Creating DimHoliday...")


dim_holiday = df.select(
    "date",
    "holiday_name",
    "is_holiday"
).distinct()


dim_holiday = dim_holiday.withColumn(
    "holiday_key",
    monotonically_increasing_id()
)


dim_holiday.show(5)



# =====================================================
# FACT TABLE
# =====================================================

print("Creating FactBikeDemand...")


fact_bike = df.select(

    "date",

    "ride_count",

    "lag_1",
    "lag_7",
    "rolling_mean_7",

    "temperature_2m_mean",
    "precipitation_sum",
    "windspeed_10m_max",

    "is_holiday",
    "day_of_week",
    "is_weekend",
    "month"

)


fact_bike = fact_bike.withColumn(
    "date_key",
    date_format(
        col("date"),
        "yyyyMMdd"
    ).cast("int")
)


fact_bike.show(5)



# =====================================================
# SAVE DATA WAREHOUSE
# =====================================================

output = "data/warehouse"

os.makedirs(output, exist_ok=True)


print("Saving warehouse tables...")


def save_csv(df, name):

    path = f"{output}/{name}"

    (
        df.toPandas()
        .to_csv(
            path,
            index=False
        )
    )

    print("Saved:", path)



save_csv(
    fact_bike,
    "fact_bike_demand.csv"
)


save_csv(
    dim_date,
    "dim_date.csv"
)


save_csv(
    dim_weather,
    "dim_weather.csv"
)


save_csv(
    dim_holiday,
    "dim_holiday.csv"
)



print("==============================")
print("STAR SCHEMA CREATED SUCCESSFULLY")
print("==============================")


spark.stop()