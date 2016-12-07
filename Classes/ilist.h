#ifndef __ILIST_H__
#define __ILIST_H__
using namespace std;

template<class T>
class ilist
{
public:
        //  list cell
        struct Node
        {
                T data;
                Node *next, *prev;
                Node(T s = 0, Node* n = nullptr, Node* p = nullptr) : data(s), next(n), prev(p) {};
        };
        class listIterator
        {
        public:
                friend class ilist;
                explicit listIterator(Node *p = 0)
                {
                        current = p;
                }

                //  Constructs a copy of other.
                listIterator(const listIterator& other)
                {
                        current = other.current;
                }

                //  The prefix ++ operator, advances the iterator to the next item in the object.
                //  Returns an iterator to the new current item.
                listIterator& operator++()
                {
                        current = current->next;
                        return *this;
                }

                //  The prefix -- operator, makes the preceding item current.
                //  Returns an iterator pointing to the new current item.
                listIterator& operator--()
                {
                        current = current->prev;
                        return *this;
                }

                //  The postfix ++ operator, advances the iterator to the next item in the object.
                //  Returns an iterator to the previously current item.
                listIterator operator++(int)
                {
                        listIterator temp = *this;
                        ++(*this);
                        return temp;
                }

                //  The postfix -- operator, makes the preceding item current.
                //  Returns an iterator pointing to the previously current item.
                listIterator operator--(int)
                {
                        listIterator temp = *this;
                        --(*this);
                        return temp;
                }

                //  Returns a pointer to the current item.
                Node* operator->()
                {
                        return current;
                }

                //  Returns the current item's value.
                T& operator*()
                {
                        return current->data;
                }

                //  Returns true if rhs points to the same item as this iterator; otherwise returns false.
                bool operator==(const listIterator & rhs) const
                {
                        return current == rhs.current;
                }

                //  Returns true if rhs points to a different item than this iterator; otherwise returns false.
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

        // Returns an iterator pointing the head of the ilist.
        listIterator begin() const
        {
                return listIterator(head->next);
        }

        //  Returns an iterator referring to the end of the ilist.
        listIterator end() const
        {
                return listIterator(tail);
        }

        //  Returns the number of elements in the ilist.
        //  This is the number of actual objects held in the ilist, which is not necessarily equal to its storage capacity.
        size_t size() const
        {
                return _size;
        }

        //  Adds a new element at the end of the ilist.
        void pushBack(const T& it)
        {
                insert(end(), it);
        }

        //  Removes the last element in the ilist.
        void popBack()
        {
                erase(--end());
        }

        //  Insert an object at certain position.
        listIterator insert(listIterator position, const T& val)
        {
                Node* p = position.current;
                _size++;
                return listIterator(p->prev = p->prev->next = new Node(val, p, p->prev));
        }

        //  Remove a certain object in ilist.
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

        //  Returns whether the ilist is empty.
        //  This function does not modify the container in any way. To clear the content of a list, see ilist<T>::clear.
        bool empty() const
        {
                return _size == 0;
        }

        //  Returns the first element in the ilist.
        T& front()
        {
                return *begin();
        }

        //  Returns the last element in the ilist.
        T& back()
        {
                return *(--end());
        }

        //  Removes all elements from the ilist, leaving the container with a size of 0.
        //  All the elements in the ilist will be released.
        void clear()
        {
                while (!empty())
                {
                        popBack();
                }
        }







//        // Don't uses operator since we could not decide whether it needs 'retain'/'release'.
////    T& operator[](int index)
////    {
////        return _data[index];
////    }
////
////    const T& operator[](int index) const
////    {
////        return _data[index];
////    }
//
//    /**
//     * Requests that the vector capacity be at least enough to contain n elements.
//     * @param capacity Minimum capacity requested of the Vector.
//     */
//    void reserve(ssize_t n)
//    {
//        _data.reserve(n);
//    }
//
//    /** @brief Returns the size of the storage space currently allocated for the Vector, expressed in terms of elements.
//     *  @note This capacity is not necessarily equal to the Vector size.
//     *        It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
//     *  @return The size of the currently allocated storage capacity in the Vector, measured in terms of the number elements it can hold.
//     */
//    ssize_t capacity() const
//    {
//        return _data.capacity();
//    }
//
//    /** @brief Returns the number of elements in the Vector.
//     *  @note This is the number of actual objects held in the Vector, which is not necessarily equal to its storage capacity.
//     *  @return The number of elements in the Vector.
//     */
//    ssize_t size() const
//    {
//        return  _data.size();
//    }
//
//    /** @brief Returns whether the Vector is empty (i.e. whether its size is 0).
//     *  @note This function does not modify the container in any way. To clear the content of a vector, see Vector<T>::clear.
//     */
//    bool empty() const
//    {
//        return _data.empty();
//    }
//
//    /** Returns the maximum number of elements that the Vector can hold. */
//    ssize_t max_size() const
//    {
//        return _data.max_size();
//    }
//
//    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
//    ssize_t getIndex(T object) const
//    {
//        auto iter = std::find(_data.begin(), _data.end(), object);
//        if (iter != _data.end())
//            return iter - _data.begin();
//
//        return -1;
//    }
//
//    /** @brief Find the object in the Vector.
//     *  @param object The object to find.
//     *  @return Returns an iterator which refers to the element that its value is equals to object.
//     *          Returns Vector::end() if not found.
//     */
//    const_iterator find(T object) const
//    {
//        return std::find(_data.begin(), _data.end(), object);
//    }
//
//    /** @brief Find the object in the Vector.
//     *  @param object The object to find.
//     *  @return Returns an iterator which refers to the element that its value is equals to object.
//     *          Returns Vector::end() if not found.
//     */
//    iterator find(T object)
//    {
//        return std::find(_data.begin(), _data.end(), object);
//    }


//     * Checks whether an object is in the container.
//     * @param object The object to be checked.
//     * @return True if the object is in the container, false if not.
//     */
//    bool contains(T object) const
//    {
//        return( std::find(_data.begin(), _data.end(), object) != _data.end() );
//    }
//
//    /**
//     * Checks whether two vectors are equal.
//     * @param other The vector to be compared.
//     * @return True if two vectors are equal, false if not.
//     */
//    bool equals(const Vector<T> &other)
//    {
//        ssize_t s = this->size();
//        if (s != other.size())
//            return false;
//
//        for (ssize_t i = 0; i < s; i++)
//        {
//            if (this->at(i) != other.at(i))
//            {
//                return false;
//            }
//        }
//        return true;
//    }

};

#endif // ILIST_H
