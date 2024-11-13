/*
Enter your query here.
*/


WITH Ordered AS (
    SELECT
        LAT_N as LAT_N,
        ROW_NUMBER() OVER(ORDER BY LAT_N) AS row_num,
        COUNT(*) OVER() AS max_rows
    FROM STATION
)

SELECT round(avg(LAT_N) ,4)
    FROM Ordered
        WHERE row_num IN (floor((Ordered.max_rows + 1) / 2), ceil((Ordered.max_rows + 1) / 2));