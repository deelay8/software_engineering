#include "bptree.h"
#include <vector>
#include <sys/time.h>
#include <random>

// Function to get current time
struct timeval cur_time(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t;
}

// Function to print the tree recursively
void print_tree_core(NODE *n)
{
    printf("["); 
    for (int i = 0; i < n->nkey; i++) {
        if (!n->isLeaf) print_tree_core(n->chi[i]); 
        printf("%d", n->key[i]); 
        if (i != n->nkey-1 && n->isLeaf) putchar(' ');
    }
    if (!n->isLeaf) print_tree_core(n->chi[n->nkey]);
    printf("]");
}

// Function to print the tree
void print_tree(NODE *node)
{
    print_tree_core(node);
    printf("\n");
    fflush(stdout);
}

// Function to find the leaf node for a given key
NODE *find_leaf(NODE *node, int key)
{
    int kid;

    if (node->isLeaf) return node;
    for (kid = 0; kid < node->nkey; kid++) {
        if (key < node->key[kid]) break;
    }

    return find_leaf(node->chi[kid], key);
}

// Function to insert a key and data in a leaf node
NODE *insert_in_leaf(NODE *leaf, int key, DATA *data)
{
    int i;
    if (key < leaf->key[0]) {
        for (i = leaf->nkey; i > 0; i--) {
            leaf->chi[i] = leaf->chi[i-1] ;
            leaf->key[i] = leaf->key[i-1] ;
        } 
        leaf->key[0] = key;
        leaf->chi[0] = (NODE *)data;
    }
    else {
        for (i = 0; i < leaf->nkey; i++) {
            if (key < leaf->key[i]) break;
        }
        for (int j = leaf->nkey; j > i; j--) {        
            leaf->chi[j] = leaf->chi[j-1] ;
            leaf->key[j] = leaf->key[j-1] ;
        }
        leaf->key[i] = key;
        leaf->chi[i] = (NODE *)data;

    }
    leaf->nkey++;
    return leaf;
}

// Function to insert key and pointer into temporary structure
void insert_in_temp(TEMP *temp, int key, void *ptr)
{
    int i;
    if (key < temp->key[0]){
        for (i = temp->nkey; i > 0; i--){
            temp->key[i] = temp->key[i-1];
            temp->chi[i] = temp->chi[i-1];
        }
        temp->key[0] = key;
        temp->chi[0] = (NODE *)ptr;
    }
    else{
        for(i = 0; i < temp->nkey; i++){
            if (key < temp->key[i]){
                break;
            }
        }
        for(int j = temp->nkey; j > i; j--){
            temp->key[j] = temp->key[j-1];
            temp->chi[j] = temp->chi[j-1];
        }
        temp->key[i] = key;
        temp->chi[i] = (NODE *)ptr;
    }
    temp->nkey++;
}

// Function to allocate a new leaf node
NODE *alloc_leaf(NODE *parent)
{
    NODE *node;
    if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
    node->isLeaf = true;
    node->parent = parent;
    node->nkey = 0;
    return node;
}

