// Copyright 2022 Avram Cristian-Stefan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "utils.h"
#include <sys/time.h>

#define MAX_COMMAND_SIZE 30
#define MAX_SYMBOL_SIZE 30

/*
* Main function, the place where the user's command are being read.
* The program enters a loop that can be interrupted by "EXIT" input.
* Every command is given to a function that validates its correctness.
* Every correct command will send the process to a different function.
*
* Main linking between structures:
* 1) deck_list->head ----> deck_node	(next ----> next_deck_node)
* 2) deck_node->data ----> cards_list
* 3) cards_list->head ----> card_node	(next ----> next_card_node)
* 4) card_node->data ----> card_data
*/
int main(void) {
	dll_list *list;
	create_list(&list);

	struct timeval start, end;
    float elapsed;
	srand (0);
	gettimeofday(&start, NULL);
	while(1) {
		char command[MAX_COMMAND_SIZE];
		scanf("%s", command);
		int param1, param2;

		if (strncmp(command, "ADD_DECK", 8) == 0) {
			if (validate_command(list, command, &param1, 0, 1))
				add_deck(list, param1);
		} else if (strncmp(command, "SHOW_DECK", 9) == 0) {
			if (validate_command(list, command, &param1, 0, 1))
				show_deck(list, param1);
		} else if (strncmp(command, "SHOW_ALL", 8) == 0) {
			if (validate_command(list, command, 0, 0, -1))
				show_all(list);
		} else if (strncmp(command, "EXIT", 4) == 0) {
			if (validate_command(list, command, 0, 0, -1)) {
				exit_and_free(&list);
				break;
			}
		} else if (strncmp(command, "DECK_LEN", 8) == 0) {
			if (validate_command(list, command, &param1, 0, 1))
				print_deck_len(list, param1);
		} else if (strncmp(command, "DEL_DECK", 8) == 0) {
			if (validate_command(list, command, &param1, 0, 1))
				del_deck(&list, param1, 1);
		} else if (strncmp(command, "REVERSE_DECK", 12) == 0) {
			if (validate_command(list, command, &param1, 0, 1))
				reverse_deck(&list, param1);
		} else if (strncmp(command, "DEL_CARD", 8) == 0) {
			if (validate_command(list, command, &param1, &param2, 0))
				del_card(&list, param1, param2);
		} else if (strncmp(command, "ADD_CARDS", 9) == 0) {
			if (validate_command(list, command, &param1, &param2, 0))
				add_cards_function(list, param1, param2);
		} else if (strncmp(command, "SHUFFLE_DECK", 12) == 0) {
			if (validate_command(list, command, &param1, 0, 1))
				shuffle_deck(list, param1);
		} else if (strncmp(command, "DECK_NUMBER", 11) == 0) {
			if (validate_command(list, command, 0, 0, -1))
				printf("The number of decks is %d.\n", list->size);
		} else if (strncmp(command, "MERGE_DECKS", 11) == 0) {
			if (validate_command(list, command, &param1, &param2, 0))
				merge_decks(&list, param1, param2);
		} else if (strncmp(command, "SPLIT_DECK", 10) == 0) {
			if (validate_command(list, command, &param1, &param2, 0))
				split_deck(&list, param1, param2);
		} else if (strncmp(command, "SORT_DECK", 9) == 0) {
			if (validate_command(list, command, &param1, 0, 1))
				sort_deck(list, param1);
		} else {
			char buffer[MAX_COMMAND_SIZE];
			fgets(buffer, MAX_COMMAND_SIZE, stdin);
			printf("Invalid command. Please try again.\n");
		}
	}
	gettimeofday(&end, NULL);

	register int diff_interval = end.tv_sec - start.tv_sec;
    elapsed = ((diff_interval)*1000000.0f + diff_interval)/1000000.0f;

	FILE *fout = fopen("../../not_optimised.out", "w");
    fprintf(fout, "TIME (simple): %12f\n", elapsed);
	fclose(fout);

	return 0;
}
