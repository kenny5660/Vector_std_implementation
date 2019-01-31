#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Vector_std_implementation/vector.h"
#include <map>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vector_std_implementation_Unit_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(push_back_test){
			const Vector<int>::size_type size = 10000;
			Vector<int> vec;
			for (int i = 0; i < size; ++i) {
				vec.push_back(i);
			}
			Assert::AreEqual(vec.size(),size);
			for (int i = 0; i < size; ++i) {
				Assert::AreEqual(vec[i],i);
			}
		}
		TEST_METHOD(iter_op_inc_test){
			const Vector<int>::size_type size = 10000;
			Vector<int> vec;
			for (int i = 0; i < size; ++i) {
				vec.push_back(i);
			}
			Assert::AreEqual(vec.size(),size);
			int i = 0;
			for (auto it = vec.begin(); it < vec.end(); ++it) {
				Assert::AreEqual(*it,i);
                          i++;
			}
		}
		TEST_METHOD(at_const_test){
			const Vector<int>::size_type size = 10000;
			Vector<int> vec;
			for (int i = 0; i < size; ++i) {
				vec.push_back(i);
			}
			const Vector<int>& ref_vec = vec;
            Assert::AreEqual(ref_vec.size(), size);
			for (int i = 0; i < size; ++i) {
				Assert::AreEqual(ref_vec.at(i),i);
			}
		}
		TEST_METHOD(at_const_op_test){
			const Vector<int>::size_type size = 10000;
			Vector<int> vec;
			for (int i = 0; i < size; ++i) {
				vec.push_back(i);
			}
			const Vector<int>& ref_vec = vec;
            Assert::AreEqual(ref_vec.size(), size);
			for (int i = 0; i < size; ++i) {
				Assert::AreEqual(ref_vec[i],i);
			}
		}
		TEST_METHOD(constructor_default_test){
			const Vector<int>::size_type size = 0;
			Vector<int> vec;
            Assert::AreEqual(vec.size(), size);
			vec.push_back(113);
            Assert::AreEqual(vec.back(), 113);
		}
		TEST_METHOD(constructor_size_test){
			const Vector<int>::size_type size = 10000;
			Vector<int> vec(size);
            Assert::AreEqual(vec.size(), size);
			vec[size-1] = 113;
            Assert::AreEqual(vec[size - 1], 113);
		}
		TEST_METHOD(constructor_size_with_val_test){
			const Vector<int>::size_type size = 10000;
			const int val =113;
			Vector<int> vec(size,val);
            Assert::AreEqual(vec.size(), size);
			for (int i = 0; i < size; ++i) {
				Assert::AreEqual(vec[i],val);
			}
		}
		TEST_METHOD(constructor_initializer_list_test){
			Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
                  Assert::AreEqual(vec.size(), (Vector<int>::size_type)10);
			for (int i = 0; i < 10; ++i) {
				Assert::AreEqual(vec[i],i+1);
			}
		}
		TEST_METHOD(constructor_copy_test){
			Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
			Vector<int> vec2(vec);
            Assert::AreEqual(vec2.size(), (Vector<int>::size_type)10);
			for (int i = 0; i < 10; ++i) {
				Assert::AreEqual(vec2[i],i+1);
			}
		}
		TEST_METHOD(constructor_iterators_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
			Vector<int> vec2(vec.begin(),vec.end());
            Assert::AreEqual(vec2.size(), (Vector<int>::size_type)10);
			for (int i = 0; i < 10; ++i) {
				Assert::AreEqual(vec2[i],i+1);
			}
		}
		TEST_METHOD(op_asig_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
			Vector<int> vec2;
            vec2 = vec;
			vec[0] = 113;
            Assert::AreEqual(vec2.size(), (Vector<int>::size_type)10);
			for (int i = 0; i < 10; ++i) {
				Assert::AreEqual(vec2[i],i+1);
			}
		}
		TEST_METHOD(clear_empty_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
			Assert::AreEqual(vec.empty(), false);
            vec.clear();
            Assert::AreEqual(vec.size(), (Vector<int>::size_type)0);
			Assert::AreEqual(vec.empty(), true);
		}
		TEST_METHOD(front_back_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
            Assert::AreEqual(vec.front(), 1);
			Assert::AreEqual(vec.back(), 10);
		}
		TEST_METHOD(front_back_const_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
			const Vector<int>& ref_vec = vec;
            Assert::AreEqual(ref_vec.front(), 1);
			Assert::AreEqual(ref_vec.back(), 10);
		}
		TEST_METHOD(insert_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
			auto it = vec.begin()+3;
            auto it2 = vec.insert(it, 13);
            Assert::AreEqual(*it, 13);
            Assert::AreEqual(*it2, 13);
			Assert::AreEqual(vec[3], 13);
            Assert::AreEqual(vec[4], 4);
			Assert::AreEqual(vec.back(), 10);
		}
		TEST_METHOD(emplace_test){
            Vector<std::pair<int,int>> vec = {{1,2},{2,3},{3,4},{4,5},{5,6}};
			auto it = vec.begin()+3;
            auto it2 = vec.emplace(it, 12,13);
            Assert::AreEqual(*it == std::pair<int,int>{12,13},true);
            Assert::AreEqual(*it2 == std::pair<int, int>{12, 13}, true);
            Assert::AreEqual(vec[3] == std::pair<int, int>{12, 13}, true);
            Assert::AreEqual(vec[4] == std::pair<int, int>{4, 5}, true);
            Assert::AreEqual(vec.back() == std::pair<int, int>{5, 6}, true);
		}
		TEST_METHOD(emplace_back_test){
            Vector<std::pair<int,int>> vec = {{1,2},{2,3},{3,4},{4,5},{5,6}};
            auto it2 = vec.emplace_back(12,13);
            Assert::AreEqual(*it2 == std::pair<int, int>{12, 13}, true);
            Assert::AreEqual(vec.back() == std::pair<int, int>{12, 13}, true);
		}
		TEST_METHOD(erase_iter_test){
            Vector<std::pair<int,int>> vec = {{1,2},{2,3},{3,4},{4,5},{5,6}};
			auto it_first = vec.begin()+1;
            auto it_last = vec.begin() + 3;
			auto it2 = vec.erase(it_first,it_last);
            Assert::AreEqual(vec.size(), (Vector<int>::size_type)3);
            Assert::AreEqual(*it2 == std::pair<int, int>{4, 5}, true);
            Assert::AreEqual(vec.back() == std::pair<int, int>{5, 6}, true);
            Assert::AreEqual(vec.front() == std::pair<int, int>{1, 2}, true);
		}
		TEST_METHOD(erase_test){
            Vector<std::pair<int,int>> vec = {{1,2},{2,3},{3,4},{4,5},{5,6}};
			auto it_first = vec.begin()+1;
			auto it2 = vec.erase(it_first);
            Assert::AreEqual(vec.size(), (Vector<int>::size_type)4);
            Assert::AreEqual(*it2 == std::pair<int, int>{3, 4}, true);
            Assert::AreEqual(vec.back() == std::pair<int, int>{5, 6}, true);
            Assert::AreEqual(vec.front() == std::pair<int, int>{1, 2}, true);
		}
		TEST_METHOD(pop_back_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
            vec.pop_back();
            Assert::AreEqual(vec.size(), (Vector<int>::size_type)9);
			Assert::AreEqual(vec.back(), 9);
		}
		TEST_METHOD(rbegin_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
           auto it =  vec.rbegin();
			Assert::AreEqual(vec.back(), *it);
           it++;
		   Assert::AreEqual(*(vec.end()-2), *it);
		}
		TEST_METHOD(rbegin_const_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
		    const Vector<int>& ref_vec = vec;
            auto it = ref_vec.rbegin();
            Assert::AreEqual(ref_vec.back(), *it);
            it++;
            Assert::AreEqual(*(ref_vec.end() - 2), *it);
		}

		TEST_METHOD(rend_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
           auto it =  vec.rend();
            it--;
			Assert::AreEqual(vec.front(), *it);
		}
		TEST_METHOD(rend_const_test){
            Vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
			const Vector<int>& ref_vec = vec;
            auto it = ref_vec.rend();
            it--;
			Assert::AreEqual(vec.front(), *it);
		}

	};
}