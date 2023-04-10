#include <iostream>
#include "sorted.hpp"

int main(){

    int arr1[9] = {3,2,1,5,9,4,7,6,8};
    Sorted<int> a(arr1, 9);
    //std::cout<<a;
    const Sorted<int> a2(a);
    a.add(0);
    //std::cout<<a2[2]<<'\n';
    Sorted<int> a3(a);
    
    a.remove();
    a3=a;
    std::cout<<a3;
    //std::cout<<a.search(2);
    int val = 5;

    a3.filter([val](const int& num){ return num>val; });
    std::cout<<a3;

    a3.map([val](const int& num){return num*val;});
    std::cout<<a3;

}