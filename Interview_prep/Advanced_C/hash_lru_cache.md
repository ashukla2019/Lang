# Advanced C Interview Coding Solutions - Part 3

# Hash Table + LRU Cache

Topics covered:

1. Hash table design
2. Hash function
3. Collision handling using chaining
4. Insert
5. Search
6. Delete
7. LRU cache design
8. O(1) get()
9. O(1) put()

---

# 1. Hash Table Implementation

## Concept

A hash table stores data using:

```
Key ---> Hash Function ---> Index ---> Bucket
```

Example:

```
Key = 25

hash(25)

25 % 10 = 5


Bucket[5]

```

---

# Collision Handling

Two keys may produce same index.

Example:

```
15 % 10 = 5

25 % 10 = 5

```

Solution:

## Separate Chaining

Each bucket contains a linked list.

```
Bucket[5]

 |
 v

15 -> 25 -> 35

```

---

# Data Structures

## Hash Node

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 100


typedef struct HashNode
{
    int key;

    int value;

    struct HashNode *next;

}HashNode;
```

---

## Hash Table

```c
typedef struct
{
    HashNode *table[TABLE_SIZE];

}HashTable;
```

---

# 2. Hash Function

Simple integer hash:

```c
int hash_function(int key)
{
    return key % TABLE_SIZE;
}
```

---

# 3. Create Hash Node

```c
HashNode *create_hash_node(int key,
                           int value)
{
    HashNode *node =
        malloc(sizeof(HashNode));


    if(node == NULL)
        return NULL;


    node->key = key;

    node->value = value;

    node->next = NULL;


    return node;
}
```

---

# 4. Initialize Hash Table

```c
HashTable *create_hash_table()
{
    HashTable *ht =
        malloc(sizeof(HashTable));


    if(ht == NULL)
        return NULL;


    for(int i=0;i<TABLE_SIZE;i++)
    {
        ht->table[i] = NULL;
    }


    return ht;
}
```

---

# 5. Insert Into Hash Table

## Algorithm

1. Calculate index
2. Check existing key
3. Update value if found
4. Otherwise add node


---

## Implementation

```c
void hash_insert(HashTable *ht,
                 int key,
                 int value)
{
    int index =
        hash_function(key);


    HashNode *current =
        ht->table[index];


    while(current)
    {
        if(current->key == key)
        {
            current->value = value;

            return;
        }


        current = current->next;
    }


    HashNode *node =
        create_hash_node(key,value);


    node->next =
        ht->table[index];


    ht->table[index] = node;
}
```

---

# 6. Search In Hash Table

```c
int hash_search(HashTable *ht,
                int key,
                int *value)
{
    int index =
        hash_function(key);


    HashNode *current =
        ht->table[index];


    while(current)
    {
        if(current->key == key)
        {
            *value = current->value;

            return 1;
        }


        current=current->next;
    }


    return 0;
}
```

---

# 7. Delete From Hash Table

```c
void hash_delete(HashTable *ht,
                 int key)
{
    int index =
        hash_function(key);


    HashNode *current =
        ht->table[index];


    HashNode *previous = NULL;


    while(current)
    {
        if(current->key == key)
        {
            if(previous)
            {
                previous->next =
                    current->next;
            }
            else
            {
                ht->table[index] =
                    current->next;
            }


            free(current);

            return;
        }


        previous = current;

        current = current->next;
    }
}
```

---

# Hash Table Complexity

Average:

| Operation | Time |
|-|-|
| Insert | O(1) |
| Search | O(1) |
| Delete | O(1) |

Worst case:

```
O(n)

```

when all keys collide.

---

# 8. LRU Cache Design

## Requirement

Implement:

```
get(key)

put(key,value)

```

Both should be:

```
O(1)

```

---

# Design

Use two data structures:

## 1. Hash Map

Provides:

```
key -> node address

```

O(1)

---

## 2. Doubly Linked List

Maintains usage order.

```
Most Recent

   |
   v

10 <-> 20 <-> 30

             ^
             |
        Least Recent

```

When accessed:

Move node to front.

When full:

Remove tail.

---

# LRU Node

```c
typedef struct LRUNode
{
    int key;

    int value;


    struct LRUNode *prev;

    struct LRUNode *next;


}LRUNode;
```

---

# LRU Cache Structure

```c
#define LRU_SIZE 100


typedef struct
{
    int capacity;

    int count;


    LRUNode *head;

    LRUNode *tail;


    LRUNode *map[LRU_SIZE];


}LRUCache;
```

---

# 9. Remove Node

```c
void remove_node(LRUNode *node)
{
    node->prev->next =
        node->next;


    node->next->prev =
        node->prev;
}
```

---

# 10. Add Node At Front

```c
void add_front(LRUCache *cache,
               LRUNode *node)
{
    node->next =
        cache->head->next;


    node->prev =
        cache->head;


    cache->head->next->prev =
        node;


    cache->head->next =
        node;
}
```

---

# 11. Move Node To Front

```c
void move_to_front(LRUCache *cache,
                   LRUNode *node)
{
    remove_node(node);

    add_front(cache,node);
}
```

---

# 12. LRU Get()

## Algorithm

1. Search hash map
2. If found:
   - Move node to front
   - Return value
3. Else return -1


---

## Implementation

```c
int lru_get(LRUCache *cache,
            int key)
{
    LRUNode *node =
        cache->map[key];


    if(node == NULL)
        return -1;


    move_to_front(cache,node);


    return node->value;
}
```

---

# 13. LRU Put()

## Algorithm

If key exists:

```
update value
move front

```

Else:

```
create node

add front

if capacity exceeded:

remove tail

```

---

## Implementation

```c
void lru_put(LRUCache *cache,
             int key,
             int value)
{
    LRUNode *node =
        cache->map[key];


    if(node)
    {
        node->value=value;

        move_to_front(cache,node);

        return;
    }


    node =
        malloc(sizeof(LRUNode));


    node->key=key;

    node->value=value;


    add_front(cache,node);


    cache->map[key]=node;


    cache->count++;


    if(cache->count >
       cache->capacity)
    {
        LRUNode *remove =
            cache->tail->prev;


        remove_node(remove);


        cache->map[remove->key]=NULL;


        free(remove);


        cache->count--;
    }
}
```

---

# LRU Complexity

| Operation | Complexity |
|-|-|
| get() | O(1) |
| put() | O(1) |
| Remove | O(1) |
| Insert | O(1) |

---

# Senior Interview Discussion

## Why doubly linked list?

Because removal requires:

```
previous node
next node

```

in O(1).

---

## Why hash map?

To find nodes quickly.

Without hash map:

```
Search list = O(n)

```

With hash map:

```
Search = O(1)

```

---

## Production Improvements

Real implementation should add:

- Dynamic resizing
- Generic keys
- Thread safety
- Memory pool
- Lock striping
- Reference counting

---

# Next Part

## Part 4

Will cover:

1. Memory Pool Allocator
2. Thread-safe Queue
3. POSIX mutex
4. Condition variables
5. Producer-consumer implementation

