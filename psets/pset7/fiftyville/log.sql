-- Report of crime scene
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2021 and street = "Humphrey Street";
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Witness statements
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28 AND year = 2021;
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

/*
Thief leaves in time frame (10:15 - 10:25)
ATM Location : Legget Street
Transaction Type : Withdraw
Time of Withdrawal : morning of robbery
Duration of Phone call with Accomplice : less than 60 seconds
Flight : earliest flight out of Fiftyville the day after robbery (7/29/2021)
Misc : asked Accomplice to buy tickets
*/

-- selected ids of all people that left the bakery within 10 minutes of robbery
SELECT id AS bakeryPeopleID FROM people WHERE license_plate IN 
    (SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute > 15
        AND minute <= 25
        AND activity = "exit")
;

-- selected ids of all people that made a withdrawal at Leggett Street the day of robbery
SELECT person_id AS peopleAtATMID FROM bank_accounts WHERE account_number IN
    (SELECT account_number FROM atm_transactions
        WHERE atm_location = "Leggett Street"
        AND transaction_type = "withdraw"
        AND month = 7
        AND day = 28
        AND year = 2021
    )
;

/*
The previous two queries and following query resulted in 4 common people IDS and their names
396669 - Iman
467400 - Luca
514354 - Diana
686048 - Bruce
*/

SELECT id, name FROM people
    WHERE id = 396669
    OR id = 467400
    OR id = 514354
    OR id = 686048
;

-- Determine origin airport ID of airport at Fiftyville
-- SELECT id FROM airports WHERE city = "Fiftyville";
-- Airport ID of Fiftyville : 8

-- determine the earliest flight out of Fiftyville on 7/29/2021
SELECT id,hour FROM flights
    WHERE origin_airport_id = 8
    AND month = 7
    AND day = 29
    AND year = 2021
    ORDER BY hour
;
-- earliest flight out of Fiftyville ID : 36

-- select which of those four people where on the flight (id = 8)
SELECT id FROM people
    WHERE passport_number IN
        (SELECT passport_number FROM passengers
            WHERE flight_id = 36
        )
    AND id = 396669
    OR id = 467400
    OR id = 514354
    OR id = 696048
;

-- Boiled down to two people
/*
467400 - Luca
686048 - Bruce
*/
-- in order to link id to phone number
SELECT id,phone_number FROM people
    WHERE id = 467400
    OR id = 686048
;

-- Phone numbers to ID
/*
467400 : 389-555-5198
686048 : 367-555-5533
*/

-- Select the determine the people that a person called for less than 60 seconds
SELECT receiver FROM phone_calls
    WHERE duration < 60
    AND caller = "(367) 555-5533"
;

-- We know for sure 686048 is the thief
-- We have to determine the accomplice
SELECT id,phone_number,passport_number FROM people
    WHERE phone_number IN
        (SELECT receiver FROM phone_calls
            WHERE duration < 60
            AND caller = "(367) 555-5533"
            AND year = 2021
            AND month = 7
            AND day = 28
        )
;

-- possible accomplices
-- 639344
-- 864400

-- THIEF : 686048
-- ACCOMPLICE : 864400
-- find destination airport city
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);

/*
Thief : 686048
Accomplice : 864400
City : New York City
*/
