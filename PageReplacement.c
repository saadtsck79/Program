#include <stdio.h>
void fifoPageReplacement(int pageRequests[], int numRequests, int numFrames) {
    int pageFaults = 0;
    int frames[numFrames];
    int front = 0;
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }
    for (int i = 0; i < numRequests; i++) {
        int page = pageRequests[i];
        int found = 0;
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int emptySlot = -1;
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    emptySlot = j;
                    break;
                }
            }
            if (emptySlot != -1) {
                frames[emptySlot] = page;
            } else {
                frames[front] = page;
                front = (front + 1) % numFrames;
            }
            pageFaults++;
        }
        printf("Page Requested: %d | Frames: ", page);
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}
int main() {
    int pageRequests[] = {1, 3, 0, 3, 5, 6};
    int numRequests = sizeof(pageRequests) / sizeof(pageRequests[0]);
    int numFrames = 3;
    printf("FIFO Page Replacement Algorithm\n");
    fifoPageReplacement(pageRequests, numRequests, numFrames);
    return 0;
}