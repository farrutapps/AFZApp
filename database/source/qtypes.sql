-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS qtypes;

CREATE TABLE qtypes(
id INTEGER PRIMARY KEY,
surveytype_id INT,
qtype INT,

FOREIGN KEY (surveytype_id) REFERENCES surveytypes(id)
);