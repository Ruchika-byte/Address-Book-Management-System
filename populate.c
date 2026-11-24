#include "contact.h"
#include<stdio.h>

// Dummy contact data
static Contact dummyContacts[] = 
{
	{"Prafulla", "1234567890", "john@example.com"},
	{"Alice Smith", "0987654321", "alice@example.com"},
	{"Bob Johnson", "1112223333", "bob@company.com"},
	{"Carol White", "4445556666", "carol@company.com"},
	{"David Brown", "7778889999", "david@example.com"},
	{"Eve Davis", "6665554444", "eve@example.com"},
	{"Frank Miller", "3334445555", "frank@example.com"},
	{"Grace Wilson", "2223334444", "grace@example.com"},
	{"Hannah Clark", "5556667777", "hannah@example.com"},
	{"Ian Lewis", "8889990000", "ian@example.com"}
};
/*
void initialize(AddressBook* addressBook)//This function is used to store the dummy contacts in the csv file 
{
	addressBook -> contactCount = 0;

	int numDummyContacts=sizeof(dummyContacts)/sizeof(dummyContacts[0]);

	for (int i=0;i<numDummyContacts&&addressBook->contactCount<100;++i)    
	{
		addressBook->contacts[i]=dummyContacts[i];
		addressBook->contactCount++;
	}
}
*/
void load(AddressBook *addressBook)
{
    FILE *fp;
    addressBook->contactCount = 0;                                  
    fp = fopen("contact.csv","r");
    if(fp==NULL)
    {
        printf("File could not be opened\n");
        return;
    }
    if(fscanf(fp,"%d",&addressBook->contactCount)!=1 || addressBook->contactCount<0)  
        addressBook->contactCount = 0;
    if(addressBook->contactCount > 100)                             
        addressBook->contactCount = 100;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(fscanf(fp," %49[^,],%19[^,],%49[^\n]",                   
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email)!=3)               
        {
            addressBook->contactCount = i;
            break;
        }
    }
    fclose(fp);
}







