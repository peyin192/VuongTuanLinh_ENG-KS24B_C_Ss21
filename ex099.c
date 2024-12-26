#include <stdio.h>
#include <string.h>

typedef struct {
    char bookId[20];
    char title[100];
    char auth[50];
    float price;
    char category[50];
} Book;

void addBook(Book book[], int *n);
void saveBooksToFile(Book book[], int n);
void loadBooksFromFile(Book book[], int *n);
void displayBooks(Book book[], int n);

int main() {
    FILE *file;
    int option = 0;
    int n = 0;
    Book book[100];

    do {
        printf("MENU\n");
        printf("1. Nhap so luong va thong tin sach: \n");
        printf("2. Luu thong tin sach vao file\n");
        printf("3. Lay thong tin sach tu file\n");
        printf("4. Hien thi thong tin sach\n");
        printf("5. Thoat\n");

        printf("Nhap lua chon: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                printf("Nhap so luong sach: ");
                scanf("%d", &n);
                getchar();
                addBook(book, &n);
                break;
            }
            case 2: {
                saveBooksToFile(book, n);
                break;
            }
            case 3: {
                loadBooksFromFile(book, &n);
                break;
            }
            case 4: {
                displayBooks(book, n);
                break;
            }
            case 5: {
                printf("Exiting program. Goodbye!\n");
                return 0;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
            }
        }

    } while(option != 5);

    return 0;
}

void addBook(Book book[], int *n) {
    for (int i = 0; i < *n; i++) {
        printf("Moi nhap thong tin cua quyen sach thu %d\n", i + 1);

        printf("Ma sach: ");
        fgets(book[i].bookId, sizeof(book[i].bookId), stdin);
        book[i].bookId[strcspn(book[i].bookId, "\n")] = '\0';

        printf("Ten sach: ");
        fgets(book[i].title, sizeof(book[i].title), stdin);
        book[i].title[strcspn(book[i].title, "\n")] = '\0';

        printf("Ten tac gia: ");
        fgets(book[i].auth, sizeof(book[i].auth), stdin);
        book[i].auth[strcspn(book[i].auth, "\n")] = '\0';

        printf("Gia tien: ");
        scanf("%f", &book[i].price);
        getchar();

        printf("The loai: ");
        fgets(book[i].category, sizeof(book[i].category), stdin);
        book[i].category[strcspn(book[i].category, "\n")] = '\0';
    }
}

void saveBooksToFile(Book book[], int n) {
    FILE *file = fopen("book_info.bin", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&n, sizeof(int), 1, file);
    fwrite(book, sizeof(Book), n, file);
    fclose(file);
    printf("\nBooks saved to file successfully.\n");
}

void loadBooksFromFile(Book book[], int *n) {
    FILE *file = fopen("book_info.bin", "rb");
    if (file == NULL) {
        printf("\nError opening file for reading or file does not exist.\n");
        return;
    }

    fread(n, sizeof(int), 1, file);
    fread(book, sizeof(Book), *n, file);
    fclose(file);
    printf("\nBooks loaded from file successfully.\n");
}

void displayBooks(Book book[], int n) {
    if (n == 0) {
        printf("\nNo books to display.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\nBook %d:\n", i + 1);
        printf("Ma sach: %s\n", book[i].bookId);
        printf("Ten sach: %s\n", book[i].title);
        printf("Ten tac gia: %s\n", book[i].auth);
        printf("Gia tien: %.2f\n", book[i].price);
        printf("The loai: %s\n", book[i].category);
    }
}

