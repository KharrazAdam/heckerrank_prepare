/*
Enter your query here.
*/
SELECT round(sqrt(pow(min(LAT_N) - max(LAT_N), 2) + pow(min(LONG_W) - max(LONG_W), 2)), 4)
    FROM STATION;