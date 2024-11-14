//
// Created by Lenovo on 13/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_GUESTS 4


#define ROOM1_2_PRICE 100
#define ROOM3_PRICE 85
#define ROOM4_5_PRICE 75
#define ROOM6_PRICE 50

// Board rates
#define FULL_BOARD_RATE 20
#define HALF_BOARD_RATE 15
#define BB_RATE 5

// Function to generate a random Booking ID
void generateBookingID(char *surname, char *bookingID) {
    int random_number = rand() % 1000;  // Random number between 0 and 999
    sprintf(bookingID, "%s%d", surname, random_number);
}

// Function to get the room choice
int getRoomChoice() {
    int roomChoice;
    do {
        printf("\nChoose your room (1-6): ");
        scanf("%d", &roomChoice);
        if (roomChoice < 1 || roomChoice > 6) {
            printf("Invalid room selection. Please select a room from 1 to 6.\n");
        }
    } while (roomChoice < 1 || roomChoice > 6);
    return roomChoice;
}

