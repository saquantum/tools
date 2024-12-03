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

**grouping**. after grouping, new queries are usually aggregate functions or columns. use having to filter output after grouping.

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
lpad(STR, N, PAD)		pad PAD to the left of STR repeatedly until the length of STR reach N
rpad(STR, N, PAD)		pad PAD to the right of STR repeatedly until the length of STR reach N
trim(STR)			delete leftmost and rightmost spaces 
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
if(BOOL, T, F)										if BOOL is true then return T.
ifnull(VALUE1, VALUE2)									if VALUE1 is not null the return VALUE1.
case when [BOOL1] then [VALUE1] when [BOOL2] then [VALUE2] ... else [VALUE] end		return VALUE1 when BOOl is true.
case [EXP] when [VALUE1] then [RET1] when [VALUE2] then [RET2] ... else [VALUE] end	return RET1 when EXP==VALUE1.
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

create table with foreign key and compoiste primary key:

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
	depa_id int,
	constraint FK_department foreign key (depa_id) references department(id) on update cascade on delete set null
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
