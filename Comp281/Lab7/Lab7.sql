describe BOOKS_CHECKED_OUT;
select * from BOOKS_CHECKED_OUT;
describe BOOK_LIST;
select * from BOOK_LIST;
describe CARD_HOLDERS;
select * from CARD_HOLDERS;
describe BOOK_CATEGORIES;
select * from BOOK_CATEGORIES;


Create USER saigonosu identified by Bigdevosu

grant create session to saigonosu

create role awesome


grant select, insert, update on devlin08.CARD_HOLDERS to awesome

grant awesome to saigonosu

commit



set role awesome

commit

Revoke Insert on devlin08.CARD_HOLDERS from awesome

SELECT * FROM devlin08.CARD_HOLDERS;
INSERT INTO devlin08.CARD_HOLDERS VALUES (12, 'Carol', 'Adams', '101 Arc Street',
'Seattle', 'WA', '01256');
UPDATE devlin08.CARD_HOLDERS SET LAST_NAME = 'Camel' WHERE
CARDHOLDER_NUMBER = 1;
DELETE FROM devlin08.CARD_HOLDERS WHERE LAST_NAME = 'Camel';
commit

CREATE VIEW DEVLIN08.S_LIST AS Select CH.Cardholder_Number, CH.Last_name, CH.First_Name, BCO.Due_date
FROM DEVLIN08.CARD_HOLDERS CH
JOIN DEVLIN08.BOOKS_CHECKED_OUT BCO
ON CH.Cardholder_Number = BCO.Cardholder_Number
WHERE BCO.Actual_Return_date is null;

grant select on DEVLIN08.S_LIST to awesome


select * from devlin08.S_LIST;


Create role teammates;
grant insert, delete on devlin08.BOOKS_CHECKED_OUT to teammates;
grant insert, delete on devlin08.BOOK_LIST to teammates;
grant insert, delete on devlin08.CARD_HOLDERS to teammates;
grant insert, delete on devlin08.BOOK_CATEGORIES to teammates;
grant teammates to student1;
grant teammates to student2;
grant teammates to student3;
grant teammates to student4;
grant teammates to crawforl;
set teammates;