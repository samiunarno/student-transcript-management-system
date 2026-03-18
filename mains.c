#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBJECTS 5

typedef struct Student {
    int id;
    char name[50];
    float scores[SUBJECTS];
    float total;
    struct Student *next;
} Student;

Student *head = NULL;
char currentRole[20];

int validateUser(char username[], char password[]);
void registerUser();
void changeUserRole();
float calculateTotal(float scores[]);
void loadFromFile();
void display();
void addStudent();
void searchStudent();
void deleteStudent();
void sortByTotal();
void saveToFile();
void menu();

int validateUser(char username[], char password[]){
    char fileUser[50], filePass[50], role[20];

    FILE *fp = fopen("./users.txt","r");
    if(fp == NULL){
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileUser, filePass, role) != EOF) {
        if (strcmp(username, fileUser) == 0 &&
            strcmp(password, filePass) == 0) {

            strcpy(currentRole, role);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void registerUser(){
    char username[50], password[50];
    char fileUser[50], filePass[50], role[20];

    FILE *fp = fopen("./users.txt","a+");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }

    printf("Enter New Username: ");
    scanf("%s", username);

    rewind(fp);

    while(fscanf(fp, "%s %s %s", fileUser, filePass, role) != EOF){
        if(strcmp(username, fileUser) == 0){
            printf("Username already exists!\n");
            fclose(fp);
            return;
        }
    }

    printf("Enter New Password: ");
    scanf("%s", password);

    fprintf(fp, "%s %s user\n", username, password);
    fclose(fp);

    printf("Registration Successful! (Role: user)\n");
}

void changeUserRole(){
    if(strcmp(currentRole, "admin") != 0){
        printf("Access Denied! Only admin allowed.\n");
        return;
    }

    char targetUser[50];
    printf("Enter username to change role: ");
    scanf("%s", targetUser);

    FILE *fp = fopen("./users.txt", "r");
    FILE *temp = fopen("./temp.txt", "w");

    if(!fp || !temp){
        printf("File error!\n");
        return;
    }

    char u[50], p[50], r[20];
    int found = 0;

    while(fscanf(fp, "%s %s %s", u, p, r) != EOF){
        if(strcmp(u, targetUser) == 0){
            found = 1;

            if(strcmp(u, "admin") == 0){
                printf("Cannot change main admin role!\n");
                fprintf(temp, "%s %s %s\n", u, p, r);
                continue;
            }

            if(strcmp(r, "user") == 0){
                strcpy(r, "admin");
                printf("User promoted to admin!\n");
            } else {
                strcpy(r, "user");
                printf("Admin demoted to user!\n");
            }
        }

        fprintf(temp, "%s %s %s\n", u, p, r);
    }

    fclose(fp);
    fclose(temp);

    remove("./users.txt");
    rename("./temp.txt", "./users.txt");

    if(!found){
        printf("User not found!\n");
    }
}

float calculateTotal(float scores[]){
    float sum = 0;
    for(int i = 0; i<SUBJECTS;i++){
        sum += scores[i];
    }
    return sum;
}

void loadFromFile(){
    char filename[100];
    strcpy(filename, "./student.txt");

    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("File Not Found! \n");
        return;
    }

    while(!feof(fp)){
        Student *newNode = (Student *)malloc(sizeof(Student));
        newNode->next = NULL;

        if (fscanf(fp, "%d %s", &newNode->id, newNode->name) != 2) {
            free(newNode);
            break;
        }
        for(int i = 0 ; i<SUBJECTS; i++){
            fscanf(fp, "%f",&newNode->scores[i]);
        }
        newNode->total = calculateTotal(newNode->scores);
        newNode->next = head;
        head = newNode;
    }
    fclose(fp);
    printf("Data Loaded Success\n");
}

void display(){
    Student *temp = head;
    while(temp){
        printf("ID: %d Name: %s Total: %.2f\n",temp->id, temp->name,temp->total);
        temp = temp->next;
    }
}

