/*
Enter your query here.
*/
SELECT DISTINCT c.company_code, c.founder, 
                count(DISTINCT e.lead_manager_code), 
                count(DISTINCT e.senior_manager_code),
                count(DISTINCT e.manager_code),
                count(DISTINCT e.employee_code)
    FROM Company c, Employee e
        WHERE c.company_code = e.company_code
    GROUP BY c.company_code
    ORDER BY c.company_code ASC;