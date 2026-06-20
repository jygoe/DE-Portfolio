CREATE DATABASE car_rental;
USE car_rental;

DROP TABLE IF EXISTS vehicles;
DROP TABLE IF EXISTS customers;
DROP TABLE IF EXISTS bookings;
DROP TABLE IF EXISTS payments;

CREATE TABLE vehicles (
	vehicle_id INT AUTO_INCREMENT PRIMARY KEY,
    class VARCHAR(20) NOT NULL,						-- vehicle category eg.sedan,SUV,van
    plate_no VARCHAR(20) UNIQUE NOT NULL,
    vin VARCHAR(17) UNIQUE NOT NULL,				-- Vehicle Identification Number
    make VARCHAR(50) NOT NULL,						-- Manufacturer eg.Toyota,Honda
    model VARCHAR(50) NOT NULL,						-- Specific model name eg.Myvi, Civic
    year INT NOT NULL CHECK (year >= 1990),			-- must >= 1990
	vehicle_status VARCHAR(20) DEFAULT 'available', -- eg. available, rented, maintenance
    odometer_km INT DEFAULT 0,						-- Total kilometers driven.
    vehicle_location TEXT,							-- location where the vehicle is stored
    vehicle_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE customers (
	customer_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone_no VARCHAR(20),
    license_no VARCHAR(50) UNIQUE NOT NULL,
    address TEXT,
    register_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE bookings (
	booking_id INT AUTO_INCREMENT PRIMARY KEY,
    pickup_date DATE NOT NULL,
    return_date DATE NOT NULL,
    pickup_location TEXT,
    return_location TEXT,
    booking_status VARCHAR(20) DEFAULT 'booked',		-- eg.booked, completed,cancelled
    booking_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE payments (
	payment_id INT AUTO_INCREMENT PRIMARY KEY,
    amount DECIMAL(10,2) NOT NULL CHECK (amount >= 0),		-- total amount
    method VARCHAR(50),										-- eg. cash, credit card, TNG
    payment_date DATE NOT NULL,
    payment_status VARCHAR(50), 							-- eg. paid, pending
    deposit_amount DECIMAL(10,2) NOT NULL CHECK (deposit_amount >= 0),
    deposit_refund_status VARCHAR(50),						-- eg. refunded, forfeited, processing
    deposit_refund_date DATE
);
    
ALTER TABLE bookings
ADD customer_id INT NOT NULL,
ADD vehicle_id INT NOT NULL,
ADD FOREIGN KEY (customer_id) REFERENCES customers(customer_id),
ADD FOREIGN KEY (vehicle_id) REFERENCES vehicles(vehicle_id);

ALTER TABLE payments
ADD booking_id INT NOT NULL,
ADD FOREIGN KEY (booking_id) REFERENCES bookings(booking_id);

INSERT INTO vehicles (class, plate_no, vin, make, model, year, vehicle_status, odometer_km, vehicle_location)
VALUES
('Sedan',   'ABC123', '1HGCM82633A004352', 'Toyota',   'Vios',     2020, 'available', 25000, 'Kuala Lumpur'),
('SUV',     'BDF456', '2HGFA16578H311789', 'Honda',    'CR-V',     2019, 'rented',    40000, 'Selangor'),
('Hatchback','GHT789','3N1BC13E58L530294', 'Perodua',  'Myvi',     2022, 'available', 12000, 'Penang'),
('Sedan',   'JKL111', '5YJ3E1EA7JF000111', 'Honda',    'City',     2021, 'maintenance',31000, 'Johor Bahru'),
('Van',     'POI222', '4T1BF1FK5EU365555', 'Toyota',   'Hiace',    2018, 'available', 66000, 'Melaka'),
('SUV',     'TYU333', '1FTRX18L4XKA34567', 'Proton',   'X70',      2023, 'available', 8000,  'Ipoh'),
('Sedan',   'QWE444', '3VWFE21C04M000999', 'BMW',      '320i',     2017, 'rented',    55000, 'Kuala Lumpur'),
('Hatchback','RTY555','2G1WF55KX89345670', 'Perodua',  'Axia',     2020, 'available', 30000, 'Sabah'),
('SUV',     'ZXC666', '1HGCG1659WA035678', 'Mazda',    'CX-5',     2019, 'maintenance',42000, 'Sarawak'),
('Sedan',   'MNB777', '2HGFB2F50DH123456', 'Mercedes', 'C200',     2021, 'available', 21000, 'Kuala Lumpur');
select * from vehicles;

INSERT INTO customers (name, email, phone_no, license_no, address)
VALUES
('Nur Aisyah Binti Ahmad',       'aisyah.ahmad@example.com',     '0123456789', 'L1234567', 'Selangor'),
('Lim Wei Jian',                 'weijian.lim@example.com',      '0134567890', 'L9876543', 'Kuala Lumpur'),
('A/L Arjun Kumar',              'arjun.kumar@example.com',      '0145678901', 'L4567891', 'Penang'),
('Siti Nur Farhana',             'farhana.siti@example.com',     '0156789012', 'L2222333', 'Johor'),
('Tan Mei Ling',                 'meiling.tan@example.com',      '0167890123', 'L4444555', 'Melaka'),
('Muhammad Iqbal Bin Rashid',    'iqbal.rashid@example.com',     '0178901234', 'L6666777', 'Perak'),
('Kavitha A/P Mani',             'kavitha.mani@example.com',     '0189012345', 'L1111222', 'Selangor'),
('Chong Kai Wen',                'kaiwen.chong@example.com',     '0190123456', 'L5555666', 'Sabah'),
('Harish A/L Rajendran',         'harish.raj@example.com',       '0112345678', 'L3333444', 'Sarawak'),
('Nurul Huda Binti Zulkifli',    'nurul.huda@example.com',       '0198765432', 'L8888999', 'Kelantan');
select * from customers;

INSERT INTO bookings (pickup_date, return_date, pickup_location, return_location, booking_status, customer_id, vehicle_id)
VALUES
('2025-01-01', '2025-01-03', 'KL TRX', 'KL TRX', 'completed', 1, 2),
('2025-01-04', '2025-01-06', 'Selangor Sunway Pyramid', 'Selangor Sunway Pyramid', 'completed', 2, 1),
('2025-02-01', '2025-02-05', 'Penang Airport', 'KL Sentral', 'cancelled', 3, 3),
('2025-02-10', '2025-02-12', 'Johor Mid Valley Southkey', 'KLIA Terminal 1', 'booked', 4, 4),
('2025-03-15', '2025-03-17', 'KL Pavilion', 'KL Pavilion', 'completed', 5, 5),
('2025-03-20', '2025-03-22', 'Ipoh Amanjaya Terminal', 'Penang Queensbay Mall', 'booked', 6, 6),
('2025-04-01', '2025-04-04', 'KL KLCC', 'Sarawak Kuching Waterfront', 'completed', 7, 7),
('2025-04-05', '2025-04-10', 'KL Bukit Bintang', 'KL Bukit Bintang', 'cancelled', 8, 8),
('2025-04-12', '2025-04-13', 'Sabah KKIA Airport', 'Sabah KKIA Airport', 'completed', 9, 9),
('2025-04-15', '2025-04-18', 'KL IOI City Mall', 'KL IOI City Mall', 'booked', 10, 10);

select * from bookings;

UPDATE bookings SET booking_date = '2024-12-20 10:15:00' WHERE booking_id = 1;
UPDATE bookings SET booking_date = '2024-12-28 09:45:00' WHERE booking_id = 2;
UPDATE bookings SET booking_date = '2025-01-20 14:30:00' WHERE booking_id = 3;
UPDATE bookings SET booking_date = '2025-01-31 11:10:00' WHERE booking_id = 4;
UPDATE bookings SET booking_date = '2025-03-01 16:00:00' WHERE booking_id = 5;
UPDATE bookings SET booking_date = '2025-03-08 13:25:00' WHERE booking_id = 6;
UPDATE bookings SET booking_date = '2025-03-18 08:50:00' WHERE booking_id = 7;
UPDATE bookings SET booking_date = '2025-03-25 17:40:00' WHERE booking_id = 8;
UPDATE bookings SET booking_date = '2025-03-30 09:00:00' WHERE booking_id = 9;
UPDATE bookings SET booking_date = '2025-04-01 15:35:00' WHERE booking_id = 10;
SELECT * FROM bookings;


INSERT INTO payments (amount, method, payment_date, payment_status, deposit_amount, deposit_refund_status, deposit_refund_date, booking_id)
VALUES
(300.00, 'Credit Card', '2025-01-01', 'paid',     100.00, 'refunded',   '2025-01-03', 1),
(250.00, 'Cash',        '2025-01-04', 'paid',     80.00,  'refunded',   '2025-01-06', 2),
(500.00, 'TNG',         '2025-02-01', 'pending',  150.00, 'processing', NULL,         3),
(280.00, 'Credit Card', '2025-02-10', 'paid',     90.00,  'forfeited',  NULL,         4),
(400.00, 'Cash',        '2025-03-15', 'paid',     120.00, 'refunded',   '2025-03-17', 5),
(350.00, 'TNG',         '2025-03-20', 'pending',  110.00, 'processing', NULL,         6),
(600.00, 'Credit Card', '2025-04-01', 'paid',     200.00, 'refunded',   '2025-04-04', 7),
(260.00, 'Cash',        '2025-04-05', 'paid',     85.00,  'refunded',   '2025-04-10', 8),
(500.00, 'TNG',         '2025-04-12', 'paid',     170.00, 'refunded',   '2025-04-13', 9),
(320.00, 'Credit Card', '2025-04-15', 'pending',  95.00,  'processing', NULL,         10);
select * from payments;

-- C. Data Retrieval (DQL/SELECT)
-- 1.0 Filtering
-- 1.1 Car available for rental (WHERE)
SELECT * 
FROM vehicles
WHERE vehicle_status = 'available';

-- 1.2 Vehichle between 2020 and 2023 (BETWEEN, AND)
SELECT *
FROM vehicles
WHERE year BETWEEN 2020 AND 2023;

-- 1.3 Honda or Toyata Car (OR)
SELECT *
FROM vehicles
WHERE make = 'Honda' OR make = 'Toyota';

-- 1.4 Successful paid payment (NOT)
SELECT *
FROM payments
WHERE NOT payment_status = 'pending';

-- 1.5 Bookings that picked up in KL (LIKE)
SELECT *
FROM bookings
WHERE pickup_location LIKE '%KL%';

-- 1.6 Payments where deposit_refund_date is NULL (NULL)
SELECT *
FROM payments
WHERE deposit_refund_date IS NULL;

-- 2.0 Sorting
-- 2.1 Sort the vehichle by year (ORDER BY)
SELECT vehicle_id, make, model, year
FROM vehicles
ORDER BY year DESC;

-- 2.2 Top 5 highest deposit amount (LIMIT)
SELECT booking_id, deposit_amount, deposit_refund_status, deposit_refund_date
FROM payments
ORDER BY deposit_amount DESC
LIMIT 5;

-- 3.0 Aggregation 
-- 3.1 The number of customer (COUNT)
SELECT COUNT(*) AS total_customers
FROM customers;

-- 3.2 Total payment collected (SUM)
SELECT SUM(amount) AS total_payment
FROM payments
WHERE payment_status = 'paid';

-- 3.3 Average vehichle odometer reading (AVG)
SELECT AVG(odometer_km) AS avg_odometer
FROM vehicles;

-- 3.4 Maximum and Minimum odometer reading (MAX & MIN)
SELECT 
    MAX(odometer_km) AS highest_odometer,
    MIN(odometer_km) AS lowest_odometer
FROM vehicles;

-- 4.0 Grouping and Filtering Groups
-- 4.1 Count bookings per vehicle (GROUP BY)
SELECT vehicle_id, COUNT(*) AS total_bookings
FROM bookings
GROUP BY vehicle_id;

-- 4.2 Vechile with more that 40000km odometer reading
SELECT vehicle_id, make, model, odometer_km
FROM vehicles
GROUP BY vehicle_id, make, model, odometer_km
HAVING odometer_km > 40000;

-- 5.0 Numeric and String Functions
-- 5.1 Round Payment Amount and Remove Demical Places (ROUND & TRUNCATE)
SELECT payment_id, amount, ROUND(amount, 0) AS rounded_amount, 
	TRUNCATE(amount, 0) AS truncated_amount
FROM payments;

-- 5.2 Change Customer Name to UPPERCASE and count the length (UPPER & LENGTH)
SELECT customer_id, UPPER(name) AS uppercase_name, LENGTH(name) AS name_length
FROM customers;

-- 5.3 Combine the vehicle's model (CONCAT)
SELECT vehicle_id, CONCAT(make, ' ', model) AS full_model
FROM vehicles;

-- 5.4 The Car Plate No. for the vehicle (SUBSTR)
SELECT plate_no, SUBSTR(plate_no, -3) AS car_plate_no
FROM vehicles;

-- 6.0 Conditional Logic
-- 6.1 Categorize payments (CASE WHEN)
SELECT payment_id, amount, payment_status,
       CASE
           WHEN payment_status = 'paid' THEN 'Completed'
           WHEN payment_status = 'pending' THEN 'Pending'
           ELSE 'Unknown'
       END AS current_status
FROM payments;

-- 7.0 Subqueries
-- 7.1 Vehicle the newer than average year (Single-row)
SELECT *
FROM vehicles
WHERE year > (SELECT AVG(year) FROM vehicles);

-- 7.2 Customer that booked a 'SUV' vehicle (Multi-row)
SELECT *
FROM customers
WHERE customer_id IN (
    SELECT customer_id
    FROM bookings
    WHERE vehicle_id IN (
        SELECT vehicle_id
        FROM vehicles
        WHERE class = 'SUV'
    )
);

-- 7.3 Latest booking date for each customer (Correlated)
SELECT c.customer_id, c.name,
       (SELECT MAX(b.booking_date)
        FROM bookings b
        WHERE b.customer_id = c.customer_id) AS latest_booking
FROM customers c;

-- 8.0 Set Operations
-- 8.1 List all pickup and return locations (UNION)
SELECT pickup_location AS location
FROM bookings
UNION
SELECT return_location
FROM bookings;

-- 8.2 Customer with no completed bookings (NOT EXIST)
SELECT *
FROM customers c
WHERE NOT EXISTS (
    SELECT *
    FROM bookings b
    WHERE b.customer_id = c.customer_id
      AND b.booking_status = 'completed'
);

-- 9.0 Joins
-- 9.1 Combine bookings and payments (NATURAL)
SELECT *
FROM bookings
NATURAL JOIN payments;

-- 9.2 Booking with customer's name (INNER)
SELECT b.booking_id, c.name AS customer_name, b.pickup_date, b.return_date
FROM bookings b
INNER JOIN customers c
    ON b.customer_id = c.customer_id;

-- 9.3 Vehicle with booking (LEFT)
SELECT v.vehicle_id, v.make, v.model, b.booking_id
FROM vehicles v
LEFT JOIN bookings b
    ON v.vehicle_id = b.vehicle_id;

-- 9.4 Customer that live in same state (SELF)
SELECT c1.name AS customer1, c2.name AS customer2, c1.address
FROM customers c1
JOIN customers c2
    ON c1.address = c2.address
   AND c1.customer_id < c2.customer_id;

