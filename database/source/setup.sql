-- Create Survey Types
-- GENERATE SURVEYTYPES
INSERT INTO surveytypes VALUES (0, 'DA Trainingsseminar');
INSERT INTO surveytypes VALUES (1, 'DA Feedbackseminar');
INSERT INTO surveytypes VALUES (2, 'EgfH Trainingsseminar');
INSERT INTO surveytypes VALUES (3, 'EgfH Feedbackseminar');
INSERT INTO surveytypes VALUES (4, 'LMI Trainingsseminar');
INSERT INTO surveytypes VALUES (5, 'LMI Trainingsseminar');

-- ADD QUESTIONTYPES TO SURVEYTYPES: DA TRAININGSSEMINAR
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);	-- 0 - ignore question
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 1); -- 1 - mean value
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 2); -- 2 -- share of non zeros, how many agre with...
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 6);	-- 6 - text question
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 6);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 6);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 4); -- 4 age
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 3); -- 3 - gender
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 5); -- 5 - Schooltype (DA Questionaire)
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (0, 0);

-- DA Feedbackseminar

INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,6);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,7); -- 7 ELEARNING
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,8); --8  GRUPPENANZAHL
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,0);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,2);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,6);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,6);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,1);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,6);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,6);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,4);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,5);
INSERT INTO qtypes(surveytype_id, qtype) VALUES (1,3);


















