#include <stdio.h>
#include <stdlib.h>


struct ll_node {
    int value;
    struct ll_node *next;
};


// This overly complex code reads integers from stdin and places them in 
// a linked list. Then, it sums the items in the list and prints the result.
int main() {
    int user_inp = 0;
    int sum = 0;

    // Using a dummy head node
    struct ll_node *front = malloc(sizeof(struct ll_node));
    struct ll_node *current = front;
    current->value = 0;
    struct ll_node *front2 = front;
    struct ll_node *temp = fron2;

    while (scanf("%d", &user_inp) != EOF) {
        current->next = malloc(sizeof(struct ll_node));
        current = current->next;

        current->value = user_inp;
        current->next = NULL;

    }

    for (sum = 0; front != NULL; front = front->next) {
        sum += front->value;
        
    }
    while(temp != NULL){
        temp = temp->next;
        free(front2);
        front2 = temp;

    }
    printf("The sum of the inputs is %d.\n", sum);

    return 0;
}
