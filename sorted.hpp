#ifndef SORTED_HPP
#define SORTED_HPP

#include <iostream>
#include <functional>

template<typename T>
class Sorted{
private:
    T* arr;
    std::size_t size, capacity;

    void sort();
    void copy(const Sorted& other);
    void destroy();
    void resize();
    
public:
    Sorted();
    Sorted(const T arr[], std::size_t size);

    Sorted(const Sorted& other);
    Sorted &operator=(const Sorted& other);
    ~Sorted();

    void add(T elem);
    void remove();

    T operator[](int index);
    const T operator[](int index) const;
    

    std::size_t getsize() const;

    using Predicate = std::function<bool(const T&)>;
    void filter(Predicate p);

    using Mapfn = std::function<T(const T&)>;
    void map(Mapfn fn);

    bool search(T elem) const;

    template <typename V>
    friend const std::ostream &operator<<(std::ostream &stream, const Sorted<V> &other);

};

template <typename T>
void Sorted<T>::sort(){
    if(size>1)
        for(int i=0; i<size-1; i++){
            for(int j=1; j<size-i; j++){
                if(arr[j]<arr[j-1]){
                    T hold = arr[j];
                    arr[j] = arr[j-1];
                    arr[j-1] = hold;
                }

            }
        }
}

template<typename T>
void Sorted<T>::copy(const Sorted& other){
    size = other.size;
    capacity = other.capacity;
    arr = new T[capacity];
    for (int i = 0; i < size; i++){
        arr[i]=other.arr[i];
    }
    
}

template<typename T>
void Sorted<T>::destroy(){
    delete[] arr;
}

template<typename T>
void Sorted<T>::resize(){
    if(capacity==0)
        capacity=1;
    
    capacity*=2;
    T* newmem = new T[capacity];
    for (int i = 0; i < size; i++){
        newmem[i] = arr[i];
    }
    delete[] arr;
    arr = newmem;
    
}

template<typename T>
Sorted<T>::Sorted():capacity(0),size(0){}

template<typename T>
Sorted<T>::Sorted(const T _arr[], std::size_t _size):capacity(_size),size(_size),arr(new T[_size]){
    for (int i = 0; i < size; i++)
    {
        arr[i] = _arr[i];
    }
    sort();
}

template<typename T>
Sorted<T>::Sorted(const Sorted<T>& other){
    copy(other);
}

template<typename T>
Sorted<T> &Sorted<T>::operator=(const Sorted<T>& other){
    if(this!=&other){
        destroy();
        copy(other);
    }
    return *this;
}

template<typename T>
Sorted<T>::~Sorted(){
    destroy();
}

template<typename T>
void Sorted<T>::add(T elem){
    if(size==capacity)
        resize();
    
    arr[size] = elem;
    size++;
    sort();
}

template<typename T>
void Sorted<T>::remove(){
    if(size>0)
        size--;
}


template<typename T>
T Sorted<T>::operator[](int index){
    T result = arr[index];
    return result;
}

template<typename T>
const T Sorted<T>::operator[](int index) const{
    return arr[index];
}


template<typename T>
std::size_t Sorted<T>::getsize() const{
    return size;
}

template<typename T>
void Sorted<T>::filter(Predicate p){
    T *newArr = new T[capacity];
    std::size_t newSize = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (p(arr[i]))
        {
            newArr[newSize++] = arr[i];
        }
    }
    delete[] arr;
    arr = newArr;
    size = newSize;
}

template<typename T>
void Sorted<T>::map(Mapfn f){
    for(int i=0; i<size; i++){
        arr[i] = f(arr[i]);
    }
}

template<typename T>
bool Sorted<T>::search(T elem) const{
    int low=0;
    int high=size-1;
    while(low!=high){
        int mid = (high+low)/2;

        if(arr[mid]==elem)
            return true;

        if(arr[mid]>elem)
            high=mid-1;

        if(arr[mid]<elem)
            low=mid+1; 
    }
    return false;
}


template<typename T>
const std::ostream &operator<<(std::ostream &stream, const Sorted<T> &s){
    for(int i=0; i<s.getsize(); i++){
        stream<<s[i]<<" ";
    }
    stream << '\n';
    return stream;
}

#endif