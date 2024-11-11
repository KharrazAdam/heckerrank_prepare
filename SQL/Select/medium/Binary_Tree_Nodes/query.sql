/*
Enter your query here.
*/

SELECT N,
        CASE
            WHEN P IS NULL THEN 'Root' -- Ma weld 7ed
        WHEN (SELECT COUNT(*) FROM BST AS inner_bst WHERE inner_bst.P = BST.N) > 0 THEN 'Inner' -- 3ando wlad
            ELSE 'Leaf'
        END AS node_type
FROM BST ORDER BY N ASC;