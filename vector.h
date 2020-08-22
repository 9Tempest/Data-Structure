#ifndef __VECTOR__
#define __VECTOR__

#include <iostream>
#include <util.h>
#include <string>



class VectorException{
    std::string msg;
    public:
        VectorException(std::string msg):msg{msg}{}
        //void ewhat();
};

template<typename T>
class Vector{
    int _size;
    int _capacity;
    T *data;

    public:
    class VectorIterator{
        T *data;
        VectorIterator(T *data):data{data}{}
        public:
            T& operator*() {return *data;}
            VectorIterator& operator++() {
                data++;
                return *this;
            }
            int operator-(const VectorIterator &other){
                return data-other.data;
            }
            VectorIterator& operator+(int n){
                data += n;
                return *this;
            }
            VectorIterator& operator--(){
                data--;
                return *this;
            }
            VectorIterator& operator-(const int n) {
                data -= n;
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
        //ctor&dtor
        Vector(int n);
        Vector(Vector<T> &&v);
        Vector(int n, T i);
        Vector(const T *begin, const T *end);
        Vector(const Vector<T> &v);
        Vector();
        virtual ~Vector();

        //accesser
        const VectorIterator begin(){
            return VectorIterator{data};
        }

        const VectorIterator end(){
            return VectorIterator{data+_size};
        }
        T &operator[](int index) const;
        const T& front() const;
        const T& back() const;
        const int size() const noexcept;
        const int capacity() const noexcept;
        bool empty() const noexcept;

        //mutator
        void push_back(const T &item) noexcept;
        void push_back(T &&item) noexcept;
        void pop_back();

        void erase(const VectorIterator& it);
        void erase(const VectorIterator& it1, const VectorIterator& it2);

        void insert(VectorIterator& it, T& item);
        void insert(VectorIterator& it, int num, T& item);
        void insert(VectorIterator& it, T *begin, T *end);
        

        //other
        void swap(Vector<T> &v);
        void print();


};


template <typename T>
void Vector<T>::swap(Vector<T> &v){
    std::swap(_size, v._size);
    std::swap(_capacity, v._capacity);
    std::swap(data, v.data);
}

template <typename T>
Vector<T>::Vector(int n): _size{n}, _capacity{8} {
    while (_capacity < _size)
    {
        _capacity *= 2;
    }
    data = new T[_capacity];
}

template <typename T>
Vector<T>::Vector(): _size{0}, _capacity{8}{
    data = new T[_capacity];
}

template <typename T>
Vector<T>::Vector(int n, T I): _size{n}, _capacity{8} {
    while (_capacity < _size)
    {
        _capacity *= 2;
    }
    data = new T[_capacity];
    for (int i = 0; i < _size; i++){
        data[i] = I;
    }
}

template <typename T>
Vector<T>::Vector(const T *begin, const T *end):_size{end-begin}, _capacity{8} {
    while (_capacity < _size)
    {
        _capacity *= 2;
    }
    data = new T[_capacity];
    for (int i = 0; i < _size; i++){
        data[i] = *(begin+i);
    }
}


template <typename T>
Vector<T>::Vector(Vector<T> &&v):_size{v._size}, _capacity{v._capacity}{

    data = new T[_capacity];
    for (int i = 0; i < v._size; i++){
        data[i] = v.data[i];
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &v):_size{v._size}, _capacity{v._capacity}{
    data = new T[_capacity];
    for (int i = 0; i < _size; i++){
        data[i] = v.data[i];
    }
}

template <typename T>
Vector<T>::~Vector(){
    delete[] data;
}


//accessor part
template <typename T>
T &Vector<T>::operator[](int index) const{
    if (index >= _size) throw VectorException{"index out of range"};
    return data[index];
}
template <typename T>
const T& Vector<T>::front() const{
    if (_size == 0) throw VectorException{"This vector is empty!"};
    return *data;
}

template <typename T>
const T& Vector<T>::back() const{
    if (_size == 0) throw VectorException{"This vector is empty!"};
    return data[_size-1];
}

template <typename T>
const int Vector<T>::size() const noexcept{
    return _size;
}

template <typename T>
const int Vector<T>::capacity() const noexcept{
    return _capacity;
}

template <typename T>
bool Vector<T>::empty() const noexcept{
    return _size == 0;
}




//mutator part
template <typename T>
void Vector<T>::push_back(const T& item) noexcept{
    if (_size == _capacity){
        _capacity *= 2;
        T *temp = new T[_capacity];
        for (int i = 0; i < _size; i++){
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    data[_size] = item;
    _size++;
}

template <typename T>
void Vector<T>::push_back(T&& item) noexcept{
    if (_size == _capacity){
        _capacity *= 2;
        T *temp = new T[_capacity];
        for (int i = 0; i < _size; i++){
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    data[_size] = item;
    _size++;
}

template <typename T>
void Vector<T>::pop_back(){
    if (empty()) throw VectorException{"Vector is empty!"};
    _size--;
}

template <typename T>
void Vector<T>::erase(const VectorIterator& it){
    for (auto i = data; i != _size+data; ++i){
        if (i == it.data){
            for (auto j = it.data; j != _size+data-1; ++j){
                *j = *(j+1);
            }
            _size--;
            return;
        }
    }
}

template <typename T>
void Vector<T>::erase(const VectorIterator& it1, const VectorIterator& it2){
    auto end = data+_size-1-(it2-it1);
    for (auto i = data; i != _size+data; i++){
        //add exception
        if (i == it1.data){
            for (auto j = it1.data; j != end; ++j){
                *j = *(j+1+(it2-it1));
            }
            _size -= it2-it1;
            return;
        }
    }
}

template <typename T>
void Vector<T>::insert(VectorIterator& it, T& item){
    if (_size == _capacity){
        _capacity *= 2;
        T *temp = new T[_capacity];
        for (int i = 0; i < _size; i++){
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    for (auto i = data; i != data+_size; i++){
        if (i == it.data){
            for (auto j = _size+data; j != data; --j){
                *j = *(j-1);
            }
            *i = item;
            _size++;
            return;
        }
    }
}

template <typename T>
void Vector<T>::insert(VectorIterator& it, int num, T& item){
    if (_size+num-1 >= _capacity){
        while (_size+num-1 >= _capacity){
            _capacity *= 2;
        }
        T *temp = new T[_capacity];
        for (int i = 0; i < _size; i++){
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    for (auto i = data; i != _size+data; i++){
        if (i == it){
            for (auto j = _size+data+num-1; j != data+num-1; --j){
                *j = *(j-num);
            }
            for (auto j = it; j < it + num; j++){
                *j = item;
            }
            _size += num;
            return;
        }
    }
}

template <typename T>
void Vector<T>::insert(VectorIterator& it, T *begin, T *end){
    int num = begin - end;
    if (_size+num-1 >= _capacity){
        while (_size+num-1 >= _capacity){
            _capacity *= 2;
        }
        T *temp = new T[_capacity];
        for (int i = 0; i < _size; i++){
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    for (auto i = data; i != data+_size; i++){
        if (i == it.data){
            for (auto j = data+_size+num-1; j != data+num-1; --j){
                *j = *(j-num);
            }
            for (int j = 0; j < num; j++){
                *(i+j) = *(begin+j);
            }
            _size += num;
            return;
        }
    }
}


template <typename T>
void Vector<T>::print(){
    for (int i = 0; i < _size; i++){
        if (i){
            std::cout <<", ";
        }
        std::cout << data[i];
    }
    std::cout << std::endl;
}







#endif