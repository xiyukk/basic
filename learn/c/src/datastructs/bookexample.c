#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Book structure
struct Book {
    char title[100];
    char author[100];
    int publicationYear;
    struct Book* next;
};

// Function to create a new book
struct Book* createBook(const char* title, const char* author, int publicationYear) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    strncpy(newBook->title, title, sizeof(newBook->title));
    strncpy(newBook->author, author, sizeof(newBook->author));
    newBook->publicationYear = publicationYear;
    newBook->next = NULL;
    return newBook;
}

// Function to add a book to the list
void addBook(struct Book** library, const char* title, const char* author, int publicationYear) {
    struct Book* newBook = createBook(title, author, publicationYear);
    newBook->next = *library;
    *library = newBook;
}

// Function to print the library
void printLibrary(struct Book* library) {
    struct Book* current = library;
    int count = 1;
    while (current != NULL) {
        printf("Book %d:\n", count);
        printf("  Title: %s\n", current->title);
        printf("  Author: %s\n", current->author);
        printf("  Publication Year: %d\n", current->publicationYear);
        current = current->next;
        count++;
    }
}

// Function to free the memory allocated for the library
void freeLibrary(struct Book* library) {
    struct Book* current = library;
    struct Book* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct Book* library = NULL;

    addBook(&library, "The Catcher in the Rye", "J.D. Salinger", 1951);
    addBook(&library, "To Kill a Mockingbird", "Harper Lee", 1960);
    addBook(&library, "1984", "George Orwell", 1949);

    printf("Library:\n");
    printLibrary(library);

    freeLibrary(library);

    return 0;
}