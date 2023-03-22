-- Keep a log of any SQL queries you execute as you solve the mystery.

/* Background Info:
Crime: CS50 duck has been stolen
Date of Crime: July 28, 2021
Location: Humphrey St, Fiftyville (town)
Persons Involved: ONE Thief, ONE Accomplice
Details: Shortly after (time) the crime the thief took a flight (mode of transport) out of town (location).
Accomplice helped the thief escape (assume the accomplice was not involved with the direct crime)
*/

--Analyze records given in db: crime_scene_reports, interviews, atm_transactions, bank_accounts, airports, flights, passengers, phone_calls, people, bakery_security_logs

/* Off the bat:
Thief may (?) have a previous crime record.
Inspect eye-witness interviews for clues.
Assume accomplice would be paid for their help -> Check for large sum deposited to (online or cash) account shortly after crime was committed. Thief may be using an offshore account / or using all cash.
Assume crime was premeditated as an accomplice was accounted for (not a spur of the moment decision), safely assume that the date of the crime and flight details were booked/planned in advance.
Back and forth phone calls (?) made between thief and accomplice before crime (weeks or months)

Inferences:
If I was a thief who stole a large sum of money I would not be flying economy class out of town (choose First Class)
*/

--Step 1: Review crime scene report from July 28, 2021
/*Analysis: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
3 witnesses - each one mentions the bakery */

SELECT *
  FROM crime_scene_reports
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND street = "Humphrey Street";

--Step 2: Gather witness transcripts
/*Analysis:
| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

Thief left the scene sometime between 10:15 - 10:25
Accomplice was not with the thief during the time of the theft.
*/

SELECT *
  FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28;

--Step 3: Review bakery security logs from the time the crime was committed to 10 minutes past (according to Ruth's statement)
/*Analysis:
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
+-----+------+-------+-----+------+--------+----------+---------------+
*/

SELECT *
  FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND hour = 10
   AND minute BETWEEN 15 AND 25;

--Step 4: Review ATM Withdrawls on Leggett Street (according to Eugene's statement)
/*Analysis:
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
*/

SELECT *
  FROM atm_transactions
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND atm_location = "Leggett Street"
   AND transaction_type = "withdraw";

--Step 5: Review incoming/outgoing phone calls made between 10:15 and 10:25
/*Analysis:
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+
Thief (caller) and Accomplice (receiver)
*/

SELECT *
  FROM phone_calls
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60;   --Duration of the call was less than a minute

--Step 6: Gather possible list of suspects (Thief)
/*Analysis:
+-------+
| name  |
+-------+
| Bruce |
| Diana |
+-------+
*/

SELECT name
  FROM people
       JOIN bank_accounts
       ON bank_accounts.person_id = people.id

 WHERE license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND hour = 10
           AND minute BETWEEN 15 AND 25)
   AND phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND duration < 60)
   AND account_number IN
       (SELECT account_number
          FROM atm_transactions
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND atm_location = "Leggett Street"
           AND transaction_type = "withdraw");

--Step 7: Identify Fiftyville's airport code
/*Analysis:
+----+--------------+-----------------------------+------------+
| id | abbreviation |          full_name          |    city    |
+----+--------------+-----------------------------+------------+
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
+----+--------------+-----------------------------+------------+
*/

SELECT *
  FROM airports
 WHERE city = "Fiftyville";

--Step 8: Identify earliest flight out of Fiftyville scheduled on July 29, 2021 (according to Raymond's statement)
/*Analysis:
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
*/

SELECT *
  FROM flights
 WHERE origin_airport_id = 8
   AND year = 2021
   AND month = 7
   AND day = 29
 ORDER BY hour;

--Step 9: Identify flight destination
/*Analysis:
+----+--------------+-------------------+---------------+
| id | abbreviation |     full_name     |     city      |
+----+--------------+-------------------+---------------+
| 4  | LGA          | LaGuardia Airport | New York City |
+----+--------------+-------------------+---------------+
*/

SELECT *
  FROM airports
 WHERE id = 4;

 --Step 10: Review passenger list of CSF -> LGA flight on July 29, 2021 (0820 hrs)
/*Analysis:
+-------+
| name  |
+-------+
| Bruce |
+-------+

Bruce is the culprit.
*/

SELECT name
  FROM people
 WHERE passport_number IN
       (SELECT passport_number
          FROM passengers
         WHERE flight_id = 36)
   AND name IN
       ("Bruce", "Diana");

--Step 11: Find accomplice. Who did Bruce make an outgoing call to on July 28, 2021 between the time of 10:15 and 10:25
/*Analysis:
+-------+
| name  |
+-------+
| Robin |
+-------+

Robin is the accomplice.
*/

SELECT phone_number FROM people WHERE name = "Bruce";
/*
+----------------+
|  phone_number  |
+----------------+
| (367) 555-5533 |
+----------------+
*/

SELECT name
  FROM people
 WHERE phone_number IN
       (SELECT receiver
          FROM phone_calls
         WHERE caller = "(367) 555-5533"
           AND year = 2021
           AND month = 7
           AND day = 28
           AND duration < 60);