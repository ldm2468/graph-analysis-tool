#ifndef LIST_H
#define LIST_H

// 템플릿으로 list 구현
// 출처 : https://gist.github.com/harish-r/873ce92a91bb7b685b81


// node class를 list class 내의 private struct로 선언해서 구현하는게 더 낫지 않을까?
// 방법은?

template <typename T>
class Node
{
public:
    Node<T>* next;
    T data;
    
    Node(T data);
};

Node<T>::Node(T data) : data(data)
{
  next=NULL; 
}

template <typename T>
class List
{
public:
    int length;
    Node* head;

    List();
    void add(T data);
    void print();
    
    // iterator 구현 필요
    
};

List<T>::List(){
    this->length = 0;
    this->head = NULL;
}

// 앞에 삽입
void List<T>::add(T data)
{
    Node* node = new Node(data);
    node->next = this->head;
    this->head = node;
    this->length++;
}

void print()
{
       
}

#endif
