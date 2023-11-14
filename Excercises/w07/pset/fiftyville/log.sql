-- Keep a log of any SQL queries you execute as you solve the mystery.
-- See the crime reports table
SELECT * FROM crime_scene_reports;

-- Query the table for events on specific day on specific street
SELECT * FROM crime_scene_reports WHERE year=2021 AND month=7 AND day=28 AND street='Humphrey Street';
-- this gave two reults, the proper one has crime_scene_reports.id = 295


SELECT description FROM crime_scene_reports WHERE id = 295;
-- This gives description:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.


SELECT * FROM interviews WHERE transcript LIKE "%bakery%";
-- There are 4 reports that mention bakery. 1 of those is from before the crime (id = 192)
-- Interviews id = (161,162,163) are from the day of the crime
-- The thief:
--- Parked in the parking lot -> check logs - around ten minutes earlier
--- Used ATM in the morning on Leggett Street -> withdraw
--- Planned to take a flight on 2021-07-29

SELECT * FROM airports WHERE city = 'Fiftyville';
-- found airport: abbreviation = 'CSF' full_name = 'Fiftyville Regional Airport'

SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >=15 AND minute <= 25;
-- narrow down to the names
SELECT name FROM people, bakery_security_logs WHERE people.license_plate = bakery_security_logs.license_plate AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

SELECT * FROM atm_transactions WHERE year=2021 AND month=7 AND day=28 AND atm_location='Leggett Street';
-- a lot of different withdraws and one deposit
SELECT name FROM people, bank_accounts, atm_transactions
    WHERE people.id = bank_accounts.person_id
    AND bank_accounts.account_number = atm_transactions.account_number
    AND month = 7
    AND day = 28
    AND transaction_type = "withdraw"
    AND atm_location = "Leggett Street";

SELECT name FROM people, bank_accounts, atm_transactions
    WHERE people.id = bank_accounts.person_id
    AND bank_accounts.account_number = atm_transactions.account_number
    AND month = 7
    AND day = 28
    AND transaction_type = "withdraw"
    AND atm_location = "Leggett Street"
    AND name IN
        (SELECT name FROM people, bakery_security_logs
            WHERE people.license_plate = bakery_security_logs.license_plate
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 25);
-- Getting all the people that left the bakery in 10 minutes of theft with car, and also withdrawn money at Leggett Street: Bruze, Diana, Iman, Luca

-- check flight next day
SELECT flights.id, full_name, city, flights.hour, flights.minute FROM airports
    JOIN flights ON airports.id = flights.destination_airport_id
        WHERE flights.origin_airport_id =
            (SELECT id FROM airports WHERE city = 'Fiftyville')
        AND flights.year = 2021
        AND flights.month = 7
        AND flights.day = 29
        ORDER BY flights.hour, flights.minute;

--fist one to new york
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
  FROM people
  JOIN passengers
    ON people.passport_number = passengers.passport_number
  JOIN flights
    ON passengers.flight_id = flights.id
 WHERE flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29
   AND flights.hour = 8
   AND flights.minute = 20
 ORDER BY passengers.passport_number;

 -- combine sql queries
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
    FROM people
    JOIN passengers
    ON people.passport_number = passengers.passport_number
    JOIN flights
    ON passengers.flight_id = flights.id
    WHERE flights.year = 2021
    AND flights.month = 7
    AND flights.day = 29
    AND flights.hour = 8
    AND flights.minute = 20
    AND name IN
        (SELECT name FROM people, bank_accounts, atm_transactions
            WHERE people.id = bank_accounts.person_id
            AND bank_accounts.account_number = atm_transactions.account_number
            AND month = 7
            AND day = 28
            AND transaction_type = "withdraw"
            AND atm_location = "Leggett Street"
            AND name IN
                (SELECT name FROM people, bakery_security_logs
                    WHERE people.license_plate = bakery_security_logs.license_plate
                    AND month = 7
                    AND day = 28
                    AND hour = 10
                    AND minute >= 15
                    AND minute <= 25))
    ORDER BY passengers.passport_number;
-- getting Bruce and Luca

SELECT name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28;
--getting all the callers from that day



SELECT DISTINCT name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND name IN
        (SELECT name FROM people
            JOIN passengers
            ON people.passport_number = passengers.passport_number
            JOIN flights
            ON passengers.flight_id = flights.id
            WHERE flights.year = 2021
            AND flights.month = 7
            AND flights.day = 29
            AND flights.hour = 8
            AND flights.minute = 20
            AND name IN
                (SELECT name FROM people, bank_accounts, atm_transactions
                    WHERE people.id = bank_accounts.person_id
                    AND bank_accounts.account_number = atm_transactions.account_number
                    AND month = 7
                    AND day = 28
                    AND transaction_type = "withdraw"
                    AND atm_location = "Leggett Street"
                    AND name IN
                        (SELECT name FROM people, bakery_security_logs
                        WHERE people.license_plate = bakery_security_logs.license_plate
                        AND month = 7
                        AND day = 28
                        AND hour = 10
                        AND minute >= 15
                        AND minute <= 25))
 ORDER BY passengers.passport_number);
 -- Bruce is the only person that appears in all the lists


-- find the accomplice by checking who did Bruce spoke to on that day
SELECT people.name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.receiver
    WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration <= 60
    AND phone_calls.caller =
        (SELECT DISTINCT phone_calls.caller FROM people
            JOIN phone_calls ON people.phone_number = phone_calls.caller
            WHERE phone_calls.year = 2021
            AND phone_calls.month = 7
            AND phone_calls.day = 28
            AND name IN
                (SELECT name FROM people
                    JOIN passengers
                    ON people.passport_number = passengers.passport_number
                    JOIN flights
                    ON passengers.flight_id = flights.id
                    WHERE flights.year = 2021
                    AND flights.month = 7
                    AND flights.day = 29
                    AND flights.hour = 8
                    AND flights.minute = 20
                    AND name IN
                        (SELECT name FROM people, bank_accounts, atm_transactions
                            WHERE people.id = bank_accounts.person_id
                            AND bank_accounts.account_number = atm_transactions.account_number
                            AND month = 7
                            AND day = 28
                            AND transaction_type = "withdraw"
                            AND atm_location = "Leggett Street"
                            AND name IN
                                (SELECT name FROM people, bakery_security_logs
                                WHERE people.license_plate = bakery_security_logs.license_plate
                                AND month = 7
                                AND day = 28
                                AND hour = 10
                                AND minute >= 15
                                AND minute <= 25))
 ORDER BY passengers.passport_number));
-- getting Robin
