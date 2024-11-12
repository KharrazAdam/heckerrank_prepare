/*
Enter your query here.
*/

SELECT MAX(salary * months), count(Name)
    FROM Employee
        WHERE salary * months = (SELECT MAX(salary * months) FROM Employee);
        