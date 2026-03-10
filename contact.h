#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<stdio_ext.h>

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct
{
    int contactCount;
    Contact contacts[100];
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);
void swap(AddressBook *addressBook,int i,int j);
void searchout(AddressBook *addressBook,int i);
void validate_name(char*);
void validate_phone(AddressBook *,char*);
void validate_email(AddressBook *,char*);

#endif
