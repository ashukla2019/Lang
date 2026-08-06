# Advanced C Interview Coding Solutions - Part 2

# Linked List Implementations

Topics covered:

1. Linked list node design
2. Insert node
3. Delete node
4. Traverse list
5. Reverse linked list (iterative)
6. Reverse linked list (recursive)
7. Detect cycle using Floyd algorithm
8. Find cycle start node
9. Find middle node

---

# 1. Linked List Node Structure

A singly linked list node contains:

- Data
- Pointer to next node

## Implementation

```c
#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    int data;
    struct Node *next;

} Node;
```

Memory layout:

```
+--------+--------+
| data   | next   |
+--------+--------+

```

---

# 2. Create New Node

```c
Node *create_node(int value)
{
    Node *new_node =
        (Node *)malloc(sizeof(Node));


    if(new_node == NULL)
        return NULL;


    new_node->data = value;
    new_node->next = NULL;


    return new_node;
}
```

---

# 3. Insert Node At Beginning

## Algorithm

New node points to current head.

New node becomes head.

```
Before:

head
 |
 v
10 -> 20 -> 30


Insert 5


After:

head
 |
 v
5 -> 10 -> 20 -> 30

```

---

## Implementation

```c
void insert_front(Node **head, int value)
{
    Node *new_node =
        create_node(value);


    if(new_node == NULL)
        return;


    new_node->next = *head;

    *head = new_node;
}
```

---

# 4. Insert Node At End

## Implementation

```c
void insert_end(Node **head, int value)
{
    Node *new_node =
        create_node(value);


    if(new_node == NULL)
        return;


    if(*head == NULL)
    {
        *head = new_node;
        return;
    }


    Node *temp = *head;


    while(temp->next != NULL)
    {
        temp = temp->next;
    }


    temp->next = new_node;
}
```

---

# 5. Traverse Linked List

```c
void print_list(Node *head)
{
    Node *temp = head;


    while(temp != NULL)
    {
        printf("%d ", temp->data);

        temp = temp->next;
    }


    printf("\n");
}
```

Example:

```
Input:

10 -> 20 -> 30


Output:

10 20 30

```

---

# 6. Delete Node

Delete first occurrence of a value.

## Algorithm

Cases:

1. Node is head
2. Node is middle
3. Node is last


---

## Implementation

```c
void delete_node(Node **head, int value)
{
    if(*head == NULL)
        return;


    Node *temp = *head;


    if(temp->data == value)
    {
        *head = temp->next;

        free(temp);

        return;
    }


    Node *prev = NULL;


    while(temp != NULL &&
          temp->data != value)
    {
        prev = temp;
        temp = temp->next;
    }


    if(temp == NULL)
        return;


    prev->next = temp->next;


    free(temp);
}
```

---

# 7. Reverse Linked List (Iterative)

## Problem

Reverse:

```
Before:

10 -> 20 -> 30 -> NULL


After:

30 -> 20 -> 10 -> NULL

```

---

## Algorithm

Maintain three pointers:

```
previous
current
next

```

Steps:

1. Save next node
2. Reverse current pointer
3. Move forward


---

## Implementation

```c
Node *reverse_list(Node *head)
{
    Node *prev = NULL;

    Node *current = head;


    while(current != NULL)
    {
        Node *next = current->next;


        current->next = prev;


        prev = current;


        current = next;
    }


    return prev;
}
```

---

## Complexity

Time:

```
O(n)
```

Space:

```
O(1)
```

---

# 8. Reverse Linked List (Recursive)

## Idea

Reverse remaining list first.

Then attach current node at end.

---

## Implementation

```c
Node *reverse_recursive(Node *head)
{
    if(head == NULL ||
       head->next == NULL)
    {
        return head;
    }


    Node *new_head =
        reverse_recursive(head->next);


    head->next->next = head;


    head->next = NULL;


    return new_head;
}
```

---

## Complexity

Time:

```
O(n)
```

Space:

```
O(n)
```

because of recursion stack.

---

# 9. Detect Cycle In Linked List

## Floyd Cycle Detection Algorithm

Uses:

- Slow pointer
- Fast pointer


Slow moves:

```
1 step
```

Fast moves:

```
2 steps
```

If cycle exists:

```
slow == fast

```

---

## Example

```
10 -> 20 -> 30
          ^    |
          |____|

```

---

## Implementation

```c
int detect_cycle(Node *head)
{
    Node *slow = head;

    Node *fast = head;


    while(fast != NULL &&
          fast->next != NULL)
    {
        slow = slow->next;

        fast = fast->next->next;


        if(slow == fast)
        {
            return 1;
        }
    }


    return 0;
}
```

---

## Complexity

Time:

```
O(n)
```

Space:

```
O(1)
```

---

# 10. Find Cycle Starting Node

## Algorithm

After slow and fast meet:

1. Move one pointer to head
2. Move both one step
3. Meeting point is cycle start


---

## Implementation

```c
Node *find_cycle_start(Node *head)
{
    Node *slow = head;

    Node *fast = head;


    while(fast &&
          fast->next)
    {
        slow = slow->next;

        fast = fast->next->next;


        if(slow == fast)
        {
            break;
        }
    }


    if(fast == NULL ||
       fast->next == NULL)
    {
        return NULL;
    }


    slow = head;


    while(slow != fast)
    {
        slow = slow->next;

        fast = fast->next;
    }


    return slow;
}
```

---

# 11. Find Middle Node

## Algorithm

Use:

- Slow pointer
- Fast pointer


Fast moves twice as fast.

When fast reaches end:

Slow is middle.

---

## Implementation

```c
Node *find_middle(Node *head)
{
    Node *slow = head;

    Node *fast = head;


    while(fast != NULL &&
          fast->next != NULL)
    {
        slow = slow->next;

        fast = fast->next->next;
    }


    return slow;
}
```

---

# 12. Free Entire List

Important for memory leak prevention.

```c
void free_list(Node *head)
{
    Node *temp;


    while(head != NULL)
    {
        temp = head;

        head = head->next;


        free(temp);
    }
}
```

---

# Interview Discussion Points

## Why use Node **head in insert/delete?

Because function needs to modify caller's head pointer.

Example:

```c
insert_front(&head,10);

```

A normal pointer copies the address.

Double pointer modifies original pointer.

---

## Reverse Linked List Common Mistakes

Wrong:

```c
current->next = prev;

current = current->next;

```

You lose remaining nodes.

Correct:

```c
next = current->next;

current->next = prev;

current = next;

```

---

## Common Senior Interview Follow-ups

1. Reverse linked list in groups of K nodes.
2. Merge two sorted linked lists.
3. Remove duplicate nodes.
4. Find Nth node from end.
5. Check if linked list is palindrome.
6. Detect intersection of two linked lists.

---

# Complexity Summary

| Operation | Time | Space |
|-|-|-|
| Insert front | O(1) | O(1) |
| Insert end | O(n) | O(1) |
| Delete | O(n) | O(1) |
| Traverse | O(n) | O(1) |
| Reverse iterative | O(n) | O(1) |
| Reverse recursive | O(n) | O(n) |
| Detect cycle | O(n) | O(1) |
| Find middle | O(n) | O(1) |

---

# Next Part

## Part 3: Hash Table + LRU Cache

Will cover:

- Hash table design
- Collision handling
- Insert
- Search
- Delete
- Resize
- LRU cache using:
  - Hash map
  - Doubly linked list
  - O(1) get()
  - O(1) put()

