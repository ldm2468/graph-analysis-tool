#ifndef LIST_H
#define LIST_H

// 템플릿으로 list 구현
// 참고 출처 : https://gist.github.com/harish-r/873ce92a91bb7b685b81
// 참고 출처2 : https://codereview.stackexchange.com/questions/60994/stl-list-implementation

// node class를 list class 내의 private struct로 선언해서 구현하는게 더 낫지 않을까?
// 수정함!

template <typename T>
class List
{
public:
    List();
    ~List();
    void add(T data);
    void print();   // test용 function
    // 인접 vertex 검색을 위한 iterator 구현 필요
    
private:
    struct Node
    {  
        T data;
        Node* next;
        Node(T const& data, Node* next) : data(data), next(next){}
        Node(T& data, Node* next) : data(data), next(next){}
    };
    int elements;
    Node* head; 
};

List<T>::List(){
    this->elements = 0;
    this->head = nullptr;
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

// iterator 참고자료 1
// std::iterator 사용 예시 code
// 출처 : http://www.cplusplus.com/reference/iterator/iterator/

/*
// std::iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag

class MyIterator : public std::iterator<std::input_iterator_tag, int>
{
  int* p;
public:
  MyIterator(int* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
  int& operator*() {return *p;}
};

int main () {
  int numbers[]={10,20,30,40,50};
  MyIterator from(numbers);
  MyIterator until(numbers+5);
  for (MyIterator it=from; it!=until; it++)
    std::cout << *it << ' ';
  std::cout << '\n';

  return 0;
}
*/

// iterator 참고자료 2
// 출처 : https://stackoverflow.com/questions/28508407/implementing-a-list-iterator-and-operators

/*
struct iterator;
    struct const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
    {
        const_iterator() = default;
        T operator*() { return itm->data; }
        const T* operator->() { return &(itm->data); }
        const_iterator operator++() { itm = itm->next; return *this; }
        const_iterator operator--() { itm = itm->prev; return *this; }
        const_iterator operator++(int) { const_iterator ret=*this; itm = itm->next; return ret; }
        const_iterator operator--(int) { const_iterator ret=*this; itm = itm->prev; return ret; }
        bool operator==(const_iterator oth) const { return itm==oth.itm; }
        bool operator!=(const_iterator oth) const { return itm!=oth.itm; }
    private:
        element<T>* itm = nullptr;
        const_iterator(element<T>* i) : itm(i) {}
    friend
        class list;
    friend
        struct iterator;
    };
    struct iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
        iterator() = default;
        T& operator*() { return itm->data; }
        T* operator->() { return &(itm->data); }
        iterator operator++() { itm = itm->next; return *this; }
        iterator operator--() { itm = itm->prev; return *this; }
        iterator operator++(int) { iterator ret=*this; itm = itm->next; return ret; }
        iterator operator--(int) { iterator ret=*this; itm = itm->prev; return ret; }
        bool operator==(iterator oth) const { return itm==oth.itm; }
        bool operator!=(iterator oth) const { return itm!=oth.itm; }
        operator const_iterator() { return {itm}; }
    private:
        element<T>* itm = nullptr;
        iterator(element<T>* i) : itm(i) {}
    friend
        class list;
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

*/


