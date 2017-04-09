set echo on;
set serveroutput on;

--1. Create an SQL query that uses set operations to display the union of the last names in table CUSTOMER and
--the last names in table EMPLOYEE. Do not include duplicates in the output.


SELECT CUS_LNAME FROM CUSTOMER
UNION
SELECT EMP_LNAME FROM EMPLOYEE;

--2. Create an SQL query that uses set operations to display the union of the last names in table CUSTOMER and
--the last names in table EMPLOYEE. This time, include duplicates in the output.


SELECT CUS_LNAME FROM CUSTOMER
UNION ALL
SELECT EMP_LNAME FROM EMPLOYEE;

--3. Create an SQL query that USES AN UNCORRELATED SUBQUERY2 AND NO JOINS3
--to display the
--descriptions for products provided by a vendor in area code 615.

SELECT P_DESCRIPT FROM PRODUCT 
WHERE V_CODE IN (SELECT V_CODE FROM VENDOR
WHERE V_AREACODE = '615');

--4. Create an SQL query that USES A CORRELATED SUBQUERY to display the descriptions for products
--provided by a vendor in area code 615 (a join is okay here).

SELECT P_DESCRIPT FROM PRODUCT
WHERE V_CODE = (SELECT V_CODE FROM VENDOR 
WHERE VENDOR.V_CODE = PRODUCT.V_CODE
AND VENDOR.V_AREACODE = '615');


/*
SQL> set echo on
SQL> set serveroutput on
SQL> --1. Create an SQL query that uses set operations to display the union of the last names in table CUSTOMER and
SQL> --the last names in table EMPLOYEE. Do not include duplicates in the output.
SQL> SELECT CUS_LNAME FROM CUSTOMER
UNION
SELECT EMP_LNAME FROM EMPLOYEE;

CUS_LNAME     
---------------
Brandon        
Brown          
Diante         
Dunne          
Farriss        
Genkazi        
Johnson        
Jones          
Kolmycz        
Lange          
Lewis          

CUS_LNAME     
---------------
O'Brian        
Olowski        
Orlando        
Ramas          
Saranda        
Smith          
Smythe         
Vandam         
Washington     
Wiesenbach     
Williams       

 22 rows selected 

SQL> --2. Create an SQL query that uses set operations to display the union of the last names in table CUSTOMER and
SQL> --the last names in table EMPLOYEE. This time, include duplicates in the output.
SQL> SELECT CUS_LNAME FROM CUSTOMER
UNION ALL
SELECT EMP_LNAME FROM EMPLOYEE;

CUS_LNAME     
---------------
Brown          
Dunne          
Farriss        
O'Brian        
Olowski        
Orlando        
Ramas          
Smith          
Smith          
Williams       
Kolmycz        

CUS_LNAME     
---------------
Lewis          
Vandam         
Jones          
Williams       
Lange          
Smith          
Diante         
Wiesenbach     
Smith          
Genkazi        
Washington     

CUS_LNAME     
---------------
Johnson        
Smythe         
Brandon        
Saranda        
Smith          

 27 rows selected 

SQL> --3. Create an SQL query that USES AN UNCORRELATED SUBQUERY2 AND NO JOINS3
SQL> --to display the
SQL> --descriptions for products provided by a vendor in area code 615.
SQL> SELECT P_DESCRIPT FROM PRODUCT 
WHERE V_CODE IN (SELECT V_CODE FROM VENDOR
WHERE V_AREACODE = '615');

P_DESCRIPT                        
-----------------------------------
7.25-in. pwr. saw blade            
9.00-in. pwr. saw blade            
B&D jigsaw, 12-in. blade           
B&D jigsaw, 8-in. blade            
Claw hammer                        
Rat-tail file, 1/8-in. fine        
Hicut chain saw, 16 in.            
1.25-in. metal screw, 25           
2.5-in. wd. screw, 50              

 9 rows selected 

SQL> --4. Create an SQL query that USES A CORRELATED SUBQUERY to display the descriptions for products
SQL> --provided by a vendor in area code 615 (a join is okay here).
SQL> SELECT P_DESCRIPT FROM PRODUCT
WHERE V_CODE = (SELECT V_CODE FROM VENDOR 
WHERE VENDOR.V_CODE = PRODUCT.V_CODE
AND VENDOR.V_AREACODE = '615');

P_DESCRIPT                        
-----------------------------------
7.25-in. pwr. saw blade            
9.00-in. pwr. saw blade            
B&D jigsaw, 12-in. blade           
B&D jigsaw, 8-in. blade            
Claw hammer                        
Rat-tail file, 1/8-in. fine        
Hicut chain saw, 16 in.            
1.25-in. metal screw, 25           
2.5-in. wd. screw, 50              

 9 rows selected 

*/