//
// Created by Michael McGregor on 10/25/19.
//


#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main() {
    int tests_passed = 0;
    int total_tests = 29;
    char *test_names[] = {"my_strlen(short)",
                         "my_strlen(long)",
                         "my_strlen(zero)",
                         "my_strcat()",
                         "my_strncat(n < strlen(src))",
                         "my_strncat(n > strlen(src))",
                         "my_strchr(pos)",
                         "my_strchr(neg)",
                         "my_strchr(zero)",
                         "my_strrchr(pos)",
                         "my_strrchr(neg)",
                         "my_strrchr(zero)",
                         "my_strcmp(<)",
                         "my_strcmp(=)",
                         "my_strcmp(>)",
                         "my_strncmp(<,pos)",
                         "my_strncmp(=,pos)",
                         "my_strncmp(>,pos)",
                         "my_strncmp(<,neg)",
                         "my_strncmp(>,neg)",
                         "my_strcpy()",
                         "my_strncpy(n < strlen(src))",
                         "my_strncpy(n > strlen(src))",
                         "my_strdup()",
                         "my_strndup(n < strlen(src))",
                         "my_strndup(n > strlen(src))",
                         "my_strstr(pos)",
                         "my_strstr(neg)",
                         "my_strstr(superset)"};

    // Test i - my_strlen(short)
    {
        unsigned int test_id = 1;
        unsigned int failed = 0;
        char *s = "ABCDabcd1234  \137*&@<>.";
        int expval = 21;
        int retval = my_strlen(s);
        if (retval != expval)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\tResult from my_strlen() does not match expected result. (%d != %d)\n", retval, expval);
            printf("\n");
        }
    }

    // Test ii - my_strlen(long)
    {
        unsigned int test_id = 2;
        unsigned int failed = 0;
        int expval = 999998;
        char *s = malloc(expval + 1);
        for (int i = 0; i <= expval; i++)
            s[i] = 'A';
        s[expval] = '\0';
        int retval = my_strlen(s);
        if (retval != expval)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\tResult from my_strlen() does not match expected result. (%d != %d)\n", retval, expval);
            printf("\n");
        }
        free(s);
    }

    // Test iii - my_strlen(zero)
    {
        unsigned int test_id = 3;
        unsigned int failed = 0;
        char s[1];
        s[0] = 0;
        int expval = 0;
        int retval = my_strlen(s);
        if (retval != expval)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\tResult from my_strlen() does not match expected result. (%d != %d)\n", retval, expval);
            printf("\n");
        }
    }

    // Test iv - my_strcat()
    {
        unsigned int test_id = 4;
        unsigned int failed = 0;
        char *dest = malloc(20);
        char *src = malloc(20);
        int length = 0;
        int expected_length = 16;
        for (int i = 0; i < 8; i++) {
            dest[i] = 'A';
            src[i] = 'B';
        }
        dest[8] = 0;
        src[8] = 0;

        char *retval = my_strcat(dest, src);
        if (dest != NULL) {
            length = my_strlen(dest);
            for (int i = 0; i < 8; i++)
                if (dest[i] != 'A')
                    failed |= 0x1u;
            for (int i = 0; i < 8; i++)
                if (dest[i + 8] != 'B')
                    failed |= 0x2u;
            if (length != expected_length)
                failed |= 0x4u;
            if (retval != dest)
                failed |= 0x8u;
        }
        else
            failed |= 0x10u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\tDestination string does not start with original contents of destination string buffer.\n");
            if (failed & 0x2u)
                printf("\tDestination string does not contain contents from source string after original contents.\n");
            if (failed & 0x4u)
                printf("\tDestination string length does not equal original destination string length plus source string length. (%d != %d)\n", length, expected_length);
            if (failed & 0x8u)
                printf("\tPointer returned from my_strcat does not equal address for destination string.\n");
            if (failed & 0x10u)
                printf("\tdest is NULL after calling my_strcat(), skipping remaining components of test.\n");
            printf("\n");
        }
        free(dest);
        free(src);
    }

    // Test v - my_strncat(n < my_strlen(src))
    {
        unsigned int test_id = 5;
        unsigned int failed = 0;
        char *dest = malloc(20);
        char *src = malloc(20);
        int n = 5;
        int length = 0;
        int expected_length = 13;
        for (int i = 0; i < 8; i++) {
            dest[i] = 'A';
            src[i] = 'B';
        }
        dest[8] = 0;
        src[8] = 0;

        char *retval = my_strncat(dest, src, n);
        if (dest != NULL) {
            length = my_strlen(dest);
            for (int i = 0; i < 8; i++)
                if (dest[i] != 'A')
                    failed |= 0x1u;
            for (int i = 0; i < 5; i++)
                if (dest[i + 8] != 'B')
                    failed |= 0x2u;
            if (length != expected_length)
                failed |= 0x4u;
            if (retval != dest)
                failed |= 0x8u;
        }
        else
            failed |= 0x10u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\tDestination string does not start with original contents of destination string buffer.\n");
            if (failed & 0x2u)
                printf("\tDestination string does not contain contents from source string after original contents.\n");
            if (failed & 0x4u)
                printf("\tDestination string length does not equal original destination string length plus min(n, strlen(src)). (%d != %d)\n", length, expected_length);
            if (failed & 0x8u)
                printf("\tPointer returned from my_strncat does not equal address for destination string.\n");
            if (failed & 0x10u)
                printf("\tdest is NULL after calling my_strncat(), skipping remaining components of test.\n");
            printf("\n");
        }
        free(dest);
        free(src);
    }

    // Test vi - my_strncat(n > my_strlen(src))
    {
        unsigned int test_id = 6;
        unsigned int failed = 0;
        char *dest = malloc(20);
        char *src = malloc(20);
        int n = 12;
        int length = 0;
        int expected_length = 16;
        for (int i = 0; i < 8; i++) {
            dest[i] = 'A';
            src[i] = 'B';
        }
        dest[8] = 0;
        src[8] = 0;

        char *retval = my_strncat(dest, src, n);
        if (dest != NULL) {
            length = my_strlen(dest);
            for (int i = 0; i < 8; i++)
                if (dest[i] != 'A')
                    failed |= 0x1u;
            for (int i = 0; i < 8; i++)
                if (dest[i + 8] != 'B')
                    failed |= 0x2u;
            if (length != expected_length)
                failed |= 0x4u;
            if (retval != dest)
                failed |= 0x8u;
        }
        else
            failed |= 0x10u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\tDestination string does not start with original contents of destination string buffer.\n");
            if (failed & 0x2u)
                printf("\tDestination string does not contain contents from source string after original contents.\n");
            if (failed & 0x4u)
                printf("\tDestination string length does not equal original destination string length plus min(n, strlen(src)). (%d != %d)\n", length, expected_length);
            if (failed & 0x8u)
                printf("\tPointer returned from my_strncat does not equal address for destination string.\n");
            if (failed & 0x10u)
                printf("\tdest is NULL after calling my_strncat(), skipping remaining components of test.\n");
            printf("\n");
        }
        free(dest);
        free(src);
    }

    // Test vii - my_strchr(pos)
    {
        unsigned int test_id = 7;
        unsigned int failed = 0;
        char *s = "abcdabcdabcd";
        int c = 'c';
        int expected_offset = 2;
        char *retval = my_strchr(s, c);
        if (retval != s + expected_offset)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\tPointer returned is not to the source base address + %d bytes.\n", expected_offset);
        }
        printf("\n");
    }

    // Test viii - my_strchr(neg)
    {
        unsigned int test_id = 8;
        unsigned int failed = 0;
        char *s = "abcdabcdabcd";
        int c = 'C';
        char *retval = my_strchr(s, c);
        if (retval != NULL)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\tPointer returned is not NULL.\n");
            printf("\n");
        }
    }

    // Test ix - my_strchr(zero)
    {
        unsigned int test_id = 9;
        unsigned int failed = 0;
        char *s = "abcdabcdabcd";
        int c = '\0';
        int expected_offset = 12;
        char *retval = my_strchr(s, c);
        if (retval != s + expected_offset)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\tPointer returned is not to the source base address + %d bytes.\n", expected_offset);
            printf("\n");
        }
    }

    // Test x - my_strrchr(pos)
    {
        unsigned int test_id = 10;
        unsigned int failed = 0;
        char *s = "abcdabcdabcd";
        int c = 'c';
        int expected_offset = 10;
        char *retval = my_strrchr(s, c);
        if (retval != s + expected_offset)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Pointer returned is not to the source base address + %d bytes.\n", expected_offset);
            printf("\n");
        }
    }

    // Test xi - my_strrchr(neg)
    {
        unsigned int test_id = 11;
        unsigned int failed = 0;
        char *s = "abcdabcdabcd";
        int c = 'C';
        char *retval = my_strrchr(s, c);
        if (retval != NULL)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Pointer returned is not NULL.\n");
            printf("\n");
        }
    }

    // Test xii - my_strrchr(zero)
    {
        unsigned int test_id = 12;
        unsigned int failed = 0;
        char *s = "abcdabcdabcd";
        int c = '\0';
        int expected_output = 12;
        char *retval = my_strrchr(s, c);
        if (retval != s + expected_output)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Pointer returned is not to the source base address + %d bytes.\n", expected_output);
            printf("\n");
        }
    }

    // Test xiii - my_strcmp(<)
    {
        unsigned int test_id = 13;
        unsigned int failed = 0;
        char *s1 = "abcdabcdabcd";
        char *s2 = "abcdabcdabce";
        if (my_strcmp(s1, s2) >= 0)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Value returned was not less than zero.\n");
            printf("\n");
        }
    }

    // Test xiv - my_strcmp(=)
    {
        unsigned int test_id = 14;
        unsigned int failed = 0;
        char *s1 = "abcdabcdabcd";
        char *s2 = "abcdabcdabcd";
        if (my_strcmp(s1, s2) != 0)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Value returned was not equal to zero.\n");
            printf("\n");
        }
    }

    // Test xv - my_strcmp(>)
    {
        unsigned int test_id = 15;
        unsigned int failed = 0;
        char *s1 = "abcdabcdabcd";
        char *s2 = "abcdabcdabcc";
        if (my_strcmp(s1, s2) <= 0)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Value returned was not greater than zero.\n");
            printf("\n");
        }
    }

    // Test xvi - my_strncmp(<,pos)
    {
        unsigned int test_id = 16;
        unsigned int failed = 0;
        char *s1 = "abcdabcdabcd";
        char *s2 = "abceabcdabcd";
        int n = 4;
        if (my_strncmp(s1, s2, n) >= 0)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Value returned was not less than zero.\n");
            printf("\n");
        }
    }

    // Test xvii - my_strncmp(=)
    {
        unsigned int test_id = 17;
        unsigned int failed = 0;
        char *s1 = "abcdabcdabcd";
        char *s2 = "abcdabcdabcd";
        int n = 4;
        if (my_strncmp(s1, s2, n) != 0)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Value returned was not equal to zero.\n");
            printf("\n");
        }
    }

    // Test xviii - my_strncmp(>, pos)
    {
        unsigned int test_id = 18;
        unsigned int failed = 0;
        char *s1 = "abcdabcdabcd";
        char *s2 = "abccabcdabcd";
        int n = 4;
        if (my_strncmp(s1, s2, n) <= 0)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Value returned was not greater than zero.\n");
            printf("\n");
        }
    }

    // Test xix - my_strncmp(<, neg)
    {
        unsigned int test_id = 19;
        unsigned int failed = 0;
        char *s1 = "abcdabcdabcd";
        char *s2 = "abcdbbcdabcd";
        int n = 4;
        if (my_strncmp(s1, s2, n) != 0)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Value returned was not equal to zero.\n");
            printf("\n");
        }
    }

    // Test xx - my_strncmp(>, neg)
    {
        unsigned int test_id = 20;
        unsigned int failed = 0;
        char *s1 = "abcdbbcdabcd";
        char *s2 = "abcdabcdabcd";
        int n = 4;
        if (my_strncmp(s1, s2, n) != 0)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Value returned was not equal to zero.\n");
            printf("\n");
        }
    }

    // Test xxi - my_strcpy()
    {
        unsigned int test_id = 21;
        unsigned int failed = 0;
        char *dest = malloc(20);
        char *src = malloc(20);
        int expected_length = 15;
        int length = 0;
        for (int i = 0; i < expected_length; i++)
            src[i] = 'A';
        src[expected_length] = 0;

        char *retval = my_strcpy(dest, src);
        if (dest != NULL) {
            length = my_strlen(dest);
            for (int i = 0; i < 15; i++)
                if (dest[i] != 'A')
                    failed |= 0x1u;
            if (length != expected_length)
                failed |= 0x2u;
            if (retval != dest)
                failed |= 0x4u;
        }
        else
            failed |= 0x8u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Destination string does not contain source string.\n");
            if (failed & 0x2u)
                printf("\t Destination string is not the same expected_length as source string.\n");
            if (failed & 0x4u)
                printf("\t Pointer returned not equal to address passed in as destination string.\n");
            if (failed & 0x8u)
                printf("\t dest is NULL after calling my_strcpy(), skipping remaining components of test.\n");
            printf("\n");
        }

        free(dest);
        free(src);
    }

    // Test xxii - my_strncpy(n < my_strlen(src))
    {
        unsigned int test_id = 22;
        unsigned int failed = 0;
        char *dest = malloc(20);
        char *src = malloc(20);
        int n = 10;
        int expected_length = 15;
        int length = 0;
        for (int i = 0; i < expected_length; i++) {
            src[i] = 'A';
            dest[i] = 'B';
        }
        src[expected_length] = 0;
        dest[expected_length] = 0;

        char *retval = my_strncpy(dest, src, n);
        if (dest != NULL) {
            length = my_strlen(dest);
            for (int i = 0; i < 10; i++)
                if (dest[i] != 'A')
                    failed |= 0x1u;
            if (dest[10] != 'B')
                failed |= 0x2u;
            if (retval != dest)
                failed |= 0x4u;
            if (length != expected_length)
                failed |= 0x8u;
        }
        else
            failed |= 0x10u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Destination string does not contain first n bytes from source string.\n");
            if (failed & 0x2u)
                printf("\t More than n bytes overwritten in dest string.\n");
            if (failed & 0x4u)
                printf("\t Pointer returned not equal to address passed in as destination string.\n");
            if (failed & 0x8u)
                printf("\t Destination string expected_length (originally greater than n) was modified.\n");
            if (failed & 0x10u)
                printf("\t dest is NULL after calling my_strncpy(), skipping remaining components of test.\n");
            printf("\n");
        }

        free(dest);
        free(src);
    }

    // Test xxiii - my_strncpy(n > my_strlen(src))
    {
        unsigned int test_id = 23;
        unsigned int failed = 0;
        char *dest = malloc(20);
        char *src = malloc(20);
        int n = 20;
        int expected_length = 15;
        int length = 0;
        for (int i = 0; i < expected_length; i++)
            src[i] = 'A';
        for (int i = 0; i < n; i++)
            dest[i] = 'B';
        src[expected_length] = 0;

        char *retval = my_strncpy(dest, src, n);
        if (dest != NULL) {
            length = my_strlen(dest);
            for (int i = 0; i < expected_length; i++)
                if (dest[i] != 'A')
                    failed |= 0x1u;
            if (length != expected_length)
                failed |= 0x2u;
            if (retval != dest)
                failed |= 0x4u;
            for (int i = expected_length; i < n; i++)
                if (dest[i] != 0)
                    failed |= 0x8u;
        }
        else
            failed |= 0x10u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Destination string does not contain source string.\n");
            if (failed & 0x2u)
                printf("\t More than n bytes overwritten in dest string.\n");
            if (failed & 0x4u)
                printf("\t Pointer returned not equal to address passed in as destination string.\n");
            if (failed & 0x8u)
                printf("\t Additional null bytes were not written to dest to ensure a total of n bytes were written.\n");
            if (failed & 0x10u)
                printf("\t dest is NULL after calling my_strncpy(), skipping remaining components of test.\n");
            printf("\n");
        }

        free(dest);
        free(src);
    }

    // Test xxiv - my_strdup()
    {
        unsigned int test_id = 24;
        unsigned int failed = 0;
        char *s = "ABCDabcdDEFGdefg";
        int length = 16;
        int actual_length = 0;
        int comp = -1;
        char *retval = my_strdup(s);
        if (retval != NULL) {
            actual_length = my_strlen(retval);
            comp = my_strcmp(retval, s);
            if (actual_length != length)
                failed |= 0x1u;
            if (retval == s)
                failed |= 0x2u;
            if (comp != 0)
                failed |= 0x4u;
        }
        else
            failed |= 0x8u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t New string length does not equal source string length. (%d != %d)\n", actual_length, length);
            if (failed & 0x2u)
                printf("\t Pointer returned is equal to pointer passed in. Should be newly allocated memory.\n");
            if (failed & 0x4u)
                printf("\t New string is not same as source string, my_strcmp() != 0.\n");
            if (failed & 0x8u)
                printf("\t Value returned from my_strdup() is NULL, skipping remaining components of test.\n");
            printf("\n");
        }

        if (retval != NULL)
            free(retval);
    }

    // Test xxv - my_strndup(n < my_strlen(src))
    {
        unsigned int test_id = 25;
        unsigned int failed = 0;
        char *s = "ABCDabcdDEFGdefg";
        int n = 10;
        int actual_length = 0;
        int comp = -1;
        char *retval = my_strndup(s, n);
        if (retval != NULL) {
            actual_length = my_strlen(retval);
            comp = my_strncmp(retval, s, n);
            if (actual_length != n)
                failed |= 0x1u;
            if (retval == s)
                failed |= 0x2u;
            if (comp != 0)
                failed |= 0x4u;
        }
        else
            failed |= 0x8u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t New string length does not equal min(n, strlen(src)). (%d != %d)\n", actual_length, n);
            if (failed & 0x2u)
                printf("\t Pointer returned is equal to pointer passed in. Should be newly allocated memory.\n");
            if (failed & 0x4u)
                printf("\t New string is not same as source string, my_strcmp() != 0.\n");
            if (failed & 0x8u)
                printf("\t Value returned from my_strndup() is NULL, skipping remaining components of test.\n");
            printf("\n");
        }

        if (retval != NULL)
            free(retval);
    }

    // Test xxvi - my_strndup(n > my_strlen(src))
    {
        unsigned int test_id = 26;
        unsigned int failed = 0;
        char *s = "ABCDabcdDEFGdefg";
        int n = 20;
        int length = 16;
        int actual_length = 0;
        int comp = -1;
        char *retval = my_strndup(s, n);
        if (retval != NULL) {
            actual_length = my_strlen(retval);
            comp = my_strcmp(retval, s);
            if (actual_length != length)
                failed |= 0x1u;
            if (retval == s)
                failed |= 0x2u;
            if (comp != 0)
                failed |= 0x4u;
        }
        else
            failed |= 0x8u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t New string length does not equal min(n, strlen(src)). (%d != %d)\n", actual_length, length);
            if (failed & 0x2u)
                printf("\t Pointer returned is equal to pointer passed in. Should be newly allocated memory.\n");
            if (failed & 0x4u)
                printf("\t New string is not same as source string, my_strcmp() != 0.\n");
            if (failed & 0x8u)
                printf("\t Value returned from my_strndup() is NULL, skipping remaining components of test.\n");
            printf("\n");
        }

        if (retval != NULL)
            free(retval);
    }

    // Test xxvii - my_strstr(pos)
    {
        unsigned int test_id = 27;
        unsigned int failed = 0;
        char *haystack = "abcdabcabcabd";
        char *needle = "abcabd";
        int initial_char = 'a';
        int offset = 7;
        int offset_length = 6;
        int length = 0;
        char *retval = my_strstr(haystack, needle);
        if (retval != NULL) {
            length = my_strlen(retval);
            if (retval != haystack + offset)
                failed |= 0x1u;
            if (length != offset_length)
                failed |= 0x2u;
            if (retval[0] != initial_char)
                failed |= 0x4u;
        }
        else
            failed |= 0x8u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Returned pointer is not equal to original string base address + offset to beginning of substring.\n");
            if (failed & 0x2u)
                printf("\t Length of null terminated string starting at returned address is not equal to expected length. (%d != %d).\n", length, offset_length);
            if (failed & 0x4u)
                printf("\t Beginning of returned string does not match expected value. (%c != %c).\n", retval[0], initial_char);
            if (failed & 0x8u)
                printf("\t Value returned from my_strstr() is NULL, skipping remaining components of test.\n");
            printf("\n");
        }
    }

    // Test xxviii - my_strstr(neg)
    {
        unsigned int test_id = 28;
        unsigned int failed = 0;
        char *haystack = "abcdEFGIhijkLMNO";
        char *needle = "dEFGIH";
        char *retval = my_strstr(haystack, needle);
        if (retval != NULL)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Function did not return NULL\n");
            printf("\n");
        }
    }

    // Test xxix - my_strstr(superset)
    {
        unsigned int test_id = 29;
        unsigned int failed = 0;
        char *haystack = "abcdEFGIhijkLMNO";
        char *needle = "dEFGIhijkLMNOp";
        char *retval = my_strstr(haystack, needle);
        if (retval != NULL)
            failed |= 0x1u;

        if (!failed)
            tests_passed++;
        else {
            printf("Test %d: %s failed. Error code %d-%d.\n", test_id, test_names[test_id - 1], test_id, failed);
            if (failed & 0x1u)
                printf("\t Function did not return NULL\n");
            printf("\n");
        }
    }

    // Wrap it up
    printf("%d of %d tests passed\n", tests_passed, total_tests);

    return 0;
}
