#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef int Key;

#define N 100000
#define INF N + 1

/*
 * Basic version, using infinity as sentinel
 * Refer to CLRS:
 * Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein. 
 * ``Introduction to Algorithms, Second Edition''. ISBN:0262032937. The MIT Press. 2001
 */
void msort(Key* xs, int l, int u) {
    int i, j, m;
    Key *as, *bs;
    if (u - l > 1) {
        m = l + (u - l) / 2;  /* avoid int overflow */
        msort(xs, l, m);
        msort(xs, m, u);
        as = (Key*) malloc(sizeof(Key) * (m - l + 1));
        bs = (Key*) malloc(sizeof(Key) * (u - m + 1));
        memcpy((void*)as, (void*)(xs + l), sizeof(Key) * (m - l));
        memcpy((void*)bs, (void*)(xs + m), sizeof(Key) * (u - m));
        as[m - l] = bs[u - m] = INF;
        for (i = j = 0; l < u; ++l)
            xs[l] = as[i] < bs[j] ? as[i++] : bs[j++];
        free(as);
        free(bs);
    }
}

/* test */
int cmp(const void* x, const void* y) {
    return *(Key*)x - *(Key*)y;
}

void testqsort(void (*fsort)(Key*, int, int)) {
    int i, j, n, xs[N], ys[N];
    for (j = 0; j < 100; ++j) {
        for (i = 0, n = rand() % N; i < n; ++i)
            xs[i] = rand() % N;
        memcpy((void*)ys, (const void*)xs, n * sizeof(int));
        qsort(xs, n, sizeof(int), cmp);
        fsort(ys, 0, n);
        assert(!memcmp(xs, ys, n * sizeof(int)));
    }
}

int main() {
    testqsort(msort);
    printf("basic version tested\n");
    return 0;
}
