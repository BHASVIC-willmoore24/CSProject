#include<stdio.h>
#include<string.h>

int total_guests = 0;
char selected_board_type[3] = "";
char booking_id[50] = "";
int available_tables[3][2] = {{4, 4}, {4, 4}, {4, 4}};

const char *table_names[3] = {"Endor", "Naboo", "Tatooine"};
const char *time_slots[2] = {"7 PM", "9 PM"};

void book_table_menu();
int is_booking_id_valid(const char *id);
int is_board_type_allowed(const char *board_type);
void display_available_tables();
int book_table(int table_choice, int time_choice);

void book_table_menu() {
    char input_booking_id[50];
    int table_choice, time_choice;

    if (strlen(booking_id) == 0 || total_guests <= 0 || strlen(selected_board_type) == 0) {
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

int is_board_type_allowed(const char *board_type) {
    if (strcmp(board_type, "FB") == 0 || strcmp(board_type, "HB") == 0) {
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

int main() {
    int choice;

    while (1) {
        printf("\n--- Hotel Booking System ---\n");
        printf("1. Book a Dinner Table\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case !1 || !2:
                printf("Invalid choice. Please try again.\n");
            break;
            case 1:
                book_table_menu();
            break;
            case 2:
                printf("Exiting the system.\n"); // this will go to main menu
            return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}