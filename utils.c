// Copyright 2022 Avram Cristian-Stefan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "struct.h"

#define DIE(assertion, call_description)                                       \
    do {                                                                       \
        if (assertion) {                                                       \
            fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                 \
            perror(call_description);                                          \
            exit(errno);                                                       \
        }                                                                      \
    } while (0)

#define MAX_COMMAND_SIZE 30
#define MAX_SYMBOL_SIZE 30
#define INVALID_MESSAGE (printf("Invalid command. Please try again.\n"))
typedef unsigned int uint;

/*
* Function that is creating a list and initialize its head pointer to NULL.
* It is used to create the deck list and the cards list.
*/ 
void create_list(dll_list **list) {
	*list = (dll_list *)malloc(sizeof(dll_list));
	DIE(NULL == list, "Malloc failed");
	(*list)->head = NULL;
	(*list)->size = 0;
}

/*
* Function that is creating a node in the deck list.
* Its "data" pointer relates to the list of cards.
*/ 
void create_deck(dll_node **deck, int n) {
	*deck = (dll_node *)malloc(sizeof(dll_node));
	DIE(NULL == deck, "Malloc failed");
	(*deck)->next = NULL;
	(*deck)->prev = NULL;

	dll_list *temp = malloc(sizeof(dll_list));
	DIE(NULL == temp, "Malloc failed");
	temp->size = n;
	temp->head = NULL;
	(*deck)->data = temp;
}

/*
* Function that is creating a node in the cards list.
* Its "data" pointer relates to a card info-structure (value and symbol).
*/
void create_card(dll_node **card, int val, char symb[MAX_SYMBOL_SIZE]) {
	*card = (dll_node *)malloc(sizeof(dll_node));
	DIE(NULL == card, "Malloc failed");
	(*card)->next = NULL;
	(*card)->prev = NULL;

	dll_card *temp = malloc(sizeof(dll_card));
	DIE(NULL == temp, "Malloc failed");
	temp->value = val;
	strcpy(temp->symbol, symb);
	(*card)->data = temp;
}

// Function that adds a card at the end of a cards list.
void add_card(dll_node *deck, int val, char symb[MAX_SYMBOL_SIZE]) {
	dll_node *card;
	create_card(&card, val, symb);

	dll_list *deck_list = deck->data;

	if (deck_list->head == NULL) {
		deck_list->head = card;
		return;
	} else {
		dll_node *node = deck_list->head, *previous = deck_list->head;
		while (node != NULL) {
			previous = node;
			node = node->next;
		}

		node = card;
		node->prev = previous;
		previous->next = node;
	}
}

// Function that determines if a card data input is correct or not.
int check_if_valid(int val, char symb[MAX_SYMBOL_SIZE]) {
	if (val < 1 || val > 14)
		return 0;
	if (strstr("HEART SPADE CLUB DIAMOND", symb) == 0)
		return 0;
	return 1;
}

// Function that checks if the given string contains just numbers
int check_if_number(char val[MAX_SYMBOL_SIZE]) {
	for (uint i = 0; i < strlen(val); i++)
		if (val[i] >= 'A' && val[i] <= 'Z')
			return 0;
	return 1;
}

// If there any spaces in the symbol input, it is automatically not correct.
int check_if_valid_symb_input(char symb[MAX_SYMBOL_SIZE]) {
	if (strstr(symb, " "))
		return 0;
	return 1;
}

/*
* Function that is used for adding cards into a deck (cards list).
* Cards are verified by input and, while there is not a correct card given,
* the loop of reading won't stop.
*/
void add_cards_in_deck(dll_node *deck, int n) {
	int index = 0;
	while (index < n) {
		char val_string[MAX_SYMBOL_SIZE];
		char symb[MAX_SYMBOL_SIZE];
		int val;

		scanf("%s", val_string);
		fgets(symb, MAX_SYMBOL_SIZE, stdin);
		symb[strlen(symb) - 1] = '\0';

		memmove(symb, symb + 1, strlen(symb));

		if (check_if_number(val_string) && check_if_valid_symb_input(symb)) {
			val = atoi(val_string);
		} else {
			printf("The provided card is not a valid one.\n");
			continue;
		}

		if (check_if_valid(val, symb) == 0) {
			printf("The provided card is not a valid one.\n");
			continue;
		}

		add_card(deck, val, symb);
		index++;
	}
}

