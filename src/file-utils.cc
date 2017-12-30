#include "mpi.h"
#include <iostream>

#include "file-utils.h"

void openFile(char *fileName, MPI_File *file) {

    int ierr = MPI_File_open(MPI_COMM_WORLD, fileName, MPI_MODE_RDONLY, MPI_INFO_NULL, file);

    if (ierr) {
        std::cout << "Couldn't open file " << fileName << std::endl;
        MPI_Finalize();
    }
}

int getFileSize(MPI_File file) {

    MPI_Offset offset;
    MPI_File_get_size(file, &offset);

    return offset / sizeof(char);
}

void readFile(MPI_File file, int fileSize, char *out) {

    MPI_File_read(file, out, fileSize, MPI_CHAR, MPI_STATUS_IGNORE);
}

int getLinesCount(char *buf, int size) {
    unsigned count = 0;
    for (unsigned i = 0; i < size; i++) {
        if (buf[i] == '\n') {
            count++;
        }
    }

    return count;
}

void readDoubles(char *buf, int size, double *out) {

    int j = 0;
    std::string d_str = "";

    for (unsigned i = 0; i < size; i++) {
        char c = buf[i];
        if (c == '\n') {
            out[j] = std::stod(d_str);
            d_str = "";
            j++;
        } else {
            d_str.append(1, c);
        }
    }
}


int getFileLinesCount(char *fileName) {

    MPI_File file;
    openFile(fileName, &file);

    int fileSize = getFileSize(file);
    char *buf = (char *) malloc(fileSize);
    readFile(file, fileSize, buf);

    int lines = getLinesCount(buf, fileSize);

    MPI_File_close(&file);
    free(buf);

    return lines;
}

void readDoublesFromFile(char *fileName, double *out) {

    MPI_File file;
    openFile(fileName, &file);

    int fileSize = getFileSize(file);
    char *buf = (char *) malloc(fileSize);
    readFile(file, fileSize, buf);

    readDoubles(buf, fileSize, out);

    MPI_File_close(&file);
    free(buf);
}
