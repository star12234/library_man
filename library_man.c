#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_BOOKS 100

// 도서 구조체 정의
struct Book {
    int id;
    char title[50];
    char author[50];
    int is_borrowed;    // 대출 상태 (0: 대출 가능, 1: 대출 중)
};
void add_book(struct Book library[], int* book_count);
void delete_book(struct Book library[], int* book_count);
void search_book(struct Book library[], int book_count);
void display_books(struct Book library[], int book_count);
void borrow_book(struct Book library[], int book_count);
void return_book(struct Book library[], int book_count);

// 관리자 로그인 상태를 저장할 전역 변수
int is_admin_logged_in = 0;

// 관리자 로그인 함수
int admin_login() {
    char password[20];
    const char admin_password[] = "admin1234";

    printf("관리자 비밀번호를 입력하세요: ");
    scanf(" %s", password);

    if (strcmp(password, admin_password) == 0) {
        is_admin_logged_in = 1;
        printf("관리자로 로그인되었습니다.\n");
        return 1;
    }
    printf("비밀번호가 일치하지 않습니다.\n");
    return 0;
}

// 관리자 로그아웃 함수
void admin_logout() {
    is_admin_logged_in = 0;
    printf("관리자 로그아웃되었습니다.\n");
}

int main() {
    struct Book library[MAX_BOOKS];
    int book_count = 0;
    int choice;
    int id;

    printf("===== 도서관 관리 시스템 =====\n");

    while (1) {
        printf("\n=== 메인 메뉴 ===\n");
        if (is_admin_logged_in) {
            // 관리자 메뉴
            printf("1. 도서 추가\n");
            printf("2. 도서 삭제\n");
            printf("3. 도서 검색\n");
            printf("4. 도서 목록 표시\n");
            printf("5. 도서 대출\n");
            printf("6. 도서 반납\n");
            printf("7. 관리자 로그아웃\n");
            printf("8. 프로그램 종료\n");
        }
        else {
            // 일반 사용자 메뉴
            printf("1. 도서 검색\n");
            printf("2. 도서 목록 표시\n");
            printf("3. 도서 대출\n");
            printf("4. 도서 반납\n");
            printf("5. 관리자 로그인\n");
            printf("6. 프로그램 종료\n");
        }
        printf("선택: ");

        if (scanf("%d", &choice) != 1) {
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
            while (getchar() != '\n');
            continue;
        }

        if (is_admin_logged_in) {
            // 관리자 메뉴 처리
            switch (choice) {
            case 1:
                add_book(library, &book_count);
                break;
            case 2:
                delete_book(library, &book_count);
                break;
            case 3:
                search_book(library, book_count);
                break;
            case 4:
                display_books(library, book_count);
                break;
            case 5:
                borrow_book(library, book_count);
                break;
            case 6:
                return_book(library, book_count);
                break;
            case 7:
                admin_logout();
                break;
            case 8:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다.\n");
            }
        }
        else {
            // 일반 사용자 메뉴 처리
            switch (choice) {
            case 1:
                search_book(library, book_count);
                break;
            case 2:
                display_books(library, book_count);
                break;
            case 3:
                borrow_book(library, book_count);
                break;
            case 4:
                return_book(library, book_count);
                break;
            case 5:
                admin_login();
                break;
            case 6:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다.\n");
            }
        }
    }
}


void add_book(struct Book library[], int* book_count) {

    if (*book_count >= MAX_BOOKS) {
        printf("더 이상 도서를 추가할 수 없습니다.\n");
        return;
    }

    struct Book new_book;
    new_book.id = *book_count + 1;
    new_book.is_borrowed = 0;

    printf("도서 제목: ");
    scanf(" %[^\n]", new_book.title);
    printf("저자 이름: ");
    scanf(" %[^\n]", new_book.author);

    for (int i = 0; i < *book_count; i++) {
        if (strcmp(library[i].title, new_book.title) == 0) {
            printf("이미 등록된 도서입니다.\n");
            return;
        }
    }

    library[*book_count] = new_book;
    (*book_count)++;
    printf("도서가 추가되었습니다: %s (ID: %d)\n", new_book.title, new_book.id);
}

// 도서 삭제 함수 수정
void delete_book(struct Book library[], int* book_count) {
 
    int id;
    printf("삭제할 도서의 ID를 입력하세요: ");
    scanf("%d", &id);

    for (int i = 0; i < *book_count; i++) {
        if (library[i].id == id) {
            for (int j = i; j < *book_count - 1; j++) {
                library[j] = library[j + 1];
            }
            (*book_count)--;
            printf("도서가 삭제되었습니다.\n");
            return;
        }
    }
    printf("해당 ID의 도서를 찾을 수 없습니다.\n");
}

// 도서 검색 함수
void search_book(struct Book library[], int book_count) {
    char title[50];
    printf("검색할 도서 제목을 입력하세요: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < book_count; i++) {
        if (strcmp(library[i].title, title) == 0) {
            printf("도서 ID: %d\n", library[i].id);
            printf("제목: %s\n", library[i].title);
            printf("저자: %s\n", library[i].author);
            return;
        }
    }
    printf("해당 제목의 도서를 찾을 수 없습니다.\n");
}

// 도서 목록 표시 함수
void display_books(struct Book library[], int book_count) {
    if (book_count == 0) {
        printf("등록된 도서가 없습니다.\n");
        return;
    }

    printf("\n===== 도서 목록 =====\n");
    for (int i = 0; i < book_count; i++) {
        printf("ID: %d, 제목: %s, 저자: %s\n", library[i].id, library[i].title, library[i].author);
    }
}
// 도서 대출 함수
void borrow_book(struct Book library[], int book_count) {
    char title[50];
    printf("대출할 도서의 제목을 입력하세요: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < book_count; i++) {
        if (strcmp(library[i].title, title) == 0) {
            if (library[i].is_borrowed) {
                printf("'%s' 도서는 이미 대출 중입니다.\n", library[i].title);
                return;
            }
            library[i].is_borrowed = 1;
            printf("'%s' 도서가 대출되었습니다.\n", library[i].title);
            return;
        }
    }
    printf("해당 제목의 도서를 찾을 수 없습니다.\n"); 
}

void return_book(struct Book library[], int book_count) {
    char title[50];
    printf("반납할 도서의 제목을 입력하세요: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < book_count; i++) {
        if (strcmp(library[i].title, title) == 0) {
            if (library[i].is_borrowed) {
                printf("'%s' 도서가 반납되었습니다.\n", library[i].title);
                return;
            }
            library[i].is_borrowed = 0;
            printf("'%s' 도서가 반납되었습니다.\n", library[i].title);
            return;
        }
    }
    printf("해당 제목의 도서를 찾을 수 없습니다.\n");
}
