

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include<ctype.h>

void listContacts(AddressBook *addressBook)//This function is used to list all contacts that the user has entered
{
    printf("------------------------------------------------------------------------------------------\n");
	printf("NAME\t\t\t\tPHONENUMBER\t\t\tEMAIL-ID\t\t\n");
    printf("------------------------------------------------------------------------------------------\n");



   for(int i=0; i< addressBook -> contactCount;i++)
   {
   printf("%s\t\t\t%s\t\t\t%s\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
   }

}

void createContact(AddressBook *addressBook)//This function is used to create a new contact
{
    /* Define the logic to create a Contacts */
  
    int i = addressBook->contactCount;
    
    if(i>=100)//Logic to check if the addressbook is out of memory.
    {
        printf("Addressbook is out of storage!!!\n");
        return;
    }

    read_name  (addressBook,i);
    
    read_number(addressBook,i);
    
    read_email (addressBook,i);
   
    
    addressBook->contactCount++; //Increment the counter after the name,number and email_id is sucessfully stored.
}  

void searchContact(AddressBook *addressBook)//This function is used to search contact
{
    //Define the logic to search a Contacts 
    int count[100];
    search_and_show(addressBook, count);
}


void editContact(AddressBook *addressBook)/*Search and display contact first
Ask user to enter new details and save the contact again after performing validation checks*/
{
    // Define the logic for Editcontact 
    
    int serial_num,choice=0,temp1,isvalid=0;
    int count[100];
    int ret = search_and_show(addressBook,count);//First use search function to find if the contact is available
    {
        if (ret==0)
        return;
    }
    do
    {
        printf("Enter the serial number of the contact you wish to edit:");
        temp1=scanf("%d",&serial_num);
        clean_input_buffer();
        if(temp1==1 && serial_num>=1 && serial_num <=ret)
        {
            isvalid=1;
            break;
        }
        else
        {
           printf("Serial number is incorrect\n");
           continue;
        }

    } while (isvalid!=1);
    do
    {   
        printf("What do you want to edit?\n");
        printf("1.Edit Name?\n");
        printf("2.Edit Mobile Number\n");
        printf("3.Edit Email-Id\n");
        printf("Enter your choice:");
        temp1=scanf("%d",&choice);
        if(temp1!=1)
        {
            choice=0;
        }
        clean_input_buffer();
         
        switch(choice)
        {
            case 1:
            {
                printf("Enter the new details:\n");
                read_name(addressBook,count[serial_num-1]);
                break;     
            }
            case 2:
            {
                printf("Enter the new details:\n");
                read_number(addressBook,count[serial_num-1]);
                break;  
            }
            case 3:
            {
                printf("Enter the new details:\n");
                read_email(addressBook,count[serial_num-1]);
                break; 

            }
            default:
            {
                printf("Invalid choice! Please try again\n");
            }

        }
    } while (choice!=1 && choice !=2 && choice !=3);
        
 
}


void deleteContact(AddressBook *addressBook)//This function is used to overwrite the contact which you wish to delete with the next contact.
{
    // Define the logic for delete contact 
   
    int serial_num,temp;
    int count[100];
    int isvalid=0;

    int ret = search_and_show(addressBook,count);
    if(ret==0)
    {
        return;
    }
     do
    {
        printf("Enter the serial number of the contact you wish to delete:");
        temp=scanf("%d",&serial_num);
        clean_input_buffer();
        if(temp==1 &&serial_num>=1 && serial_num<=ret)
        {
            isvalid=1;
            break;
        }
        else
        {
            printf("Serial number is incorrect\n");
            continue;
        }

    } while (isvalid!=1);
  
    int j= serial_num-1;
    int delete_index =count[j];
    for(j=delete_index;j<addressBook->contactCount-1;j++)
    {
        addressBook->contacts[j] = addressBook->contacts[j +1];
    }
    printf("Contact successfully deleted\n");
    addressBook->contactCount--;
}

int name_checker(char ptr[])//It validates whether the name contains letters of not and returns 1 on sucessfull name validation
{
    int count=0;
    while(ptr[count])
    {
        if(isalpha(ptr[count])==0 && ptr[count]!=' ')
            return 0;
        else
            count++;
    }
    return 1; 
}


int digit_checker(char ptr[])/*This function validates the user entered number and returns 0 if the number is valid .Additionally 
it returns different return values against each failed condition */
{
    int count=0;
    if (ptr[0]<'6' || ptr[0]>'9')
    {
        return 1 ;// As per National Numbering plan by TRAI number should start with '6','7','8' or '9'
    }

    while(ptr[count])
    {
        if(isdigit(ptr[count])==0)
            return 2;//User didnot enter valid digits
        else
            count++;
    }
    if(count!=10)
    {
        return 3;//User entered more than 10 digits
    }

    return 0; //User entered valid number
}
   
          
int duplicate_checker(AddressBook *addressbook,char ptr[],int choice, int skip)/*This is a generic duplicate_checker function,if the user's 
choice is 1 -it compared the current mobile number against the existing mobile number.If the choice is 2 -it compares the current email
against existing email-id.It both cases if same email-id or phone number exits it returns 0 */
{
    int temp= addressbook->contactCount;
    for(int i =0;i<temp;i++)
    {
         if(i==skip)
            continue;
        if(choice==1 && strcasecmp(ptr,addressbook->contacts[i].phone)==0)
        {
            return 0;
        }
        else if(choice==2 && strcasecmp(ptr,addressbook->contacts[i].email)==0)
        {
            return 0;
        }
    }

    return 1;
}

int email_checker(char ptr[])
/*Email checker functions checks the email against following conditions
1.The email should not contain multiple .com and @
2.The email should contain atleast one letter between @ and .com
3.The email should end with .com
In case all conditions are fullfilled the function returns '0' or it return different return values depending 
on where the logic failed*/
{
    char* temp=ptr;
    char* at =strchr(ptr,'@');
    char* com=strstr(ptr,".com");
    
    int at_found=0;
    int com_count=0;
    int count=0;
    while(temp[count])
    {
        if(temp[count]=='@')
        {
            at_found+=1;
        }
        count++;
    }
    while((temp=strstr(temp,".com"))!=NULL) 
    {
        com_count+=1;
        temp= temp+4;
    }
    if(at_found!=1 || com_count!=1)
    {
        return 1;
    }
    /*
    char* at =strchr(ptr,'@');
    char* com=strstr(ptr,".com");

    if(at ==NULL|| com ==NULL)
    {
        return 1; //Invalid due to absence of @ and .com
    }
    */
    else if(com-at <2)// Pointer distance 
    {
        return 2;//Invalid no letter between @ and .com
    }
    else if (strcmp(com,".com")!=0)
    {
        return 3;//Contains letters after .com
    }
    else
        return 0;//Valid email id
}
void read_name(AddressBook*addressBook,int i )/*This function is used to read the name entered by the user.It validates whether
the user input is sucessfully stored or not.Additionally it removes any consecutive blanks,leading blanks or trailing blank*/
{
   int temp1,temp2;
    do{
        printf("Enter the name:");
        temp1=scanf("%49[^\n]",addressBook->contacts[i].name);

        clean_input_buffer();//Clean incase any content is left in the input buffer.
        if(temp1==1) //Used to check if scanf has sucessfully worked or not
        {
            trim_blanks(addressBook->contacts[i].name);//Trim any spaces given by the user
            if ((temp2 = name_checker(addressBook->contacts[i].name))!=1)
            printf("Error!Name cannot contain digits or special characters\n");
        }
        else
        {
            printf("Error!Name cannot be blank\n");
            temp2=0;//Remove garbage value from temp2
        }
    }while(temp2!=1);
}

void read_number(AddressBook*addressBook,int i )/*This function is designed to read nunmber from user 
1. It calls a duplicate_checker function to check whether same number already exists.
2. It removed any leading,trailing and consecutive blank.
3. It checks whether the number entered by the user is sucessfully stored using scanf function
4.It calls a  digit_checker function and returns 0 when a valid number is found 
5.In case validation fails ,it prints the reason behind the failure.
6.Process continues until user enters valid number.
*/
{
    int isvalid=0;
    char temp_phone[20];
    int temp1,temp2;
    int choice=1;
    do{
        printf("Enter the 10 Digit mobile number:");
        temp1=scanf("%19[^\n]",temp_phone);
        clean_input_buffer();
        if(temp1==1) 
        {
            trim_blanks(temp_phone);
            int ret = duplicate_checker(addressBook,temp_phone,choice,i);
            if (ret == 0) 
            {
                printf("Error! This phone number already exists.\n");
                continue; // Skip the rest and ask for input again
            }
            temp2 = digit_checker(temp_phone);
            switch(temp2)
            {
             case 1:
                {
                    printf("Error!Number should start with '6','7','8' or '9'\n");
                    break;
                }
            case 2:
               {
                    printf("Error!Number should not contain alphabets or special character\n");
                    break;
               }
            case 3:
               {
                    printf("Error!Numbers must be exactly 10 digits\n");
                    break;
               }
            case 0:
                    // Valid number found! Break the loop by setting validation flag
                {
                    isvalid=1;
                    strcpy(addressBook->contacts[i].phone,temp_phone);
                    break;
                }
            default:
                    printf("Invalid");

            }
       }
        else
        {
            printf("Error!Number cannot be blank\n");
        }

    }while(isvalid!=1);

}
void read_email(AddressBook*addressBook,int i) /*This function is designed to read email from user 
1. It checks whether the number entered by the user is sucessfully stored using the scanf function.
2. It calls a duplicate_checker function to check whether same email-id already exists.
3. It removes any leading,trailing and consecutive blank.
4.It calls a  email_checker function and returns 0 when a valid number is found 
5.In case validation fails ,it prints the reason behind the failure
6.The process continues until the user enters valid email*/
{
char temp_email[50];
int temp1,choice,isvalid;
choice=2;
isvalid=0;
do
{
    printf("Enter the email id:");
    temp1=scanf("%49[^\n]",temp_email);
    clean_input_buffer();//Clean input buffer

    
    if(temp1==1) 
        {
            trim_blanks(temp_email);
            int ret = duplicate_checker(addressBook,temp_email,choice,i);
            if (ret == 0) 
            {
                printf("Error! This email-id already exists.\n");
                continue; // Skip the rest and ask for input again
            }

           int checker = email_checker(temp_email);
           switch(checker)
           {
                case 1:
                {
                    printf("Error! email is not valid.Check @ and .com for error\n");
                    break;
                }
                case 2:
                {
                    printf("Error!@ and .com cannot be adjacent\n");
                    break;
                }
                case 3:
                {
                    printf("Error!Cannot enter anything after .com\n");
                    break;
                }
                case 0:
                {
                    isvalid=1;
                    strcpy(addressBook->contacts[i].email,temp_email);
                    break;
                }
                default:
                    printf("Invalid");

            }


        }


    else
    {
        printf("Error!Email cannot be blank\n");
    }


}while(isvalid!=1);

}

int search_menu()/*This function helps user to select the optio using different options.Re-promt incase user enters invalid choice*/
{
    int choice;

    do {
        printf("\nSEARCH USING.....\n");
        printf("1. Contact Name\n");
        printf("2. Contact Phonenumber\n");
        printf("3. Contact email-id\n");
        printf("Enter your choice: ");
        if((scanf("%d", &choice))!=1)
        {
            choice = 0;   // so the invalid-choice check below doesn't read garbage
        }
        clean_input_buffer();

        if (choice != 1 && choice != 2 && choice != 3)
            printf("Invalid choice. Please try again.\n");
    } while (choice != 1 && choice != 2 && choice != 3);

    return choice;
}

int search_by_name(AddressBook *addressBook, int count[])//Search contact if name is found store the index in count array.
{
    char temp[50]=" ";
    int j, k = 0;

    printf("Enter the name you want search for:");
    scanf("%49[^\n]",temp);
    clean_input_buffer();
    trim_blanks(temp);
    for (j=0; j<addressBook->contactCount; j++)
    {
        if(strcasecmp(temp,addressBook->contacts[j].name)==0)
        {
            count[k]=j;
            k++;
        }
    }
    return k;  
}
int search_by_phone(AddressBook *addressBook, int count[])//Search contact if the phone number is found store the index in count array.
{
    char temp[20]=" ";
    int j;

    printf("Enter the phonenumber you want search for:");
    scanf("%19[^\n]",temp);
    clean_input_buffer();
    trim_blanks(temp);
    for (j=0; j<addressBook->contactCount; j++)
    {
        if(strcasecmp(temp,addressBook->contacts[j].phone)==0)
        {
            count[0]=j;
            return 1;   
        }
    }
    return 0;
}
int search_by_email(AddressBook *addressBook, int count[])//Search contact if the email-id is found store the index in count array
{
    char temp[50]=" ";
    int j;

    printf("Enter the email-id you want search for:");
    scanf("%49[^\n]",temp);
    clean_input_buffer();
    trim_blanks(temp);
    for (j=0; j<addressBook->contactCount; j++)
    {
        if(strcasecmp(temp,addressBook->contacts[j].email)==0)
        {
            count[0]=j;
            return 1;   
        }
    }
    return 0;
}
void print_results(AddressBook *addressBook, int count[], int size)/*Used in search function. 
Used to print the contacts using the index stored in count array*/
{
    printf("------------------------------------------------------------------------------------------------\n");
    printf("SL\t\tNAME\t\t\t\tPHONENUMBER\t\t\tEMAIL-ID\t\t\n");
    printf("------------------------------------------------------------------------------------------------\n");

    for(int k=0; k<size; k++)
    {
        printf("%d\t\t%s\t\t\t%s\t\t\t%s\n",k+1,addressBook -> contacts[count[k]].name,addressBook -> contacts[count[k]].phone, addressBook -> contacts[count[k]].email);
    }
}
int search_and_show(AddressBook *addressBook, int count[])/*This function calls the search_menu function and according to the selection made
3 modes are available
1.search_by_name
2.search_by_phone
3.search_by_email
if match is found display the contact details using print_results function.
*/

{
    int size = 0;

    switch (search_menu())
    {
        case 1: 
        {
            size = search_by_name(addressBook, count);  
            break;
        }
        case 2: 
        {
            size = search_by_phone(addressBook, count); 
            break;
        }
        case 3: 
        {
            size = search_by_email(addressBook, count); 
            break;
        }
    }

    if (size > 0)
    {
        print_results(addressBook, count, size);
    }
    else
    {
        printf("Contact not found\n");
        printf("Try again !!!\n");
    
    }
    return size;
}
void clean_input_buffer()//This function is used to clean input_buffer
{
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

void trim_blanks(char ptr[])//Used to remove any leading blank,trailing blank and consecutive blank
{
    char *p = ptr;
    while(*p)
    {
        if((*p ==' ' || *p =='\t') && (*(p+1)==' ' ||*(p+1) =='\t'))
        {
            char * temp =p;
            while(*temp)
            {
                *temp=*(temp+1);
                 temp++;
            }
        }
        else
        {
            p++;
        }
    }
    if(ptr[0]==' ' || ptr[0]=='\t')
        memmove(ptr, ptr+1, strlen(ptr));
    int len = strlen(ptr);
    if(len > 0 && (ptr[len-1]==' ' || ptr[len-1]=='\t'))
        ptr[len-1] = '\0';
}

void save_contacts(AddressBook *addressBook)//This function is used to load all the new contacts made into a csv file before exiting the program
{
    FILE *fp;
    fp = fopen("contact.csv","w");
     if(fp==NULL)
    {
        printf("File opening failed");
        return ;
    }
    fprintf(fp,"%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}