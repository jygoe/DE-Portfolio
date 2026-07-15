# 📘 Data Dictionary — Bike Demand Prediction Dataset

## 🧾 Target Variable

### `ride_count`

* **Type:** Integer
* **Meaning:** Total number of bike trips per day
* **Source:** Aggregated from trip-level bike-sharing data
* **Usage:** This is the **label / target variable** your Random Forest predicts
* **Example:** 2294, 17085, 30735

---

# 🌤️ Weather Features

These come from your weather dataset and represent daily weather conditions.

### `temperature_2m_mean`

* **Type:** Float
* **Meaning:** Average temperature of the day (°C)
* **Why it matters:** Bike usage increases in comfortable temperatures

### `temperature_2m_max`

* **Type:** Float
* **Meaning:** Highest temperature recorded during the day (°C)

### `temperature_2m_min`

* **Type:** Float
* **Meaning:** Lowest temperature recorded during the day (°C)

### `precipitation_sum`

* **Type:** Float
* **Meaning:** Total precipitation in the day (mm)
* **Impact:** High rain usually reduces bike usage

### `rain_sum`

* **Type:** Float
* **Meaning:** Total rainfall amount (mm)

### `snowfall_sum`

* **Type:** Float
* **Meaning:** Snowfall amount (mm)
* **Note:** Likely near zero in your dataset (important for US winter seasons)

### `precipitation_hours`

* **Type:** Integer/Float
* **Meaning:** Number of hours with precipitation

### `windspeed_10m_max`

* **Type:** Float
* **Meaning:** Maximum wind speed (10m above ground, km/h or m/s depending on source)
* **Impact:** Strong winds reduce cycling demand

---

# 📅 Calendar / Time Features

### `date`

* **Type:** Date
* **Meaning:** Aggregated daily timestamp
* **Usage:** Used for sorting, joins, and time-based analysis in Power BI

### `day_of_week`

* **Type:** Integer (0–6 or 1–7 depending on your encoding)
* **Meaning:** Day index (Mon–Sun)
* **Insight:** Weekends usually have different demand patterns

### `month`

* **Type:** Integer (1–12)
* **Meaning:** Month of the year
* **Insight:** Captures seasonality

### `week_of_year`

* **Type:** Integer
* **Meaning:** Week number in the year
* **Insight:** Helps capture seasonal trends more smoothly than month

### `day`

* **Type:** Integer
* **Meaning:** Day of month (1–31)

---

# 🎉 Holiday Features

### `holiday_name`

* **Type:** String
* **Meaning:** Name of holiday (e.g., Christmas, Labor Day)
* **Example:** "Christmas Day", "None"

### `is_holiday`

* **Type:** Binary (0/1)
* **Meaning:** Whether the day is a public holiday
* **Impact:** Bike usage often drops or spikes depending on holiday type

---

# 📊 Derived Time Features

### `is_weekend`

* **Type:** Binary (0/1)
* **Meaning:** 1 = Saturday/Sunday, 0 = weekday
* **Impact:** Strong predictor of leisure cycling

### `season`

* **Type:** String (Spring, Summer, Autumn, Winter)
* **Meaning:** Derived from month
* **Impact:** Very strong demand pattern driver

---

# 🔁 Time-Series Lag Features (VERY IMPORTANT for your model)

These are what make your model “smart”.

### `lag_1`

* **Type:** Integer
* **Meaning:** Ride count from previous day
* **Why important:** Captures short-term momentum in demand

### `lag_7`

* **Type:** Integer
* **Meaning:** Ride count from same day last week
* **Why important:** Captures weekly cycling pattern

### `rolling_mean_7`

* **Type:** Float
* **Meaning:** Average ride count over last 7 days
* **Why important:** Smooths noise and captures trend

---

# 🤖 Model Input Summary

Your Random Forest uses:

### 🌟 Core Inputs

* Weather (temperature, rain, wind)
* Calendar (month, weekday, weekend, holiday)
* Time series memory (lag_1, lag_7, rolling_mean_7)

### 🎯 Output

* `ride_count` (daily demand prediction)

---
