/*
   Name: Ruchika Paul
   Date:30/10/2026
   Description: A terminal-based **Address Book management system** written in C, 
   built and run using Visual Studio Code (VS Code) on Windows. 
   Main output layout
   Address Book Menu:
              1. Create contact
              2. Search contact
              3. Edit contact
              4. Delete contact
              5. List all contacts
              6. Save and Exit
              Enter your choice: 
User can enter any choice from 1-6.
When the choice is 6 the program will save all any new contacts created,updated or deleted in the the contact.csv file. 
*/

#include <stdio.h>
#include "contact.h"

int main()
{
    
    int choice;
    AddressBook addressBook;
    load(&addressBook);
    //initialize(&addressBook);
  // Initialize the address book


    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1)
        {
            choice = 0;
        }
    clean_input_buffer();
       
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                
                save_contacts(&addressBook);
                printf(" Saving and Exiting...\n");
//				exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
