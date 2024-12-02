#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "file.h"

Status isname(char *name) {
    for (int i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return e_failure;
        }
    }
    return e_success;
}
Status ismobile(char *mobile_no) {
    if (strlen(mobile_no) != 10) {
        return e_failure;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(mobile_no[i])) {
            return e_failure;
        }
    }
    return e_success;
}
Status isemail(char *email) {
    int p1 =-1, p2 =-1;
    int at_count = 0;
    for (int i=0; i<strlen(email);i++) {
        if (email[i] == '@') {
            if (p1==-1) {
                p1=i;
            }
            at_count++;
        } else if (email[i] == '.') {
            if (i>p1) {
                p2=i;
            }
        } else if (!isalnum(email[i]) && email[i] != '-' && email[i] != '_') {
            return e_failure; 
        }
    }
    if (at_count!=1||p1 < 1||p2<p1+2||p2>=strlen(email)-1) {
        return e_failure;
    }
    if (strcmp(email + p2, ".com") != 0 && strcmp(email + p2, ".in") != 0) {
        return e_failure;
    }
    return e_success;
}
int byserial(struct address_book data[], int serial) {
    for (int i = 0; i < count; i++) {
        if (data[i].serial_no == serial)
            return i;
    }
    return -1;
}
int find_contact_by_name(struct address_book data[], char *name, int *indices) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(data[i].name, name) == 0) {
            indices[found++] = i;
        }
    }
    return found;
}
int find_contact_by_mobile(struct address_book data[], char *mobile_no, int *indices) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(data[i].mobile_no, mobile_no) == 0) {
            indices[found++] = i;
        }
    }
    return found;
}
int find_contact_by_email(struct address_book data[], char *mail_id, int *indices) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(data[i].mail_id, mail_id) == 0) {
            indices[found++] = i;
        }
    }
    return found;
}
