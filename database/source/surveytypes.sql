-- Sebastian Ratz @ 2016-02-11 [YYYY-MM-DD]
-- BERLIN

-- DATABASE : Feedbacker_db 
-- ORIGIN   : MS SQL 
-- SOURCE   : SQLITE 3
-- 
-- using foreign keys

DROP TABLE IF EXISTS surveytypes CASCADE;

CREATE TABLE surveytypes(
surveytype_id SERIAL PRIMARY KEY,
surveytype_name VARCHAR(50)

);