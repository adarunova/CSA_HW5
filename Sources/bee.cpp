#include <stdio.h>
#include "../Headers/bee.h"

// Конструктор.
Bee::Bee(int id) {
    id_ = id;
}

// Выводит сообщение о действии пчелы.
void Bee::bringHoney(FILE *file_out) const {
    printf("BEE %d: put one sip of honey in a pot.\n", id_);
    fprintf(file_out, "BEE %d: put one sip of honey in a pot.\n", id_);
}

// Получение времени, на которое улетает пчела.
int Bee::flyAway(FILE *file_out) const {
    int milliseconds = flight_time_.get();
    printf("BEE %d: fly away for %d seconds.\n\n", id_, milliseconds);
    fprintf(file_out, "BEE %d: fly away for %d seconds.\n\n", id_, milliseconds);
    return milliseconds;
}

// Пчела прекращает приносить мёд.
void Bee::stopBringHoney(FILE *file_out) const {
    printf("BEE %d: stop bringing honey.\n", id_);
    fprintf(file_out, "BEE %d: stop bringing honey.\n", id_);
}