/*
* Function that is used for adding a deck into the deck list.
* This deck is added at the end of the list and its pointers are initialized.
*/
void add_deck(dll_list *list, int n) {
	dll_node *deck;
	create_deck(&deck, n);

	if (list->size == 0) {
		list->head = deck;
	} else {
		dll_node *node = list->head, *previous = list->head;
		while (node != NULL) {
			previous = node;
			node = node->next;
		}
		node = deck;
		node->prev = previous;
		previous->next = node;
	}

	add_cards_in_deck(deck, n);

	dll_list *deck_list = deck->data;

	printf("The deck was successfully created with %d cards.\n",
			 deck_list->size);

	list->size++;
}

// Function that prints the cards from the deck with the given index.
void show_deck(dll_list *list, int index) {
	dll_node *node;
	node = list->head;

	printf("Deck %d:\n", index);

	while (index) {
		node = node->next;
		index--;
	}

	dll_list *deck_list = node->data;
	dll_node *card_node;
	card_node = deck_list->head;

	for (int i = 0; i < deck_list->size; i++) {
		dll_card *card_data = card_node->data;
		printf("\t%d %s\n", card_data->value, card_data->symbol);
		card_node = card_node->next;
	}
}

// Function that prints the cards from all decks. It uses show_deck function.
void show_all(dll_list *list) {
	for (int i = 0; i < list->size; i++)
		show_deck(list, i);
}

/*
* Before interrupting the program and exit, the allocated memory is freed
* in this function. 
*/
void exit_and_free(dll_list **list) {
	dll_node *deck_node = (*list)->head, *prev_node;
	for (int i = 0; i < (*list)->size; i++) {
		dll_list *deck_list = deck_node->data;
		dll_node *card = deck_list->head, *prev = card;

		for (int i = 0; i < deck_list->size; i++) {
			dll_card *card_data = prev->data;
			card = card->next;
			free(card_data);
			free(prev);
			prev = card;
		}

		prev_node = deck_node;
		deck_node = deck_node->next;
		free(prev_node->data);
		free(prev_node);
	}
	free(*list);
}

// Function that prints the number of cards from a deck.
void print_deck_len(dll_list *list, int index) {
	dll_node *deck_node = list->head;
	int index_2 = index;

	while (index_2--)
		deck_node = deck_node->next;

	dll_list *deck_list = deck_node->data;
	printf("The length of deck %d is %d.\n", index, deck_list->size);
}

/*
* Reversing the deck by swapping the cards pointers
* and eventually putting them on NULL.
* The cards list head will be pointing to the initial last card.
*/
void reverse_deck(dll_list **list, int index) {
	dll_node *deck_node = (*list)->head;

	for (int i = 0; i < index; i++)
		deck_node = deck_node->next;

	dll_list *deck_list = deck_node->data;
	dll_node *card = deck_list->head, *previous = NULL;

	for (int i = 0; i < deck_list->size; i++) {
		card->prev = card->next;
		card->next = previous;
		previous = card;
		card = card->prev;
	}

	deck_list->head = previous;

	printf("The deck %d was successfully reversed.\n", index);
}

