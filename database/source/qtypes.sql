-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS qtypes;

CREATE TABLE qtypes(
qtype_id INTEGER PRIMARY KEY,
surveytype_id INT REFERENCES surveytypes ON UPDATE CASCADE ON DELETE CASCADE,
qtype INT
);