/* A program that generates 200 random integers, sorts them, then deletes the duplicates.
   By John Abdelmalek
   February 13 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct list
{
    int data;
    struct list * next;
    struct list * previous;
} list;

list * create_list(int * data_ptr)
{
    list * head = NULL;
    head = (list *) malloc(sizeof(list));
    head ->data = *data_ptr;
    head -> next = NULL;
    head -> previous = NULL;
   
    return head;
}

list * add_to_front(list * head, int * data_ptr)
{
    list * h = NULL;
    h = create_list(data_ptr);
    h -> next = head;
    head -> previous = h;
    h ->previous = NULL;
    return h;
}

int * number_generator(void)
{
    //int temp = 0;
    int * data_ptr = NULL;
    data_ptr = (int *) malloc(sizeof(int));
    *data_ptr = rand() % 50;
    return data_ptr;
}


list * list_generator(void)
{
    list * h = NULL;
    int counter;   // to track how many data ints are created. We want 200.
    int * data_ptr = NULL;

    for(counter = 0; counter < 200; counter++)
    {
        data_ptr = number_generator();
        if(counter == 0)
        {
            h = create_list(data_ptr);
        }
        else
        {
            h = add_to_front(h, data_ptr);
        }
    }

    free(data_ptr);
    data_ptr = NULL;

    return h;
}

list * bubble_sort(list * head)
{
    list * former = NULL;   //before first.
    list * first = NULL;
    list * second = NULL;
    list * third = NULL;
    list * latter = NULL;   //after third.
    int swap = 0;    //to keep track of how many node swaps occur while sorting

    first = head;
    second = head -> next;
    third = second -> next;
    latter = third -> next;
    
    while(second != NULL)
    {
        if(first -> data < second -> data)
        {
            former = first;
            first = second;
            //swap++;
            if(second -> next != NULL)
            {
                second = third;
            }
            else
            {
                second = NULL;
            }
            if(third != NULL && third -> next != NULL)
            {
                third = latter;
            }
            else
            {
                third = NULL;
            }
            if(latter != NULL)
            {
            latter = latter -> next;
            }
            else
            {
                latter = NULL;
            }
        }
        else if(first -> data > second -> data)
        {
            if(third != NULL)
            {
                first -> next = third;
            }
            else
            {
                first -> next = NULL;
            }
            first -> previous = second;
            if(third != NULL)
            {
                third -> previous = first;
            }
            second -> next = first;
            if(former != NULL)
            {
                second -> previous = former;
            }
            else
            {
                second -> previous = NULL;
            }
            if(former != NULL)
            {
                former -> next = second;
            }
            former = second;
            if(first -> next != NULL)
            {
                second = third;
            }
            else
            {
                second = NULL;
            }
            swap++;
            if(third != NULL && third -> next != NULL)
            {
                third = latter;
            }
            else
            {
                third = NULL;
            }
            if(latter != NULL && latter -> next != NULL)
            {
                latter = latter -> next;
            }
            else
            {
                latter = NULL;
            }
        }
        else if (first -> data == second -> data)
        {
            former = first;
            first = second;
            if(second -> next != NULL)
            {
                second = third;
            }
            else
            {
                second = NULL;
            }
            if(third != NULL && third -> next != NULL)
            {
                third = latter;
            }
            else
            {
                third = NULL;
            }
            if(latter != NULL && latter -> next != NULL)
            {
                latter = latter -> next;
            }
            else
            {
                latter = NULL;
            }
        }
        if(second == NULL)
        {
            while(first -> previous != NULL)
            {
                first = first -> previous;
            }
            former = NULL;
            second = first -> next;
            third = second -> next;
            latter = third -> next;
            if(swap != 0)
            {
                swap = 0;
            }
            else if(swap == 0)
            {
                break;
            }
        }
    }
 
    former = NULL;
    second = NULL;
    third = NULL;
    latter = NULL;

    return first;
}
   

list * delete_duplicates(list * h)
{
    list * first = NULL;
    list * second = NULL;
    list * third = NULL;

    first = h;
    second = first -> next;
    third = second -> next;

    while(second != NULL)
    {
        if(first -> data == second -> data)
        {
            if(second != NULL && second -> next != NULL)
            {
                first -> next = third;
                third -> previous = first;
                //free(second);
                second -> next = NULL;
                second -> previous = NULL;
                second = NULL;
                second = third;
                if(third -> next != NULL)
                {
                    third = third -> next;
                }
                else
                {
                    third = NULL;
                }
            }
            else if(second != NULL && second -> next == NULL)
            {
                first -> next = NULL;
                second -> previous = NULL;
                second = NULL;
            }
        }
        else
        {
            if(first -> next != NULL)
            {
                first = second;
            }
            if(second != NULL && second -> next != NULL)
            {
                second = third;
            }
            else if(second != NULL && second -> next == NULL)
            {
                second = NULL;
            }
            if(third != NULL && third -> next != NULL)
            {
                third = third -> next;
            }
            else if(third != NULL && third -> next == NULL)
            {
                third = NULL;
            }
        }
    }

    while(first -> previous != NULL)
    {
        first = first -> previous;
    }
   
    second = NULL;
    third = NULL;

    return first;
}

void free_list(list * h)
{
    list * temp = NULL;

    while(h != NULL)
    {
        temp = h;
        h = h -> next;
        temp -> next = NULL;
        temp -> previous = NULL;
        free(temp);
        temp = NULL;
    }
}

list * print_and_rewind(list * h)
{
    int counter = 0;
    list * temp = NULL;   ///to use to retrace list to its beginning after printing list.
    while(h != NULL)
    {
        printf("%d\t", h -> data);
        if(h -> next == NULL)
        {
            temp = h;
        }
        if(h -> next != NULL)
        {
            h = h -> next;
        }
        else
        {
            h = NULL;
        }
        counter++;
        if(counter % 5 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n");

    h = temp;
    while(h -> previous != NULL)
    {
        h = h -> previous;
    }
  
    h = h -> next;
    h = h -> previous;
    return h;
}

int main(void)
{
    srand(time(NULL));
    list * head = NULL;

    head = list_generator();

    printf("The generated list before sorting:\n");

    head = print_and_rewind(head);
 
    head = bubble_sort(head);

    printf("The sorted list:\n");

    head = print_and_rewind(head);

    head = delete_duplicates(head);

    printf("The sorted list after deleting duplicate numbers:\n");

    print_and_rewind(head);

    free_list(head);

    return 0;
}
