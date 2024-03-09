#include "forward_list.h"
#include <algorithm>
#include <iterator>
#include <iostream>
int main()
{
    forward_list<int> list{1,2,3,4,3,2,1,3,2};
    forward_list<int> list2{5,4,6,5,3};
    list.print();
    list.assign({110,333,234,221,3332});
    // std::for_each(list.begin(), list.end(), [](int value){std::cout << value << "  ";});
    list.clear();
    list.print();
    return 0;



return 0;
}