#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

struct Size {
    char minS[100];
    char maxS[100];
};

// �������� ��������� ��� ������
typedef struct Node {
    char nom[10];
    char nazv[100];
    struct Size size; // ��������� ���������
    float stoit;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;  // ��������� �� ������ ������� ������
} LinkedList;
// ������� ��� �������� ������ ����
Node* createNode(const char* nom, const char* nazv, const char* minS, const char* maxS, float stoit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->nom, nom);
    strcpy(newNode->nazv, nazv);
    strcpy(newNode->size.minS, minS);
    strcpy(newNode->size.maxS, maxS);
    newNode->stoit = stoit;

    newNode->next = NULL;
    return newNode;
}

// ������� ��� ���������� ���� � ����� ������
void append(LinkedList* list, const char* nom, const char* nazv, const char* minS, const char* maxS, float stoit) {
    Node* newNode = createNode(nom, nazv, minS, maxS, stoit);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// ������� ��� ����������� ������
void display(LinkedList* list) {
    Node* current = list->head;
    const char shapka[] =
        "+-------------------------------------------------------------+\n"
        "|   |                 |       ������       |                  |\n"
        "| # |  ��������       |----------+---------|       ����       |\n"
        "|   |                 | ���      | ����    |                  |\n"
        "+---+-----------------+----------+---------+------------------+\n";

    printf("%s", shapka);
    
    while (current != NULL) {
        // ���������, ���� min ��� max ������ ����� 45
        char modifiedNazv[100];
        if (strcmp(current->size.minS, "45") == 0 || strcmp(current->size.maxS, "45") == 0) {
            strcpy(modifiedNazv, current->nazv);
            strcat(modifiedNazv, " (45)"); // ��������� "(45)" � ��������
        } else {
            strcpy(modifiedNazv, current->nazv);
        }

        printf("| %2s| %-15s | %8s | %7s | %16.2f |\n",
               current->nom, modifiedNazv, current->size.minS, current->size.maxS, current->stoit);
        printf("+---+-----------------+----------+---------+------------------+\n");
        current = current->next;
    }
}

// ������� ��� ������������ ������� � ���������� ��������� ������
void swapFirstLast(LinkedList* list) {

    Node* first = list->head;
    Node* last = list->head;
    Node* prevToLast = NULL;

    // ������� ��������� � ������������� ��������
    while (last->next != NULL) {
        prevToLast = last;
        last = last->next;
    }

    // ������������
    if (prevToLast != NULL) {
        prevToLast->next = first;  // ������������� ��������� �� ������
        last->next = first->next;   // ��������� ��������� �� ������ �������
        list->head = last;          // ����� ������ ������ - ��������� �������
        first->next = NULL;         // ������ ������� ������ ���������
    }
}

// ������� ��� ������������ ������
void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL; // �������� ��������� �� ������ ������
}

int main() {
    LinkedList list;
    list.head = NULL;

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    while (1) {
        char nom[10];
        char nazv[100];
        char minS[100];
        char maxS[100];
        float stoit;

        printf("������� ����� ������ (��� '*' ��� ���������� �����): ");
        scanf("%s", nom);
        if (strcmp(nom, "*") == 0) {
            break;
        }
        
        printf("������� �������� ������: ");
        scanf("%s", nazv);  
        
        printf("������� min ������: ");
        scanf("%s", minS);

        printf("������� max ������: ");
        scanf("%s", maxS);
        
        printf("������� ����: ");
        scanf("%f", &stoit);

        append(&list, nom, nazv, minS, maxS, stoit);
    }

    printf("\n�������� ������:\n");
    display(&list);

    swapFirstLast(&list);

    printf("\nC����� ����� ������������ ������� � ���������� ���������:\n");
    display(&list);

    // ������������ ������
    freeList(&list);

    getch();
    return 0;
}
