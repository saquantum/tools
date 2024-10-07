#define MAX_TOLERANCE 0.001

void copyboard(board* dest, board* source);
bool three_in_a_sequence(int x, int y, board* brd);
bool counting(int x, int y, board* brd);
bool recursion(int index, board* brd, board* temp, int* solutions);
void printboard(board* brd);

bool solve_board(board* brd) {
    int solutions = 0;
    board temp;
    copyboard(&temp,brd);
    return !recursion(0, brd, &temp, &solutions);
}

bool recursion(int index, board* brd, board* temp, int* solutions) {
    int sz = brd->sz;
    int x = index % sz;
    int y = index / sz;

    if (index>=sz*sz) { // escape recursion
        copyboard(brd, temp);
        (*solutions)++;
        if (*solutions > 1) {  
            return true; // 2: for the second time we find a solution, it returns a true
        }
        return false; // 1: for the first time we find a solution, it returns a false
    }
    // skip an occupied cell 
    if (temp->b2d[y][x] != UNK) {
        return recursion(index + 1, brd, temp, solutions);
    }

    static char elements[] = {ZERO,ONE};
    for (int i = 0; i < 2; i++) {
        char guess = elements[i];
        temp->b2d[y][x] = guess;
        // check validity of current guess 
        if (three_in_a_sequence(x, y, temp) && counting(x, y, temp)) {
            /* go to the next guess
               1: since its a false, we wont go inside the following if
               2: now its a true, and we immediately finish current recursion by returning a true
                    and subsequently finish all parent recursions since we'll always go inside  */
            if (recursion(index + 1, brd, temp, solutions)) {
                if (*solutions > 1) {
                    return true;  // early escape in case of multiple solutions
                }
            }
        }
        // backtracking: reset the current cell and go back to its parent
        temp->b2d[y][x] = UNK;
    }
    // 0: if fails to find any solution
    return false;
}

void copyboard(board* dest, board* source) {
    int sz = source->sz;
    dest->sz = sz;
    for (int j = 0; j < sz; j++) {
        for (int i = 0; i < sz; i++) {
            dest->b2d[j][i] = source->b2d[j][i];
        }
    }
}

bool str2board(board* brd, char* str) {
    // edge cases
    if (str == NULL) {
        return false;
    }
    if (strlen(str) <= 0) {
        return false;
    }

    double sz_f = sqrt((double)strlen(str));
    // the size of the board must be an integer
    if ((fabs(sz_f - floor(sz_f))) > MAX_TOLERANCE || (fabs(sz_f - ceil(sz_f))) > MAX_TOLERANCE) {
        return false;
    }
    int sz = (int)round(sz_f);
    // the size of the board must be an even number to satisfy the counting rule
    if (sz % 2 != 0) {
        return false;
    }
    brd->sz = sz;
    for (int j = 0; j < sz; j++) {
        for (int i = 0; i < sz; i++) {
            brd->b2d[j][i] = str[j * sz + i];
        }
    }
    return true;
}

void board2str(char* str, board* brd) {
    int N = brd->sz;
    // edge cases
    if (N == 0) {
        str[0] = '\0';
        return;
    }
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            str[j * N + i] = brd->b2d[j][i];
        }
    }
    str[N * N] = '\0';
}

bool three_in_a_sequence(int x, int y, board* brd) {
    // return false if three in a sequence
    int sz = brd->sz;
    // x-2 x-1 x
    if (0 <= x - 2 && brd->b2d[y][x] != UNK && brd->b2d[y][x] == brd->b2d[y][x - 2] && brd->b2d[y][x] == brd->b2d[y][x - 1]) {
        return false;
    }
    // x-1 x x+1
    if (0 <= x - 1 && x + 1 < sz && brd->b2d[y][x] != UNK \
        && brd->b2d[y][x] == brd->b2d[y][x - 1] && brd->b2d[y][x] == brd->b2d[y][x + 1]) {
        return false;
    }
    // x x+1 x+2
    if (x + 2 < sz && brd->b2d[y][x] != UNK && brd->b2d[y][x] == brd->b2d[y][x + 1] && brd->b2d[y][x] == brd->b2d[y][x + 2]) {
        return false;
    }
    // y-2 y-1 y
    if (0 <= y - 2 && brd->b2d[y][x] != UNK && brd->b2d[y][x] == brd->b2d[y - 2][x] && brd->b2d[y][x] == brd->b2d[y - 1][x]) {
        return false;
    }
    // y-1 y y+1
    if (0 <= y - 1 && y + 1 < sz && brd->b2d[y][x] != UNK \
        && brd->b2d[y][x] == brd->b2d[y - 1][x] && brd->b2d[y][x] == brd->b2d[y + 1][x]) {
        return false;
    }
    // y y+1 y+2
    if (y + 2 < sz && brd->b2d[y][x] != UNK && brd->b2d[y][x] == brd->b2d[y + 1][x] && brd->b2d[y][x] == brd->b2d[y + 2][x]) {
        return false;
    }
    return true;
}

bool counting(int x, int y, board* brd) {
    // return false if the numbers of zeros and ones in a line differ
    int sz = brd->sz;
    // count zeros and ones of that row
    int count0 = 0;
    int count1 = 0;
    for (int i = 0; i < sz; i++) {
        if (brd->b2d[y][i] == ZERO) {
            count0++;
        }
        if (brd->b2d[y][i] == ONE) {
            count1++;
        }
    }
    if (count0 > sz / 2 || count1 > sz / 2) {
        return false;
    }
    // count zeros and ones of that column
    count0 = 0;
    count1 = 0;
    for (int j = 0; j < sz; j++) {
        if (brd->b2d[j][x] == ZERO) {
            count0++;
        }
        if (brd->b2d[j][x] == ONE) {
            count1++;
        }
    }
    if (count0 > sz / 2 || count1 > sz / 2) {
        return false;
    }
    return true;
}

void printboard(board* brd) {
    for (int j = 0; j < brd->sz; j++) {
        for (int i = 0; i < brd->sz; i++) {
            printf("%c ", brd->b2d[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

void test(void)
{
    board b;
    char str[BOARDSTR] = {0};

    assert(str2board(&b, "111..011.01.1001"));
    for (int j = 0; j < b.sz; j++) {
        for (int i = 0; i < b.sz; i++) {
            str[j * b.sz + i] = three_in_a_sequence(i, j, &b) + '0';
        }
    }
    assert(!strcmp(str, "0001100110011011"));

    for (int j = 0; j < b.sz; j++) {
        for (int i = 0; i < b.sz; i++) {
            str[j * b.sz + i] = counting(i, j, &b) + '0';
        }
    }
    assert(!strcmp(str, "0000100110011001"));
}
