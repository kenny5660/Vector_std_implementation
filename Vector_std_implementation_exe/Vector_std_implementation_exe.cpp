// Vector_std_implementation_exe.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "../Vector_std_implementation/vector.h"
int main()
{
  Vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Vector<int> vec2(vec);
  vec.push_back(20);
  vec.push_back(21);
  vec.push_back(22);
  vec.push_back(23);
  vec.push_back(24);
  vec.push_back(25);
  vec.push_back(26);
  vec.push_back(27);
    std::cout << "Hello World!\n"; 
}

