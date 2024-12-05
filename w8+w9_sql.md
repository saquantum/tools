# Entity-Relationship Diagram

![crow's foot notation](https://www.softwareideas.net/i/DirectImage/1859/crow-s-foot-notation)

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
