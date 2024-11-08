/*
Enter your query here.
*/
SELECT
    CASE
        WHEN a + b <= c OR a + c <= b OR b + c <= a THEN 'Not A Triangle'
        WHEN a = b AND b = c THEN 'Equilateral'
        WHEN a != b AND b != c AND a != c THEN 'Scalene'
        WHEN a = b OR b = c or a = c THEN 'Isosceles'
    END AS comparison_result
FROM triangles;
