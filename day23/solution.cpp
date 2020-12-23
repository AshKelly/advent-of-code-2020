#include "../lib/aoc.h"

class Cup {
    public:
        Cup * next;
        int value;

        Cup (int v) : value(v) {};
        void set_next(Cup * n){
            next = n;
        };
};

std::vector<Cup> solve(std::vector<Cup> cups, int padding, int reps){
    for(int i=10; i<=padding; i++)
        cups.push_back(Cup(i));

    for(size_t i=0; i<cups.size()-1; i++)
        cups[i].set_next(&cups[i+1]);
    cups[cups.size()-1].set_next(&cups[0]);

    Cup * curr = &cups[0];
    Cup * start, * end, * destination;
    for(int i=0; i<reps; i++){
        start = curr->next;

        int target = curr->value - 1;
        if (target == 0)
            target = cups.size();

        // Select pickup
        end = curr;
        for(int j=0; j<3; j++){
            end = end->next;
        }

        // Find destination cup by ensuring our target is not in the pickup
        bool found = false;
        Cup * temp;
        while (!found){
            temp = start;
            found = true;

            for(int j=0; j<3; j++){
                if (temp->value == target){
                    target--;
                    if (target == 0)
                        target = cups.size();

                    found = false;
                    break;
                }
                temp = temp->next;
            }
        }

        // The first few cups aren't in order, so I must search for the cups
        // however, after cup 10, every cup is in order!
        if (target >= 10){
            destination = &cups[target-1];
        }
        else{
            for(auto &cup : cups){
                if (cup.value == target){
                    destination = &cup;
                    break;
                }
            }
        }

        // Remove the elements
        curr->next = end->next;

        // Reinsert after destination
        temp = destination->next;
        destination->next = start;
        end->next = temp;

        // Move to next cup
        curr = curr->next;
    }


    return cups;
}

int main (int argc, char *argv[]){
    long int ans1 = 0, ans2 = 1;

    std::vector<Cup> cups = {1, 9, 3, 4, 6, 7, 2, 5, 8};
    std::vector<Cup> cups1 = solve(cups, 0, 100);
    std::vector<Cup> cups2 = solve(cups, 1000000, 10000000);

    /* Find cup 1 */
    Cup * start;
    for(auto &cup : cups1){
        if (cup.value == 1){
            start = &cup;
            break;
        }
    }
    /* Print all the numbers after cup 1 */
    std::cout << "Answer 1: ";
    start = start->next;
    for(int j=0; j<8; j++){
        std::cout << start->value;
        start = start->next;
    }
    std::cout << std::endl;


    /* Find cup 1 */
    for(auto &cup : cups2){
        if (cup.value == 1){
            start = &cup;
            break;
        }
    }
    /* Multiply two numbers afterwards */
    for(int j=0; j<3; j++){
        ans2 *= start->value;
        start = start->next;
    }
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}