-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS questions;

CREATE TABLE questions (
id INTEGER PRIMARY KEY,
survey_id INT,
question VARCHAR(256),
type INT,

FOREIGN KEY (survey_id) REFERENCES surveys(id)
);