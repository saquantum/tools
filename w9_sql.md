# SQLite Query

### Elections

1. List the names of all parties that stood in the election, ordered alphabetically by name.

   ```
   select name from party order by party.name asc;
   ```

2. List the names of all parties that stood in the Bedminster ward.

   ```
   select party.name from party where party.id in ( select candidate.party from candidate join ward on candidate.ward = ( select ward.id where ward.name = 'Bedminster' ) );
   ```

3. How many votes did Labour get in the Stockwood ward?

   ```
   select sum(c.votes) from candidate c join party p on p.id = c.party join ward w on w.id = c.ward where p.name='Labour' and w.name='Stockwood';
   ```

4. List the names, parties and number of votes obtained for all candidates in the Southville ward. Order the candidates by number of votes obtained descending (winner comes first).

   ```
   select c.name, p.name, c.votes from candidate c join party p on p.id = c.party join ward w on w.id=c.ward where w.name = 'Southville' order by c.votes desc;
   ```

5. List the name, party and number of votes obtained for the winner only in the Knowle ward.

   ```
   select c.name, p.name, c.votes from candidate c join party p on p.id = c.party join ward w on w.id=c.ward where w.name = 'Knowle' order by c.votes desc limit 1;
   ```

1. How many votes were cast in all of Bristol in the 2014 elections?

   ```
   select sum(c.votes) from candidate c;
   ```

2. How many votes were cast in the 'Windmill Hill' ward and what percentage of the electorate in this ward does this represent? Your statement should produce a table with one row and two columns called 'votes' and 'percentage'.

   ```
   select sum(c.votes) as votes, (sum(c.votes)*100.0/w.electorate) as percentage from candidate c join ward w on w.id = c.ward where w.name='Windmill Hill';
   ```

3. List the names, parties and percentage of votes obtained for all candidates in the Southville ward. Order the candidates by percentage of votes obtained descending.

   ```
   select c.name, p.name, c.votes, sum(c.votes)*100.0/w.electorate as percentage from candidate c join party p on p.id = c.party join ward w on w.id=c.ward where w.name = 'Southville' order by percentage desc;
   ```

4. How successful (in % of votes cast) was the Conservative party in each ward?

   ```
   select w.name, c.votes*100.0/w.electorate as per from candidate c join ( select ward, sum(candidate.votes) total_votes from candidate group by ward) as wv on w.id = wv.ward join party p on p.id = c.party join ward w on w.id=c.ward where p.name = 'Conservative' group by w.name, wv.total_votes order by per;
   ```

5. Which rank did Labour end up in the 'Whitchurch Park' ward? Your statement should produce a table with a single row and column containing the answer as a number. You can assume no ties.

   ```
   select ranking from (select c.votes, p.name pname, rank() over (order by c.votes desc) ranking from candidate c join ward w on w.id=c.ward join party p on p.id=c.party where w.name='Whitchurch Park') as ranked where pname='Labour';
   ```

6. What is the total number of votes that each party got in the elections? Your result should be a table with two columns party, votes.

   ```
   select p.name, sum(c.votes) votes from candidate c join party p on p.id=c.party group by p.name order by votes desc;
   ```

7. Find all wards where the Green party beat Labour and create a table with two columns ward, difference where the difference column is the number of Green votes minus the number of Labour votes. Your table should be ordered by difference, with the highest one first.

   ```
   select green.ward, green.votes-labour.votes diff
   from
   (select w.name ward, c.votes votes from candidate c join party p on p.id=c.party join ward w on w.id=c.ward where p.name='Green') green
   join 
   (select w.name ward, c.votes votes from candidate c join party p on p.id=c.party join ward w on w.id=c.ward where p.name='Labour') labour
   on green.ward=labour.ward
   where green.votes>=labour.votes
   order by diff desc;
   ```

## Census

1. The university of Bristol is situated in the Cabot ward (ward names are not always distinct, but this one is). Find the names and codes of the CLU, region and country containing the Cabot ward (CLU = county level unit = "row in County table").
2. Find the number of women managers in the Cabot ward.
3. For the Stoke Bishop ward, list the 9 occupation class names and the number of men in each occupation. Your table should have two columns called name and number.

1. How many women work in sales and customer service occupations and live in the Cabot ward of Bristol?
2. How many people work in sales and customer service occupations and live in the Cabot ward of Bristol?
3. How many people work in caring, leisure and other service occupations in all of the City of Bristol CLU?
4. In the Cabot ward, produce a table listing the names of the 9 occupation classes and the number of people in each of the classes in this ward.
5. Find the working population, ward name and CLU name for the smallest ward (by working population) in the 2011 census.
6. The same as the last question, but now produce a table with two rows, one for the smallest and one for the largest ward. There's no quicker way than repeating the last query twice, the question is how to stick the two "copies" together.
7. Find the average size of a ward's working population in the London region.
8. The same as the last question but now for every region—your query should produce a table with one row per region.
9. Produce a table that lists, for each of the 9 regions of England, the percentage of people in managerial occupations who are women.
10. For all CLUs in the London region, produce a table with three columns called CLU, occupation and count such that:

- CLU is the CLU name.
- count is the number of people of the occupation class in question in the given CLU.
- occupation is the name of the occupation class.
- Only rows with count >= 10000 appear in the table.
- The table is sorted by count ascending.

1. Create a table with three columns occupation, women and men and one row per occupation class. The occupation column should list the occupation class names. The women and men columns in each row should list the total number of women resp. men in the row's occupation class in the whole dataset. The intention here is not to have to copy-paste a subquery 9 times.
2. The same as question 9, but now with a 10th row in the table listing the value for all of England. You can use the string 'England' for the region column.