#ifndef ILIST_H
#define ILIST_H
using namespace std;

template<class T>
class ilist
{
public:
        struct Node
        {
                T data;
                Node *next, *prev;
                Node(T s = 0, Node* n = NULL, Node* p = NULL) : data(s), next(n), prev(p) {};
        };
        class listIterator
        {
        public:
                friend class ilist;
                explicit listIterator(Node *p = 0)
                {
                        current = p;
                }
                listIterator(const listIterator& other)
                {
                        current = other.current;
                }
                listIterator& operator++()
                {
                        current = current->next;
                        return *this;
                }
                listIterator& operator--()
                {
                        current = current->prev;
                        return *this;
                }
                listIterator operator++(int)
                {
                        listIterator temp = *this;
                        ++(*this);
                        return temp;
                }
                listIterator operator--(int)
                {
                        listIterator temp = *this;
                        --(*this);
                        return temp;
                }
                Node* operator->()
                {
                        return current;
                }
                T& operator*()
                {
                        return current->data;
                }
                bool operator==(const listIterator & rhs) const
                {
                        return current == rhs.current;
                }
                bool operator!=(const listIterator & rhs) const
                {
                        return !( *this == rhs );
                }
                operator Node * ()
                {
                        return current;
                }
        private:
                Node* current;
        };
private:
        Node *head, *tail;
        int _size;
        void init()
        {
                _size = 0;
                head = new Node();
                tail = new Node();
                head->next = tail;
                tail->prev = head;
        }
public:
        ilist()
        {
                init();
        }
        ~ilist()
        {
                clear();
                delete head;
                delete tail;
        }
        ilist(size_t n_elements, const T& c)
        {
                init();
                for (int i = 0; i != n_elements; i++)
                {
                        pushBack(c);
                }
        }
        ilist(const ilist& it)
        {
                init();
                for (listIterator iter = it.begin(); iter != it.end(); iter++)
                {
                        pushBack(*iter);
                }
        }
        ilist(listIterator it1, listIterator it2)
        {
                init();
                for (listIterator iter = it1; iter != it2; iter++)
                {
                        pushBack(*iter);
                }
        }
        listIterator begin() const
        {
                return listIterator(head->next);
        }
        listIterator end() const
        {
                return listIterator(tail);
        }
        size_t size() const
        {
                return _size;
        }
        void pushBack(const T& it)
        {
                insert(end(), it);
        }
        void popBack()
        {
                erase(--end());
        }
        listIterator insert(listIterator position, const T& val)
        {
                Node* p = position.current;
                _size++;
                return listIterator(p->prev = p->prev->next = new Node(val, p, p->prev));
        }
        listIterator erase(listIterator position)
        {
                Node* p = position.current;
                listIterator retVal(p->next);
                p->prev->next = p->next;
                p->next->prev = p->prev;
                delete p;
                _size--;
                return retVal;
        }
        bool empty() const
        {
                return _size == 0;
        }
        T& front()
        {
                return *begin();
        }
        T& back()
        {
                return *(--end());
        }
        void clear()
        {
                while (!empty())
                {
                        popBack();
                }
        }
        friend ostream& operator << (ostream& out, const ilist& it)
        {
                for (listIterator iter = it.begin(); iter != (it.end())->prev; iter++)
                {
                        out << *iter << " ";
                }
                out << (it.end())->prev->data;
                return out;
        }
};

#endif // ILIST_H
