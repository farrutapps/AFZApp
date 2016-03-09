-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS qtypes CASCADE;

CREATE TABLE qtypes(
qtype_id SERIAL PRIMARY KEY,
surveytype_id INTEGER REFERENCES surveytypes ON UPDATE CASCADE ON DELETE CASCADE,
qtype INTEGER
);