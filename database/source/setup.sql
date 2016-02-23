-- Create Survey Types
-- GENERATE SURVEYTYPES
INSERT INTO surveytypes VALUES (1, 'DA Trainingsseminar');
INSERT INTO surveytypes VALUES (2, 'DA Feedbackseminar');
INSERT INTO surveytypes VALUES (3, 'EgfH Trainingsseminar');
INSERT INTO surveytypes VALUES (4, 'EgfH Feedbackseminar');
INSERT INTO surveytypes VALUES (5, 'LMI Trainingsseminar');
INSERT INTO surveytypes VALUES (6, 'LMI Trainingsseminar');

-- ADD QUESTIONTYPES TO SURVEYTYPES: DA TRAININGSSEMINAR
INSERT INTO qtypes VALUES (NULL, 1, 0);	-- 0 - ignore question
INSERT INTO qtypes VALUES (NULL, 1, 0);
INSERT INTO qtypes VALUES (NULL, 1, 0);
INSERT INTO qtypes VALUES (NULL, 1, 0);
INSERT INTO qtypes VALUES (NULL, 1, 0);
INSERT INTO qtypes VALUES (NULL, 1, 0);
INSERT INTO qtypes VALUES (NULL, 1, 0);
INSERT INTO qtypes VALUES (NULL, 1, 0);
INSERT INTO qtypes VALUES (NULL, 1, 0);
INSERT INTO qtypes VALUES (NULL, 1, 1); -- 1 - mean value
INSERT INTO qtypes VALUES (NULL, 1, 2); -- 2 -- share of non zeros, how many agre with...
INSERT INTO qtypes VALUES (NULL, 1, 2);
INSERT INTO qtypes VALUES (NULL, 1, 2);
INSERT INTO qtypes VALUES (NULL, 1, 2);
INSERT INTO qtypes VALUES (NULL, 1, 2);
INSERT INTO qtypes VALUES (NULL, 1, 2);
INSERT INTO qtypes VALUES (NULL, 1, 2);
INSERT INTO qtypes VALUES (NULL, 1, 1);
INSERT INTO qtypes VALUES (NULL, 1, 1);
INSERT INTO qtypes VALUES (NULL, 1, 1);
INSERT INTO qtypes VALUES (NULL, 1, 1);
INSERT INTO qtypes VALUES (NULL, 1, 1);
INSERT INTO qtypes VALUES (NULL, 1, 1);
INSERT INTO qtypes VALUES (NULL, 1, 1);
INSERT INTO qtypes VALUES (NULL, 1, 1);
INSERT INTO qtypes VALUES (NULL, 1, 6);	-- 6 - text question
INSERT INTO qtypes VALUES (NULL, 1, 6);
INSERT INTO qtypes VALUES (NULL, 1, 6);
INSERT INTO qtypes VALUES (NULL, 1, 4); -- 4 age
INSERT INTO qtypes VALUES (NULL, 1, 3); -- 3 - gender
INSERT INTO qtypes VALUES (NULL, 1, 5); -- 5 - Schooltype (DA Questionaire)
INSERT INTO qtypes VALUES (NULL, 1, 0);
INSERT INTO qtypes VALUES (NULL, 1, 0);











{0,0,0,0,0,0,0,0,0,1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,6,6,6,4,3,5,0,0}