/*
* Function that deletes a deck node and free its allocated data.
* Eventually, previous and next nodes will be linked together.
* If the user wants to delete the first deck, the deck list head
* will point to the next deck or to NULL if there won't be any decks left.
*/
void del_deck(dll_list **list, int index, int option) {
	int cp_index = index;
	dll_node *deck_node = (*list)->head, *previous = NULL;

	while (index--) {
		previous = deck_node;
		deck_node = deck_node->next;
	}

	if (previous != NULL)
		previous->next = deck_node->next;
	if (deck_node->next != NULL)
		deck_node->next->prev = previous;

	dll_list *deck_list = deck_node->data;
	dll_node *card = deck_list->head, *previous_card = NULL;

	if (option) {
		for (int i = 0; i < deck_list->size; i++) {
			previous_card = card;
			card = card->next;
			free(previous_card->data);
			free(previous_card);
		}
	}

	if (deck_node == (*list)->head && (*list)->size > 1)
		(*list)->head = deck_node->next;

	free(deck_node->data);
	free(deck_node);

	(*list)->size--;

	if (option)
		printf("The deck %d was successfully deleted.\n", cp_index);
}

/*
* Function that deletes a card node and free its allocated data.
* Eventually, previous and next nodes will be linked together.
* If the user wants to delete the first card, the cards list head
* will point to the next card.
* If all cards are deleted, the deck that was holding this cards list will
* also be deleted and freed.
*/
void del_card(dll_list **list, int deck_index, int card_index) {
	dll_node *deck_node = (*list)->head;
	int cp_deck_index = deck_index;

	while (deck_index--)
		deck_node = deck_node->next;

	dll_list *deck_list = deck_node->data;
	dll_node *card = deck_list->head, *previous_card = NULL;

	if (card_index >= deck_list->size || card_index < 0) {
		printf("The provided index is out of bounds for deck %d.\n",
				cp_deck_index);
		return;
	}

	while (card_index--) {
		previous_card = card;
		card = card->next;
	}

	if (previous_card != NULL)
		previous_card->next = card->next;
	if (card->next != NULL)
		card->next->prev = previous_card;

	if (card == deck_list->head && deck_list->size > 1)
		deck_list->head = card->next;

	free(card->data);
	free(card);
	deck_list->size--;

	printf("The card was successfully deleted from deck %d.\n", cp_deck_index);

	if (deck_list->size == 0)
		del_deck(list, cp_deck_index, 0);
}

// Function that adds cards to an existing deck.
void add_cards_function(dll_list *list, int index, int nr_cards) {
	dll_node *deck_node = list->head;
	int cp_index = index;

	while (index--)
		deck_node = deck_node->next;

	add_cards_in_deck(deck_node, nr_cards);

	dll_list *deck_list = deck_node->data;
	deck_list->size += nr_cards;

	printf("The cards were successfully added to deck %d.\n", cp_index);
}

/*
* Shuffling deck function. It has to swap the beginning and the end of
* the given index deck. 
* So, if nr_cards is the number of cards, then:
* cards list head will be (the nr_cards / 2)th card; (index from 0)
* the end of cards list will be (nr_cards / 2 - 1)th card;
* the initial final card with point to the initial cards list head. 
*/
void shuffle_deck(dll_list *list, int index) {
	dll_node *deck_node = list->head;
	int cp_index = index;

	while (index--)
		deck_node = deck_node->next;

	dll_list *deck_list = deck_node->data;
	dll_node *card = deck_list->head, *final = deck_list->head;
	int half = deck_list->size / 2, full_size = deck_list->size;

	while (full_size > 1) {
		if (half > 1)
			card = card->next;
		half--;
		full_size--;
		final = final->next;
	}

	final->next = deck_list->head;
	deck_list->head = final;
	deck_list->head = card->next;
	card->next = NULL;

	printf("The deck %d was successfully shuffled.\n", cp_index);
}

