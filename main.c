#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// опис вузла зв'язного списку
typedef struct BookNode {
    char title[128];        // назва книги
    double price;           // ціна (у грн)
    int pages;              // кількість сторінок
    char language[32];      // мова
    double weight;          // вага (у грамах)
    int year;               // рік видання
    struct BookNode* next;  // вказівник на наступну книгу
} BookNode;

// функція для створення нового вузла
BookNode* createBook(const char* title, double price, int pages, const char* language, double weight, int year) {
    BookNode* newNode = (BookNode*)malloc(sizeof(BookNode));
    if (newNode == NULL) {
        printf("Помилка виділення пам'яті!\n");
        exit(1);
    }

    // заповнення полів даними
    strncpy(newNode->title, title, sizeof(newNode->title) - 1);
    newNode->title[sizeof(newNode->title) - 1] = '\0';

    newNode->price = price;
    newNode->pages = pages;

    strncpy(newNode->language, language, sizeof(newNode->language) - 1);
    newNode->language[sizeof(newNode->language) - 1] = '\0';

    newNode->weight = weight;
    newNode->year = year;
    newNode->next = NULL;

    return newNode;
}

// функція додавання книги в кінець списку
void appendBook(BookNode** head, const char* title, double price, int pages, const char* language, double weight, int year) {
    BookNode* newNode = createBook(title, price, pages, language, weight, year);

    // якщо список порожній, новий елемент стає початком списку
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // інакше шукаємо останній вузол списку
    BookNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    // прив'язуємо новий вузол до кінця
    current->next = newNode;
}

// функція для виведення всього списку на екран
void printBooks(const BookNode* head) {
    const BookNode* current = head;
    int index = 1;
    
    printf("Серія книг про Гарі Поттера\n");

    while (current != NULL) {
        printf("[%d] \"%s\"\n", index++, current->title);
        printf("Рік видання:      %d р.\n", current->year);
        printf("Мова:             %s\n", current->language);
        printf("Кількість сторінок: %d\n", current->pages);
        printf("Вага:             %.1f г\n", current->weight);
        printf("Ціна:             %.2f грн\n", current->price);

        current = current->next; // перехід до наступного вузла
    }
}

// функція звільнення пам'яті
void freeBooks(BookNode* head) {
    BookNode* current = head;
    while (current != NULL) {
        BookNode* nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main() {
    // вмикаємо UTF-8 для коректного виведення українського тексту
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    BookNode* bookList = NULL; // початок зв'язного списку (head)

    // наповнюємо список книгами серії про Гаррі Поттера
    appendBook(&bookList, "Гаррі Поттер і філософський камінь", 320.00, 320, "Українська", 450.0, 1997);
    appendBook(&bookList, "Гаррі Поттер і таємна кімната", 330.00, 352, "Українська", 480.0, 1998);
    appendBook(&bookList, "Гаррі Поттер і в'язень Азкабану", 350.00, 384, "Українська", 510.0, 1999);
    appendBook(&bookList, "Гаррі Поттер і Келих вогню", 420.00, 672, "Українська", 750.0, 2000);
    appendBook(&bookList, "Гаррі Поттер і Орден Фенікса", 480.00, 816, "Українська", 880.0, 2003);
    appendBook(&bookList, "Гаррі Поттер і Напівкровний Принц", 410.00, 608, "Українська", 690.0, 2005);
    appendBook(&bookList, "Гаррі Поттер і Смертельні реліквії", 450.00, 640, "Українська", 720.0, 2007);

    // виведення списку
    printBooks(bookList);

    // звільнення виділеної динамічної пам'яті
    freeBooks(bookList);
    bookList = NULL;

    return 0;
}