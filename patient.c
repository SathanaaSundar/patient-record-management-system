
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int reg_no;
    char name[50];
    char guardian[50];
    char gender[15];
    int age;
    char blood_group[10];
    char phone[20];
    char address[100];
    char city[50];
    char state[50];
    char disease[100];
    char doctor[50];
    char history[200];
    struct node *next;
};

struct node *head = NULL;

void readString(const char *message, char str[], int size) {
    printf("%s", message);
    if (fgets(str, size, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
    }
}

int readInt(const char *message) {
    char line[50];
    int value;
    char extra;

    while (1) {
        printf("%s", message);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            return -1;
        }

        if (sscanf(line, " %d %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid input. Enter a whole number.\n");
    }
}

struct node *searchPatient(int id) {
    struct node *temp = head;

    while (temp != NULL) {
        if (temp->reg_no == id) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

void addPatient(void) {
    struct node *newnode;
    int id;

    id = readInt("Enter registration number: ");

    if (id <= 0) {
        printf("Registration number must be positive.\n");
        return;
    }

    if (searchPatient(id) != NULL) {
        printf("Registration number already exists.\n");
        return;
    }

    newnode = malloc(sizeof(struct node));

    if (newnode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newnode->reg_no = id;

    readString("Patient name: ", newnode->name,
               sizeof(newnode->name));
    readString("Guardian name: ", newnode->guardian,
               sizeof(newnode->guardian));
    readString("Gender: ", newnode->gender,
               sizeof(newnode->gender));

    newnode->age = readInt("Age: ");

    if (newnode->age < 0 || newnode->age > 120) {
        printf("Invalid age.\n");
        free(newnode);
        return;
    }

    readString("Blood group: ", newnode->blood_group,
               sizeof(newnode->blood_group));
    readString("Phone number: ", newnode->phone,
               sizeof(newnode->phone));
    readString("Address: ", newnode->address,
               sizeof(newnode->address));
    readString("City: ", newnode->city,
               sizeof(newnode->city));
    readString("State: ", newnode->state,
               sizeof(newnode->state));
    readString("Disease/problem: ", newnode->disease,
               sizeof(newnode->disease));
    readString("Referred doctor: ", newnode->doctor,
               sizeof(newnode->doctor));
    readString("Medical history: ", newnode->history,
               sizeof(newnode->history));

    newnode->next = NULL;

    if (head == NULL) {
        head = newnode;
    } else {
        struct node *temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newnode;
    }

    printf("Patient record added successfully.\n");
}

void displayPatient(struct node *p) {
    printf("\nRegistration number : %d\n", p->reg_no);
    printf("Patient name        : %s\n", p->name);
    printf("Guardian name       : %s\n", p->guardian);
    printf("Gender              : %s\n", p->gender);
    printf("Age                 : %d\n", p->age);
    printf("Blood group         : %s\n", p->blood_group);
    printf("Phone number        : %s\n", p->phone);
    printf("Address             : %s\n", p->address);
    printf("City                : %s\n", p->city);
    printf("State               : %s\n", p->state);
    printf("Disease/problem     : %s\n", p->disease);
    printf("Referred doctor     : %s\n", p->doctor);
    printf("Medical history     : %s\n", p->history);
    printf("-----------------------------------\n");
}

void displayAll(void) {
    struct node *temp = head;

    if (head == NULL) {
        printf("No patient records found.\n");
        return;
    }

    while (temp != NULL) {
        displayPatient(temp);
        temp = temp->next;
    }
}

void searchRecord(void) {
    int id = readInt("Enter registration number to search: ");
    struct node *result = searchPatient(id);

    if (result == NULL) {
        printf("Patient record not found.\n");
    } else {
        displayPatient(result);
    }
}

void updatePatient(void) {
    int id, choice;
    struct node *temp;

    id = readInt("Enter registration number to update: ");
    temp = searchPatient(id);

    if (temp == NULL) {
        printf("Patient record not found.\n");
        return;
    }

    printf("\n1. Update patient name\n");
    printf("2. Update phone number\n");
    printf("3. Update age\n");
    printf("4. Update medical history\n");

    choice = readInt("Enter your choice: ");

    switch (choice) {
        case 1:
            readString("Enter new patient name: ",
                       temp->name, sizeof(temp->name));
            break;

        case 2:
            readString("Enter new phone number: ",
                       temp->phone, sizeof(temp->phone));
            break;

        case 3:
            temp->age = readInt("Enter new age: ");

            if (temp->age < 0 || temp->age > 120) {
                printf("Invalid age. Age not updated.\n");
                return;
            }
            break;

        case 4:
            readString("Enter new medical history: ",
                       temp->history, sizeof(temp->history));
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }

    printf("Patient record updated successfully.\n");
}

void deletePatient(void) {
    int id = readInt("Enter registration number to delete: ");
    struct node *temp = head;
    struct node *prev = NULL;

    while (temp != NULL && temp->reg_no != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Patient record not found.\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Patient record deleted successfully.\n");
}

void sortPatients(void) {
    struct node *sorted = NULL;
    struct node *current = head;

    if (head == NULL || head->next == NULL) {
        printf("Records are already sorted.\n");
        return;
    }

    while (current != NULL) {
        struct node *nextNode = current->next;

        if (sorted == NULL ||
            current->reg_no < sorted->reg_no) {
            current->next = sorted;
            sorted = current;
        } else {
            struct node *temp = sorted;

            while (temp->next != NULL &&
                   temp->next->reg_no < current->reg_no) {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = nextNode;
    }

    head = sorted;
    printf("Records sorted by registration number.\n");
}

void freeList(void) {
    struct node *temp = head;

    while (temp != NULL) {
        struct node *nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    head = NULL;
}

int main(void) {
    int choice;

    while (1) {
        printf("\n===== PATIENT RECORD MANAGEMENT SYSTEM =====\n");
        printf("1. Add patient\n");
        printf("2. Display all patients\n");
        printf("3. Search patient\n");
        printf("4. Update patient\n");
        printf("5. Delete patient\n");
        printf("6. Sort by registration number\n");
        printf("7. Exit\n");

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addPatient();
                break;

            case 2:
                displayAll();
                break;

            case 3:
                searchRecord();
                break;

            case 4:
                updatePatient();
                break;

            case 5:
                deletePatient();
                break;

            case 6:
                sortPatients();
                break;

            case 7:
                freeList();
                printf("Program exited successfully.\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
