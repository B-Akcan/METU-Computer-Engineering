-- Q1
SELECT DISTINCT P.Name
FROM Professor P, Teaching T, Course C
WHERE P.DeptID != "CENG" AND P.ProfessorId = T.ProfessorId AND T.CourseId = C.CourseId AND C.DeptID = "CENG";

-- Q2
SELECT S.name
FROM Student S
WHERE S.studentId IN
    (SELECT S1.StudentId
    FROM Student S1, Transcript T1, Course C1
    WHERE S1.StudentId = T1.studentId AND T1.courseID = C1.courseId AND C1.courseName = "Introduction to C Programming"
    INTERSECT
    SELECT S1.StudentId
    FROM Student S1, Transcript T1, Course C1
    WHERE S1.StudentId = T1.studentId AND T1.courseID = C1.courseId AND C1.courseName = "Electrical Circuits Laboratory");

-- Q3
SELECT P.name, P.age
FROM Professor P
WHERE P.deptId = "CENG"
UNION
SELECT P.name, P.age
FROM Professor P, Teaching T, Course C
WHERE P.professorId = T.professorID AND T.CourseId = C.courseId AND C.deptId = "CENG";

-- Q4
SELECT S.name, S.gpa
FROM Student S
WHERE S.gpa > (SELECT MAX(S2.gpa)
               FROM Student S2
               WHERE S2.status = "Senior");

-- Q5
SELECT S.studentID, AVG(T.score)
FROM Student S, Transcript T
WHERE S.studentId = T.studentID AND (T.semester = "F2013" OR T.semester = "S2014")
GROUP BY S.studentID
HAVING AVG(T.score) > 50;

-- Q6
SELECT S.name
FROM Student S
WHERE NOT EXISTS (SELECT C.courseID
                    FROM Course C
                    WHERE C.deptId = "EE"
                    EXCEPT
                    SELECT C1.courseId
                    FROM Course C1, Transcript T
                    WHERE T.studentID = S.studentID AND T.courseId = C1.courseId);