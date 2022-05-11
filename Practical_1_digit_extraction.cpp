#include<iostream>
#include<string.h>
using namespace std;

struct Node
{
    int data;
    struct Node *next;
};


void add_chain(struct Node **chain, int number, int index)
{
    if(chain[index] == NULL)
    {
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = number;
        newNode->next = NULL;
        chain[index] = newNode;
    }
    else
    {
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = number;
        newNode->next = NULL;

        struct Node *ptr = chain[index];

        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
}

void print_hashtable(int *actual_hashtable, struct Node **chain)
{
    for(int i = 0; i < 100; i++)
    {
        cout<<i<<") ";
        if(actual_hashtable[i] != -1)
        {
            cout<<actual_hashtable[i];
            if(chain[i] != NULL)
            {
                struct Node *ptr = chain[i];
                while(ptr != NULL)
                {
                    cout<<" --> "<<ptr->data;
                    ptr = ptr->next;
                }
            }
        }
        cout<<endl;
    }
    cout<<endl;
}


void free_storage(struct Node **chain, int size)
{
    for(int i = 0; i<size; i++)
    {
        if(chain[i] != NULL)
        {
            struct Node *ptr = chain[i];
            struct Node *nextptr;
            
            while(ptr != NULL)
            {
                nextptr = ptr->next;
                free(ptr);
                ptr = nextptr;
            }
        }
    }
    cout<<endl<<"Memory Released..."<<endl;
}


int digit_extraction(int number)
{
    string stringNum = to_string(number);
    string index = "";

    index += stringNum[1];
    index += stringNum[3];

    return stoi(index);
}


void search_number(int number, int *actual_hastable, struct Node **chain, int size)
{
    bool found = 0;

    int index = digit_extraction(number);

    if(actual_hastable[index] != -1)
    {
        if(actual_hastable[index] == number)
        {
            cout<<number<<" found at "<< index<<endl;
            found = 1;
        }
        else if(chain[index] != NULL)
        {
            struct Node *ptr = chain[index];
            int counter_posititon = 2;

            while(ptr != NULL)
            {
                if(ptr->data == number)
                {
                    cout<<number<<" found at "<<index<<", "<<counter_posititon<<endl;
                    found = 1;
                    break;
                }
                ptr = ptr->next;
                counter_posititon++;
            }
        }
    }

    if(!found)
        cout<<number<<" not found."<<endl;
}


int main()
{
    int size;
    cout<<"Enter no. of Elements: ";
    cin>>size;

    int arr[size];
    int actual_hastable[100];
    struct Node *chain[100];

    for(int i = 0; i<size; i++)
    {
        cout<<"Enter Number "<<i+1<<" :";
        cin>>arr[i];
    }

    for(int i = 0; i<100; i++)
    {
        actual_hastable[i] = -1;
        chain[i] = NULL;
    }

    for(int i = 0; i<size; i++)
    {
        int index = digit_extraction(arr[i]);
        cout<<arr[i]<<" will be stored at "<<index<<endl;
        
        if(actual_hastable[index] == -1)
        {
            actual_hastable[index] = arr[i];
        }
        else
        {
            add_chain(chain, arr[i], index);
        }
    }

    cout<<endl<<"HashTable is: "<<endl<<endl;

    print_hashtable(actual_hastable, chain);

    search_number(1234, actual_hastable, chain, size);

    free_storage(chain, size);

}