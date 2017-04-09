set echo on;
set serveroutput on;

CREATE OR REPLACE TRIGGER trg_prod_QOH_on_line_delete
AFTER DELETE ON LINE FOR EACH ROW
BEGIN
UPDATE PRODUCT
SET P_QOH = P_QOH + :old.LINE_UNITS
where P_CODE = :old.P_CODE;
END;
/
COMMIT;

SELECT P_CODE, P_QOH FROM PRODUCT WHERE P_CODE='54778-2T';
SELECT * FROM LINE WHERE P_CODE='54778-2T';

DELETE FROM LINE WHERE INV_NUMBER = 1004 AND P_CODE ='54778-2T'; 


SELECT P_CODE, P_QOH FROM PRODUCT WHERE P_CODE='54778-2T';
SELECT * FROM LINE WHERE P_CODE='54778-2T';


rollback;
/*
SQL> set echo on
SQL> set serveroutput on
SQL> CREATE OR REPLACE TRIGGER trg_prod_QOH_on_line_delete
AFTER DELETE ON LINE FOR EACH ROW
BEGIN
UPDATE PRODUCT
SET P_QOH = P_QOH + :old.LINE_UNITS
where P_CODE = :old.P_CODE;
END;
/

Trigger TRG_PROD_QOH_ON_LINE_DELETE compiled
SQL> SELECT P_CODE, P_QOH FROM PRODUCT WHERE P_CODE='54778-2T';

P_CODE          P_QOH
---------- ----------
54778-2T           43

SQL> SELECT * FROM LINE WHERE P_CODE='54778-2T';
INV_NUMBER LINE_NUMBER P_CODE     LINE_UNITS LINE_PRICE
---------- ----------- ---------- ---------- ----------
      1002           1 54778-2T            2       4.99
      1004           1 54778-2T            3       4.99
      1007           2 54778-2T            1       4.99

SQL> DELETE FROM LINE WHERE INV_NUMBER = 1004 AND P_CODE ='54778-2T';

1 row deleted.

SQL> SELECT P_CODE, P_QOH FROM PRODUCT WHERE P_CODE='54778-2T';

P_CODE          P_QOH
---------- ----------
54778-2T           46

SQL> SELECT * FROM LINE WHERE P_CODE='54778-2T';

INV_NUMBER LINE_NUMBER P_CODE     LINE_UNITS LINE_PRICE
---------- ----------- ---------- ---------- ----------
      1002           1 54778-2T            2       4.99
      1007           2 54778-2T            1       4.99

SQL> rollback;

Rollback complete.

*/