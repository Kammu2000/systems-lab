#pragma once

#include <cstddef>

template <typename T>
class SharedPtr
{
  public:
    explicit SharedPtr(T* other_ptr) : ptr(other_ptr), ref_count(new size_t(1)) {};

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count)
    {
        ++(*ref_count);
    };

    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this == &other)
        {
            return *this;
        }

        --(*ref_count);

        if (*ref_count == 0)
        {
            delete ptr;
            delete ref_count;
        }

        ptr = other.ptr;
        ref_count = other.ref_count;
        ++(*ref_count);

        return *this;
    };

    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count)
    {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    };

    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
        --(*ref_count);

        if (*ref_count == 0)
        {
            delete ptr;
            delete ref_count;
        }

        ptr = other.ptr;
        ref_count = other.ref_count;

        other.ptr = nullptr;
        other.ref_count = nullptr;

        return *this;
    };

    ~SharedPtr()
    {
        delete ptr;
        --(*ref_count);

        if (*ref_count == 0)
        {
            delete ref_count;
        }
    };

  private:
    T* ptr;
    size_t* ref_count;
};
