#include <stdio.h>
#include "../Headers/winnie_the_pooh.h"

// Конструктор.
WinnieThePooh::WinnieThePooh(int saturate_pots_number) {
    eaten_pots_ = 0;
    saturate_pots_ = saturate_pots_number;
}

// Съесть горшок мёда.
void WinnieThePooh::eatPot(FILE *file_out) {
    ++eaten_pots_;
    printf("WINNIE-THE-POOH: ate %d pots of honey.\n\n", eaten_pots_);
    fprintf(file_out, "WINNIE-THE-POOH: ate %d pots of honey.\n\n", eaten_pots_);
}

// Наелся ли Винни-Пух.
bool WinnieThePooh::isSatiated() const {
    return (eaten_pots_ == saturate_pots_);
}
