//
// Created by aknight on 9/26/18.
//

#ifndef LINKEDLISTS_LIST_H
#define LINKEDLISTS_LIST_H
#include <cstdlib>
#include <utility>

#include <cstdlib>
#include <utility>

namespace edu { namespace vcccd { namespace vc { namespace csv15 {
    template<class T>
    class LinkedList {
    private:
        struct Node {
            Node(T data, Node *next) : _data(data), _next(next) {}
            Node* _next;
            T _data;
        };
    public:
        class iterator {
        public:
            iterator(Node *node): _node(node) {}
            iterator(const iterator &other) : _node(other._node) {}

        public:
            const T &operator*() { return _node->_data; }
            const T &operator*() const { return _node->_data; }
            iterator &operator++() { _node = _node->_next; return *this; }
            iterator operator++(int) { iterator before(*this); _node = _node->_next; return before; }
            bool operator==(const iterator &other) { return other._node == _node; }
            bool operator!=(const iterator &other) { return !operator==(other); }
            Node *node() { return _node; }
        private:
            Node *_node;
        };

    public:
        LinkedList(): head(nullptr), tail(nullptr), _size(0) {}
        LinkedList(const LinkedList &other): _size(0), head(nullptr), tail(nullptr) {
            for (const T& val: other) push_front(val);
        }

        ~LinkedList() { clear(); }

    public:
        bool empty() const { return _size == 0; }
        T &front() { return head->_data; }
        const T &front() const { return head->_data; }
        T &back() { return tail->_data; }
        const T &back() const { return tail->_data; }
        size_t size() const { return _size; }

    public:
        iterator begin() { return iterator(head); }
        const iterator begin() const { return iterator(head); }
        iterator end() { return iterator(nullptr); }
        const iterator end() const { return iterator(nullptr); }

    public:
        void clear() {
            erase(begin(), end());
            delete head;
            head = nullptr;
            _size = 0;
        }

        iterator insert(iterator where, const T &value) {
            where.node()->_next = new Node(value, where.node()->_next);
            if (where.node() == tail) tail = where.node()->_next;
            _size++;
        }

        iterator erase(iterator where) {
            Node *old = where.node() == nullptr ? nullptr: where.node()->_next;
            if (old != nullptr) {
                where.node()->_next = old->_next;
                delete old;
            }
            _size--;
        }
        iterator erase(iterator first, iterator last) {
            for (auto i = first; i != last; erase(i), i++);
        }
        void push_back(const T &value) {
            Node *newNode = new Node(value, nullptr);
            if (tail == nullptr) head = tail = newNode;
            else tail = tail->_next = newNode;
            _size++;
        }
        void pop_back() {
            if (_size == 0) return;
            if (_size == 1) {
                delete head;
                head = tail = nullptr;
                _size = 0;
                return;
            }
            Node *curr = head;
            for(;curr->_next != tail; curr = curr->_next);
            delete tail;
            curr->_next = nullptr;
            tail = curr;
            _size--;
        }

        void push_front(const T &value) {
            Node *newNode = new Node(value, nullptr);
            if (head == nullptr) head = tail = newNode;
            else {
                newNode->_next = head;
                head = newNode;
            }
            _size++;
        }
        void pop_front() {
            if (_size == 0) return;
            if (_size == 1) {
                delete head;
                head = tail = nullptr;
                _size = 0;
                return;
            }
            Node *old = head;
            if (old != nullptr){
                head = old->_next;
                delete old;
            }
            _size--;
        }

    public:
        void swap(LinkedList &other) {
            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(_size, other._size);
        }

    private:
        Node *head;
        Node *tail;
        size_t _size;
    };
}}}}
#endif //LINKEDLISTS_LIST_H
