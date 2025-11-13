#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void) {
    #define BUFFER_SIZE 1000
    char command[10];
    char filename[100];
    char user_input[50];
    char full_path[256];
    char extension[10];
    char dp[100];
    char* test_file = "testfile";
    char test_file_full[256];
    int ifdpnull = 0;
    int cyc;
    int cycen;
    int simflag = 0;
    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE];


    system("clear");

    printf("TEXRED ver 1.6, Programmed by Kruchinin Ilia\n");
    new:
    printf("Enter a file name: ");
    scanf("%s", user_input);
    printf("Enter a file extension: .");
    scanf("%s", extension);


    sprintf(filename, "%s.%s", user_input, extension);
    com:
    //Commands
    printf("Command? ");
    scanf("%s", command);
    if (strstr(command, "@new") != NULL){
        goto new;
    }
    if (strstr(command, "@wri") != NULL){
        goto write;
    }
    if (strstr(command, "@ls") != NULL){
        goto read;
    }
    if (strstr(command, "@exit") != NULL){
        return 0;
    }
    if (strstr(command, "@dir") != NULL) {
        goto dir;
    }
    if (strstr(command, "@cd") != NULL) {
        goto change_dir;
    }
    if (strstr(command, "@help") != NULL) {
        goto help;
    }
    if (strstr(command, "@del") != NULL) {
        goto delete;
    }
    if (strstr(command, "@edit") != NULL) {
        goto edit;
    }
    if (strstr(command, "@cls") != NULL) {
        system("clear");
        printf("CURRENT FILE IS: %s    \t", filename);
        DIR *show;
        if (ifdpnull == 1) {
            show = opendir(dp);
            printf("CURRENT DIRECTORY IS: %s\n", dp);
        }
        else{
            const char *directory_path = ".";
            show = opendir(directory_path);
            printf("CURRENT DIRECTORY IS: %s\n", directory_path);
        }
    }
    else
        printf("Bad command (use '@help' to get commands)\n");
    goto com;
    help:
    printf("Commands:\n@new - create a new file\n@wri - edit file (Write mode)\n@sav - save file (Only in write mode)\n@edit - edit a line\n@ls - list file\n@exit - close the program\n@dir - list the current directory\n@cd - change current directory\n@del - delete current file\n@cls - clear screen\n@help - show this menu\n");
    goto com;
    dir:
    DIR *d;
    struct dirent *dir;
    if (ifdpnull == 1) {
        d = opendir(dp);
        printf("Current directory is: %s", dp);
    }
    else{
        ifdpnull = 0;
        const char *directory_path = ".";
        d = opendir(directory_path);
        printf("Current directory is: %s", directory_path);
    }
    if (d == NULL) {
        const char *directory_path = ".";
        d = opendir(directory_path);
        printf("Current directory is: %s", directory_path);
    }
    while ((dir = readdir(d)) != NULL) {
        printf("%s\n", dir->d_name);
    }
    goto com;
    change_dir:
    DIR *cd;
    printf("Enter new directory path: ");
    scanf("%s", dp);
    d = opendir(dp);
    if (d == NULL) {
        perror("Error opening directory! Error:");
        ifdpnull = 0;
        goto com; }
        d = opendir(dp);
        ifdpnull = 1;
        goto com;


        delete:
        FILE *del;
        if(ifdpnull == 1) {
            sprintf(full_path, "%s/%s", dp, filename);
            del = fopen(full_path, "r");
        }
        else {
            del = fopen(filename, "r");

        }
        if(del == NULL) {
            perror("File doesn't exist! Error");
            goto com;
        }
        fclose(del);
        switch (ifdpnull) {

            case 0:
                if (remove(filename) == 0) {
                    printf("File '");
                    printf("%s' deleted\n", filename);
                    goto com;
                }
                else {
                    perror("Error deleting file! Error");
                    goto com;
                }
            case 1:
                if (remove(full_path) == 0) {
                    printf("File '");
                    printf("%s' deleted\n", filename);
                    goto com;
                }
                else {
                    perror("Error deleting file! Error");
                    goto com;

                }
        }

        read:
        //Read mode
        FILE *file_ptrr;
        if(ifdpnull == 1) {
            sprintf(full_path, "%s/%s", dp, filename);
            file_ptrr = fopen(full_path, "r+");
        }
        else {
            file_ptrr = fopen(filename, "r+");

        }

        if (file_ptrr == NULL) {
            perror("Error opening file! Error");
            goto com;
        }
        char ch;
        int linecount = 1;
        printf("1.");
        while ((ch = fgetc(file_ptrr)) != EOF){
            putchar(ch);
            if (ch == '\n') {
                ++linecount;
                printf("%d.", linecount);
            }
        }
        printf("\n");
        if (cyc >> 1) {
            printf("\x1b[2K");
            printf("\x1b[1F");
        }
        fclose(file_ptrr);
        goto com;
        write:
        //Writing
        if (d == NULL){
            perror("Please enter correct directory! Error");
            goto com;
        }
        FILE *file_ptrt;
        if (ifdpnull == 1) {
            sprintf(test_file_full, "%s/%s", dp, test_file);
            file_ptrt = fopen(test_file_full, "w");
            if (file_ptrt == NULL) {
                perror("Error creating file! Error");
                goto com;
            }
            fclose(file_ptrt);
            remove(test_file_full);
        }
        FILE *file_ptr;
        FILE *file_ptrw;
        file_ptr = fopen("temp.txt", "w");
        if (file_ptr == NULL) {
            perror("Error creating file! Error");
            goto com;
        }
        printf("Do you want continue editing? (Y/N) ");
        char yn[100];

        yn:
        scanf("%s", yn);
        if (strstr(yn, "Y") != NULL) {
            goto cont;
        }
        if (strstr(yn, "N") != NULL) {
            simflag = 0;
            goto no;
        }
        else {
            printf("Choose Y/N: ");
            goto yn;
        }

        cont:
        cyc = 0;
        ++linecount;
        if(ifdpnull == 1) {
            sprintf(full_path, "%s/%s", dp, filename);
            file_ptrw = fopen(full_path, "r");
        }
        else {
            file_ptrw = fopen(filename, "r");
        }
        if (file_ptrw == NULL) {
            file_ptr = fopen("temp.txt", "w");
        }
        else {
            simflag = 1;
            char ct;
            printf(">>");
            while ((ct = fgetc(file_ptrw)) != EOF) {
                putchar(ct);
                fputc(ct, file_ptr);

                if (ct == '\n') {
                    printf(">>");
                }

            }
        }


        no:


        if (file_ptr == NULL) {
            perror("Error opening file! Error");
            goto com;
        }

        printf(">>");
        char dc;
        scanf("%c", &dc);

        // Strings
        for (cyc = 0; cycen != EOF; ++cyc ){
            char str1[100];
            fgets(str1, sizeof(str1), stdin);
            if (strstr(str1, "@sav") != NULL){
                goto save;
            }
            fprintf(file_ptr, "%s", str1);

            printf(">>");
        }


        edit:
        FILE *edit;
        FILE *temp;

        int line, count;
        printf("Enter line number to replace: ");
        scanf("%d", &line);

        printf(">>");
        scanf("%c", &dc);

        fgets(newline, BUFFER_SIZE, stdin);


        if(ifdpnull == 1) {
            sprintf(full_path, "%s/%s", dp, filename);
            edit = fopen(full_path, "r+");
        } else {
            edit = fopen(filename, "r+");

        }
        if (edit == NULL) {
            perror("Error opening file! Error");
            goto com;
        }
        temp = fopen("temp_edi.txt", "w");




        count = 0;
        while ((fgets(buffer, BUFFER_SIZE, edit)) != NULL) {
            count++;

            /* If current line is line to replace */
            if (count == line)
                fputs(newline, temp);
            else
                fputs(buffer, temp);
        }
        fclose(edit);
        fclose(temp);

        if(ifdpnull == 1) {
            remove(full_path);
            sprintf(full_path, "%s/%s", dp, filename);
            rename("temp_edi.txt", full_path);
        } else {
            remove(filename);
            rename("temp_edi.txt", filename);
        }

        goto com;



        save:
        fclose(file_ptr);
        if (simflag == 1) {
            fclose(file_ptrw);
        }

        simflag = 0;
        if(ifdpnull == 1) {
            remove(full_path);
            sprintf(full_path, "%s/%s", dp, filename);
            rename("temp.txt", full_path);
        } else {
            remove(filename);
            rename("temp.txt", filename);
        }

        printf("File writen\n");

        goto com;

}
