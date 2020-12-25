#include "../lib/aoc.h"


long int transform(long int current, long int subject, long int loop_size){
    for(int i=0; i<loop_size; i++){
        current *= subject;
        current %= 20201227;
    }
    return current;
}

int main (int argc, char *argv[]){
    long int ans1 = 0, ans2 = 0;

    long int key1 = 9789649;
    long int key2 = 3647239;

    long int guess = 1;
    long int i = 1;
    long int n1 = 0, n2 = 0;
    while (n1 * n2 == 0){
        guess = transform(guess, 7, 1); 
        if (guess == key1)
            n1 = i;
        if (guess == key2)
            n2 = i;
        i++;
    }

    ans1 = transform(1, key1, n2);
    std::cout << "Answer 1: " << ans1 << std::endl;

    return 0;
 }
