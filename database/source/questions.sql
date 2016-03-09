-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS questions CASCADE;

CREATE TABLE questions (
question_id SERIAL PRIMARY KEY,
survey_id INTEGER REFERENCES surveys ON UPDATE CASCADE ON DELETE CASCADE,
question_name VARCHAR(256),
question_type INTEGER,

FOREIGN KEY (survey_id) REFERENCES surveys(survey_id)
);