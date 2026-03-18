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

int validateUser(char username[], char password[]);
int login();
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
    char fileUser[50], filePass[50];

    FILE *fp = fopen("./users.txt","r");
    if(fp == NULL){
        return 0;
    }

    while (fscanf(fp, "%s %s", fileUser, filePass) != EOF) {
        if (strcmp(username, fileUser) == 0 &&
            strcmp(password, filePass) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int login(){
    char username[50], password[50];
    char fileUser[50], filePass[50];

    FILE *fp = fopen("./users.txt","r");   // fixed
    if(fp == NULL){
        printf("Error");
        return 0;
    }

    printf("Username : ");
    scanf("%s", username);
    printf("Password : ");
    scanf("%s", password);

    while (fscanf(fp, "%s %s", fileUser, filePass) != EOF) {
        if (strcmp(username, fileUser) == 0 &&
            strcmp(password, filePass) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
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

    FILE *fp = fopen(filename, "r");   // fixed
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
        newNode ->total = calculateTotal(newNode->scores);
        newNode -> next = head;
        head = newNode;
    }
    fclose(fp);
    printf("Data Loaded Success");
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
    printf("Student Not Exist");
}

void deleteStudent(){
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    Student *temp = head, *prev = NULL;

    while(temp){
        if(temp->id ==id){
            if(prev == NULL){
                head = temp ->next;
            }
            else{
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
        printf("1. Load File\n");
        printf("2. Display\n");
        printf("3. Add\n");
        printf("4. Search\n");
        printf("5. Delete\n");
        printf("6. Sort by Total\n");
        printf("7. Save\n");
        printf("0. Exit\n");

        scanf("%d", &c);

        switch(c){
            case 1:{
                loadFromFile();
                break;
            }
            case 2 : {
                display();
                break;
            }
            case 3 : {
                addStudent();
                saveToFile();
                break;
            }
            case 4: {
                searchStudent();
                break;
            }
            case 5 :{
                deleteStudent();
                saveToFile();
                break;
            }
            case 6 : {
                sortByTotal();
                break;
            }
            case 7 : {
                saveToFile();
                break;
            }
            case 0 : {
                return;
            }
            default : {
                printf("Invalid Options\n");
            }
        }
    }
}

int main (){
    printf("=======Please Login ======= \n");
    char username[50], password[50];
    printf("Enter Your Username: ");
    scanf("%s", username);
    printf("Enter Your Password: ");
    scanf("%s", password);

    if (validateUser(username, password)) {
        printf("Login Successful!\n");
        loadFromFile();
        menu();
    } else {
        printf("Invalid Credentials!\n");
    }
    return 0;
}