import os
from pyspark.sql import SparkSession

# FORCE Spark to use correct Python
PYTHON_PATH = r"C:\Users\User\Downloads\BikeDemandPrediction\.venv\Scripts\python.exe"

os.environ["PYSPARK_PYTHON"] = PYTHON_PATH
os.environ["PYSPARK_DRIVER_PYTHON"] = PYTHON_PATH

spark = SparkSession.builder \
    .appName("Bike Test") \
    .master("local[*]") \
    .config("spark.python.worker.faulthandler.enabled", "true") \
    .getOrCreate()

data = [("Alice", 25), ("Bob", 30), ("Charlie", 28)]

df = spark.createDataFrame(data, ["Name", "Age"])

df.show()

spark.stop()