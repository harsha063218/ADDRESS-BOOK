#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#include "types.h"
struct address_book {
    char name[30];
    char mobile_no[11];
    char mail_id[30];
    int serial_no;
};
void add(struct address_book data[]);
void list(struct address_book data[]);
int search_contact(struct address_book data[], int *indices, int mode);
void edit(struct address_book data[]);
void delete_contact(struct address_book data[]);
void search(struct address_book data[]);
Status isname(char *name);
Status ismobile(char *mobile);
Status isemail(char *email);

int find_contact_by_name(struct address_book data[], char *name, int *indices);
int find_contact_by_mobile(struct address_book data[], char *mobile_no, int *indices);
int find_contact_by_email(struct address_book data[], char *mail_id, int *indices);
int byserial(struct address_book data[], int serial);