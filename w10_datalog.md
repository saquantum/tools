# Week 10: Datalog

# The Addams Family



[![addams.png](https://github.com/cs-uob/software-tools/raw/main/10-sql/lab/addams.png)](https://github.com/cs-uob/software-tools/blob/main/10-sql/lab/addams.png)

The Addams Family tree is shown above. Your task is to encode the family tree in Datalog. To do this you’ll need to describe the relationships in Horn clauses.

Firstly you’ll need to create the knowledge base in Horn-clauses. Start by defining a relationship between parent and children. For example, `parent(pugsley,gomez)` states that Pugsley’s parent is Gomez.

**Task 1.** Capture the Addams Family tree using Horn clauses. To test run the query `parent(X,sharron)` to see if *Sharron* is anyone’s parent. The only match should be *Debbie*.

**Task 2.** A sibling is someone who shares a parent with you. Define a rule `sibling(X,Y)` that captures this. Check that Gomez’s sibling is Fester.

**Task 3.** AbcDatalog allows negation in rules. We can specify that two variables are not equal in a rule by saying `X!=Y`. Check whether `sibling(wednesday,wednesday)` is true, and if so fix it.

**Task 4.** A cousin is someone you share a grandparent with, but who isn’t your sibling. Write the rule `cousin(X,Y)` and check that Gomez and Morticia are cousins.

**Task 5.** An aunt or uncle is your parent’s sibling. Define the rule and query whose Uncle Fester is.

**Task 6.** Who are Pugsley’s aunts and uncles? What about Debbie?

```
% Parent relationships
parent(debbie, sharron).
parent(debbie, dave).
parent(fester, eudora).
parent(fester, father).
parent(gomez, eudora).
parent(gomez, father).
parent(morticia, hester).
parent(morticia, father_frump).
parent(ophella, hester).
parent(ophella, father_frump).
parent(pugsley, morticia).
parent(pugsley, gomez).
parent(wednesday, morticia).
parent(wednesday, gomez).
parent(pubert, morticia).
parent(pubert, gomez).
parent(father_frump, mooma).
parent(father_frump, slurp).
parent(sloom, mooma).
parent(sloom, slurp).
parent(jester, mooma).
parent(jester, slurp).
parent(eudora, mooma).
parent(eudora, slurp).

% rules
grandparent(X,Z) :- parent(X,Y), parent(Y,Z).
sibling(X,Y) :- parent(X,Z), parent(Y,Z), X!=Y.
cousin(X,Y) :- grandparent(X,Z), grandparent(Y,Z), X!=Y, not sibling(X,Y).
aunt_or_uncle(X,Y) :- parent(X,Z), sibling(Y,Z).
```

# Access control

## Absolute basics

In your system you should have the following predicates:

- `file(X)` to state that `X` is a file.
- `principal(X)` to state that `X` is a principal (which is a fancy way of saying a *user*).
- `canRead(P, F)` to state that the principal `P` can read file `F`.

## Discretionary access control

- All files have an `owner`. `owner(F,P)` states that principal `P` is the owner of file `F`.

- You can read a file if you are it’s owner.

- You can read a file if `othersCanRead(F)` is true.

  ```
  file(doc1). file(doc2). file(doc3).
  principal(A). principal(B). principal(C).
  owner(doc1, A). owner(doc2, B). owner(doc3, C). 
  othersCanRead(doc1).
  
  canRead(P, F) :- file(F), principal(P), owner(F, P).
  canRead(P, F) :- file(F), principal(P), othersCanRead(F).
  canRead(P, F) :- file(F), principal(P), owner(F, P0), saysCanRead(P0,P,F).
  ```

## Delegated access control

- The owner of a file can state who else can read it. `saysCanRead(P1,P2,F)` states that `P1` says that `P2` can read file `F`. Remember to check that `P1` can only delegate access if they own `F`.
- A principal can delegate to other principals to decide who can read their files. `delegatesTo(P1,P2)` states that `P1` will allow `P2` to make access control decisions for them.
- Make sure that a principal whose been delegated to can also redelegate the decision to someone else!

## Role-based access control

- Add roles to your access control system. For example, a principal may be happy to say that an auditor can read their files, but may not know who the auditor’s currently are.

- `holds(P,R)` states that a principal `P` holds a role `R`. Update your `saysCanRead` rule to account for roles.

  ```
  delegatesTo(B, C).
  holds(A, user). holds(B, user). holds(C, user). 
  holds(A, auditor). holds(B, auditor). holds(C, auditor). 
  principal(D). principal(E).
  holds(D, auditor). holds(E, common).
  
  saysCanRead(P1, P2, F) :- saysCanRead(P1, P3, F), saysCanRead(P3, P2, F).
  saysCanRead(P1, P2, F) :- owner(F, P1), holds(P1, R), holds(P2, R), P1!=P2, principal(P1). principal(P2), file(F).
  saysCanRead(P1, P2, F) :- owner(F, P1), delegatesTo(P1, P2), P1!=P2, principal(P1). principal(P2), file(F).
  ```

## Mandatory access control

- Files have a security level.
  - `unclassified(F)` states the file is publicly available.
  - `secret(F)` states that the file is secret.
  - `topsecret(F)` states that the file is top secret.
- Security levels have an ordering
  - `unclassified` < `secret` < `topsecret`
- Principals have a clearance. `clearance(P,secret)` states that Principal `P` has a `secret` security clearance.

Implement the following security models:

### Read down, write up *(Bell LaPadula)*

The *read down, write up* access control model is used to protect access to data.

- You can read a file if you have an appropriate or higher clearance than the file.

- You can write to a file if you have an appropriate or lesser clearance than the file (so that you can tell people with more clearance than you things without informing your peers).

  ```
  unclassified(doc1).
  secret(doc2).
  topsecret(doc3).
  file(doc4).
  secret(doc4).
  clearance(A,unclassified).
  clearance(B,secret).
  clearance(C,topsecret).
  clearance(D,secret).
  clearance(E,unclassified).
  
  canRead(P,F) :- file(F), principal(P), unclassified(F).
  canRead(P,F) :- file(F), principal(P), clearance(P, secret), secret(F).
  canRead(P,F) :- file(F), principal(P), clearance(P, topsecret), secret(F).
  canRead(P,F) :- file(F), principal(P), clearance(P, topsecret), topsecret(F).
  
  canWrite(P,F) :- file(F), principal(P), topsecret(F).
  canWrite(P,F) :- file(F), principal(P), clearance(P, secret), secret(F).
  canWrite(P,F) :- file(F), principal(P), clearance(P, unclassified), secret(F).
  canWrite(P,F) :- file(F), principal(P), clearance(P, unclassified), unclassified(F).
  ```

### Write down, read up (*Biba*)

This one is a bit more surprising but is used when you want to protect the integrity of data.

- You can write to a file if you have a strictly higher clearance than the file. The idea is that you should be able to send orders to people with less clearance than you.
- You can read a file only with more clearance than you have. The idea is that you shouldn’t be influenced by ideas from outside sources.

