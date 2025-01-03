# MySQL Syntax

DDL: Data Definition Language

DML: Data Manipulation Language

DQL: Data Query Language

DCL: Data Control Language

### DDL - database

show all databases

```
show databases;
```

show current database in use

 ```
select database();
 ```

change to database

```
use DBNAME;
```

create a new database

```
create database [if not exists] DBNAME [default charset CSNAME] [collate RULE]
```

with `if not exists` option first check if the database exists or not. `charset` option assigns it a specific charset. `collate` assigns the rule of sorting.

### DDL - table

show all tables in current database

```
show tables;
```

show information of table 

```
desc TABLENAME;
```

show the statement creating table

```
show create table TABLENAME;
```

create a new table

```
create table [if not exists] TABLENAME(
	COLUMN1 TYPE1 [CONSTRAINT] [comment COMMENT],
	COLUMN2 TYPE2 [CONSTRAINT] [comment COMMENT],
	...
	COLUMN TYPE [CONSTRAINT] [comment COMMENT]
)[comment COMMENT];
```

create table with composite primary key:

```
create table TABLENAME(
	...
	primary key (COLUMN1, COLUMN2, ...)
);
```

numeric types:

```
tinyint
smallint
mediumint
int or integer
bigint
float(M,D)
double(M,D)
```

```
age tinyint unsigned
score double(4,1)
```

string types:

```
char(N)
varchar)(N)
[tiny/medium/long]blob
[tiny/medium/long]text
```

date types:

```
date		(1000-01-01 ~ 9999-12-31)
time		(-838:59:59 ~ 838:59:59)
year		(1901 ~ 2155)
datetime	(1000-01-01 00:00:00 ~ 9999-12-31 23:59:59)
timestamp	(1970-01-01 00:00:00 ~ 2038-01-19 03:14:07)
```

modification of tables:

add a new column

```
alter table TABLENAME add COLUMN TYPE [comment COMMENT] [CONSTRAINT];
```

modify column type

```
alter table TABLENAME modify COLUMN NEWTYPE;
```

change column name and type

```
alter table TABLENAME change OLDNAME NEWNAME TYPE [comment COMMENT] [CONSTRAINT];
```

delete a column

```
alter table TABLENAME drop COLUMN;
```

rename table

```
alter table TABLENAME rename to NEWNAME;
```

delete table

```
drop table [if exists] TABLENAME;
```

clear table

```
truncate table TABLENAME;
```

### DML

insert data to specific column:

```
insert into TABLENAME(COLUMN1, COLUMN2, ...) values (VALUE1, VALUE2, ...);
```

insert data to all columns:

```
insert into TABLENAME values (VALUE1, VALUE2, ...);
```

insert multiple data:

```
insert into TABLENAME(COLUMN1, COLUMN2, ...) values (VALUE1, VALUE2, ...), (VALUE1, VALUE2, ...), ...;
insert into TABLENAME values (VALUE1, VALUE2, ...), (VALUE1, VALUE2, ...), ...;
```

update and delete data:

```
update TABLENAME set COLUMN1=VALUE1, COLUMN2=VALUE2, ... [where CONDITION];
delete from TABLENAME [where CONDITION];
```

if no condition, then it updates or deletes all data. 

```
#show databases;
use test;
#show tables;
create table if not exists newtable(
	id int unsigned,
    age tinyint unsigned,
    name varchar(50),
    gender char(1)
);
truncate table newtable;
insert into newtable(id, age, name, gender) values (1,20,"TYU", "M"), (2,21,"YUI", "F"), (3,22,"ERT", "F");
update newtable set name="QWE" where id=1;
delete from newtable where gender='F';
update newtable set gender=NULL;
select * from newtable;
```

### DQL

```
select
	COLUMNS
from
	TABLES
where
	CONDITIONS
group by
	COLUMNS
having
	CONDITIONS
order by
	SORTED COLUMNS
limit
	PAGER
```

query multiple columns

```
select COLUMN1, COLUMN2, ... from TABLENAME;
select * from TABLENAME;
```

set alias

```
select COLUMN1 [as ALIAS1], COLUMN2 [as ALIAS2], ... from TABLENAME;
```

remove duplicate query

```
select distinct COLUMNS from TABLENAME;
```

query conditions:

```
between MIN and MAX
in(LIST)
like ...  (use wildcards, _ as one character, % as any number of any characters)
is null
>, >=, <, <=, =, !=, !, not, &&, and, ||, or
```

```
select * from newtable where gender is not null;
select * from newtable where age between 15 and 20;
select * from newtable where age in (18,19,20);
select * from newtable where name like "__";
```

**aggregate functions**. performed on a whole column and null values are not counted. regarded as a single column.

```
count
sum
avg
min
max

select AGGREGATE_FUNCTION(COLUMNS) from TABLENAME;
```

```
select avg(age) from newtable;
select sum(age) from newtable where gender='F';
```

