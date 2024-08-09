#include <stdio.h>


int main() {
    int x = 5;
    int y;
    y = ++x;
    // will apply operation before value is used
    printf("postfix x=%d, y=%d\n",x,y);
    
    x = 5;
    // will apply operation after value is used
    y = x++;
    printf("prefix x=%d, y=%d\n",x,y);
    return 0;
}
