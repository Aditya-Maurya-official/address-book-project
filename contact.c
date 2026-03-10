#include <stdio.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

void listContacts(AddressBook *addressBook)
{    
    char choice;
    do
    {   
        printf("\nSort By:\n");
        printf("1. Name\n");
        printf("2. Contact Number\n");
        printf("3. Email id\n");
        printf("4. Exit\n");
        printf("Enter your choice: \n");
        scanf(" %c", &choice);
        __fpurge(stdin);
        
        switch (choice)
        {
        case '1': //NAME
            if (choice >= '1' && choice <= '3') 
                    {
                    printf("*********************************************************\n");
                    printf("%-5s %-15s %-15s %-25s\n", "Index", "Name", "Phone", "Email");
                    printf("*********************************************************\n");
                    }
           for (int i = 0; i < addressBook->contactCount ; i++)
            {
            for (int j =i+ 1; j < addressBook->contactCount; j++)
                {
                     
                if (strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0)
                    {
                   
                    swap(addressBook,i,j);
                    }
                }
            }
            for(int i=0;i<addressBook ->contactCount;i++)
            {
                searchout(addressBook,i);
            }
            break;

        case '2':     //CONTACT NUMBER
                 if (choice >= '1' && choice <= '3') 
                    {
                    printf("*********************************************************\n");
                    printf("%-5s %-15s %-15s %-25s\n", "Index", "Name", "Phone", "Email");
                    printf("*********************************************************\n");
                    }
            for (int i = 0; i < addressBook->contactCount ; i++)
            {
            for (int j = i + 1; j < addressBook->contactCount; j++)
                {
                       
                if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone) > 0)
                    {
                    
                    // Swap contacts
                    swap(addressBook,i,j);
                    }
                }
            }
            for(int i=0;i<addressBook ->contactCount;i++)
            {
                searchout(addressBook,i);
            }
            break;
        case '3':     //Email id
                 if (choice >= '1' && choice <= '3') 
                    {
                    printf("*********************************************************\n");
                    printf("%-5s %-15s %-15s %-25s\n", "Index", "Name", "Phone", "Email");
                    printf("*********************************************************\n");
                    }
            for (int i = 0; i < addressBook->contactCount;i++)
            {
            for (int j = i + 1; j < addressBook->contactCount; j++)
                {
                    
                if (strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email) > 0)
                    {
                       // Swap contacts
                    swap(addressBook,i,j);
                    }
                }
            }
            for(int i=0;i<addressBook ->contactCount;i++)
            {
                searchout(addressBook,i);
            }
            break;
        case '4':     //Exit
            break;
        
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '4');

}

void swap(AddressBook *addressBook,int i,int j)
    {   
        Contact temp = addressBook->contacts[i];
        addressBook->contacts[i] = addressBook->contacts[j];
        addressBook->contacts[j] = temp;     
        return;          
    }

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file during initialization (After files)
     loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)

{   
    Contact *newContact = &addressBook->contacts[addressBook->contactCount];
                                    
    int digit,len,upper,atr,atr_index,com;

    // Taking name as input and validate it
        validate_name(newContact->name);

    // Taking Contact number as input and validate it
        validate_phone(addressBook,newContact->phone);

    // Taking E-mail as input and validate it
        validate_email(addressBook,newContact->email);

        addressBook->contactCount++;

        printf("Contact created Successfully!!!\n\n");
}

void validate_name(char* name)
{  

    int digit;

    do
    {   digit=0;
        printf("Enter Name: \n");
        scanf(" %[^\n]",name);
        for(int i=0;name[i]!='\0';i++)
        {
            if(!isalpha(name[i]) && name[i] != ' ')
            {
            digit=1;
            break;
            }
        }
        if(digit)
        printf("Error!!! Write alphabet only.\n");
        
    } 
    while(digit);
   // printf("************** Valid Name Entered: %s *****************\n", name);
}
void validate_phone(AddressBook *addressBook,char *phone)
{   
    int digit,len,flag;
    do
    {   digit=0;
        flag=0;
        printf("\nEnter Contact number :\n");
        scanf("%s",phone);
        len=strlen(phone);
        if(len==10) //length should be 10 characters
        {    
            for(int i=0;phone[i]!='\0';i++)
            {
                if(isdigit(phone[i]))   // all characters should be digits2
                {
                    digit++;
                }
            }
        }
        if(digit!=10)
        printf("Enter valid contact !!!\n");

        //Contact number should be unique
        for (int i = 0; i <addressBook->contactCount && digit; i++) 
        {    if (addressBook->contacts[i].phone == phone)
                continue;   // same contact, skip
            if ( strcmp(addressBook->contacts[i].phone, phone) == 0) //phone should not be compared with itself
                {
                printf("Duplicate phone number! Contact already exists.\n");
                flag=1;
                }
        }
    }
    while (len!=10 || digit!=10 || flag);
    printf("************** Valid Contact Number Entered: %s ***************\n", phone);
}

