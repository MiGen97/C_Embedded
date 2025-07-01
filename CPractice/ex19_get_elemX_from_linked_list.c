/**********************************************************************
 * \file        ex19_get_elemX_from_linked_list.c
 *
 * \brief       Write a function that returns the nth element of a linked list.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 10:15PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int value;
    struct Node* next;
};

typedef struct Node node;

node* createNode(const int value);
int insertNode(node** head, const int index, const int value);
node* getElement(node* head, const int index);
void deleteList(node** head);

 int main(void){
    //create linked list
    node* linkedList = NULL;
    linkedList = createNode(10);
    if(linkedList == NULL){
        return 1;
    }
    //insert multiple elements in linked list
    if(insertNode(&linkedList,0,20) == 1){
        return 1;
    }
    if(insertNode(&linkedList,0,30) == 1){
        return 1;
    }
    if(insertNode(&linkedList,0,40) == 1){
        return 1;
    }
    if(insertNode(&linkedList,0,50) == 1){
        return 1;
    }
    printf("List items after insertions.\n");
    int i=0;
    for(node* iter=linkedList; iter!=NULL; iter=iter->next,i++){
        printf("List[%d].value= %d.\n",i,iter->value);
        printf("List[%d].next= %p.\n",i,iter->next);
    }

    //get the nth element from linked list
    int n;
    printf("Enter the index of the element that you want to extract from the linked list:");
    scanf("%d",&n);
    node* element=getElement(linkedList,n);
    if(element != NULL)
        printf("%dth element from linked list have value %d.\n",n,element->value);

    deleteList(&linkedList);
    return 0;
 }

node* createNode(const int value){
    node* head=(node*)malloc(sizeof(node));
    if(head == NULL){
        printf("Failed to allocate memory to create the linked list.\n");
        return NULL;
    }
    head->value=value;
    head->next=NULL;
    return head;
}

int insertNode(node** head, const int index, const int value){
    node* element=createNode(value);
    if(element == NULL){
        printf("Failed to insert element %d.\n",value);
        return 1;
    }

    //if empty list given, insert the first element
    if(*head == NULL){
        *head = element;
    }else{
        //insert element at the beginning
        if(index == 0){
            element->next = *head;
            *head = element;
        }else{
            int i=0;
            for(node* iter=*head; iter!=NULL; iter=iter->next){
                if(i==(index-1)){
                    element->next = iter->next;
                    iter->next = element;
                    i++;
                    break;
                }
                i++;
            }
            if(i != index) printf("Index %d out of bounds. Max index in linked list is %d.\n",index,i);
        }
    }
    return 0;
}


node* getElement(node* head, const int index){
    int i=0;
    for(node* iter=head; iter !=NULL; iter=iter->next){
        if(i == index-1)
            return iter;
        i++;
    }
    printf("Element not found. Index %d out of bound. Max number of elements in list is %d.\n",index,i);
    return NULL;
}


void deleteList(node** head){
    for(node* iter=*head; iter !=NULL; ){
        node* temp = iter;
        iter=iter->next;
        free(temp);
    }
    *head = NULL;
}