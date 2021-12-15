#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../Headers/package.h"

// Максимальное количество пчёл.
const int MAX_BEES_NUMBER = 100;

// Максимальная вместимость горшка.
const int MAX_POT_CAPACITY_NUMBER = 1000;

// Максимальная количество порций, которые насыщают Винни-Пуха.
const int MAX_STATURE_POTS = 100;

// Мьютекс для синхронизации заполнения пчёлами горшка.
pthread_mutex_t mutex;


void errorMessage1() {
    printf("Incorrect command line!\n"
           "  Waited:\n"
           "     command -f input_file output_file\n"
           "  Or:\n"
           "     command -n <number1> <number2> <number3> output_file\n");
}

void errorMessage2() {
    printf("Incorrect qualifier value!\n"
           "  Waited:\n"
           "     command -f input_file output_file\n"
           "  Or:\n"
           "     command -n <number1> <number2> <number3> output_file\n");
}

void errorMessage3() {
    printf("Incorrect data format in the file!\n");
}

void errorMessage4() {
    printf("Incorrect number of bees. Set 0 < number <= %d\n", MAX_BEES_NUMBER);
}

void errorMessage5() {
    printf("Incorrect pot capacity. Set 0 < number <= %d\n", MAX_POT_CAPACITY_NUMBER);
}

void errorMessage6() {
    printf("Incorrect number of pots Winnie-the-Pooh can eat. Set 0 < number <= %d\n",
           MAX_STATURE_POTS);
}


// Считывает количество пчёл, вместимость горшка и количество порций, которые насыщают Винни-Пуха, из файла.
// Если количество данных в файле корректно, то возвращает true, иначе false.
bool readArguments(FILE *file_in, int &bees, int &pot_capacity, int &saturate_pots) {
    if (fscanf(file_in, "%d", &bees) != EOF) {
        if (fscanf(file_in, "%d", &pot_capacity) != EOF) {
            fscanf(file_in, "%d", &saturate_pots);
            return true;
        }
    }
    return false;
}


// Устанавливает данные.
int setData(int argc, char *argv[], int &bees, int &pot_capacity, int &saturate_pots) {
    if (argc != 6 && argc != 4) {
        errorMessage1();
        return 1;
    }

    if (argc == 4 && !strcmp(argv[1], "-f")) {
        FILE *file_in = fopen(argv[2], "r");
        if (file_in == nullptr) {
            printf("Cannot find file with name %s\n", argv[2]);
            return 7;
        }
        if (!readArguments(file_in, bees, pot_capacity, saturate_pots)) {
            errorMessage3();
            return 3;
        }
        fclose(file_in);
    } else if (argc == 6 && !strcmp(argv[1], "-n")) {
        bees = atoi(argv[2]);
        pot_capacity = atoi(argv[3]);
        saturate_pots = atoi(argv[4]);
    } else {
        errorMessage2();
        return 2;
    }

    if (bees <= 0 || bees > MAX_BEES_NUMBER) {
        errorMessage4();
        return 4;
    }
    if (pot_capacity <= 0 || pot_capacity > MAX_POT_CAPACITY_NUMBER) {
        errorMessage5();
        return 5;
    }
    if (saturate_pots <= 0 || saturate_pots > MAX_STATURE_POTS) {
        errorMessage6();
        return 6;
    }
    return 0;
}


// Метод, используемый в многопоточности. Моделирует работу пчёл.
void *fillHoneyPot(void *param) {
    auto *package = (Package *) param;

    // В один момент времени только одна пчела может положить мёд в горшок.
    pthread_mutex_lock(&mutex);
    // Пчёлы приносят мёд пока Винни-Пух не насытится.
    if (!package->winnie_the_pooh->isSatiated()) {
        package->bee->bringHoney(package->file_out);
        package->honey_pot->addSip();
        package->honey_pot->print(package->file_out);

        int sleep_milliseconds = package->bee->flyAway(package->file_out);

        if (package->honey_pot->isFull()) {
            package->winnie_the_pooh->eatPot(package->file_out);
            package->honey_pot->emptyPot();
        }
        pthread_mutex_unlock(&mutex);

        usleep(sleep_milliseconds);

        fillHoneyPot(param);
        return nullptr;
    }
    pthread_mutex_unlock(&mutex);

    // Окончание выполнения потока (пчёлы перкращают нести мёд).
    package->bee->stopBringHoney(package->file_out);
    return nullptr;
}


int main(int argc, char *argv[]) {
    // Начальное время.
    clock_t start_time = clock();

    // Количество пчёл (n).
    int bees;
    // Вместимость горшка (H).
    int pot_capacity;
    // Количество порций, необходимых для насыщения.
    int saturate_pots;

    int result = setData(argc, argv, bees, pot_capacity, saturate_pots);
    if (result) {
        return result;
    }

    FILE *file_out = fopen(argv[argc - 1], "w");

    auto *honey_pot = new HoneyPot(pot_capacity);
    auto *winnie_the_pooh = new WinnieThePooh(saturate_pots);

    auto *threads = new pthread_t[bees];
    auto *thread_info = new Package[bees];

    // Создание дочерних потоков.
    for (int i = 0; i < bees; ++i) {
        thread_info[i] = {new Bee(i + 1), honey_pot, winnie_the_pooh, file_out};
        pthread_create(&threads[i], nullptr, fillHoneyPot, (void *) &thread_info[i]);
    }

    // Время начла работы потоков.
    clock_t thread_started_time = clock();

    // Ожидание завершения работы дочерних потоков.
    for (int i = 0; i < bees; i++) {
        pthread_join(threads[i], nullptr);
    }

    fclose(file_out);
    for (int i = 0; i < bees; ++i) {
        delete thread_info[i].bee;
    }
    delete[] thread_info;
    delete[] threads;
    delete honey_pot;
    delete winnie_the_pooh;

    // Конечное время.
    clock_t end_time = clock();

    printf("Threads started: %.6f sec\n", (double) (thread_started_time - start_time) / CLOCKS_PER_SEC);
    printf("Time taken: %.6f sec\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
