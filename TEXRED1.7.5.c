#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>


int main(void) {

    DIR *d;
    #define BUFFER_SIZE 1000
    char command[10];
    char filename[100];
    char user_input[50];
    char full_path[256];
    char extension[10];
    char dp[100];
    char new_dir[50];
    char temptxt[10];
    char temptxt_edi[10];
    char testfile[10];
    char tempdel[10];
    char tempins[10];
    char del_dir[100];
    char test_file_full[256];
    char cwd[PATH_MAX];
    char *directory_path = ".";
    int first_line;
    int last_line;
    int ifdpnull = 0;
    int cyc;
    int cycen;
    int simflag = 0;
    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE];


    sprintf(testfile,"%d",rand());
    sprintf(temptxt,"%d.txt",rand());
    sprintf(temptxt_edi,"%d.txt",rand());
    sprintf(tempdel, "%d", rand());
    sprintf(tempins, "%d", rand());

    system("clear");

    printf("TEXRED ver 1.7.5, Programmed by Kruchinin Ilia\n");
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
    if (strstr(command, "@lsr") != NULL) {
        goto read_range;
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
    if (strstr(command, "@rmdir") != NULL) {
        goto remove_dir;
    }
    if (strstr(command, "@lndel") != NULL) {
        goto delete_line;
    }
    if (strstr(command, "@lnins") != NULL) {
        goto insert_line;
    }
    if (strstr(command, "@edit") != NULL) {
        goto edit;
    }
    if (strstr(command, "@mkdir") != NULL) {
        goto make_dir;
    }
    if (strstr(command, "@cls") != NULL) {
        system("clear");
        printf("CURRENT FILE IS: %s    \t", filename);

        if (ifdpnull == 1) {
            d = opendir(dp);
            chdir(dp);
            if (getcwd(dp, sizeof(dp)) != NULL) {
                printf("CURRENT DIRECTORY IS: %s\n", dp);
            }
        }
        else {
            d = opendir(directory_path);
            chdir(directory_path);
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("CURRENT DIRECTORY IS: %s\n", cwd);
            }
        }
    }
    else
        printf("Bad command (use '@help' to get commands)\n");
    goto com;
    help:
    printf("Commands:\n@new - select a new file\n@wri - edit file (Write mode)\n@sav - save file (Only in write mode)\n@edit - edit a line\n@ls - list a file\n@lsr - list a file in range\n@exit - close the program\n@dir - list the current directory\n@cd - change current directory\n@mkdir - create a new directory\n@rmdir - delete a directory\n@del - delete current file\n@lnins - insert a line after existig line\n@lndel - delete a line\n@cls - clear screen\n@help - show this menu\n");
    goto com;
    dir:
    struct dirent *dir;
    if (ifdpnull == 1) {
        d = opendir(dp);
        chdir(dp);
        if (getcwd(dp, sizeof(dp)) != NULL) {
            printf("Current directory is: %s\n", dp);
        }
    }
    else {
        d = opendir(directory_path);
        chdir(directory_path);
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Current directory is: %s\n", cwd);
        }
    }
    while ((dir = readdir(d)) != NULL) {
        printf("%s\n", dir->d_name);
    }
    goto com;
    change_dir:
    DIR *cd;
    cwd == NULL;
    printf("Enter new directory path: ");
    scanf("%s", dp);
    d = opendir(dp);
    if (d == NULL) {
        perror("Error opening directory! Error:");
        ifdpnull = 0;
        goto com;
        closedir(d);
    }
    closedir(d);
    ifdpnull = 1;
    goto com;



    make_dir:

    printf("Enter a new directory name: ");
    scanf("%s", new_dir);

    struct stat st = {0};

    if (stat(new_dir, &st) == -1) {
        mkdir(new_dir, 0700);
        printf("Directory '%s' is created!\n", new_dir);
    }
    else {
        printf("Directory already exist!");
        goto com;
    }
    goto com;

    remove_dir:

    printf("Enter a directory name to delete: ");
    scanf("%s", del_dir);


    if (rmdir(del_dir) == 0) {
        printf("Directory '%s' removed\n", del_dir);
    }
    else {
        printf("Directory doesn't exist!\n");
        goto com;
    }
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


    read_range:
    char us;
    char ch;
    //Read mode (range)
    FILE *file_ptra;
    if(ifdpnull == 1) {
        sprintf(full_path, "%s/%s", dp, filename);
        file_ptra = fopen(full_path, "r+");
    }
    else {
        file_ptra = fopen(filename, "r+");

    }

    if (file_ptra == NULL) {
        perror("Error opening file! Error");
        goto com;
    }

    int total_lines = 0;
    while ((ch = fgetc(file_ptra)) != EOF) {
        if (ch == '\n') {
            total_lines++;
        }
    }
    total_lines++; // Count the last line if it doesn't end with newline

    // Reset file pointer to beginning
    fseek(file_ptra, 0, SEEK_SET);

    // Get and validate first line
    do {
        printf("Enter first line (1-%d): ", total_lines);
        if (scanf("%d", &first_line) == 1) {
            continue;
        } else {
            printf("Please enter a correct first line number!\n");
            scanf("%c", &us);
            goto com;
        }
        if (first_line < 1 || first_line > total_lines) {
            printf("Error: First line must be between 1 and %d\n", total_lines);
            break;
            goto read_range;
        }
        if (!first_line) {
             printf("Error: First line must be between 1 and %d\n", total_lines);
             break;
             goto com;
        }
    } while (first_line < 1 || first_line > total_lines);

     scanf("%c", &us);
    // Get and validate last line
    do {
        printf("Enter last line (%d-%d): ", first_line, total_lines);
       if (scanf("%d", &last_line) == 1) {
           continue;
       } else {
           printf("Please enter a correct last line number!\n");
           scanf("%c", &us);
           goto com;
       }
        if (last_line < first_line || last_line > total_lines) {
            printf("Error: Last line must be between %d and %d\n", first_line, total_lines);
            break;
            goto read_range;
        }
        if (!last_line) {
            printf("Error: First line must be between 1 and %d\n", total_lines);
            break;
            goto com;
        }
    } while (last_line < first_line || last_line > total_lines);

    if (us == ' ') {
        printf("\n");
    }
    last_line++;

    int iffirst = 0;
    int linecount = 1;

    if (first_line == 1) {
        iffirst = 1;
    }

    while ((ch = fgetc(file_ptra)) != EOF){
        if (ch == '\n') {
            ++linecount;
        }
        if (linecount == first_line) {
            if (iffirst == 1){
                printf("%d.", linecount);
                putchar(ch);
                iffirst = 0;
            }
            else
                printf("%d.", linecount);
            while ((ch = fgetc(file_ptra)) != EOF){
                putchar(ch);
                if (ch == '\n') {
                    ++linecount;
                    printf("%d.", linecount);

                }
                if (linecount == last_line) {
                    printf("\x1b[2K");
                    printf("\x1b[1F");
                    goto c_c;
            }
          }
        }
    }
    c_c:
    if (cyc >> 0) {
        printf("\x1b[2K");
        printf("\x1b[1F");
        printf("\n");
    }
    else
        printf("\n");
    fclose(file_ptra);
    goto com;






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
    linecount = 1;
    printf("1.");
    while ((ch = fgetc(file_ptrr)) != EOF){
        putchar(ch);
        if (ch == '\n') {
            ++linecount;
            printf("%d.", linecount);
        }
    }
    if (cyc >> 0) {
        printf("\x1b[2K");
        printf("\x1b[1F");
        printf("\n");
    }
    else
        printf("\n");
    fclose(file_ptrr);
    goto com;


    write:
    //Writing
    FILE *file_ptrt;
    if (ifdpnull == 1) {
        sprintf(test_file_full, "%s/%s", dp, testfile);
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
    file_ptr = fopen(temptxt, "w");
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
        file_ptr = fopen(temptxt, "w");
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
        printf("\b\b");
        perror("Error opening file! Error");
        goto com;
    }
    temp = fopen(temptxt_edi, "w");




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
        rename(temptxt_edi, full_path);
    } else {
        remove(filename);
        rename(temptxt_edi, filename);
    }

    goto com;



    insert_line:
    FILE *ins_line;
    FILE *temp_ins;

    int line_ins, count_ins;
    int cycins;
    printf("After which line: ");
    scanf("%d", &line_ins);

    scanf("%c", &dc);

    if(ifdpnull == 1) {
        sprintf(full_path, "%s/%s", dp, filename);
        ins_line = fopen(full_path, "r+");
    } else {
        ins_line = fopen(filename, "r+");

    }
    if (ins_line == NULL) {
        perror("Error opening file! Error");
        goto com;
    }
    temp_ins = fopen(tempins, "w");

    count_ins = 0;
    while ((fgets(buffer, BUFFER_SIZE, ins_line)) != NULL) {
        count_ins++;



        for (cycins = 1; cycins < 2; ++cycins) {
            /* If current line is line to delete */
            if (count_ins == line_ins) {
                /*ANSI Escape Stuff*/
                fputs(buffer, temp_ins);
                fputs("\n", temp_ins);
            }
            else
                fputs(buffer, temp_ins);
        }
    }
    fclose(ins_line);
    fclose(temp_ins);

    if(ifdpnull == 1) {
        remove(full_path);
        sprintf(full_path, "%s/%s", dp, filename);
        rename(tempins, full_path);
    } else {
        remove(filename);
        rename(tempins, filename);
    }

    goto com;


    delete_line:
    FILE *del_line;
    FILE *temp_line;

    int line_del, count_del;
    printf("Enter line number to delete: ");
    scanf("%d", &line_del);

    scanf("%c", &dc);

    if(ifdpnull == 1) {
        sprintf(full_path, "%s/%s", dp, filename);
        del_line = fopen(full_path, "r+");
    } else {
        del_line = fopen(filename, "r+");

    }
    if (del_line == NULL) {
        perror("Error opening file! Error");
        goto com;
    }
    temp_line = fopen(tempdel, "w");

    count_del = 0;
    while ((fgets(buffer, BUFFER_SIZE, del_line)) != NULL) {
        count_del++;

        /* If current line is line to delete */
        if (count_del == line_del) {
            /*ANSI Escape Stuff*/
            while (!'\n')
                fputs("\b", temp_line);
        }
        else
            fputs(buffer, temp_line);
    }
    fclose(del_line);
    fclose(temp_line);

    if(ifdpnull == 1) {
        remove(full_path);
        sprintf(full_path, "%s/%s", dp, filename);
        rename(tempdel, full_path);
    } else {
        remove(filename);
        rename(tempdel, filename);
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
        rename(temptxt, full_path);
    } else {
        remove(filename);
        rename(temptxt, filename);
    }

    printf("File '%s' written!\n", filename);

    goto com;

}
