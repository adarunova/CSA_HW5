#include "bee.h"
#include "honey_pot.h"
#include "winnie_the_pooh.h"

// Данные, передаваемые в поток.
struct Package {
    // Пчела, отвечающая за данный поток.
    Bee *bee;
    // Горшок с мёдом.
    HoneyPot *honey_pot;
    // Винни-Пух.
    WinnieThePooh *winnie_the_pooh;

    // Файл для вывода результатов работы потока.
    FILE *file_out;
};
