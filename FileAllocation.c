#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILES 10
#define MAX_BLOCKS 1000
struct File {
    char name[20];
    int start_block;
    int length;
};
struct File file_table[MAX_FILES];
int block_status[MAX_BLOCKS];
int num_files = 0;
void initialize_blocks() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        block_status[i] = 0;
    }
}
void create_file() {
    if (num_files >= MAX_FILES) {
        printf("Error: Maximum file limit reached.\n");
        return;
    }
    struct File new_file;
    printf("Enter the name of the file: ");
    scanf("%s", new_file.name);
    printf("Enter the starting block of the file: ");
    scanf("%d", &new_file.start_block);
    printf("Enter the length of the file: ");
    scanf("%d", &new_file.length);
    for (int i = new_file.start_block; i < new_file.start_block + new_file.length; i++) {
        if (i >= MAX_BLOCKS || block_status[i] == 1) {
            printf("Block already in use or out of bounds.\n");
            return;
        }
    }
    for (int i = new_file.start_block; i < new_file.start_block + new_file.length; i++) {
        block_status[i] = 1;
    }
    file_table[num_files++] = new_file;
    printf("File %s allocated disk space starting at block %d.\n", new_file.name, new_file.start_block);
}
void delete_file() {
    char name[20];
    printf("Enter the name of the file to delete: ");
    scanf("%s", name);
    for (int i = 0; i < num_files; i++) {
        if (strcmp(file_table[i].name, name) == 0) {
            for (int j = file_table[i].start_block; j < file_table[i].start_block + file_table[i].length; j++) {
                block_status[j] = 0;
            }
            for (int k = i; k < num_files - 1; k++) {
                file_table[k] = file_table[k + 1];
            }
            num_files--;
            printf("File %s deleted successfully.\n", name);
            return;
        }
    }
    printf("File not found.\n");
}
void display_fat() {
    printf("File Allocation Table:\n");
    printf("File Name\tStart Block\tLength\n");
    for (int i = 0; i < num_files; i++) {
        printf("%s\t\t%d\t\t%d\n", file_table[i].name, file_table[i].start_block, file_table[i].length);
    }
}
int main() {
    initialize_blocks();
    int choice;
    while (1) {
        printf("\nContiguous File Allocation\n");
        printf("1. File Creation\n");
        printf("2. File Deletion\n");
        printf("3. Display File Allocation Table\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: create_file(); break;
            case 2: delete_file(); break;
            case 3: display_fat(); break;
            case 4: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}