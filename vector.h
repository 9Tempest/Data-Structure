#ifndef __VECTOR__
#define __VECTOR__

#include <iostream>
#include <util.h>
#include <string>


template<typename T>


class VectorException{
    std::string msg;
    public:
        //void ewhat();
};

template<typename T>
class Vector{
    int size;
    int capacity;
    T *data;
    class VectorIterator{
        T *data;
        explicit VectorIterator(T *data):data{data}{}
        public:
            T& operator*() {return *data;}
            VectorIterator& operator++() {
                data++;
                return *this;
            }
            bool operator==(const VectorIterator& other){
                return data == other.data;
            }
            bool operator!=(const VectorIterator& other){
                return data != other.data;
            }
        friend class Vector;
    };
    
    friend std::ostream &operator<<(std::ostream& out, const Vector &v);
    //public methods for a vector
    public:
        //ctor&dtor
        Vector(int n);
        Vector(Vector<T> &&v);
        Vector(int n, T i);
        Vector(const T *begin, const T *end);
        Vector(const Vector<T> &v);
        Vector();
        virtual ~Vector();

        //accesser&mutator
        const VectorIterator begin(){
            return VectorIterator{data};
        }
        const VectorIterator end(){
            return VectorIterator{data+size};
        }
        void push_back(const T &item) noexcept;
        void push_back(T &&item) noexcept;

        //other
        void swap(Vector<T> &v);
        void print();


};




template <typename T>
void Vector<T>::swap(Vector<T> &v){
    std::swap(size, v.size);
    std::swap(capacity, v.capacity);
    std::swap(data, v.data);
}

template <typename T>
Vector<T>::Vector(int n): size{n}, capacity{8} {
    while (capacity < size)
    {
        capacity *= 2;
    }
    data = new T[capacity];
}

template <typename T>
Vector<T>::Vector(): size{0}, capacity{8}{
    data = new T[capacity];
}

template <typename T>
Vector<T>::Vector(int n, T I): size{n}, capacity{8} {
    while (capacity < size)
    {
        capacity *= 2;
    }
    data = new T[capacity];
    for (int i = 0; i < size; i++){
        data[i] = I;
    }
}

template <typename T>
Vector<T>::Vector(const T *begin, const T *end):size{end-begin}, capacity{8} {
    while (capacity < size)
    {
        capacity *= 2;
    }
    data = new T[capacity];
    for (int i = 0; i < size; i++){
        data[i] = *(begin+i);
    }
}


template <typename T>
Vector<T>::Vector(Vector<T> &&v):size{v.size}, capacity{v.capacity}{

    data = new T[capacity];
    for (int i = 0; i < v.size; i++){
        data[i] = v.data[i];
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &v):size{v.size}, capacity{v.capacity}{
    data = new T[capacity];
    for (int i = 0; i < size; i++){
        data[i] = v.data[i];
    }
}

template <typename T>
Vector<T>::~Vector(){
    delete[] data;
}


//accessor






//mutator
template <typename T>
void Vector<T>::push_back(const T& item) noexcept{
    if (size == capacity){
        capacity *= 2;
        T *temp = new T[capacity];
        for (int i = 0; i < size; i++){
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    data[size] = item;
    size++;
}

template <typename T>
void Vector<T>::push_back(T &&item) noexcept{
    if (size == capacity){
        capacity *= 2;
        T *temp = new T[capacity];
        for (int i = 0; i < size; i++){
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    data[size] = item;
    size++;
}

template <typename T>
void Vector<T>::print(){
    for (int i = 0; i < size; i++){
        if (i){
            std::cout <<", ";
        }
        std::cout << data[i];
    }
    std::cout << std::endl;
}







#endif