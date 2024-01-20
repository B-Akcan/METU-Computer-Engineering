-- Q1
SELECT DISTINCT R.sid
FROM Reserves R;

-- Q2
SELECT DISTINCT R.sid
FROM Reserves R, Boats B
WHERE R.bid = B.bid AND (B.color = "red" OR B.color = "green");

-- Q3
SELECT DISTINCT S.sid
FROM Sailors S, Reserves R, Boats B
WHERE S.sid = R.sid AND R.bid = B.bid AND B.color = "red"
INTERSECT
SELECT DISTINCT S.sid
FROM Sailors S, Reserves R, Boats B
WHERE S.sid = R.sid AND R.bid = B.bid AND B.color = "green";

-- Q4
SELECT DISTINCT S1.sname
FROM Sailors S1
WHERE S1.sid IN
(SELECT S.sid
FROM Sailors S, Reserves R, Boats B
WHERE S.sid = R.sid AND R.bid = B.bid AND B.color = "red"
INTERSECT
SELECT S.sid
FROM Sailors S, Reserves R, Boats B
WHERE S.sid = R.sid AND R.bid = B.bid AND B.color = "green");

-- Q5
SELECT DISTINCT S.sname
FROM Sailors S, Reserves R
WHERE S.sid = R.sid AND R.bid = 103
ORDER BY S.sname ASC;

-- Q6
SELECT S.sid, S.sname, S.rating, S.age
FROM Sailors S
WHERE S.rating > (SELECT MIN(S2.rating)
                  FROM Sailors S2
                  WHERE S2.sname = "Horatio");

-- Q7
SELECT S.sid, S.sname, S.rating, S.age
FROM Sailors S
WHERE S.rating > (SELECT MAX(S2.rating)
                  FROM Sailors S2
                  WHERE S2.sname = "Horatio");

-- Q8
SELECT S.sid, S.sname, S.rating, S.age
FROM Sailors S
WHERE S.rating = (SELECT MAX(S2.rating)
                  FROM Sailors S2);

-- Q9
SELECT S.sname
FROM Sailors S
WHERE NOT EXISTS (SELECT B.bid
                  FROM Boats B
                  EXCEPT
                  SELECT R.bid
                  FROM Reserves R
                  WHERE S.sid = R.sid);

-- Q10
SELECT S.sname, S.age
FROM Sailors S
WHERE S.age = (SELECT MAX(S2.age)
               FROM Sailors S2);

-- Q11
SELECT S.rating, MIN(S.age)
FROM Sailors S
WHERE S.age >= 18
GROUP BY S.rating
HAVING COUNT(*) > 1;

-- Q12
SELECT B.bid, COUNT(*)
FROM Reserves R, Boats B
WHERE R.bid = B.bid AND B.color = "red"
GROUP BY B.bid;

-- Q13
SELECT S.rating, MIN(S.age)
FROM Sailors S
WHERE S.age >= 18
GROUP BY S.rating
HAVING S.rating IN (SELECT S2.rating
                    FROM Sailors S2
                    GROUP BY S2.rating
                    HAVING COUNT(*) > 1);

-- Q14
SELECT S.rating, AVG(S.age)
FROM Sailors S
GROUP BY S.rating
HAVING AVG(S.age) = (SELECT MIN(avgage)
                     FROM (SELECT AVG(S2.age) AS avgage
                           FROM Sailors S2
                           GROUP BY S2.rating));