**grouping**. after grouping, new queries are usually aggregate functions or columns. use having to filter output after grouping. aggregate functions cannot be used with `where` ,but `having`.

```
select COLUMNS from TABLENAME [where CONDITION] group by COLUMN [having CONDITION]
```

```
select gender, sum(age) from newtable group by gender;
select gender, sum(age) from newtable group by gender having sum(age)>=40;
```

**sorting**. first sort as rule1, if equal then apply rule2, ... .

```
select COLUMNS from TABLENAME order by COLUMN1 RULE1, COLUMN2, RULE2, ...;
```

sort rules:

```
asc 	(ascending)
desc	(descending)
```

```
select * from newtable order by age asc, id desc;
```

**limit**.

```
select COLUMNS from TABLENAME limit STARTING_INDEX, QUERY_NUMBER;
```

```
select * from newtable limit 10,10;
```

**execution order**:

```
from -> where -> group by + having -> select -> order by ->limit
```

### DCL - user

query user

```
use mysql;
select * from user;
```

create user

```
create user 'USERNAME'@'HOSTNAME' identified by 'PASSWORD'
```

modify user information

```
alter user 'USERNAME'@'HOSTNAME' identified with mysql_native_password by 'NEWPASSWORD';
```

delete user

```
drop user 'USERNAME'@'HOSTNAME';
```

### DCL - privilege

```
all
select
insert
update
delete
alter
drop
create
```

query privileges

```
show grants for 'USERNAME'@'HOSTNAME';
```

grant privileges

```
grant PRIVILEGES on DBNAME.TABLENAME to 'USERNAME'@'HOSTNAME';
```

revoke privileges

```
revoke PRIVILEGES on DBNAME.TABLENAME from 'USERNAME'@'HOSTNAME';
```

### functions

string functions

```
concat(STR1, STR2, ...)		concatenate strings into one string
lower(STR)
upper(STR)
lpad(STR, N, PAD)			pad PAD to the left of STR repeatedly until the length of STR reach N
rpad(STR, N, PAD)			pad PAD to the right of STR repeatedly until the length of STR reach N
trim(STR)					delete leftmost and rightmost spaces 
substring(STR, START, END)	START starts at 1. includes both START and END index.
```

numerical functions

```
ceil(X)
floor(X)
mod(X,Y)			X%Y
rand()				between 0 and 1
round(X,Y)			round X and preserve Y digits
```

date functions

```
curdata()			returns YYYY-MM-DD
curtime()			returns HH:MM:SS
now()				returns both
year(DATE)
month(DATE)
day(DATE)
date_add(DATE, interval N TYPE)	type includes day, month and year.	
datediff(DATE1, DATE2)		
```

process functions

```
if(BOOL, T, F)												if BOOL is true then return T.
ifnull(VALUE1, VALUE2)										if VALUE1 is not null the return VALUE1.
case when [BOOL1] then [VALUE1] when [BOOL2] then [VALUE2] ... else [VALUE] end			return VALUE1 when BOOl is true.
case [EXP] when [VALUE1] then [RET1] when [VALUE2] then [RET2] ... else [VALUE] end		return RET1 when EXP==VALUE1.
```

### constraint

```
not null
unique
default			if not passed when inserting, use default value.
check
primary key		for composite primary key, must declare in a single line.
foreign key		cannot declare along side with the column.
```

```
create table user(
	id int unsigned primary key auto_increment,
	name varchar(10) not null unique,
	age tinyint unsigned check (age between 0 and 120),
	status char(1) default '1',
	gender char(1)
);
```

create table with foreign key and composite primary key:

```
create table TABLENAME(
	...
	[constraint] [FKNAME1] foreign key (COLUMN1) references PARENT_TABLE1(PARENT_COLUMN1) on update RULE1 on delete RULE2,
	[constraint] FKNAME2] foreign key (COLUMN2) references PARENT_TABLE2(PARENT_COLUMN2) on update RULE1 on delete RULE2,
	...
	primary key (COLUMN1, COLUMN2, ...)
);
```

add or delete foreign key constraint:

```
alter table TABLENAME add constraint FKNAME foreign key (COLUMN) references PARENT_TABLE(PARENT_COLUMN) on update RULE1 on delete RULE2;
alter table TABLENAME drop foreign key FKNAME;
```

update and delete rules:

```
no action
restrict
cascade		transit the modification on parent table column to its linked column. 
set null	only for delete. when deleted, its linked column is set to null.
set default
```

### multiple tables - relationship

1. `1 to N` relationship: create a foreign key at N side.

```
create table department(
	id int primary key,
	name varchar(20)
);

create table employee(
	id int primary key,
	name varchar(20),
	dept_id int,
	manager_id int,
	salary int,
	constraint FK_department foreign key (dept_id) references department(id) on update cascade on delete set null
);
```

2. `N to N` relationship: create a new junction table combining both tables using foreign key.

