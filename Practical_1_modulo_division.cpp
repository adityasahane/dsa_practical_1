#include<iostream>
using namespace std;

struct Node
{
    string data;
    struct Node *next;
};

void add_chain(struct Node **chain, int index, string name)
{
    if(chain[index] == NULL)
    {
        struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
        newNode->data = name;
        newNode->next = NULL;
        chain[index] = newNode;
    }
    else
    {
        struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
        newNode->data = name;
        newNode->next = NULL;
        struct Node *ptr = chain[index];

        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
        
    }
}

void print_hashtable(string *actual_hastable, struct Node **chain, int size)
{
    for(int i = 0; i < size; i++)
    {
        cout<<i<<") ";
        if(actual_hastable[i] != "nothing")
        {
            cout<<actual_hastable[i];
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


int hash_function(int sum, int size)
{
    return sum % size;
}


void search_name(string name, string *actual_hastable, struct Node **chain, int size)
{
    bool found = 0;
    int name_ascii_sum = 0;

    int ind = 0;
    char c;

    while(name[ind] != '\0')
    {
        c = name[ind];
        name_ascii_sum += (int)c;
        ind++;
    }

    int index = hash_function(name_ascii_sum, size);
    cout<<index<<endl;

    if(actual_hastable[index] != "nothing")
    {
        if(actual_hastable[index] == name)
        {
            cout<<name<<" found at "<< index<<endl;
            found = 1;
        }
        else if(chain[index] != NULL)
        {
            struct Node *ptr = chain[index];
            int counter_posititon = 2;

            while(ptr != NULL)
            {
                if(ptr->data == name)
                {
                    cout<<name<<" found at "<<index<<", "<<counter_posititon<<endl;
                    found = 1;
                    break;
                }
                ptr = ptr->next;
                counter_posititon++;
            }
        }
    }

    if(!found)
        cout<<name<<" not found."<<endl;
}


int main()
{
    int n;
    cout<<"How many names you want to insert: ";
    cin>>n;

    string arr[n];
    int ascii_sum[n];
    string actual_hastable[n];
    struct Node *chain[n];

    cout<<"Enter n Values: ";

    for(int i = 0; i < n; i++)
    {
        cin>>arr[i];
        actual_hastable[i] = "nothing";
        chain[i] = NULL;
    }

    for(int i = 0; i < n; i++)
    {
        int ind = 0;
        char c;
        ascii_sum[i] = 0;

        while(arr[i][ind] != '\0')
        {
            c = arr[i][ind];
            ascii_sum[i] += (int)c;
            ind++;
        }
    }

    // for(int i = 0; i < n; i++)
    // {
    //     cout<<ascii_sum[i]<<endl;
    // }

    cout<<endl;

    for(int i = 0; i <n; i++)
    {
        int index = hash_function(ascii_sum[i], n);
        cout<<arr[i]<<" will be stored at "<<index<<endl;

        if(actual_hastable[index] == "nothing")
        {
            actual_hastable[index] = arr[i];
        }
        else
        {
            add_chain(chain, index, arr[i]);
        }
    }


    cout<<endl<<"HashTable is: "<<endl<<endl;

    print_hashtable(actual_hastable, chain, n);

    search_name("vivek", actual_hastable, chain, n);

    free_storage(chain, n);

    return 0;
}