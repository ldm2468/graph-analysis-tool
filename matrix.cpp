#include "matrix.h"

snu::Matrix::Matrix(const size_t r, const size_t c) : rows(r), cols(c) {
    dat.resize(r * c);
}

double &snu::Matrix::at(unsigned int r, unsigned int c) {
    return dat[r * cols + c];
}

void snu::Matrix::mul(const std::vector<double> &v, std::vector<double> &res) {
    res.reserve(rows);
    for (unsigned int r = 0; r < rows; r++) {
        double acc = 0;
        for (unsigned int c = 0; c < cols; c++) {
            acc += dat[r * cols + c] * v[c];
        }
        res[r] = acc;
    }
}

void snu::Matrix::mul(const Matrix &m, Matrix &res) {
    for (unsigned int r = 0; r < rows; r++) {
        for (unsigned int c = 0; c < m.cols; c++) {
            double acc = 0;
            for (unsigned int i = 0; i < cols; i++) {
                acc += dat[r * cols + i] * m.dat[i * m.cols + c];
            }
            res.at(r, c) = acc;
        }
    }
}
