#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int room_rates[] = {100, 100, 85, 75, 75, 50};
int board_rates[] = {20, 15, 5};
int num_adults = 0;
int num_children = 0;
char wants_newspaper = "";
int selected_room_cost = 0;
int selected_board_type = 0;
int time_staying = 0;
//char user_dob ="";
int user_age = 0;
int newspaper_cost = 0;
int total_guests = 0;
char booking_id[50] = "";
int available_tables[3][2] = {{4, 4}, {4, 4}, {4, 4}};

void book_table_menu();
int is_booking_id_valid(const char *id);
int is_board_type_allowed(const char board_type);
void display_available_tables();
int book_table(int table_choice, int time_choice);
float calculate_cost(int num_adults, int num_children, char wants_newspaper, int selected_room_cost, int board_type, int time_staying, int user_age);

void generate_booking_id(char *surname, char *booking_id) {
    srand(time(0));
    int random_number = rand() % 10000;
    sprintf(booking_id, "%s%d", surname, random_number);
}


int check_in() {
    char user_first_name[50], user_surname[50], user_dob[20];
    int total_guests, num_adults, num_children, board_type, length_of_stay;
    int room_selection, newspaper_cost = 0;
    char wants_newspaper[10], booking_id[60];


    printf("Welcome to the Check-in System\n");


    printf("Enter your first name: ");
    scanf("%s", user_first_name);
    printf("Enter your surname: ");
    scanf("%s", user_surname);
    //printf("Enter your date of birth (DD/MM/YY): ");
    //scanf("%s", user_dob);
    printf("Enter your age");
    scanf("%d",&user_age);


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



const char *table_names[3] = {"Endor", "Naboo", "Tatooine"};
const char *time_slots[2] = {"7 PM", "9 PM"};

void book_table_menu() {
    char input_booking_id[50];
    int table_choice, time_choice;

    if (strlen(booking_id) == 0 || total_guests <= 0 || selected_board_type == 0) {
        printf("Error: No booking data available. Please check in first.\n");
        return;
    }

    printf("Enter your BookingID: ");
    scanf("%s", input_booking_id);

    if (!is_booking_id_valid(input_booking_id)) {
        printf("Invalid BookingID. Please try again.\n");
        return;
    }

    if (!is_board_type_allowed(selected_board_type)) {
        printf("Your board type does not allow table booking.\n");
        return;
    }

    display_available_tables();

    printf("Select a table (1 = Endor, 2 = Naboo, 3 = Tatooine): ");
    scanf("%d", &table_choice);

    if (table_choice < 1 || table_choice > 3) {
        printf("Invalid table selection. Please try again.\n");
        return;
    }

    printf("Select a time slot (1 = 7 PM, 2 = 9 PM): ");
    scanf("%d", &time_choice);

    if (time_choice < 1 || time_choice > 2) {
        printf("Invalid time selection. Please try again.\n");
        return;
    }

    if (book_table(table_choice - 1, time_choice - 1)) {
        printf("Your table has been successfully booked at %s for %s!\n",
               table_names[table_choice - 1], time_slots[time_choice - 1]);
    } else {
        printf("Table is not available. Please try another option.\n");
    }
}

int is_booking_id_valid(const char *id) {
    if (strcmp(id, booking_id) == 0) {
        return 1;
    }
    return 0;
}

int is_board_type_allowed(const char board_type) {
    if (selected_board_type == 1 || selected_board_type == 2) {
        return 1;
    }
    return 0;
}

void display_available_tables() {
    printf("Available tables:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            if (available_tables[i][j] >= total_guests) {
                printf("Table %s at %s has %d seats available.\n", table_names[i], time_slots[j], available_tables[i][j]);
            }
        }
    }
}

int book_table(int table_choice, int time_choice) {
    if (table_choice < 0 || table_choice >= 3 || time_choice < 0 || time_choice >= 2) {
        return 0;
    }

    if (available_tables[table_choice][time_choice] >= total_guests) {
        available_tables[table_choice][time_choice] -= total_guests;
        return 1;
    }

    return 0;
}

int book_a_table() {
    int choice;
    int loop_menu = 1;

    while (loop_menu == 1) {
        printf("\n--- Hotel Booking System ---\n");
        printf("1. Book a Dinner Table\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        fflush(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case !1 || !2:
                printf("Invalid choice. Please try again.\n");
                loop_menu = 1;
            break;
            case 1:
                book_table_menu();
                loop_menu = 1;
            break;
            case 2:
                printf("Exiting the system.\n"); // this will go to main menu
                loop_menu = 0;
            return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                loop_menu = 1;
        }
    }
}

void check_out (char *bookingID, char *user_firstname, char *user_surname) {
    float bill = 0;
    printf("%s : %s %s", bookingID, user_firstname, user_surname);

    bill = calculate_cost(int (num_adults), int (num_children), char (wants_newspaper), int (selected_room_cost), int (selected_board_type), int (time_staying), int (user_age));

    printf("The overall bill is %f", bill);

}


float calculate_cost (int adult, int child, char newspaper, int room, int board, int time, int user_age) {
    float cost = 0;
    float cost_room = 0;
    float cost_board = 0;

    cost_room = room;

    if (user_age > 65) {
        cost_room = cost_room * 0.9;
    }

    printf("The room cost is: %f", cost_room);

    cost = cost + cost_room;

    cost_board = (board * adult) + (board * child * 0.5);

    printf("The board cost is: %f", cost_board);

    cost = cost + cost_board;

    cost = cost * time;

    if (newspaper == 1) {
        cost = cost + 5.5;
        printf("Cost of daily newspapers: 5.5");
    }

    return (cost);
}