void addStudent(){
    Student *newNode = (Student *)malloc(sizeof(Student));
    printf("Enter ID: ");
    scanf("%d", &newNode->id);
    printf("Enter Name: ");
    scanf("%s", newNode->name);

    for(int i = 0 ; i<SUBJECTS ; i++){
        printf("Score %d: ", i + 1);
        scanf("%f", &newNode->scores[i]);
    }
    newNode->total = calculateTotal(newNode->scores);
    newNode->next = head;
    head = newNode;
}

void searchStudent(){
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    Student *temp = head;

    while(temp){
        if(temp->id ==id){
            printf("Found: %s Total: %.2f\n",temp->name, temp->total);
            return;
        }
        temp = temp -> next;
    }
    printf("Student Not Exist\n");
}

void deleteStudent(){
    if(strcmp(currentRole, "admin") != 0){
        printf("Access Denied! Only admin can delete.\n");
        return;
    }

    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    Student *temp = head, *prev = NULL;

    while(temp){
        if(temp->id == id){
            if(prev == NULL){
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Deleted Successfully \n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Student Not Exist \n");
}

void sortByTotal(){
    Student *i, *j;
    for(i=head;i!=NULL;i=i->next){
        for(j=i->next; j!=NULL;j=j->next){
            if(i->total<j->total){
                int tempId = i->id;
                char tempName[50];
                float tempScores[SUBJECTS];
                float tempTotal = i->total;

                i->id = j->id;
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                for(int k=0; k<SUBJECTS; k++){
                    tempScores[k] = i->scores[k];
                    i->scores[k] = j->scores[k];
                    j->scores[k] = tempScores[k];
                }

                j->id = tempId;
                i->total = j->total;
                j->total = tempTotal;
            }
        }
    }
    printf("Sorted By Total! \n");
}

void saveToFile(){
    FILE *fp = fopen("./student.txt", "w");
    if (!fp) {
        printf("Error saving file!\n");
        return;
    }

    Student *temp = head;
    while (temp) {
        fprintf(fp, "%d %s ", temp->id, temp->name);
        for (int i = 0; i < SUBJECTS; i++)
            fprintf(fp, "%.2f ", temp->scores[i]);
        fprintf(fp, "\n");

        temp = temp->next;
    }

    fclose(fp);
    printf("File Updated!\n");
}

void menu(){
    int c;

    while(1){
        printf("\n----- MENU -----\n");
        printf("1. Display\n");
        printf("2. Add\n");
        printf("3. Search\n");
        printf("4. Delete\n");
        printf("5. Sort by Total\n");
        printf("6. Save\n");

        if(strcmp(currentRole, "admin") == 0){
            printf("7. Change User Role\n");
        }

        printf("0. Exit\n");

        scanf("%d", &c);

        switch(c){
            case 1: display(); break;
            case 2: addStudent(); saveToFile(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); saveToFile(); break;
            case 5: sortByTotal(); break;
            case 6: saveToFile(); break;
            case 7:
                if(strcmp(currentRole, "admin") == 0)
                    changeUserRole();
                else
                    printf("Invalid Option\n");
                break;
            case 0: return;
            default: printf("Invalid Options\n");
        }
    }
}

int main (){
    int choice;

    while(1){
        printf("======= SYSTEM =======\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 2){
            registerUser();
            continue;   
        }

        else if(choice == 1){
            printf("======= Please Login ======= \n");

            char username[50], password[50];

            printf("Enter Your Username: ");
            scanf("%s", username);
            printf("Enter Your Password: ");
            scanf("%s", password);

            if (validateUser(username, password)) {
                printf("Login Successful!\n");
                printf("Role: %s\n", currentRole);
                loadFromFile();
                menu();
            } else {
                printf("Invalid Credentials!\n");
            }
        }

        else if(choice == 0){
            break;
        }

        else{
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}