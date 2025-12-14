#ifndef LOGIN_H
#define LOGIN_H

typedef struct {
    char username[50];
    char role[10];
} Session;

int login_menu(Session *session);

#endif
