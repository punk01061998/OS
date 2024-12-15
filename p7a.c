//FIRST IN FIRST OUT
#include <stdio.h>

int fr[3]; // Frame array to hold the pages

void display() {
    int i;
    printf("\n");
    for(i = 0; i < 3; i++) {
        printf("%d\t", fr[i]);
    }
}

void main() {
    int i, j, page[12] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};
    int flag1 = 0, flag2 = 0, pf = 0, frsize = 3, top = 0;

    // Initialize frames with -1
    for(i = 0; i < 3; i++) {
        fr[i] = -1;
    }

    // Loop through the pages
    for(j = 0; j < 12; j++) {
        flag1 = 0; 
        flag2 = 0;

        // Check if the page is already in any frame
        for(i = 0; i < frsize; i++) {
            if(fr[i] == page[j]) {
                flag1 = 1;  // Page found, no page fault
                flag2 = 1;
                break;
            }
        }

        // If page is not found in any frame, handle page fault
        if(flag1 == 0) {
            for(i = 0; i < frsize; i++) {
                if(fr[i] == -1) {  // Empty frame found
                    fr[i] = page[j]; 
                    flag2 = 1; 
                    break;
                }
            }
        }

        // If no empty frame is available, replace the oldest page
        if(flag2 == 0) {
            fr[top] = page[j];
            top++;
            pf++;  // Increase page fault count
            if(top >= frsize) {
                top = 0;  // Reset top to 0 if it exceeds the number of frames
            }
        }

        // Display the current frame contents
        display();
    }

    // Print total page faults, including initial empty frames
    printf("\nNumber of page faults: %d", pf + frsize);
}
