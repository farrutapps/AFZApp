-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS subquestions CASCADE;

CREATE TABLE subquestions (
subquestion_id SERIAL PRIMARY KEY,
question_id INTEGER REFERENCES questions ON UPDATE CASCADE ON DELETE CASCADE,
subquestion_name VARCHAR(256)
);