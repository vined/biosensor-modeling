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

std::vector<std::string> readLines(char *buf, int size) {

    int j = 0;
    std::string d_str = "";
    std::vector<std::string> lines;

    for (unsigned i = 0; i < size; i++) {
        char c = buf[i];
        if (c == '\n') {
            lines.push_back(d_str);
            d_str = "";
            j++;
        } else {
            d_str.append(1, c);
        }
    }

    return lines;
}

std::vector<std::string> readFileLines(char *fileName) {

    MPI_File file;
    openFile(fileName, &file);

    int fileSize = getFileSize(file);
    char *buf = (char *) malloc(fileSize);
    MPI_File_read(file, buf, fileSize, MPI_CHAR, MPI_STATUS_IGNORE);

    std::vector<std::string> lines = readLines(buf, fileSize);

    MPI_File_close(&file);
    free(buf);

    return lines;
}
