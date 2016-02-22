-- Create Survey Types

INSERT INTO surveytypes VALUES (1, 'DA Trainingsseminar');
INSERT INTO surveytypes VALUES (2, 'DA Feedbackseminar');
INSERT INTO surveytypes VALUES (3, 'EgfH Trainingsseminar');
INSERT INTO surveytypes VALUES (4, 'EgfH Feedbackseminar');
INSERT INTO surveytypes VALUES (5, 'LMI Trainingsseminar');
INSERT INTO surveytypes VALUES (6, 'LMI Trainingsseminar');

-- Create Survey
INSERT INTO surveys VALUES (1,'DA Hameln',1,'02/28/2015');

-- Create Questiontype

INSERT INTO questiontypes VALUES (1, 'Mittelwert', 'mean_value()');

--create questions

INSERT INTO questions VALUES (1, 1, 'Wie viel Spaß hats gemacht',1); 

-- create subquestion
INSERT INTO subquestions VALUES (1, 1, '');

-- add data
INSERT INTO data VALUES (1, 1, 4);
INSERT INTO data VALUES (2, 1, 7);
INSERT INTO data VALUES (3, 1, 8);
INSERT INTO data VALUES (4, 1, 0);
INSERT INTO data VALUES (5, 1, 2);

