/*
Enter your query here.
*/

SELECT ROUND(LONG_W, 4)
    FROM STATION
        WHERE LAT_N = (SELECT MAX(LAT_N) FROM STATION WHERE LAT_N < 137.2345)