/*
Enter your query here.
*/

SELECT DISTINCT  CITY
FROM STATION
WHERE  NOT CITY  REGEXP "[aeiou]$"