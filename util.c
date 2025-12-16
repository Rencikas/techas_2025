#include <sys/stat.h>
#include <direct.h>
#include <stdio.h>
#include "car.h"

void ensure_data_dir() {
    struct _stat st = {0};
    if (_stat("data", &st) == -1) {
        _mkdir("data");
    }
}
