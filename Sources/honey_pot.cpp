#include <stdio.h>
#include "../Headers/honey_pot.h"

// Конструктор.
HoneyPot::HoneyPot(int capacity) {
    capacity_ = capacity;
    // Вот горшок пустой, - он предмет простой...
    sips_count_ = 0;
}

// Проверка, заполнен ли горшок полностью.
bool HoneyPot::isFull() const {
    return sips_count_ == capacity_;
}

// Добавление глотка в горшок.
void HoneyPot::addSip() {
    ++sips_count_;
}

// Опустошение горшка.
void HoneyPot::emptyPot() {
    sips_count_ = 0;
}

// Вывод информации о горшке.
void HoneyPot::print(FILE *file_out) const {
    printf("HONEY POT: full for %d/%d sips.\n", sips_count_, capacity_);
    fprintf(file_out, "HONEY POT: full for %d/%d sips.\n", sips_count_, capacity_);
}

