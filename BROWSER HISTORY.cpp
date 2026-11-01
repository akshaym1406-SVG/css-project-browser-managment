#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_HISTORY 100
#define URL_LENGTH 256

typedef struct {
    char urls[MAX_HISTORY][URL_LENGTH];
    int top;
} BrowserStack;

void initStack(BrowserStack *s) {
    s->top = -1;
}

int isFull(BrowserStack *s) {
    return s->top == MAX_HISTORY - 1;
}

int isEmpty(BrowserStack *s) {
    return s->top == -1;
}

void push(BrowserStack *s, const char* url) {
    if (isFull(s)) {
        printf("Stack Overflow: History is full.\n");
        return;
    }
    s->top++;
    strcpy(s->urls[s->top], url);
}

void pop(BrowserStack *s, char* popped_url) {
    if (isEmpty(s)) {
        popped_url[0] = '\0';
        return;
    }
    strcpy(popped_url, s->urls[s->top]);
    s->top--;
}

void displayStack(BrowserStack *s) {
    if (isEmpty(s)) {
        printf("History is empty.\n");
        return;
    }
    printf("--- Navigation History ---\n");
    for (int i = s->top; i >= 0; i--) {
        printf("%d: %s\n", s->top - i + 1, s->urls[i]);
    }
    printf("--------------------------\n");
}

int main() {
    BrowserStack backStack, forwardStack;
    initStack(&backStack);
    initStack(&forwardStack);
    
    char current_page[URL_LENGTH] = "Start Page";
    int choice;
    char new_url[URL_LENGTH];

    while (1) {
        printf("\n[Current Page: %s]\n", current_page);
        printf("1. Visit New Page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Show Back History\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) break;
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter new URL: ");
                fgets(new_url, URL_LENGTH, stdin);
                new_url[strcspn(new_url, "\n")] = 0; 
                
                if (strcmp(current_page, "Start Page") != 0 && strlen(current_page) > 0) {
                    push(&backStack, current_page);
                }
                strcpy(current_page, new_url);
                initStack(&forwardStack); 
                printf("Visited: %s\n", current_page);
                break;
                
            case 2:
                if (isEmpty(&backStack)) {
                    printf("No backward history.\n");
                } else {
                    push(&forwardStack, current_page);
                    pop(&backStack, current_page);
                    printf("Went back to: %s\n", current_page);
                }
                break;
                
            case 3:
                if (isEmpty(&forwardStack)) {
                    printf("No forward history.\n");
                } else {
                    push(&backStack, current_page);
                    pop(&forwardStack, current_page);
                    printf("Went forward to: %s\n", current_page);
                }
                break;
                
            case 4:
                displayStack(&backStack);
                break;
                
            case 5:
                printf("Exiting browser...\n");
                return 0;
                
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
