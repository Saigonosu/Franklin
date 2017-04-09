set echo on;
set serveroutput on;

/*
1. Display all product information for products that contain the string ‘saw’ in their description.
*/

select * from product where P_DESCRIPT like '%saw%';

/*
2. Display all product information for products currently selling for less than $20.00 and which have
more than 100 units in stock (recorded in attribute P_QOH or quantity on hand).
*/

select * from product
where P_PRICE < 20.00
and P_QOH > 100;

/*
3. Display all product information for products currently selling for less than $20.00 or which have more
than 100 units in stock (recorded in attribute P_QOH or quantity on hand).
*/

select * from product
where P_PRICE < 20.00
or P_QOH > 100;

/*
4. Display the product code, description and price for products provided by vendor 21344.
*/

select P_CODE, P_DESCRIPT, P_PRICE
from product
where V_CODE = '21344';

/*
5. Display the product code, description, price and price after discount (a computed column that uses the
P_PRICE and P_DISCOUNT (a percent discount) --- name the computed column NewPrice) for products
for which no vendor is specified in table PRODUCT.
*/

select P_CODE, P_DESCRIPT, P_PRICE, (P_PRICE * (1-P_DISCOUNT)) as NewPrice
from product
where V_CODE is null;
/*
6. Display the product code, product description and vendor name for products provided by vendors
located in the state of TN.
*/

select prod.P_CODE, prod.P_DESCRIPT, vend.V_NAME from 
product prod join vendor vend using (V_CODE)
where vend.V_STATE = 'TN';

/*
7. Display the full names of employees who manage other employees, ordered by last name.
*/

select EMP_FNAME || ' ' || EMP_INITIAL || ' ' || EMP_LNAME as FullName from employee 
where EMP_NUM in (select distinct(EMP_MGR) from employee)
order by EMP_LNAME;

/*
8. Display the count of distinct products ordered so far by customers (i.e. exist in table LINE).
*/

select count(distinct P_CODE) from LINE;

/*
9. For every manager, display the manager employee code along with the total number of employees s/he
manages.
*/

select EMP_MGR, count(*) from employee 
where EMP_MGR is not null
group by EMP_MGR;

/*
10. Display the product description, the full customer name and the customer balance for products
ordered by customers having a customer balance between $100.00 and $500.00 (inclusive of both). Order
by customer last name, then first name, then initial.
*/

Select prod.P_DESCRIPT, cus.CUS_FNAME, cus.CUS_INITIAL, cus.CUS_LNAME, cus.CUS_BALANCE 
from PRODUCT prod join LINE using (P_CODE)
join INVOICE using (INV_NUMBER)
join CUSTOMER cus using (CUS_CODE)
where cus.CUS_BALANCE between '100.00' and '500.00';

/*
11. For every invoice, display the invoice number, invoice date and the total dollar amount for all
products purchased in the invoice, ordered by invoice number in descending order and then by invoice
date in ascending order.
*/

select INV_NUMBER, INV_DATE, SUM(LINE_UNITS * LINE_PRICE) as Total from INVOICE
join LINE using (INV_NUMBER)
group by INV_NUMBER, INV_DATE
order by INV_NUMBER desc, INV_DATE asc;

/*
12. Create an SQL view called VENDOR_PRODUCTS_TOTALS that shows the vendor name, vendor
code and the total number of products provided by the vendor but only for vendors providing two or more 
products. When done, issue a select * from VENDOR_PRODUCTS_TOTALS statement to display the
contents of view VENDOR_PRODUCTS_TOTALS.
PS: if you ever need to UNDO changes made to the database by an UPDATE or DELETE statement,
issue command rollback in the command input sub-window of SQL Developer.
*/

CREATE OR REPLACE VIEW VENDOR_PRODUCTS_TOTALS as 
select V_NAME, V_CODE, Count(P_CODE) as NumberOfProducts from VENDOR
join PRODUCT using (V_CODE)
group by V_NAME, V_CODE
having count(P_CODE) > 2;

Select * from VENDOR_PRODUCTS_TOTALS;

/*
13. Start by issuing a select * from product statement. Then, create and run an SQL update statement
which changes the P_DISCOUNT to 0.03 percent for all products that currently have a discount of 0.
Finally issue a select * from product statement after the update. This will show you the change produced
by your update statement.
*/

select * from product;
update product
set P_DISCOUNT = '0.03'
where P_DISCOUNT = '0';
select * from product;
commit;

/*
14. Start by issuing a select * from product statement. Then, create an SQL update statement which
doubles the P_DISCOUNT for all products provided by vendors in TN or FL. Finally issue a select * from
product statement after the update. This will show you the change produced by your update statement.
PS: remember that update queries can’t use multiple tables; as a result, you should update table
PRODUCT and use the IN operator with an inner query that finds the matching vendors from table
VENDOR --- see section “The IN Special Operator” on pages 257 and 258 in your textbook.
*/

select * from product;
update product
set P_DISCOUNT = P_DISCOUNT * 2
where V_CODE IN (
Select distinct(V_CODE) 
from VENDOR 
where V_STATE in ('TN','FL')
);
commit;
select * from product;

/*
15. Start by issuing a select * from LINE statement. Then, create an SQL delete statement to delete
invoice lines that include 2 or more units of product code ‘23109-HB’. Finally issue a select * from LINE
statement after the delet. This should show you the change produced by your delete statement.  
*/

select * from LINE;

Delete from LINE
where LINE_UNITS > 1
and P_CODE = '23109-HB';
commit;

select * from LINE;

