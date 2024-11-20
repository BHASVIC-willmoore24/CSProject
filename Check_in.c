//
// Created by Lenovo on 13/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int room_rates[] = {100, 100, 85, 75, 75, 50};
int board_rates[] = {20, 15, 5};


void generate_booking_id(char *surname, char *booking_id) {
    srand(time(0));
    int random_number = rand() % 10000;
    sprintf(booking_id, "%s", surname, random_number);
}


int main() {
    char user_first_name[50], user_surname[50], user_dob[20];
    int total_guests, num_adults, num_children, board_type, length_of_stay;
    int room_selection, newspaper_cost = 0;
    char wants_newspaper[10], booking_id[60];


    printf("Welcome to the Check-in System\n");


    printf("Enter your first name: ");
    scanf("%s", user_first_name);
    printf("Enter your surname: ");
    scanf("%s", user_surname);
    printf("Enter your date of birth (DD/MM/YY): ");
    scanf("%s", user_dob);


    printf("Enter total number of guests: ");
    scanf("%d", &total_guests);


    printf("Enter the number of adults: ");
    scanf("%d", &num_adults);


    num_children = total_guests - num_adults;


    printf("Select board type (1: Full Board, 2: Half Board, 3: Bed & Breakfast): ");
    scanf("%d", &board_type);

    printf("Enter the length of stay in days: ");
    scanf("%d", &length_of_stay);


    printf("Would you like a daily newspaper? (Yes/No): ");
    scanf("%s", wants_newspaper);
    if (strcmp(wants_newspaper, "Yes") == 0 || strcmp(wants_newspaper, "yes") == 0) {
        newspaper_cost = 1;
    }


    printf("Available rooms and daily rates:\n");
    for (int i = 0; i < 6; i++) {
        printf("Room %d: $%d\n", i + 1, room_rates[i]);
    }


    printf("Select a room number (1-6): ");
    scanf("%d", &room_selection);
    int selected_room_cost = room_rates[room_selection - 1];


    generate_booking_id(user_surname, booking_id);

  
    printf("\n--- Booking Details ---\n");
    printf("Name: %s %s\n", user_first_name, user_surname);
    printf("Date of Birth: %s\n", user_dob);
    printf("Total Guests: %d (Adults: %d, Children: %d)\n", total_guests, num_adults, num_children);
    printf("Board Type: %s\n", (board_type == 1) ? "Full Board" : (board_type == 2) ? "Half Board" : "Bed & Breakfast");
    printf("Room Selected: Room %d ($%d per night)\n", room_selection, selected_room_cost);
    printf("Length of Stay: %d days\n", length_of_stay);
    printf("Daily Newspaper: %s ($%d per day)\n", (newspaper_cost == 1) ? "Yes" : "No", newspaper_cost);
    printf("Booking ID: %s\n", booking_id);
    printf("Thank you for checking in!\n");

    return 0;
}
//take user back to main menu allowing them to exit or book a dinner table. 
