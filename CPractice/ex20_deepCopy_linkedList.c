/**********************************************************************
 * \file        ex20_deepCopy_linkedList.c
 *
 * \brief       Deep copy a linked list using pointers.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 10:55PM
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
int deepCopy(const node* srcList,node** destList);
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

    //copy the list
    node* destlinkedList = NULL;
    if(deepCopy(linkedList,&destlinkedList) == 1){
        return 1;
    }
    //print the copied list
    printf("List items after deepCopy.\n");
    int i=0;
    for(node* iter=linkedList; iter!=NULL; iter=iter->next,i++){
        printf("List[%d].value= %d.\n",i,iter->value);
        printf("List[%d].next= %p.\n",i,iter->next);
    }
    i=0;
    for(node* iter=destlinkedList; iter!=NULL; iter=iter->next,i++){
        printf("destList[%d].value= %d.\n",i,iter->value);
        printf("destList[%d].next= %p.\n",i,iter->next);
    }

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

int deepCopy(const node* srcList,node** destList){
    node* iterDest=NULL;
    for(const node* iter=srcList; iter!=NULL; iter=iter->next){
        node* element = createNode(iter->value);
        if(element == NULL){
            printf("Failed to deepcopy element %d.\n",iter->value);
            return 1;
        }
        if(*destList==NULL){
            iterDest=element;
            *destList=iterDest;
        }else{
            iterDest->next=element;
            iterDest = iterDest->next;
        }
    }
    return 0;
}

void deleteList(node** head){
    for(node* iter=*head; iter !=NULL; ){
        node* temp = iter;
        iter=iter->next;
        free(temp);
    }
    *head = NULL;
}