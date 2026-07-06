#pragma once

#include <utility>

template <typename T>
class UniquePtr
{
  public:
    explicit UniquePtr(T* other_ptr = nullptr) : ptr(other_ptr) {};
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other_ptr) noexcept : ptr(other_ptr.ptr) { other_ptr.ptr = nullptr; };
    UniquePtr& operator=(UniquePtr&& other_ptr) noexcept
    {
        if (ptr != other_ptr.ptr)
        {
            delete ptr;
            ptr = other_ptr.ptr;
            other_ptr.ptr = nullptr;
        }

        return *this;
    };
    ~UniquePtr()
    {
        delete ptr;
        ptr = nullptr;
    };

    T* get() const { return ptr; }
    T* operator->() const { return ptr; }
    T& operator*() const { return *ptr; }

    T* release()
    {
        T* old = ptr;
        ptr = nullptr;
        return old;
    }

    void reset(T* other_ptr = nullptr)
    {
        delete ptr;
        ptr = other_ptr;
    }

    void swap(UniquePtr& other_ptr) noexcept { std::swap(ptr, other_ptr.ptr); }

  private:
    T* ptr;
};
