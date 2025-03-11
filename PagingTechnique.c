#include<stdio.h>
#define MAX_PAGES 100
void simulatePaging() {
    int memorySize;
    int pageSize;
    int numFrames;
    int pageTable[MAX_PAGES];
    printf("Enter the memory size: ");
    scanf("%d", &memorySize);
    printf("Enter the page size: ");
    scanf("%d", &pageSize);
    numFrames = memorySize / pageSize;
    printf("Number of frames: %d\n", numFrames);
    for(int i=0; i<MAX_PAGES; i++) {
        pageTable[i] = -1;
    }
    printf("Enter the page table (frame number for each page):\n");
    printf("Enter -1 if the page is not in any frame.\n");
    for(int i=0; i<MAX_PAGES; i++) {
        printf("Page %d: ", i);
        scanf("%d", &pageTable[i]);
        if(pageTable[i] >= numFrames) {
            printf("Invalid frame number. Please enter a number less than %d.\n", numFrames);
            i--;
        }
    }
    int choice = 1;
    while(choice == 1) {
        int pageNo;
        int offset;
        printf("Enter the logical address (page number and offset): ");
        scanf("%d %d", &pageNo, &offset);
        if(pageTable[pageNo] == -1) {
            printf("The requires page is not available in any frame.\n");
        } else {
            int frameNo = pageTable[pageNo];
            int physicalAddress = (frameNo * pageSize) + offset;
            printf("Physical address: Frame %d, Offset %d\n", frameNo, offset);
        }
        printf("Do you want to continue? (1/0): ");
        scanf("%d", &choice);
    }
}
int main() {
    simulatePaging();
    return 0;
}