#include <stdio.h>
#include <limits.h>

#define MAX 100

// Search function to check if a page is present in the frame
int search(int page, int frame[], int f) {
    int i;
    for (i = 0; i < f; i++) {
        if (page == frame[i])
            return i;
    }
    return -1;
}

// OPTIMAL Page Replacement
int optimal(int pages[], int n, int f) {
    int frame[MAX];
    int i, j, k, fault = 0, last, idx;
    for (i = 0; i < f; i++) frame[i] = -1;

    for (i = 0; i < n; i++) {
        if (search(pages[i], frame, f) == -1) // page fault occurs 
        {
            idx = -1;
            last = i + 1;
            for (j = 0; j < f; j++) {
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k])
                        break;
                }
                if (k == n) {
                    // if a page in frame doesn't appear again, that will go out 
                    idx = j;
                    break;
                }
                if (k > last) {
                    // this is verifying if farthest occurrence is ahead of i+1
                    last = k;
                    idx = j;
                }
            }
            if (idx == -1)
                // if it is never used again, evict first one 
                idx = 0;
            frame[idx] = pages[i];
            fault++;
        }
    }
    return fault;
}

// FCFS (FIFO)
int fcfs(int pages[], int n, int f) {
    int frame[MAX], i, j = 0, fault = 0;
    for (i = 0; i < f; i++) frame[i] = -1;

    for (i = 0; i < n; i++) {
        if (search(pages[i], frame, f) == -1) // page fault occurs 
        {
            fault++;
            frame[j] = pages[i]; // moves orderwise in the frame
            j = (j + 1) % f;
        }
    }
    return fault;
}

// LRU (Least Recently Used)
int lru(int pages[], int n, int f) {
    int frame[MAX], recent[MAX];
    int idx, lru_idx, lastUsed, i, j, fault = 0;

    for (i = 0; i < f; i++) {
        frame[i] = -1;
        recent[i] = -1;
    }

    for (i = 0; i < n; i++) {
        idx = search(pages[i], frame, f);
        if (idx != -1) {
            // if page is in frame, update its last reference
            recent[idx] = i;
        } else {
            lru_idx = 0;
            lastUsed = INT_MAX;
            for (j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    // empty frame --> use immediately 
                    lru_idx = j;
                    break;
                }
                if (recent[j] < lastUsed) {
                    /* if the last used of the page is < previous page Last Used
                       then lastUsed idx should be updated, and lru_idx = j , which means that
                       the least recently used is frame[j] */
                    lastUsed = recent[j];
                    lru_idx = j;
                }
            }
            frame[lru_idx] = pages[i];
            recent[lru_idx] = i; // update last use of the newly added page 
            fault++;
        }
    }
    return fault;
}


// LFU (Least Frequently Used)
int lfu(int pages[], int n, int f) {
    int frame[MAX], freq[MAX], i, j, fault = 0;
    for (i = 0; i < f; i++) {
        frame[i] = -1;
        freq[i] = 0;
    }

    for (i = 0; i < n; i++) {
        int idx = search(pages[i], frame, f);
        if (idx != -1) {
            // if page is already in frame, increment frequency
            freq[idx]++;
        } else {
            int lfu_idx = -1, min_freq = INT_MAX;
            for (j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    // empty frame --> use immediately
                    lfu_idx = j;
                    break;
                }
                if (freq[j] < min_freq) {
                    // if frequency of page is less than current min, update
                    min_freq = freq[j];
                    lfu_idx = j;
                }
            }
            frame[lfu_idx] = pages[i];
            freq[lfu_idx] = 1; // reset frequency for new page
            fault++;
        }
    }
    return fault;
}

int main() {
    int pages[MAX], n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("\nPage Faults:\n");
    printf("OPTIMAL: %d\n", optimal(pages, n, f));
    printf("FCFS   : %d\n", fcfs(pages, n, f));
    printf("LRU    : %d\n", lru(pages, n, f));
    printf("LFU    : %d\n", lfu(pages, n, f));

    return 0;
}
