> **Name: Avram Cristian Stefan**
**Group: 311CA**

# Homework Nr. 1 - Now You See Me

## Description:

> First of all, there was a need of structure implementation for adding
different decks and cards into the memory. So, the first step consisted
in finding a good scheme to develop the program.
List of decks ---> Deck node ---> List of cards ---> Card node ---> Card data

> For different commands that the users could give, there were implemented
different functions.

* **ADD_DECK** --> Creating and allocating memory for deck node,
list of cards and card info, with data coming from the input.
The final form of this deck is then added to the list of decks.

* **DEL_DECK** --> Deleting and freeing a deck by user preference
through a given index. The linkings of the neighbour nodes will
change and will stop all the boundaries with the deck node 
that needs to be deleted.
* **DEL_CARD** --> Deleting and freeing a card from a deck
by user preference through a given index. Because cards
and decks are elements that belong to the same node structure,
the linkage will be modified in a similar way.
* **ADD_CARDS** --> After the given cards are verified,
they are being added to the end of a given index deck.
Value is read as a **char***, but it is converted to
**int** type through **atoi()** function.
* **DECK_NUMBER** --> Prints the number of decks from the 
list of decks (list->size).
* **DECK_LEN** --> Prints the number of cards from a deck
(cards_list->size or deck_node->data - - -> size).
* **SHUFFLE_DECK** --> Takes a deck and changes the order of cards.
First of all, the card from the middle (eventually middle + 1)
will become the list's of cards head. The initial head will now
placed in the middle of the deck. There are pointers changings and
no auxilliary memory is used.
HEAD ---------> MIDDLE ---------> MIDDLE + 1 ---------> END
prev_MIDDLE + 1 --> prev_END --> prev_HEAD --> prev_MIDDLE
* **MERGE_DECKS** --> Takes two decks and create a third one using
a counter that keeps track of what card to add into the new deck.
It is using a "Zig Zag" method, so, using the counter, there
will be added a card from deck_1 and then a card from deck_2 and so
on. The new deck is added to the end of the list of decks, and the
two decks that were merged are deleted and freed using the
function from the DEL_DECK command.
* **SPLIT_DECK** --> Takes a deck and does the opposite of
command "MERGE_DECKS". The difference is that the second deck
that is formed will be added in the next position in the list
of decks, which means it is not necessarily added at the end of it.
So, a new deck is added in memory, and the initial deck is shrinked.
* **REVERSE_DECK** --> A command that is practically changing the
card nodes pointers and the list's of cards head will become the
final card, while the first card next pointer will be NULL.
* **SHOW_DECK** --> It prints the cards of a deck in a formatted output.
* **SHOW_ALL** --> It prints the cards from all decks using the function
which has been implemented for command "SHOW_DECK".
* **EXIT** --> The command that makes the program end its infinite loop.
It actually has an implemented function that releases all the memory
that has been allocated for the program. It iterates through every deck,
through every card and frees their blocks of memory.
* **BONUS SORT_DECK** --> This command is implemented with bubble sort
and is swapping two cards datas in the list if the conditions are verified.
It actually does not change the card nodes pointers, it keeps the nodes
where they are and just modify their data.

## Additional info:

> * I think that, for a better implementation, I could've used
XOR linked lists and Heap Sort.
>
> * After finishing this homework, I can surely say that I have gained
some good elementary knowledge about linked lists and how they
can be used efficiently. The MERGE_DECKS command was, for me,
the hardest part of this homework and now, after completing it,
I have seen how to manipulate nodes and how "linking" concept
truly works.
>
> * The function **validate_command()** is actually used to
verify if a command line of input is given correctly. Depending
on the variable "option" that is given as a parameter, the
function will proceed reading the necessarily parameters
for the those commands from the input. After these parameters
are read with **scanf()**, I use a **fgets()** to read the
rest of the line. So, if there are others characters on the line
that are not needed , the line command will be tagged as invalid
and there will be printed a suitable message.

## Bibliography:

1. [Generic ll_](https://aticleworld.com/generic-linked-list-in-c/)
2. [XOR ll_ wannabe](https://www.techiedelight.com/xor-linked-list-overview-implementation-c-cpp/)

