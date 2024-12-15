#include<stdio.h>

int fr[3];
void display();

int main()
{
    int p[12] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2}; 
    int i, j, fs[3];
    int index, k, l, flag1 = 0, flag2 = 0, pf = 0, frsize = 3;

    // Initialize frame array with -1 (empty)
    for(i = 0; i < 3; i++) {
        fr[i] = -1;
    }

    // Iterate over the pages
    for(j = 0; j < 12; j++) {
        flag1 = 0;
        flag2 = 0;

        // Check if the page is already in the frame
        for(i = 0; i < 3; i++) {
            if(fr[i] == p[j]) {
                flag1 = 1;
                flag2 = 1;
                break;
            }
        }

        // If the page is not found, replace a frame
        if(flag1 == 0) {
            // Try to find an empty frame
            for(i = 0; i < 3; i++) {
                if(fr[i] == -1) {
                    fr[i] = p[j];
                    flag2 = 1;
                    break;
                }
            }
        }

        // If no empty frame, replace the one that won't be used for the longest time
        if(flag2 == 0) {
            for(i = 0; i < 3; i++) {
                fs[i] = 0;
            }

            // Check for future references of each page in the frame
            for(k = j + 1, l = 1; l <= frsize - 1; l++, k++) {
                for(i = 0; i < 3; i++) {
                    if(fr[i] == p[k])
                        fs[i] = 1;
                }
            }

            // Replace the page that won't be used again
            for(i = 0; i < 3; i++) {
                if(fs[i] == 0) {
                    index = i;
                }
            }

            fr[index] = p[j];
            pf++;
        }

        // Display the current frame contents
        display();
    }

    // Output the total page faults
    printf("\nNo of page faults: %d", pf + frsize);
    return 0;
}

void display() {
    int i;
    printf("\n");
    for(i = 0; i < 3; i++) {
        printf("\t%d", fr[i]);
    }
}
