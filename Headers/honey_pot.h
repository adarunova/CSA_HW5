#ifndef CSA_HW5_HONEY_POT_H
#define CSA_HW5_HONEY_POT_H

// Горшок с мёдом.
class HoneyPot {
private:
    // Вместимость горшка.
    int capacity_;
    // Текущее количество глотков в горшке.
    int sips_count_;

public:
    // Конструктор.
    explicit HoneyPot(int capacity);

    // Проверка, заполнен ли горшок полностью.
    bool isFull() const;

    // Добавление глотка в горшок.
    void addSip();

    // Опустошение горшка.
    void emptyPot();

    // Вывод информации о горшке.
    void print(FILE *file_out) const;
};

#endif //CSA_HW5_HONEY_POT_H
