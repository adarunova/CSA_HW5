#ifndef CSA_HW5_WINNIE_THE_POOH_H
#define CSA_HW5_WINNIE_THE_POOH_H

// Винни-Пух.
class WinnieThePooh {
private:
    // Количество съеденных порций.
    int eaten_pots_;
    // Количество порций, необходимых для насыщения.
    int saturate_pots_;

public:
    // Конструктор.
    explicit WinnieThePooh(int saturate_pots_number);

    // Съесть горшок мёда.
    void eatPot(FILE *file_out);

    // Наелся ли Винни-Пух.
    bool isSatiated() const;
};

#endif //CSA_HW5_WINNIE_THE_POOH_H
