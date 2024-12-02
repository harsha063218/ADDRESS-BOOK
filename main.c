/*
NAME         :  K HARSHAVARDHAN
ID           :  24016_169
PROJECT NAME :  ADDRESS BOOK
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "types.h"

int count;

int main() {
    struct address_book data[200];
    int choice;
    FILE *fptr;
    char str[100];
   fptr = fopen("data.csv", "r");
if (fptr == NULL) {
    fptr = fopen("data.csv", "w");
    if (fptr == NULL) {
        perror("Error creating file");
        return 1;
    }
    fprintf(fptr, "#0\n"); 
    fclose(fptr);

    printf("No existing contacts. A new file 'data.csv' has been created.\n");
    count = 0;
} else {
    if (fgets(str, sizeof(str), fptr) == NULL) {
        fprintf(stderr, "Error: Unable to read count from file.\n");
        fclose(fptr);
        return 1;
    }
    count = atoi(str + 1);
    if (count < 0 || count > 200) {
        fprintf(stderr, "Error: Invalid count value (%d) in file.\n", count);
        fclose(fptr);
        return 1;
    }
    for (int i = 0; i < count; i++) {
        if (fgets(str, sizeof(str), fptr) == NULL) {
            fprintf(stderr, "Error: Unable to read contact %d from file.\n", i + 1);
            fclose(fptr);
            return 1;
        }

        char *token = strtok(str, ",");
        if (token == NULL) { fprintf(stderr, "Error: Missing serial number.\n"); break; }
        data[i].serial_no = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) { fprintf(stderr, "Error: Missing name.\n"); break; }
        strcpy(data[i].name, token);

        token = strtok(NULL, ",");
        if (token == NULL) { fprintf(stderr, "Error: Missing mobile number.\n"); break; }
        strcpy(data[i].mobile_no, token);

        token = strtok(NULL, ",");
        if (token == NULL) { fprintf(stderr, "Error: Missing email ID.\n"); break; }
        strcpy(data[i].mail_id, token);
    }
    fclose(fptr);
}
    do {
        printf("==================================================================================\n");
        printf("Address Book Menu:\n");
        printf("==================================================================================\n");
        printf("1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List Contacts\n");
        printf("6. Exit\n");
        printf("==================================================================================\n");
        printf("Choose an option [1-6]: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 6) {
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case e_add:
                add(data);
                break;
            case e_search:
                search(data);
                break;
            case e_edit:
                edit(data);
                break;
            case e_delete:
                delete_contact(data);
                break;
            case e_list:
                list(data);
                break;
            case e_exit:
                printf("Exiting Address Book.\n");
                fptr = fopen("data.csv", "w");
                if (fptr == NULL) {
                    printf("Unable to open file for saving.\n");
                    exit(0);
                }
                fprintf(fptr, "#%d\n", count);
                for (int i = 0; i < count; i++) {
                    fprintf(fptr, "%d,%s,%s,%s,\n", data[i].serial_no, data[i].name, data[i].mobile_no, data[i].mail_id);
                }
                fclose(fptr);
                break;
            default:
                printf("Invalid choice. Please choose between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
void add(struct address_book data[]) {
    char name[30], mobile_no[11], mail_id[30];
    int indices[200];
    while (1) {
        printf("Enter the contact name: ");
        scanf(" %[^\n]", name);
        if (isname(name)) {
            break;
        } else {
            printf("Invalid name. Names should only contain alphabets and spaces.\n");
        }
    }
    while (1) {
        printf("Enter the mobile number: ");
        scanf("%s", mobile_no);
        if (ismobile(mobile_no)) {
            if (find_contact_by_mobile(data, mobile_no, indices) > 0) {
                printf("Mobile number already exists. Please provide a unique number.\n");
            } else {
                break;
            }
        } else {
            printf("Invalid mobile number. Mobile number should be 10 digits only.\n");
        }
    }
    while (1) {
        printf("Enter the email ID: ");
        scanf("%s", mail_id);
        if (isemail(mail_id)) {
            if (find_contact_by_email(data, mail_id, indices) > 0) {
                printf("Email ID already exists. Please provide a unique email ID.\n");
            } else {
                break;
            }
        } else {
            printf("Invalid email format.\n");
        }
    }
    strcpy(data[count].name, name);
    strcpy(data[count].mobile_no, mobile_no);
    strcpy(data[count].mail_id, mail_id);
    data[count].serial_no = count + 1;
    count++;
    printf("Contact added successfully.\n");
}

int search_contact(struct address_book data[], int *indices, int mode) {
    char input[30];
    int num_found = 0;

    switch (mode) {
        case e_name:
            while (1) {
        printf("Enter the contact name: ");
        scanf(" %[^\n]",input);
        if (isname(input)) {
            break;
        } else {
            printf("Invalid name. Names should only contain alphabets and spaces.\n");
        }
    }
            for (int i = 0; i < count; i++) {
                if (strstr(data[i].name, input) != NULL) {
                    indices[num_found++] = i;
                }
            }
            break;
        case e_mobile:
            printf("Enter the mobile number: ");
            scanf("%s", input);
            for (int i = 0; i < count; i++) {
                if (strstr(data[i].mobile_no, input) != NULL) {
                    indices[num_found++] = i;
                }
            }
            break;
        case e_email:
            printf("Enter the email ID: ");
            scanf("%s", input);
            for (int i = 0; i < count; i++) {
                if (strstr(data[i].mail_id, input) != NULL) {
                    indices[num_found++] = i;
                }
            }
            break;
        case e_serial:
            {
                int serial;
                printf("Enter the serial number: ");
                scanf("%d", &serial);
                int index = byserial(data, serial);
                if (index != -1) {
                    indices[0] = index;
                    num_found = 1;
                }
            }
            break;
        default:
            printf("Invalid search mode.\n");
            return -1;
    }

    return num_found;
}
void search(struct address_book data[]) {
    int choice, indices[200];

    if (count == 0) {
        printf("No contacts available to search.\n");
        return;
    }
        printf("\nSearch by:\n");
        printf("1. Name\n");
        printf("2. Mobile Number\n");
        printf("3. Email ID\n");
        printf("4. Serial Number\n");
    do {
        printf("Choose an option [1-4]: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 4) {
            printf("Invalid input. Please enter a value between 1 and 4.\n");
        }
        while(getchar()!='\n');
    } while (choice < 1 || choice > 4); 

    int num_found = search_contact(data, indices, choice);
    if (num_found <= 0) {
        printf("No contacts found.\n");
        return;
    }

    if (num_found == 1) {
        printf("Contact found:\n");
        printf("Serial No | Name               | Mobile No       | Email ID\n");
        printf("------------------------------------------------------------\n");
        printf("%-10d | %-18s | %-15s | %s\n", data[indices[0]].serial_no, data[indices[0]].name, data[indices[0]].mobile_no, data[indices[0]].mail_id);
    } else {
        printf("Multiple contacts found:\n");
        printf("Serial No | Name               | Mobile No       | Email ID\n");
        printf("------------------------------------------------------------\n");
        for (int i = 0; i < num_found; i++) {
            printf("%-10d | %-18s | %-15s | %s\n", data[indices[i]].serial_no, data[indices[i]].name, data[indices[i]].mobile_no, data[indices[i]].mail_id);
        }
        printf("Enter the serial number of the contact you want to view: ");
        int serial_no;
        scanf("%d", &serial_no);

        int selected_index = byserial(data, serial_no);
        if (selected_index == -1) {
            printf("Invalid serial number selected.\n");
            return;
        }
        printf("Selected contact:\n");
        printf("Serial No: %d\n", data[selected_index].serial_no);
        printf("Name     : %s\n", data[selected_index].name);
        printf("Mobile No: %s\n", data[selected_index].mobile_no);
        printf("Email ID : %s\n", data[selected_index].mail_id);
    }
}

void edit(struct address_book data[]) {
    int choice, indices[200];

    if (count == 0) {
        printf("No contacts available to edit.\n");
        return;
    }

    printf("\nEdit by:\n");
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Email ID\n");
    printf("4. Serial Number\n");
    do {
        printf("Choose an option [1-4]: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 4) {
            printf("Invalid input. Please enter a value between 1 and 4.\n");
        }
        while(getchar()!='\n');
    } while (choice < 1 || choice > 4); 

    int num_found = search_contact(data, indices, choice);
    if (num_found <= 0) {
        printf("No contacts found.\n");
        return;
    }

    if (num_found == 1) {
        printf("One contact found: %s\n", data[indices[0]].name);
        choice = indices[0]; 
    } else {
        printf("Multiple contacts found:\n");
        printf("Serial No | Name               | Mobile No       | Email ID\n");
        printf("------------------------------------------------------------\n");
        for (int i = 0; i < num_found; i++) {
            printf("%d. %s (Mobile: %s, Email: %s)\n", i + 1, data[indices[i]].name, data[indices[i]].mobile_no, data[indices[i]].mail_id);
        }
        printf("Enter the serial number of the contact you want to edit: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > num_found) {
            printf("Invalid selection.\n");
            return;
        }

        choice = indices[choice - 1];
    }

    printf("Choose the field to edit:\n");
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Email ID\n");
    printf("Choose an option [1-3]: ");
    int ch;
    scanf("%d", &ch);

    switch (ch) {
        case e_name:
            while (1) {
                printf("Enter the new name: ");
                scanf(" %[^\n]", data[choice].name);
                if (isname(data[choice].name)) {
                    break;
                } else {
                    printf("Invalid name. Names should only contain alphabets.\n");
                }
            }
            break;
        case e_mobile:
            while (1) {
                printf("Enter the new mobile number: ");
                scanf("%s", data[choice].mobile_no);
                if (ismobile(data[choice].mobile_no)) {
                    if (find_contact_by_mobile(data, data[choice].mobile_no, indices) > 0 && indices[0] != choice) {
                        printf("Mobile number already exists. Please provide a unique number.\n");
                    } else {
                        break;
                    }
                } else {
                    printf("Invalid mobile number. Mobile number should be 10 digits only.\n");
                }
            }
            break;
        case e_email: 
            while (1) {
                printf("Enter the new email ID: ");
                scanf("%s", data[choice].mail_id);
                if (isemail(data[choice].mail_id)) {
                    if (find_contact_by_email(data, data[choice].mail_id, indices) > 0 && indices[0] != choice) {
                        printf("Email ID already exists. Please provide a unique email ID.\n");
                    } else {
                        break;
                    }
                } else {
                    printf("Invalid email format.\n");
                }
            }
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    printf("Contact updated successfully.\n");
}
void delete_contact(struct address_book data[]) {
    int choice, indices[200];

    if (count == 0) {
        printf("No contacts available to delete.\n");
        return;
    }

    printf("\nDelete by:\n");
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Email ID\n");
    printf("4. Serial Number\n");
    do {
        printf("Choose an option [1-4]: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 4) {
            printf("Invalid input. Please enter a value between 1 and 4.\n");
        }
        while(getchar()!='\n');
    } while (choice < 1 || choice > 4); 

    int num_found = search_contact(data, indices, choice);
    if (num_found <= 0) {
        printf("No contacts found.\n");
        return;
    }

    if (num_found == 1) {
        printf("One contact found: %s\n", data[indices[0]].name);
        choice = indices[0];
    } else {
        printf("Multiple contacts found:\n");
        for (int i = 0; i < num_found; i++) {
            printf("%d. %s (Mobile: %s, Email: %s)\n", i + 1, data[indices[i]].name, data[indices[i]].mobile_no, data[indices[i]].mail_id);
        }
        printf("Enter the serial number of the contact you want to delete: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > num_found) {
            printf("Invalid selection.\n");
            return;
        }

        choice = indices[choice - 1];
    }
    printf("Are you sure you want to delete this contact? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("Deletion canceled.\n");
        return;
    }
    for (int i = choice; i < count - 1; i++) {
        data[i] = data[i + 1];
        data[i].serial_no = i + 1;
    }

    count--;
    printf("Contact deleted successfully.\n");
}


void list(struct address_book data[]) {
    if (count == 0) {
        printf("No contacts available.\n");
        return;
    }
    printf("==================================================================================\n");
    printf("\nList of Contacts:\n");
    printf("==================================================================================\n");
    for (int i = 0; i < count; i++) {
        printf("Serial No: %d\n", data[i].serial_no);
        printf("Name     : %s\n", data[i].name);
        printf("Mobile No: %s\n", data[i].mobile_no);
        printf("Email ID : %s\n\n", data[i].mail_id);
    }
}