/*
* As parameters, there are given 2 cards list heads from different decks.
* This function linking every card from the decks using a "Zig Zag" method.
* It has been implemented using a counter variable, that says what card to add.
*/
void interclass_cards(int new_size, dll_node **card, dll_node **card_1,
						dll_node **card_2, int size_1, int size_2) {
	int counter = 1;

	for (int i = 0; i < new_size; i++) {
		if (counter == 0 && size_1) {
			(*card_1)->prev = (*card);
			(*card)->next = (*card_1);
			(*card_1) = (*card_1)->next;
			size_1--;
			if (size_2)
				counter = 1;
		} else if (counter == 1 && size_2) {
			(*card_2)->prev = (*card);
			(*card)->next = (*card_2);
			(*card_2) = (*card_2)->next;
			size_2--;
			if (size_1)
				counter = 0;
		}
		(*card) = (*card)->next;
	}
}

/*
* There is a new deck created with the combined datas from 
* two decks. This new deck will be added to the end of the deck list.
* The decks that were used for merging will be deleted and freed.
*/
void merge_decks(dll_list **list, int index1, int index2) {
	if (index2 < 0 || index2 >= (*list)->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	dll_node *deck_node_1 = (*list)->head, *deck_node_2 = (*list)->head;
	int cp_index1 = index1, cp_index2 = index2;

	while (index1--)
		deck_node_1 = deck_node_1->next;

	while (index2--)
		deck_node_2 = deck_node_2->next;

	dll_list *deck_list_1 = deck_node_1->data, *deck_list_2 = deck_node_2->data;
	dll_node *new_deck;
	int size_1 = deck_list_1->size;
	int size_2 = deck_list_2->size;
	int new_size = size_1 + size_2;

	create_deck(&new_deck, new_size);
	dll_list *new_deck_list = new_deck->data;
	dll_node *card;

	card = deck_list_1->head;
	new_deck_list->head = card;
	size_1--;

	dll_node *card_1 = card->next, *card_2 = deck_list_2->head;

	interclass_cards(new_size, &card, &card_1, &card_2, size_1, size_2);

	if (cp_index1 == cp_index2) {
		del_deck(list, cp_index1, 0);
		new_deck_list->size /= 2;
		dll_node *card = new_deck_list->head;

		for (int i = 0; i < new_deck_list->size - 1; i++)
			card = card->next;
		card->next = NULL;
	} else {
		if (cp_index1 < cp_index2) {
			del_deck(list, cp_index1, 0);
			del_deck(list, cp_index2 - 1, 0);
		} else {
			del_deck(list, cp_index2, 0);
			del_deck(list, cp_index1 - 1, 0);
		}
	}

	if ((*list)->size == 0) {
		new_deck->next = NULL;
		(*list)->head = new_deck;
	} else {
		dll_node *final = (*list)->head;
		while (final->next != NULL)
			final = final->next;

		final->next = new_deck;
		new_deck->prev = final;
	}
	(*list)->size++;

	printf("The deck %d and the deck %d were successfully merged.\n",
			cp_index1, cp_index2);
}

/*
* Function that splits the given index deck into two different decks.
* Split index will determine the separation line into this deck.
* The second deck will be added in front of the new deck, so the
* pointers that link the nodes will be changed.
* There is no actual freeing or deleting, the new deck head will
* be pointing to the split index card, and the previous card before
* this one will actually be the final card that will remain in the
* initial deck.
*/
void split_deck(dll_list **list, int index, int split_index) {
	int cp_index = index;

	dll_node *deck_node = (*list)->head;

	while (index--)
		deck_node = deck_node->next;
	dll_list *deck_list = deck_node->data;

	if (split_index < 0 || split_index >= deck_list->size) {
		printf("The provided index is out of bounds for deck %d.\n", cp_index);
		return;
	}

	if (split_index == 0) {
		printf("The deck %d was successfully split by index %d.\n",
				cp_index, split_index);
		return;
	}

	dll_node *new_deck, *card = deck_list->head, *previous;
	create_deck(&new_deck, deck_list->size - split_index);

	for (int i = 0; i < split_index; i++) {
		previous = card;
		card = card->next;
	}

	previous->next = NULL;
	card->prev = NULL;
	deck_list->size = split_index;

	dll_list *new_deck_list = new_deck->data;
	new_deck_list->head = card;

	dll_node *tmp = deck_node->next;
	deck_node->next = new_deck;
	new_deck->prev = deck_node;
	new_deck->next = tmp;
	if (tmp != NULL)
		tmp->prev = new_deck;

	(*list)->size++;

	printf("The deck %d was successfully split by index %d.\n",
			cp_index, split_index);
}

// Function that swaps datas between 2 cards.
void swap_cards(dll_node **card1, dll_node **card2) {
	dll_card *temp = (*card1)->data;
	(*card1)->data = (*card2)->data;
	(*card2)->data = temp;
}

// Function that determines if two cards should be swapped at sort.
void check_and_swap(dll_node *card, int i, int j) {
	int index = 0;

	dll_node *card1, *card2;

	while (index < j) {
		if (index == i)
			card1 = card;
		card = card->next;
		index++;
	}

	card2 = card;

	dll_card *card1_data = card1->data, *card2_data = card2->data;

	if (card1_data->value > card2_data->value) {
		swap_cards(&card1, &card2);
	} else if (card1_data->value == card2_data->value) {
		if (strcmp(card2_data->symbol, "HEART") == 0) {
			swap_cards(&card1, &card2);
		} else if (strcmp(card2_data->symbol, "SPADE") == 0) {
			if (strcmp(card1_data->symbol, "HEART"))
				swap_cards(&card1, &card2);
		} else if (strcmp(card2_data->symbol, "DIAMOND") == 0) {
			if (strcmp(card1_data->symbol, "CLUB") == 0)
				swap_cards(&card1, &card2);
		}
	}
}

// Sorting cards with bubble sort method.
void sort_deck(dll_list *list, int index) {
	int cp_index = index;

	dll_node *deck_node = list->head;

	while (index--) {
		deck_node = deck_node->next;
	}

	dll_list *deck_list = deck_node->data;

	for (int i = 0; i < deck_list->size - 1; i++) {
		for (int j = i + 1; j < deck_list->size; j++) {
			check_and_swap(deck_list->head, i, j);
		}
	}

	printf("The deck %d was successfully sorted.\n", cp_index);
}

/*
* This function verify if the command line is valid.
* Every command needs a specific number of parameters.
* If there are given more parameters, the command will be invalid
* Variable option relates to the number of parameters that should exist.
* If option is 1, there should be one parameter.
* if option is 0, there should be two parameters.
* else, there is a command that does not need any parameters.
*/
int validate_command(dll_list *list, char com[MAX_COMMAND_SIZE],
				int *param1, int *param2, int option) {
	char line_input[MAX_COMMAND_SIZE];

	if (option == 1) {
		fgets(line_input, MAX_COMMAND_SIZE, stdin);
		for (uint i = 1; i < strlen(line_input); i++)
			if (line_input[i] == ' ') {
				INVALID_MESSAGE;
				return 0;
			}
		*param1 = atoi(line_input);

		if (strstr("ADD_DECK", com))
			return 1;

		if (*param1 < 0 || *param1 >= list->size) {
			printf("The provided index is out of bounds for the deck list.\n");
			return 0;
		} else {
			return 1;
		}
	} else if (option == 0) {
		scanf("%d", param1);
		fgets(line_input, MAX_COMMAND_SIZE, stdin);
		for (uint i = 1; i < strlen(line_input); i++)
			if (line_input[i] == ' ') {
				INVALID_MESSAGE;
				return 0;
			}
		*param2 = atoi(line_input);

		if (*param1 < 0 || *param1 >= list->size) {
			printf("The provided index is out of bounds for the deck list.\n");
			return 0;
		} else {
			return 1;
		}
	} else {
		fgets(line_input, MAX_COMMAND_SIZE, stdin);
		if (strlen(line_input) > 1) {
			INVALID_MESSAGE;
			return 0;
		}
		return 1;
	}
}
