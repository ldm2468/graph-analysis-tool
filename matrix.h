#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <vector>

namespace snu {
    class Matrix {
    public:
        const size_t rows, cols;

        Matrix(size_t r, size_t c);
        double &at(unsigned int r, unsigned int c);
        void mul(const std::vector<double> &v, std::vector<double> &res);
        void mul(const Matrix &m, Matrix &res);

    private:
        std::vector<double> dat;
    };
}

#endif //MATRIX_H
