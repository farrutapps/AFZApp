-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS data;

CREATE TABLE data(
data_id INTEGER PRIMARY KEY,
subquestion_id INT REFERENCES subquestions ON UPDATE CASCADE ON DELETE CASCADE,
answer INT

);