-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS subquestions;

CREATE TABLE subquestions (
subquestion_id INTEGER PRIMARY KEY,
question_id INT REFERENCES questions,
subquestion_name VARCHAR(256)
);