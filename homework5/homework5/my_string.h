//
// Created by Michael McGregor on 10/25/19.
//

#ifndef HOMEWORK4_MY_STRING_H
#define HOMEWORK4_MY_STRING_H


char *my_strcat(char *dest, char *src);
char *my_strncat(char *dest, char *src, int n);
char *my_strchr(char *s, int c);
char *my_strrchr(char *s, int c);
int my_strcmp(char *s1, char *s2);
int my_strncmp(char *s1, char *s2, int n);
char *my_strcpy(char *dest, char *src);
char *my_strncpy(char *dest, char *src, int n);
char *my_strdup(char *s);
char *my_strndup(char *s, int n);
int my_strlen(char *s);
char *my_strstr(char *haystack, char *needle);

#endif //HOMEWORK4_MY_STRING_H
