-- Keep a log of any SQL queries you execute as you solve the mystery.

-- You may find it helpful to start with the crime_scene_reports table.
-- Start by looking for a crime scene report that matches the date and the location of the crime.

--.schema crime_scene_reports

SELECT id, description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = "Humphrey Street";
-- We're interested in crime_scene_report id 295.
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the bakery.

--.schema interviews
SELECT id, month, day, transcript from interviews
WHERE INSTR(transcript, 'bakery') AND month = 7 AND day = 28;
/*
| 161 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
| 193 | 7     | 28  | I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.
*/

SELECT license_plate, activity, hour, minute FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 16 and 30;

/* List of possible license plates exit within 15 mins of the theft:
+---------------+----------+------+--------+
| license_plate | activity | hour | minute |
+---------------+----------+------+--------+
| 5P2BI95       | exit     | 10   | 16     |
| 94KL13X       | exit     | 10   | 18     |
| 6P58WS2       | exit     | 10   | 18     |
| 4328GD8       | exit     | 10   | 19     |
| G412CB7       | exit     | 10   | 20     |
| L93JTIZ       | exit     | 10   | 21     |
| 322W7JE       | exit     | 10   | 23     |
| 0NTHK55       | exit     | 10   | 23     |
+---------------+----------+------+--------+
*/

--Cross-referencing with people table to get names of suspects:
SELECT people.id, name, phone_number, passport_number, bakery_security_logs.license_plate, bakery_security_logs.hour, bakery_security_logs.minute FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.license_plate = people.license_plate AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 16 and 35;

/*
NAMES OF SUSPECTS
+--------+---------+----------------+-----------------+---------------+------+--------+
|   id   |  name   |  phone_number  | passport_number | license_plate | hour | minute |
+--------+---------+----------------+-----------------+---------------+------+--------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       | 10   | 16     |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 10   | 18     |
| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       | 10   | 18     |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       | 10   | 19     |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       | 10   | 20     |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       | 10   | 21     |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 10   | 23     |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       | 10   | 23     |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | 10   | 35     |
+--------+---------+----------------+-----------------+---------------+------+--------+
*/


SELECT * FROM atm_transactions
WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

/*
WITHDRAWALS that could have been by the theif
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

-- Cross reference to bank-accounts to get person ID and names

SELECT * FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

/*
+-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount | account_number | person_id | creation_year |   id   |  name   |  phone_number  | passport_number | license_plate |
+-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     | 49610011       | 686048    | 2010          | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     | 26013199       | 514354    | 2012          | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     | 16153065       | 458378    | 2012          | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     | 28296815       | 395717    | 2014          | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     | 25506511       | 396669    | 2014          | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     | 28500762       | 467400    | 2014          | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     | 76054385       | 449774    | 2015          | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     | 81061156       | 438727    | 2018          | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
+-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
*/

--cross refernce this list of license to the earlier list of possible license plates

SELECT DISTINCT people.name, people.phone_number, people.license_plate, bakery_security_logs.hour, bakery_security_logs.minute FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.license_plate = people.license_plate AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute BETWEEN 16 and 35 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw";

/* License plates linked to names matching those from bakery seurity logs and atm transactions. Remaining suspects:
+--------+----------------+---------------+------+--------+
|  name  |  phone_number  | license_plate | hour | minute |
+--------+----------------+---------------+------+--------+
| Bruce  | (367) 555-5533 | 94KL13X       | 10   | 18     |
| Luca   | (389) 555-5198 | 4328GD8       | 10   | 19     |
| Taylor | (286) 555-6063 | 1106N58       | 10   | 35     |
| Iman   | (829) 555-5269 | L93JTIZ       | 10   | 21     |
| Diana  | (770) 555-1861 | 322W7JE       | 10   | 23     |
+--------+----------------+---------------+------+--------+
*/

/*++++++++++++++++++++
As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket. |
*/

SELECT * FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE caller in ("(367) 555-5533", "(389) 555-5198", "(286) 555-6063", "(829) 555-5269", "(770) 555-1861") AND duration < 60 AND day = 28;

/* NEW SHORT LIST of suspects:
+-----+----------------+----------------+------+-------+-----+----------+--------+--------+----------------+-----------------+---------------+
| id  |     caller     |    receiver    | year | month | day | duration |   id   |  name  |  phone_number  | passport_number | license_plate |
+-----+----------------+----------------+------+-------+-----+----------+--------+--------+----------------+-----------------+---------------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       | 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
+-----+----------------+----------------+------+-------+-----+----------+--------+--------+----------------+-----------------+---------------+
*/


SELECT * FROM flights
JOIN airports ON airports.id = flights.destination_airport_id
WHERE month = 7 AND day = 29
ORDER BY month, day, hour, minute;

/* All possible flights sorted by depature time
+----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-------------------------------------+---------------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | id | abbreviation |              full_name              |     city      |
+----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-------------------------------------+---------------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 4  | LGA          | LaGuardia Airport                   | New York City |
| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     | 1  | ORD          | O'Hare International Airport        | Chicago       |
| 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     | 11 | SFO          | San Francisco International Airport | San Francisco |
| 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     | 9  | HND          | Tokyo International Airport         | Tokyo         |
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 6  | BOS          | Logan International Airport         | Boston        |
+----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-------------------------------------+---------------+

The earliest flight is at 8:20 destined for LGA, New York City, this is Where the thief escaped to
*/

Select * FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
WHERE passengers.passport_number in (5773159633, 1988161715, 3592750733) and flight_id = 36;

/* NEW SHORT LIST of suspects: Its bruce becuase Taylor was more than 15 mins on the security footage.
+-----------+-----------------+------+--------+--------+----------------+-----------------+---------------+
| flight_id | passport_number | seat |   id   |  name  |  phone_number  | passport_number | license_plate |
+-----------+-----------------+------+--------+--------+----------------+-----------------+---------------+
| 36        | 5773159633      | 4A   | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
| 36        | 1988161715      | 6D   | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
+-----------+-----------------+------+--------+--------+----------------+-----------------+---------------+
*/

--All the people Bruce called
SELECT * FROM phone_calls
JOIN people on people.phone_number = phone_calls.receiver
WHERE day = 28 and caller = "(367) 555-5533";
/*
+-----+----------------+----------------+------+-------+-----+----------+--------+---------+----------------+-----------------+---------------+
| id  |     caller     |    receiver    | year | month | day | duration |   id   |  name   |  phone_number  | passport_number | license_plate |
+-----+----------------+----------------+------+-------+-----+----------+--------+---------+----------------+-----------------+---------------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       | 864400 | Robin   | (375) 555-8161 |                 | 4V16VO0       |
| 236 | (367) 555-5533 | (344) 555-9601 | 2021 | 7     | 28  | 120      | 985497 | Deborah | (344) 555-9601 | 8714200946      | 10I5658       |
| 245 | (367) 555-5533 | (022) 555-4052 | 2021 | 7     | 28  | 241      | 315221 | Gregory | (022) 555-4052 | 3355598951      | V4C670D       |
| 285 | (367) 555-5533 | (704) 555-5790 | 2021 | 7     | 28  | 75       | 652398 | Carl    | (704) 555-5790 | 7771405611      | 81MZ921       |
+-----+----------------+----------------+------+-------+-----+----------+--------+---------+----------------+-----------------+---------------+
*/

--The accomplice is Robin, because its the only call here to last less than 60 sec.