```
create table student(
	id int primary key,
	name varchar(20)
);

create table course(
	id int primary key,
	name varchar(20)
);

create table student_course(
	student int,
	course int,
	foreign key (student) references student(id) on update cascade on delete set null,
	foreign key (course) references course(id) on update cascade on delete set null
);
```

3. `1 to 1` relationship: create a unique foreign key at either side, and connect it with the other side.

```
create table user_basic(
	id int primary key,
	name varchar(20),
	age int,
	gender char(1)
);

create table user_edu(
	id int primary key,
	primary_school varchar(50),
	middle_school varchar(50),
	high_school varchar(50),
	university varchar(50),
	user_id int not null unique,
	foreign key (user_id) references user_basic(id) on update cascade on delete cascade
);
```

### multiple tables - join

**inner join**
When to use inner join: When you only need rows with matching data from both tables, or to combine related data spread across multiple tables. (intersection of two tables)

implicit inner join

```
select COLUMNS from TABLE1, TABLE2 where CONDITIONS(TABLE1.COLUMN1,TABLE2.COLUMN2);
select A1.COLUMNS, A2.COLUMNS from TABLE1 [as] A1, TABLE2 [as] A2 where CONDITIONS(A1.COLUMN1,A2.COLUMN2);
```

explicit inner join

```
select COLUMNS from TABLE1 [inner] join TABLE2 on CONDITIONS(TABLE1.COLUMN1,TABLE2.COLUMN2);
select A1.COLUMNS, A2.COLUMNS from TABLE1 [as] A1 [inner] join TABLE2 [as] A2 on CONDITIONS(A1.COLUMN1,A2.COLUMN2);
```

```
select e.name, d.name from department d join employee e on d.id=e.dept_id;

select e.name as employee_name, d.name as department_name, p.name as project_name
from employee e
join department d
on e.dept_id = d.id
join project p
on e.project_id = p.id
where d.name = 'Engineering';
```

**outer join**
outer join gives all information on one table, combining with information from the other table.

```
select COLUMNS from TABLE1 left [outer] join TABLE2 on CONDITIONS;
select COLUMNS from TABLE1 right [outer] join TABLE2 on CONDITIONS;
```

right join is the same as left join:

```
select COLUMNS from TABLE2 left [outer] join TABLE1 on CONDITIONS;
```

**self join**
when you need to compare rows within the same table or establish relationships within the same dataset.

```
select A1.COLUMNS, A2.COLUMNS from TABLE [as] A1 [left/right/inner] join TABLE [as] A2 on CONDITIONS(A1.COLUMNS, A2.COLUMNS);
```

### multiple tables - union

combine two queries results directly. the number of columns and corresponding types of two queries must match.

```
select ...
union [all]
select ...;
```

with `all` option: does not remove duplicate query results.

### multiple tables - subquery

nest result of one query into another query. often used in `where`, `select` and `from` clauses.
its outermost can be any of `select`, `insert`, `update` or `delete`.

**scalar subquery**: the result of subquery is 1x1 scalar value. useful when you need to compare a value in the main query with a single calculated or fetched value from a subquery.

```
select * from employee where dept_id = (select id from department where name = 'Marketing');
```

**column subquery**

keywords:

```
in
not in
any
some
all
```

```
select * from employee where salary > all (select salary from employee where dept_id = (select id from department where name = 'Marketing'));
```

**row subquery**

useful keywords:

```
=, !=, in, not in
```

```
select * from employee where (salary, manager_id) = (select salary, manager_id from employee where name = 'XYZ');
```

**derived table subquery**

use the derived table as temporary table.

```
select * from employee where (job, salary) in (select job, salary from employee where name in ('ABC', 'XYZ'));

select * from (select * from employee where entrydate > '2006-01-01') as tmp left join department as d on tmp.dept_id = d.id;

select e.name, e.salary, e.dept_id
from (
    select dept_id, count(*) as emp_count
    from employee
    group by dept_id
    having count(*) > 5
) as large_departments
join (
    select avg(salary) as company_avg_salary
    from employee
) as company_avg
join employee e
on e.dept_id = large_departments.dept_id
where e.salary > company_avg.company_avg_salary;
```

### transaction rollback

```
start transaction / begin
commit;
rollback;
```

concurrent transaction problems:

1. dirty read: a transaction reads uncommitted data modified by another transaction.
2. non-repeatable read: read the same data twice but found different value.
3. phantom read: a transaction fails to find a data row but subsequently found it because another transaction has inserted new data.

solutions: four isolation levels:

| isolation level  | dirty read | non-repeatable read | phantom read |
| :--------------- | :--------: | :-----------------: | :----------: |
| read uncommitted |     √      |          √          |      √       |
| read committed   |     ×      |          √          |      √       |
| repeatable read  |     ×      |          ×          |      ×       |
| serializable     |     ×      |          ×          |      ×       |

query isolation level

```
select @@transaction_isolation
```

set isolation level

```
set [session|global] transaction isolation level {read uncommitted | read committed | repreatable read | serializable}
```



