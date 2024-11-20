#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void check_out (char *bookingID, char *user_firstname, char *user_surname) {
	float bill = 0;
	printf("%s : %s %s", bookingID, user_firstname, user_surname);

	bill = calculate_cost (num_adults, num_children, wants_newspaper, selected_room_cost, selected_board_type, time_staying, user_dob, user_age);

	printf("The overall bill is %f", bill);

	// ----------------------------
	// Exit back to main menu/start
	// ----------------------------

}


float calculate_cost (int adult, int child, bool newspaper, int room, int board, int time, char *dob, int age) {
	float cost = 0;
	float cost_room = 0;
	float cost_board = 0;

	cost_room = room;

	if (age > 65) {
		cost_room = cost_room * 0.9;
	}

	printf("The room cost is: %f", cost_room);

	cost = cost + cost_room;

	cost_board = (board * adult) + (board * child * 0.5);

	printf("The board cost is: %f", cost_board);

	cost = cost + cost_board;

	if (newspaper == true) {
		cost = cost + 5.5;
		printf("Cost of daily newspapers: 5.5");
	}

	return (cost);
}