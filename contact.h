#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
//void initialize(AddressBook *addressBook);
void read_name(AddressBook*addressBook,int );
void read_number(AddressBook*addressBook,int );
void read_email(AddressBook*addressBook,int );
int search_menu(void);
int search_by_name(AddressBook *addressBook, int count[]);
int search_by_phone(AddressBook *addressBook, int count[]);
void print_results(AddressBook *addressBook, int count[], int size);
int name_checker(char[]);
int digit_checker(char[]);
int email_checker(char[]);
int duplicate_checker(AddressBook*addressBook,char [],int,int);
int search_and_show(AddressBook *addressBook, int count[]);
void clean_input_buffer();
void trim_blanks(char ptr[]);
void save_contacts(AddressBook *addressBook);
void load(AddressBook *addressBook);


#endif
