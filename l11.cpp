#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

struct Size {
    char minS[100];
    char maxS[100];
};

// Основная структура для одежды
typedef struct Node {
    char nom[10];
    char nazv[100];
    struct Size size; // Вложенная структура
    float stoit;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;  // Указатель на первый элемент списка
} LinkedList;
// Функция для создания нового узла
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

// Функция для добавления узла в конец списка
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

// Функция для отображения списка
void display(LinkedList* list) {
    Node* current = list->head;
    const char shapka[] =
        "+-------------------------------------------------------------+\n"
        "|   |                 |       размер       |                  |\n"
        "| # |  Название       |----------+---------|       цена       |\n"
        "|   |                 | мин      | макс    |                  |\n"
        "+---+-----------------+----------+---------+------------------+\n";

    printf("%s", shapka);
    
    while (current != NULL) {
        // Проверяем, если min или max размер равен 45
        char modifiedNazv[100];
        if (strcmp(current->size.minS, "45") == 0 || strcmp(current->size.maxS, "45") == 0) {
            strcpy(modifiedNazv, current->nazv);
            strcat(modifiedNazv, " (45)"); // Добавляем "(45)" к названию
        } else {
            strcpy(modifiedNazv, current->nazv);
        }

        printf("| %2s| %-15s | %8s | %7s | %16.2f |\n",
               current->nom, modifiedNazv, current->size.minS, current->size.maxS, current->stoit);
        printf("+---+-----------------+----------+---------+------------------+\n");
        current = current->next;
    }
}

// Функция для перестановки первого и последнего элементов списка
void swapFirstLast(LinkedList* list) {

    Node* first = list->head;
    Node* last = list->head;
    Node* prevToLast = NULL;

    // Находим последний и предпоследний элементы
    while (last->next != NULL) {
        prevToLast = last;
        last = last->next;
    }

    // Перестановка
    if (prevToLast != NULL) {
        prevToLast->next = first;  // Предпоследний указывает на первый
        last->next = first->next;   // Последний указывает на второй элемент
        list->head = last;          // Новый голова списка - последний элемент
        first->next = NULL;         // Первый элемент теперь последний
    }
}

// Функция для освобождения памяти
void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL; // Обнуляем указатель на голову списка
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

        printf("Введите номер одежды (или '*' для завершения ввода): ");
        scanf("%s", nom);
        if (strcmp(nom, "*") == 0) {
            break;
        }
        
        printf("Введите название одежды: ");
        scanf("%s", nazv);  
        
        printf("Введите min размер: ");
        scanf("%s", minS);

        printf("Введите max размер: ");
        scanf("%s", maxS);
        
        printf("Введите цену: ");
        scanf("%f", &stoit);

        append(&list, nom, nazv, minS, maxS, stoit);
    }

    printf("\nИсходные данные:\n");
    display(&list);

    swapFirstLast(&list);

    printf("\nCписок после перестановки первого и последнего элементов:\n");
    display(&list);

    // Освобождение памяти
    freeList(&list);

    getch();
    return 0;
}
