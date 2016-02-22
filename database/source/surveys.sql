-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS surveys;

CREATE TABLE surveys(
id INTEGER PRIMARY KEY, 
surveytype_id INT, 
name VARCHAR(30),

survey_date DATE, 

FOREIGN KEY (surveytype_id) REFERENCES surveytypes(id)

);