void validate_email(AddressBook *addressBook,char *email)
{   
    int digit,len,upper,atr,atr_index,com,unique,gap;
    do
    {   upper=0;
        atr=0;
        atr_index=0;
        com=0;
        unique=0;
        gap=0;
        printf("\nEnter E-mail id :\n");
        scanf("%s",email);

        len=strlen(email);
        for(int i=0;email[i]!='\0';i++)
        {
           //1.No uppercase
            if(isupper(email[i]))
            {
                upper=1;
            }
            //2.'@' pressent for one time && '@' not present for at first index
            if('@'==email[i]) //&& '@'!=newContact->email[0])
            {
                atr++;
            }
            //3.'@' not present for at first index
            if('@'==email[0])
            {
                atr_index=1;
            }
            //4. '.com' should be at last
            
            if(len < 7 || strcmp(&email[len - 4], ".com") != 0)
            {
                com=1;
            }

            //5. there should be atleast one character b/w '@' and '.com'
            char *at = strchr(email, '@');
            char *dot = strstr(email, ".com");
            if (!at || !dot || at > dot - 2)
            {
            gap = 1;
            }

            //6.email should be unique
            for (int j=0;j<addressBook->contactCount;j++) 
            {
                if (strcmp(addressBook->contacts[j].email, email) == 0) 
                    {
                    unique=1;
                    }
            }

        }
        if(upper)
        {
            printf("Do not write in Upper Case!!!\n");
        }
        if(atr!=1)
        {
            printf("Do not write @ more %d times!!!\n",atr);
        }
        if(atr_index)
        {
            printf("Do not write @ at starting!!!\n"); 
        }
        if(com)
        {
            printf("Email not ending with '.com '\n");
        }
        if(gap)
        {
            printf("Give atleast 1 character b/w '@' & '.com '\n");
        }
        if(unique)
        {
            printf("Duplicate email id! Contact already exists.\n");
        }
    }
        
        while(upper || atr!=1 || atr_index || com|| gap);
      //  printf("********* Valid Email Entered: %s ***********\n", email);
}

void searchContact(AddressBook *addressBook)
{   
    int choice;int choice_flag=0;
    char arr[50];
    int valid;
    do
    {   valid=0;
        printf("\nSearch Contact By:\n");
        printf("1. Name\n");
        printf("2. Contact Number\n");
        printf("3. Email id\n");
        printf("4. Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);
        __fpurge(stdin);

        if(choice==1 || choice==2 || choice==3 || choice==4)
        choice_flag=1;


        switch (choice)
        {   

        case 1: //NAME
            printf("Enter the Name:\n");
            scanf("%[^\n]",arr);
            if (!valid) 
                    {
                    printf("*********************************************************\n");
                    printf("%-5s %-15s %-15s %-25s\n", "Index", "Name", "Phone", "Email");
                    printf("*********************************************************\n");
                    }
            for(int i=0;i< addressBook->contactCount;i++)
            {   
                if(strcmp(addressBook->contacts[i].name,arr)==0)
                {            
                    
                searchout(addressBook,i);
                valid++;
                }
            }if(!valid)
                printf("Contact not Found!!!\n");


        break;
        case 2: //Contact number
            printf("Enter the Contact Number:\n");
            scanf("%s",arr);
            if (!valid) 
                    {
                    printf("*********************************************************\n");
                    printf("%-5s %-15s %-15s %-25s\n", "Index", "Name", "Phone", "Email");
                    printf("*********************************************************\n");
                    }
            for(int i=0;i< addressBook->contactCount;i++)
            {   
                if(strcmp(addressBook->contacts[i].phone,arr)==0)
                {
                    
                searchout(addressBook,i);
                valid++;
                }
            }   
            if(!valid)
                printf("Contact not Found!!!\n");

        break;

        case 3: // Email
            printf("Enter the Email id:\n");
            scanf("%s",arr);
            if (!valid) 
                    {
                    printf("*********************************************************\n");
                    printf("%-5s %-15s %-15s %-25s\n", "Index", "Name", "Phone", "Email");
                    printf("*********************************************************\n");
                    }
            for(int i=0;i< addressBook->contactCount;i++)
            {   
                if(strcmp(addressBook->contacts[i].email,arr)==0)
                {
                    
                searchout(addressBook,i);
                valid++;
                }
            }   
            if(!valid)
                printf("Contact not Found!!!\n");

        break;

        case 4: // Exit
        
        break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (!choice_flag);

}

void searchout(AddressBook *addressBook,int i)
{   
                printf("%-5d %-15s %-15s %-25s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email); 
                printf("*********************************************************\n");
                return; 
}

void editContact(AddressBook *addressBook)
{   int choice;
    int index;
    searchContact(addressBook);
    //do
    {
        printf("\nEdit Contact By:\n");
        printf("1. Name\n");
        printf("2. Contact Number\n");
        printf("3. Email id\n");
        printf("4. Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);
        //__fpurge(stdin);
        if (choice >= 1 && choice <= 3)
        {
            printf("Enter the index number: ");
            scanf("%d", &index);

            // index validation
            if (index < 0 || index >= addressBook->contactCount)
            {
                printf("Invalid index! Please try again.\n");
                //continue;
            }
        }
        

        switch (choice)
        {
        case 1:
    // Taking name as input and validate it
        validate_name(addressBook->contacts[index].name);
        printf("Name edited Successfully !!!\n");
        break;
        case 2:
    // Taking Contact number as input and validate it
        validate_phone(addressBook,addressBook->contacts[index].phone);
        printf("Phone no. edited Successfully !!!\n");
        break;
        case 3:
    // Taking E-mail as input and validate it
        validate_email(addressBook,addressBook->contacts[index].email);
        printf("Email edited Successfully !!!\n");
        break;

        case 4: // Exit
        
        break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }// while (choice != 4);

}

void deleteContact(AddressBook *addressBook)
{   int index;
    searchContact(addressBook);
    printf("Enter the index no.");
    scanf("%d",&index);
    if (index < 0 || index >= addressBook->contactCount)
    {
        printf("Invalid index!\n");
        return;
    }

    // Shift contacts left to overwrite the deleted one
    for(int i=index;i<addressBook->contactCount -1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }

    addressBook->contactCount-- ;  // reduce total count
    printf("********** Contact deleted successfully! ************\n");
}
