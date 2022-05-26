// Copyright 2022 Avram Cristian-Stefan

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

#define MAX_COMMAND_SIZE 30
#define MAX_SYMBOL_SIZE 30

void create_list(dll_list **list);
void create_deck(dll_node **deck, int n);
void create_card(dll_node **card, int val, char symb[MAX_SYMBOL_SIZE]);
void add_card(dll_node *deck, int val, char symb[MAX_SYMBOL_SIZE]);
int check_if_valid(int val, char symb[MAX_SYMBOL_SIZE]);
int check_if_number(char val[MAX_SYMBOL_SIZE]);
int check_if_valid_symb_input(char symb[MAX_SYMBOL_SIZE]);
void add_cards_in_deck(dll_node *deck, int n);
void add_deck(dll_list *list, int n);
void show_deck(dll_list *list, int index);
void show_all(dll_list *list);
void exit_and_free(dll_list **list);
void print_deck_len(dll_list *list, int index);
void reverse_deck(dll_list **list, int index);
void del_deck(dll_list **list, int index, int option);
void del_card(dll_list **list, int deck_index, int card_index);
void add_cards_function(dll_list *list, int index, int nr_cards);
void shuffle_deck(dll_list *list, int index);
void interclass_cards(int new_size, dll_node **card, dll_node **card_1,
						dll_node **card_2, int size_1, int size_2);
void merge_decks(dll_list **list, int index1, int index2);
void split_deck(dll_list **list, int index, int split_index);
void swap_cards(dll_node **card1, dll_node **card2);
void check_and_swap(dll_node *card, int i, int j);
void sort_deck(dll_list *list, int index);
int validate_command(dll_list *list, char com[MAX_COMMAND_SIZE],
				int *param1, int *param2, int option);

#endif  //  UTILS_H_
