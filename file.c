#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;
    fptr=fopen("contact.csv","w");
    if(fptr==NULL)
    {
        perror("Error Opening File");
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.csv", "r");
        if (fptr == NULL)
        {
        return; // no file yet
        }

        char line[256];
        while (fgets(line, sizeof(line), fptr)) {
        Contact *c = &addressBook->contacts[addressBook->contactCount];
        sscanf(line, "%49[^,],%19[^,],%s", c->name, c->phone, c->email);
        addressBook->contactCount++;
    }

    fclose(fptr);
}
