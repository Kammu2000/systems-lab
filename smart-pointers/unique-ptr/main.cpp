#include <iostream>
#include <utility>

#include "unique_ptr.hpp"

struct Person
{
    std::string name;

    void greet() const { std::cout << "Hello " << name << "\n"; }
};

int main()
{
    UniquePtr<int> ptr(new int(5));
    std::cout << *ptr << "\n";

    UniquePtr<int> other_ptr = std::move(ptr);
    std::cout << other_ptr.get() << "\n";
    std::cout << ptr.get() << "\n";

    UniquePtr<Person> person_ptr(new Person{"deepanshu"});
    person_ptr->greet();

    return 0;
}
