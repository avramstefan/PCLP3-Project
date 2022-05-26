// Copyright 2022 Avram Cristian-Stefan

#ifndef STRUCT_H_
#define STRUCT_H_

#define MAX_SYMBOL_SIZE 30

// Card data structure.
typedef struct dll_card {
	int value;
	char symbol[MAX_SYMBOL_SIZE];
} dll_card;

/*
* Deck node or card node structure.
* Deck node -> data is pointing to a cards list structure.
* Card node -> data is pointing to a card data structure.
*/
typedef struct dll_node {
	void *data;
	struct dll_node *next, *prev;
} dll_node;

/*
* Deck list or cards list structure
* Deck list -> head is pointing to a deck node structure.
* Cards list -> head is pointing to a card node structure.
*/
typedef struct dll_list {
	struct dll_node *head;
	int size;
} dll_list;

#endif  //  STRUCT_H_
