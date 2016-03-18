-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS data_numeric CASCADE;

CREATE TABLE data_numeric (
data_numeric_id SERIAL PRIMARY KEY,
subquestion_id INTEGER REFERENCES subquestions ON UPDATE CASCADE ON DELETE CASCADE,
answer_numeric INTEGER

);