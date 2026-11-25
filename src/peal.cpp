#include "rostov/peal.hpp"

namespace rostov {
namespace {

[[noreturn]] void notReady() {
    // Не PealError: иначе тест на ошибку длины станет зелёным раньше решения.
    throw std::logic_error("ещё не написано");
}

}  // namespace

Peal::Peal() {}

Peal::Peal(int) {
    notReady();
}

Peal::Peal(const Stroke*, int) {
    notReady();
}

Peal::Peal(const Peal&) {
    notReady();
}

// noexcept: отсюда нельзя бросать исключение, процесс оборвётся.
// Пока источник не опустошается, тесты на перемещение красные.
Peal::Peal(Peal&&) noexcept {}

Peal::~Peal() {
    // Освободите strokes_. delete[] nullptr вызывать можно.
}

Peal& Peal::operator=(const Peal&) {
    notReady();
}

// Заглушка ничего не делает. Для присваивания себе это случайно похоже
// на правильный ответ, чужое перемещение она не выполняет.
Peal& Peal::operator=(Peal&&) noexcept {
    return *this;
}

int Peal::size() const {
    return count_;
}

Stroke& Peal::operator[](int) {
    notReady();
}

const Stroke& Peal::operator[](int) const {
    notReady();
}

Peal Peal::operator+(const Peal&) const {
    notReady();
}

Peal& Peal::operator+=(const Peal&) {
    notReady();
}

bool Peal::operator==(const Peal&) const {
    notReady();
}

bool Peal::operator!=(const Peal&) const {
    notReady();
}

Peal::operator int() const {
    if (count_ == 0) {
        return 0;
    }
    notReady();
}

}  // namespace rostov
