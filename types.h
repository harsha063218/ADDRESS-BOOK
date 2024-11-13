#ifndef TYPES_H
#define TYPES_H

typedef enum
{
    e_failure=0,
    e_success
} Status;

typedef enum
{
    e_add=1,
    e_search,
    e_edit,
    e_delete,
    e_list,
    e_exit
} Operation;

typedef enum
{
    e_name=1,
    e_mobile,
    e_email,
    e_serial
}choice;
#endif
