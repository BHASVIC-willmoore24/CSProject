#include <stdio.h>

int main(){

    int choice;
    int loop_menu = 1;

    while(loop_menu == 1){

        printf("\nWelcome to Hotel Kashyyyk!\nWould you like to:\nCheck in: (1)\nBook a dinner table: (2)\nCheck out: (3)\n-------------------------\nEnter option:");
        fflush(stdin);
        scanf("%d",&choice);

        switch (choice) {
            case 1: printf("Entering check in menu\n"); // this will go to check in
            loop_menu = 0;
            break;
            case 2: printf("Entering table booking menu\n"); // this will go to booking table
            loop_menu = 0;
            break;
            case 3: printf("Entering check out menu\n"); // this will go to check out
            loop_menu = 0;
            break;
            default: printf("Invalid choice, try again\n");
            loop_menu = 1;

        }

    }

    return 0;
}