// Function to insert a key, a leaf, and a right node in the parent
void insert_in_parent(NODE *leaf, int key, NODE *right)
{
    if(leaf == Root){
        NODE *newRoot;
        newRoot = alloc_leaf(NULL);
        newRoot->key[0] = key;
        newRoot->chi[0] = leaf;
        newRoot->chi[1] = right;
        newRoot->isLeaf = false;
        newRoot->nkey = 1;
        Root = newRoot;
        leaf->parent = Root;
        right->parent = Root;
    }
    else{
        NODE *parent = leaf->parent;

        if(parent->nkey < (N-1)){
            int i;
        
            for (i = 0; i < parent->nkey; i++) {
                if (key < parent->key[i]) break;
            }

            for (int j = parent->nkey; j > i; j--){
                parent->key[j] = parent->key[j-1];
            }
            for (int j = parent->nkey + 1; j > i + 1; j--){
                parent->chi[j] = parent->chi[j-1];
            }
            parent->key[i] = key;
            parent->nkey++;
            parent->chi[i+1] = right;
            right->parent = parent;
        }

        else{
            NODE *newInternal = alloc_leaf(parent->parent);
            newInternal->isLeaf = false;
            TEMP temp;
            temp.nkey = 0;

            for(int i = 0; i < parent->nkey; i++) {
                temp.chi[i] = parent->chi[i];
                temp.key[i] = parent->key[i];
                temp.nkey++;
            }
            temp.chi[parent->nkey] = parent->chi[parent->nkey];

            int i;
            for (i = 0; i <= temp.nkey; i++){
                if (temp.chi[i] == leaf){
                    for (int j = temp.nkey; j > i; j--){
                        temp.chi[j + 1] = temp.chi[j];
                        temp.key[j] = temp.key[j - 1];
                    }
                    temp.key[i] = key;
                    temp.chi[i + 1] = right;
                }
            }
            temp.nkey++;

            for(int i = 0; i <parent->nkey; i++){
                parent->key[i] = 0;
                parent->chi[i] = NULL;
            }
            parent->chi[parent->nkey] = NULL;
            parent->nkey = 0;

            for (int i = 0; i <= (N/2); i++){
                parent->chi[i] = temp.chi[i];
                parent->key[i] = temp.key[i];
            }
            parent->nkey = N/2;

            newInternal->nkey = 1;
            for(int i = (N/2) + 1; i <= N; i++){
                newInternal->chi[i-((N/2)+1)] = temp.chi[i];
                newInternal->key[i-((N/2)+1)] = temp.key[i];
            }
            for(int i = 0; i <=newInternal->nkey; i++){
                newInternal->chi[i]->parent = newInternal;
            }

            int internal_key = temp.key[N/2];

            insert_in_parent(parent, internal_key, newInternal);
        }
    }
}

// Function to insert a key and data into the B+ tree
void insert(int key, DATA *data)
{
    NODE *leaf;

    if (Root == NULL) {
        leaf = alloc_leaf(NULL);
        Root = leaf;
    }
    else {
        leaf = find_leaf(Root, key);
    }
    if (leaf->nkey < (N-1)) {
        insert_in_leaf(leaf, key, data);
    }
    else {
        NODE *newLeaf = alloc_leaf(leaf->parent);

        TEMP temp;
        temp.nkey = 0;
        
        int i;
        for(i = 0; i < leaf->nkey; i++){
            temp.key[i] = leaf->key[i];
            temp.chi[i] = leaf->chi[i];
            temp.nkey++;
        }
        temp.chi[i] = leaf->chi[i];

        insert_in_temp(&temp, key, data);

        newLeaf->chi[N-1] = leaf->chi[N-1];
        leaf->chi[N-1] = newLeaf;

        for(int i = 0; i <leaf->nkey; i++){
            leaf->key[i] = 0;
            leaf->chi[i] = NULL;
        }
        leaf->nkey = 0;
        newLeaf->nkey = 0;

        for (int i = 0; i < N/2; i++){
            leaf->key[i] = temp.key[i];
            leaf->chi[i] = temp.chi[i];
            leaf->nkey++;
        }

        for(int i = N/2; i < N; i++){
            newLeaf->key[i - (N/2)] = temp.key[i];
            newLeaf->chi[i - (N/2)] = temp.chi[i];
            newLeaf->nkey++;
        }

        int k = newLeaf->key[0];

        insert_in_parent(leaf, k, newLeaf);

    }
}

// Function to initialize the root of the tree
void init_root(void)
{
    Root = NULL;
}

// Function to interactively get a key from the user
int interactive()
{
    int key;

    std::cout << "Key: ";
    std::cin >> key;

    return key;
}

int main(int argc, char *argv[])
{
    struct timeval begin, end;

    init_root();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    printf("-----Insert-----\n");
    begin = cur_time();
    
    for(int i = 0; i < 1000000; i++) {
        insert(dis(gen), NULL);
    }
    print_tree(Root);

    end = cur_time();

    return 0;
}
