//#pragma once

namespace RAII {

template <typename T> class Booking {
public:
  Booking(T *pr, int counter) : provider_(pr), counter_(counter) {}

  Booking(const Booking<T> &) = delete;

  Booking(Booking<T> &&other) : provider_(other.provider_) {
    other.provider_ = nullptr;
  }

  Booking<T> &operator=(Booking<T> &) = delete;

  Booking<T> &operator=(Booking<T> &&other) {
    delete provider_;
    provider_ = other.provider_;
    other.provider_ = nullptr;
    return *this;
  }

  ~Booking() {
    if (provider_ != nullptr) {
      provider_->CancelOrComplete(*this);
    }
  }

  T *provider_;
  int counter_;
};

}; // namespace RAII