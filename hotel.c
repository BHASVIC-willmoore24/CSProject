#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// constants
int room_rates[] = {100, 100, 85, 75, 75, 50};
int board_rates[] = {20, 15, 5};

// arrays for guest information
char booking_ids[100][50];
char first_names[100][50];
char last_names[100][50];
char dobs[100][11];
int ages[100];
int total_guests[100];
int num_adults[100];
int num_children[100];
char board_types[100][3];
int lengths_of_stay[100];
int room_numbers[100];
int newspapers[100];

// tracking for room and table availability
int room_occupied[6] = {0, 0, 0, 0, 0, 0};
int available_tables[3][2] = {{4, 4}, {4, 4}, {4, 4}};
const char *table_names[3] = {"Endor", "Naboo", "Tatooine"};
const char *time_slots[2] = {"7 PM", "9 PM"};

int guest_count = 0; // total number of guests checked in

// function prototypes
int main_menu();
void check_in();
void book_table_menu();
void check_out();
int calculate_age(const char *dob);
int find_guest_index(const char *booking_id);
int book_table(int table_choice, int time_choice, int party_size);
float calculate_cost(int index);
void display_available_tables();

int main_menu() {
    int choice;
    while (1){
        printf("\nWelcome to Hotel Kashyyyk!\n");
        printf("1. Check In\n2. Book a Dinner Table\n3. Check Out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice) {
            case 1:
                check_in();
            break;
            case 2:
                book_table_menu();
            break;
            case 3:
                check_out();
            break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void check_in() {
    if (guest_count >= 6) { // doesnt let you check in if all rooms are occupied
        printf("All rooms are currently occupied. Cannot check in more guests.\n");
        return;
    }

    printf("Enter your first name: ");
    scanf("%s", first_names[guest_count]);
    printf("Enter your last name: ");
    scanf("%s", last_names[guest_count]);
    printf("Enter your date of birth (DD/MM/YYYY): ");
    scanf("%s", dobs[guest_count]);

    ages[guest_count] = calculate_age(dobs[guest_count]);
    printf("Your calculated age is: %d\n", ages[guest_count]);

    printf("Enter total number of guests (Max 4): ");
    scanf("%d", &total_guests[guest_count]);
    if (total_guests[guest_count] > 4) {
        printf("Maximum 4 guests allowed. Please try again.\n"); // validation (we need lots more of this everywhere)
        return;
    }

    printf("Enter the number of adults (over 16): ");
    scanf("%d", &num_adults[guest_count]);
    num_children[guest_count] = total_guests[guest_count] - num_adults[guest_count];

    printf("Select board type (FB, HB, BB): ");
    scanf("%s", board_types[guest_count]);

    printf("Enter the length of stay in days: ");
    scanf("%d", &lengths_of_stay[guest_count]);

    printf("Would you like a daily newspaper? (Yes=1, No=0): ");
    scanf("%d", &newspapers[guest_count]);

    printf("Available rooms and daily rates:\n");
    for (int i = 0; i < 6; i++) {
        if (room_occupied[i] == 0) {
            printf("Room %d: GBP: %d\n", i + 1, room_rates[i]);
        }
    }

    printf("Select a room number (1-6): ");
    int room_choice;
    while (1) { // loops until valid option is selected (used throughout)
        scanf("%d", &room_choice);
        fflush(stdin);
        if (room_choice < 1 || room_choice > 6 || room_occupied[room_choice - 1] == 1) {
            printf("Invalid or occupied room. Please select an available room number (1-6): ");
        } else {
            break;
        }
    }
    room_numbers[guest_count] = room_choice; // assign room to specific guest
    room_occupied[room_choice - 1] = 1; // marks room as occupied

    sprintf(booking_ids[guest_count], "%s%d", last_names[guest_count], rand() % 10000); // generates booking id

    printf("\n--- Booking Details ---\n");
    printf("Name: %s %s\n", first_names[guest_count], last_names[guest_count]);
    printf("Date of Birth: %s\n", dobs[guest_count]);
    printf("Age: %d\n", ages[guest_count]);
    printf("Booking ID: %s\n", booking_ids[guest_count]);
    printf("Room Selected: %d\n", room_numbers[guest_count]);
    printf("Thank you for checking in!\n");

    guest_count++;
}

void book_table_menu() {
    char booking_id[50];
    printf("Enter your BookingID: ");
    scanf("%s", booking_id);

    int index = find_guest_index(booking_id);
    if (index == -1) {
        printf("Invalid BookingID. Please try again.\n");
        return;
    }

    if (strcmp(board_types[index], "FB") != 0 && strcmp(board_types[index], "HB") != 0) {
        printf("Table booking is only available for Full Board or Half Board guests.\n");
        return;
    }

    display_available_tables();

    int table_choice, time_choice;
    printf("Select a table (1 = Endor, 2 = Naboo, 3 = Tatooine): ");
    scanf("%d", &table_choice);
    printf("Select a time slot (1 = 7 PM, 2 = 9 PM): ");
    scanf("%d", &time_choice);

    if (book_table(table_choice - 1, time_choice - 1, total_guests[index])) { // checks if table is available (function returns 1 if true which allows the if statement to go through)
        printf("Your table has been successfully booked at %s for %s!\n",
               table_names[table_choice - 1], time_slots[time_choice - 1]);
    } else {
        printf("Table is not available. Please try another option.\n");
    }
}

void check_out() {
    char booking_id[50];
    printf("Enter your BookingID: ");
    scanf("%s", booking_id);

    int index = find_guest_index(booking_id);
    if (index == -1) {
        printf("Invalid BookingID. Guest not found.\n");
        return;
    }

    float total_cost = calculate_cost(index);

    printf("\n--- Checkout Details ---\n");
    printf("Name: %s %s\n", first_names[index], last_names[index]);
    printf("Booking ID: %s\n", booking_id);
    printf("Total Cost: GBP: %.2f\n", total_cost);

    room_occupied[room_numbers[index] - 1] = 0; // frees the room
    printf("Room %d is now available.\n", room_numbers[index]);
}

int calculate_age(const char *dob) {
    int birth_day, birth_month, birth_year;
    sscanf(dob, "%d/%d/%d", &birth_day, &birth_month, &birth_year); // takes in just the numbers from their dob for calculation (this will be hard to validate where it is asked in check in)

    time_t t = time(NULL);
    struct tm *current_date = localtime(&t); // getting data for current date using time.h library

    // storing the current date data as variables (im not 100% sure how this works, i looked up how to use this but i dont know how else to calculate age from dob)
    int current_day = current_date->tm_mday;
    int current_month = current_date->tm_mon + 1;
    int current_year = current_date->tm_year + 1900;

    int age = current_year - birth_year;
    if (birth_month > current_month || (birth_month == current_month && birth_day > current_day)) { // checks if they havent had their birthday yet and updates accordingly
        age--;
    }

    return age;
}

// goes through guest index with provided booking id and checks if it exists
int find_guest_index(const char *booking_id) {
    for (int i = 0; i < guest_count; i++) {
        if (strcmp(booking_ids[i], booking_id) == 0) {
            return i;
        }
    }
    return -1;
}

// checks which tables are available for the users party size and updates them when chosen
int book_table(int table_choice, int time_choice, int party_size) {
    if (available_tables[table_choice][time_choice] >= party_size) {
        available_tables[table_choice][time_choice] -= party_size;
        return 1;
    }
    return 0;
}

float calculate_cost(int index) {
    float room_cost = room_rates[room_numbers[index] - 1] * lengths_of_stay[index];
    if (ages[index] > 65) { // checks senior discount
        room_cost *= 0.9;
    }

    float board_cost = (board_rates[0] * num_adults[index]) +
                       (board_rates[0] * num_children[index] * 0.5); // child discount
    board_cost *= lengths_of_stay[index];

    float newspaper_cost;
    if (newspapers[index] == 1) {
        newspaper_cost = 5.50;
    } else {
        newspaper_cost = 0;
    }

    return room_cost + board_cost + newspaper_cost;
}

void display_available_tables() {
    printf("Available tables:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("Table %s at %s has %d seats available.\n",
                   table_names[i], time_slots[j], available_tables[i][j]);
        }
    }
}

int main() {
    return main_menu();
}