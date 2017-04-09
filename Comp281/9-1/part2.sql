set echo on;
set serveroutput on;


CREATE OR REPLACE PROCEDURE prc_inv_delete (INV_NUM IN NUMBER)
IS
BEGIN
DELETE from INVOICE where INV_NUMBER = INV_NUM;
END;
/
commit;

select * from invoice where inv_number in (1001,1008);
select * from line where inv_number in (1001,1008);

exec prc_inv_delete(1001);
exec prc_inv_delete(1008);

select * from invoice where inv_number in (1001,1008);
select * from line where inv_number in (1001,1008);

rollback;

--The corresponding lines in LINE did get deleted for invoices 1001 and 1008
--This is because of the CASCADE DELETE clause on the foreign key on the LINE table
--CASCADE DELETE will delete any records in the child table (LINE) if the corresponding record in the parent table (INVOICE) is deleted
/*
SQL> set echo on
SQL> set serveroutput on
SQL> CREATE OR REPLACE PROCEDURE prc_inv_delete (INV_NUM IN NUMBER)
IS
BEGIN
DELETE from INVOICE where INV_NUMBER = INV_NUM;
END;
/

Procedure PRC_INV_DELETE compiled
SQL> commit;

Commit complete.

SQL> select * from invoice where inv_number in (1001,1008);
INV_NUMBER   CUS_CODE INV_DATE
---------- ---------- ---------
      1001      10014 16-JAN-12
      1008      10011 17-JAN-12

SQL> select * from line where inv_number in (1001,1008);

INV_NUMBER LINE_NUMBER P_CODE     LINE_UNITS LINE_PRICE
---------- ----------- ---------- ---------- ----------
      1001           1 13-Q2/P2            1      14.99
      1001           2 23109-HB            1       9.95
      1008           3 23109-HB            1       9.95
      1008           1 PVC23DRT            5       5.87
      1008           2 WR3/TT3             3     119.95
SQL> exec prc_inv_delete(1001);

PL/SQL procedure successfully completed.

SQL> exec prc_inv_delete(1008);

PL/SQL procedure successfully completed.
SQL> select * from invoice where inv_number in (1001,1008);

no rows selected


SQL> select * from line where inv_number in (1001,1008);

no rows selected

SQL> rollback;

Rollback complete.
*/