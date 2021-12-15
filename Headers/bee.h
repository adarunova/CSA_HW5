#ifndef CSA_HW5_BEE_H
#define CSA_HW5_BEE_H

#include "random.h"

// Пчела.
class Bee {
private:
    // Номер пчелы.
    int id_;
    Random flight_time_ = Random(100, 500);

public:
    // Конструктор.
    explicit Bee(int id);

    // Выводит сообщение о действии пчелы.
    void bringHoney(FILE *file_out) const;

    // Получение времени, на которое улетает пчела.
    int flyAway(FILE *file_out) const;

    // Пчела прекращает приносить мёд.
    void stopBringHoney(FILE *file_out) const;
};

#endif //CSA_HW5_BEE_H
