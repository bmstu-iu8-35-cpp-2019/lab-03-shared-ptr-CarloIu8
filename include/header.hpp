// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <atomic>
#include <exception>
#include <iostream>

template <typename T>
class SharedPtr {
 public:
  SharedPtr() {
    ptr = nullptr;
    number = nullptr;
  }
  explicit SharedPtr(T* pt) {
    ptr = pt;
    number = new std::atomic<int>;
    *number = 1;
  }
  SharedPtr(const SharedPtr& r) {
    if (r) {
      ptr = r.ptr;
      number = r.number;
      (*number)++;
    }
  }
  ~SharedPtr() {
    if (number == nullptr || ptr == nullptr) return;
    (*number)--;
    if (*number == 0) {
      delete ptr;
      delete number;
    }
  }
  // SharedPtr(SharedPtr&& r);
  SharedPtr& operator=(const SharedPtr& r) {
    if (*this && r) {
      (*number)--;
      if (*number == 0) {
        delete ptr;
        delete number;
        ptr = nullptr;
        number = nullptr;
      }
      ptr = r.ptr;
      number = r.number;
      (*number)++;
    } else {
      ptr = r.ptr;
      number = r.number;
      (*number)++;
    }
    return *this;
  }
  operator bool() const {
    if (ptr == nullptr || number == nullptr) return false;
    return true;
  }
  T& operator*() const { return *ptr; }
  T* operator->() const { return ptr; }

  T* get() { return ptr; }
  void reset() {
    if (*this) {
      if (*number == 1) {
        delete number;
        delete ptr;
        ptr = nullptr;
        number = nullptr;
      } else if (*number > 1) {
        (*number)--;
        ptr = nullptr;
      }
    }
  }
  void vivod() {
    std::cout << "Value " << *ptr << " "
              << "Count ";
    std::cout << use_count() << std::endl;
  }
  void reset(T* pt) {
    if (*this) {
      (*number)--;
      if (*number == 0) {
        delete number;
        delete ptr;
        ptr = nullptr;
        number = nullptr;
      }
      ptr = pt;
      number = new std::atomic<int>;
      *number = 1;
    } else {
      ptr = pt;
      number = new std::atomic<int>;
      *number = 1;
    }
  }
  void Swap(SharedPtr& r) {
    SharedPtr a;
    a = r;
    r = *this;
    *this = a;
  }

  size_t use_count() const { return static_cast<size_t>(*number); }

 private:
  T* ptr;
  std::atomic<int>* number;
};
#endif  // INCLUDE_HEADER_HPP_
