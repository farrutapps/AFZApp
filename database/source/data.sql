-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS data;

CREATE TABLE data(
id INTEGER PRIMARY KEY,
subq_id INT,
answer INT,


FOREIGN KEY (subq_id) REFERENCES subquestions(id)

);