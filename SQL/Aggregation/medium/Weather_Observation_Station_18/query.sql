/*
Enter your query here.
*/

SELECT round(abs(min(LAT_N) - max(LONG_W)) + abs(max(LAT_N) - min(LONG_W)), 4)
    FROM STATION;