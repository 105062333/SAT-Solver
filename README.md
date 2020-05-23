# SAT-Solver
## Boolean Satisfiability Problem
 A satisfiability problem in conjunctive normal form consists of a the conjunction of a number of clauses, where is clause is a disjunction of a number of variables or their negations. If we let xi represent variables that can assume only the values true or false, then a sample formula in conjunctive normal form would be (v1∨v2∨v3)∧(¬v2∨v4∨v3)∧(¬v2∨¬v4∨v3)∧(v1∨¬v3∨v5) where ∨ represents the or boolean connective, ∧ represents and and ¬vi is the negation of vi.
 
Given a set of clauses C1,C2,…,Cm on the variables v1,v2,…,vn, the satisfiability problem is to determine if the formula C1∧C2∧⋯∧Cm is satisfiable. That is, is there an assignment of values to the variables so that the above formula evaluates to true. Clearly, this requires that each Cj evaluate to true.

### Input
To represent an instance of such problems, we will create an input file that contains all of the information needed to define a satisfiability problem. This file will be an ASCII file consisting of a two major sections: the preamble and the clauses.

The Preamble. The preamble contains information about the instance. This information is contained in lines. Each line begins with a single character (followed by a space) that determines the type of line. These types are as follows:

###### Comments. Comment lines give human-readable information about the file and are ignored by programs. Comment lines appear at the beginning of the preamble. Each comment line begins with a lowercase character c. c This is an example of a comment line.
###### Problem line. There is one problem line per input file. The problem line must appear before any node or arc descriptor lines. For cnf instances, the problem line has the following format. p FORMAT VARIABLES CLAUSES
###### The lower-case character p signifies that this is the problem line. The FORMAT field allows programs to determine the format that will be expected, and should contain the word “cnf”. The VARIABLES field contains an integer value specifying n, the number of variables in the instance. The CLAUSES field contains an integer value specifying m, the number of clauses in the instance. This line must occur as the last line of the preamble.
The Clauses. The clauses appear immediately after the problem line. The variables are assumed to be numbered from 1 up to n. It is not necessary that every variable appear in an instance. Each clause will be represented by a sequence of numbers, each separated by either a space, a tab, or a newline character. The non–negated version of a variable vi is represented by i; the negated version is represented by -i.

Each clauses is terminated by the value 0. Unlike many formats that represent the end of a clause by a new–line character, this format allows clauses to be on multiple lines.
