# Grammars Assignment (50 points)

This file contains two questions. The first has 2 parts, the second has 7.

For all but questions 2.3 and 2.5 you'll answer questions by editing this file.
Your answers will appear in the Ax.y section after each question, replacing the
placeholders.

For question 2.3, you'll need to add an image file to the repository (.png or
.pdf) and put its file name as the answer.

For question 2.5, you'll write one or more source code files and add them to the
repository. You will then show the command used to run the files in the answer.
Do _not_ upload any binary files for this section.

Please do not edit anything outside the answers sections.


# Q1: Mr Fussy Builds a Path

# Q1

Mr Fussy wants to build a path using a row of large square pavers. His path is
one paver wide and an odd number of pavers long. Pavers come in three colors:
red, green, blue.

Mr Fussy has a rule: the sequence of colors must be symmetrical across the
length of the path: the last paver must be the same color as the first, the
second to last the same color as the second, and so on.

This is a valid path:  rgbgr
So is this: rrr

This is not: rgb
This is not: rggr    (it must be an odd length)

## Q1.1  (5 points)

Write a Chomsky type 2 grammar that describes any valid path containing at
least one paver. Use `S` as the start state, and `r`, `g`, `b` as terminals that
represent the tiles.

## A1.1

S -> r | g | b
<br />
S -> r S r
<br />
S -> g S g
<br />
S -> b S b


## Q1.2  (1 point for the O() answer, 2 for the sentence)

Using big-O notation, what is the likely memory requirement for a parser that
can validate a particular path configuration, where `n` is the number of tiles?
In one sentence, explain why.

## A1.2

O(1), the parser uses the same quantity of memory to keep track of where it is in the path and make comparisons regardless of the length of the path.

# Q2

A simple sentence structure might be

    "the" (zero or more adjectives) noun verb (optional adverb)

Adjectives are "lazy" or "smelly"

Nouns are "dog" or "cat"

Verbs are "ate" and "ran"

Adverbs are "slowly" and "noisily"

The following are examples of valid sentences:

* The smelly dog ran.
* The smelly dog ran slowly.
* The cat ate noisily.

## Q2.1 (7 points)

Write the BNF (not EBNF) description for this language.

## A2.1

\<adjective> ::= "lazy" | "smelly"
<br />
\<adjectives> ::= \<adjectives> \<adjective> | ""
<br />
\<noun> ::= "dog" | "cat"
<br />
\<verb> ::= "ate" | "ran"
<br />
\<adverb> ::= "slowly" | "noisily" | ""
<br />
\<sentence_structure> ::= "the" \<adjectives> \<noun> \<verb> \<adverb>


## Q2.2 (5 points)

Write this grammar using EBNF with common extensions

## A2.2

\<adjective> ::= "lazy" | "smelly"
<br />
\<noun> ::= "dog" | "cat"
<br />
\<verb> ::= "ate" | "ran"
<br />
\<adverb> ::= "slowly" | "noisily"
<br />
\<sentence_structure> ::= "the" {\<adjectives>} \<noun> \<verb> [\<adverb>]


## Q2.3 (6 points)

  Draw a diagram for an FSM which recognizes these sentences. Use EOI as the
  event that occurs at the end-of-input. Start with a state named S0. Receiving
  the word "the" in that state will transition to state S1. Name the final state
  END.

  You can hand draw it and snap a picture, or use a drawing tool. Either way,
  upload the image, and put the file name in the answer below.

  (Hint: my answer has seven states including the start and end states)


## A2.3

«replace this with your answer»


## Q2.4 (6 points)

Convert this diagram into a table of the form:

Current state | Next word | Next state
--------------|-----------|-----------
    S0        |    the    |     S1
    S1        |   . . .   |   . . .

(hint: my version has 13 entries. Yours _might_ be different)

## A2.4

| Current State | Next Word | Next State |
|:-------------:|:---------:|:----------:|
| S0            | the       | S1         |
| S1            | lazy      | S1         |
| S1            | smelly    | S1         |
| S1            | dog       | S2         |
| S1            | cat       | S2         |
| S2            | ate       | S3         |
| S2            | ran       | S3         |
| S3            | slowly    | S4         |
| S3            | noisily   | S4         |
| S3            | EOI       | END        |
| S4            | EOI       | END        |


## Q2.5 (12 points)

Translate this table into a programming language of your choice. Then write a
function that takes a list of words (ending "EOI") and runs the list through the
state machine. If the state machine cannot find a transition for a word when in
a given state, return false. If the state machine runs out of words and the
state is not "END" then return false. Otherwise return true.

Then write some unit tests that exercise your function, making sure that it
recognizes valid sentences and rejects invalid ones.

The answer should appear in one or more source files in the same directory as
this file. If I need to do anything more that type a single command to run your
code, include a script or makefile that will do the job.

## A2.5

`g++ FSM.cpp -o FSM && ./FSM`


## Q2.6 (3 points)

How many valid sentences are there in this language?

## A2.6

Potentially infinite. The two adjectives can be strung together endlessly to create sentences of arbitrary length.


## Q2.7 (1 point for the level, 2 for the sentence)

Which is the simplest Chomsky grammar level for this language? In one sentence,
explain why.

## A2.7

Type 3, this language is representable by a finite state machine.