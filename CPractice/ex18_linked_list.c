/**********************************************************************
 * \file        ex18_linked_list.c
 *
 * \brief       Create a linked list and implement insert, delete, and display.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 08:09PM
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>

 #define NB_ELEMENTS 10
 typedef struct Node{
    int value;
    struct Node* next;
 } Node;

 Node* createNode(const int value);
 int insertNode(Node** list, const int index, const int value);
 void deleteElement(Node** node, const int index);
 void deleteLinkedList(Node** list);

 int main(void){
    Node* linkedList= NULL;
    linkedList=createNode(0);
    printf("List items after creation.\n");
    int i=0;
    for(Node* iter=linkedList; iter!=NULL; iter=iter->next,i++){
        printf("List[%d].value= %d.\n",i,iter->value);
        printf("List[%d].next= %p.\n",i,iter->next);
    }
    
    (void)insertNode(&linkedList, 0, 10); //at the begining
    (void)insertNode(&linkedList, 2, 20); //at middle
    (void)insertNode(&linkedList, 3, 30); //at the end 
    (void)insertNode(&linkedList, 10, 40); //outside range
    (void)insertNode(&linkedList, 4, 50); //at the end
    (void)insertNode(&linkedList, 5, 60); //at the end
    (void)insertNode(&linkedList, 6, 70); //at the end
    printf("List items after insert element.\n");
    i=0;
    for(Node* iter=linkedList; iter!=NULL; iter=iter->next,i++){
        printf("List[%d].value= %d.\n",i,iter->value);
        printf("List[%d].next= %p.\n",i,iter->next);
    }
    
    deleteElement(&linkedList,0); //at the beginning
    deleteElement(&linkedList,2); //at middle
    deleteElement(&linkedList,4); //at end
    deleteElement(&linkedList,10); //outside range
    printf("List items after delete element.\n");
    i=0;
    for(Node* iter=linkedList; iter!=NULL; iter=iter->next,i++){
        printf("List[%d].value= %d.\n",i,iter->value);
        printf("List[%d].next= %p.\n",i,iter->next);
    }
    
    deleteLinkedList(&linkedList);
    printf("List items after delete linked list\n");
    if(linkedList==NULL)
        printf("No items remain after deletion of linkedList.\n");

    return 0;
 }

 Node* createNode(const int value){
    Node* node=(Node*)malloc(sizeof(Node));
    if(node == NULL){
        printf("Memory allocation failed at node creation.\n");
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
 }

 int insertNode(Node** node, const int index, const int value){
    Node* element=createNode(value);
    if(element == NULL){
        return 1;
    }

    //insert first element in list
    if(*node == NULL){
        element->next = NULL;
        *node = element;
    }else{
        //insert node at the begining of the list
        if(index == 0)
        {
            element->next = *node;
            *node = element;
        }else
        //insert node inside the list or at the end
        {
            int i=0;
            for(Node* iter=*node; iter!=NULL; iter=iter->next){
                if( i == (index-1) ){
                    element->next = iter->next;
                    iter->next = element;
                    break;
                }
                i++;
            }

            //treat case when index outside of range of the list
            if(i!=(index-1)) printf("Wrong index %d given. Max nb of elements in list is %d.\n",index,i);
        }
    }
    return 0;
 }

 void deleteElement(Node** node, const int index){

    //insert first element in list
    if(*node == NULL){
        printf("List already empty.\n");
    }

    //delete node at the begining of the list
    if(index == 0){
        Node* temp = *node;
        *node=(*node)->next;
        free(temp);
    }else
    //delete node inside the list or at the end
    {
        int i=0;
        for(Node* iter=*node;iter!=NULL; iter=iter->next, i++){
            if(i+1 == index){
                Node* temp = iter->next;
                iter->next = temp->next;
                free(temp);
                break;
            }
        }

        //treat case when index outside of range of the list
        if(i!=(index-1)) printf("Wrong index %d given. Max nb of elements in list is %d.\n",index,i);
    }
 }


 void deleteLinkedList(Node** list){
    for(Node* iter=*list; iter!=NULL;){
        Node* temp = iter;
        iter=iter->next;
        free(temp);
    }
    *list = NULL;
 }