#ifndef LIST_H
#define LIST_H

// 템플릿으로 list 구현
// 출처 : https://gist.github.com/harish-r/873ce92a91bb7b685b81

<template T>
class Node
{
public:
    Node* next;
    T data;
    
    Node(T data);
};

Node<T>::Node(T data) : data(data)
{
  next=NULL; 
}

<template T>
class List
{
public:
    int length;
    Node* head;

    List();
    void add(T data);
    
    // iterator 구현 필요
    
};

List<T>::List(){
    this->length = 0;
    this->head = NULL;
}

void List<T>::add(T data){
    Node* node = new Node(data);
    node->next = this->head;
    this->head = node;
    this->length++;
}



#endif
