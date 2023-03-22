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