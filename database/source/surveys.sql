-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS surveys;

CREATE TABLE surveys(
survey_id INTEGER PRIMARY KEY, 
surveytype_id INT REFERENCES surveytypes, 
survey_name VARCHAR(30),

survey_date DATE,
survey_datasize INT

);

