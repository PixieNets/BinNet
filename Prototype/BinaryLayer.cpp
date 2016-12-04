//
// Created by Zal on 11/19/16.
//

#include <assert.h>
#include <cmath>

#include "BinaryLayer.h"

using namespace bd;

BinaryLayer::BinaryLayer(uint w, uint h) {
    this->bl_width = w;
    this->bl_height = h;
    this->bl_binMtx = new BinaryMatrix(w, h);
    this->bl_alpha = 1.0;
}

BinaryLayer::BinaryLayer(arma::umat input2D) {
    this->bl_width = input2D.n_cols;
    this->bl_height = input2D.n_rows;
    this->bl_binMtx = new BinaryMatrix(input2D);
    this->bl_alpha = arma::mean(arma::mean(arma::abs(input2D)));
}

BinaryLayer::~BinaryLayer() {
    std::cout << "Called destructor binary layer, for pointer " << this->bl_binMtx << "\n";
    if(this->bl_binMtx != nullptr)
        delete this->bl_binMtx;
}

/**
 * Converts double precision 2D weights matrix in Armadillo to single
 * bit representation binary weights matrix
 * @param data - double precision 2D weights matrix
 */
void BinaryLayer::binarizeMat(arma::mat data) {
    assert((this->bl_width * this->bl_height) == (data.n_rows * data.n_cols));

    uint n_elems = this->bl_width * this->bl_height;
    for (uint row = 0; row < data.n_rows; ++row) {
        for (uint col = 0; col < data.n_cols; ++col) {
            uint8 result = (data(row, col) >= 0.0) ? BIT_ONE : BIT_ZERO;
            printf("[binarizeMat] data[%d, %d] = %f, result = %s\n", row, col, data(row, col),
                   this->bl_binMtx->uint8ToString(result).c_str());
            this->bl_binMtx->setValueAt(row, col, result);
        }
    }
    this->bl_alpha = arma::sum(arma::sum(arma::abs(data)))/ n_elems;
}

/**
 * Converts double precision weights matrix to single-bit representation
 * binary weights matrix
 * @param weights - double precision weights values matrix
 * @param size - #elements in the weights matrix
 */
void BinaryLayer::binarizeWeights(double *weights, int size) {
    assert(size == (this->bl_binMtx->width() * this->bl_binMtx->height()));

    double bl_alpha = 0.0;
    for (uint i = 0;  i < size; ++i) {
        bl_alpha += std::fabs(weights[i]);
        this->bl_binMtx->setValueAt(i, (weights[i] >= 0)? BIT_ONE:BIT_ZERO);
    }
    this->bl_alpha = bl_alpha / size;
}

/**
 *
 * @param weights
 * @param size
 */
void BinaryLayer::getDoubleWeights(double **weights, int *size) {
    if(*weights == nullptr) {
        *weights = new double[bl_binMtx->width()*bl_binMtx->height()];
        *size = bl_binMtx->width()*bl_binMtx->height();
    }
    else {
        assert(bl_binMtx->width()*bl_binMtx->height() == *size);
    }
    for(int i = 0; i < *size; ++i) {
        *weights[i] = this->bl_binMtx->getValueAt(i);
    }
}

BinaryLayer BinaryLayer::operator*(const BinaryLayer&other) {
    BinaryMatrix resultMtx = (*(this->bl_binMtx)) * (*(other.bl_binMtx));
    BinaryLayer result = BinaryLayer(resultMtx.width(), resultMtx.height());
    result.bl_binMtx = new BinaryMatrix(resultMtx);
    result.bl_alpha = this->bl_alpha * other.bl_alpha;
    return result;
}

BinaryLayer BinaryLayer::im2col(uint block_width, uint block_height, uint padding, uint stride) {
    BinaryMatrix resultMtx = this->bl_binMtx->im2col(block_width, block_height, padding, stride);
    BinaryLayer result = BinaryLayer(resultMtx.width(), resultMtx.height());
    *result.bl_binMtx = resultMtx;
    result.bl_alpha = this->bl_alpha;
    return result;
}

BinaryLayer BinaryLayer::repmat(uint n_rows, uint n_cols) {
    BinaryMatrix resultMtx = this->bl_binMtx->repmat(n_rows, n_cols);
    BinaryLayer result = BinaryLayer(resultMtx.width(), resultMtx.height());
    *result.bl_binMtx = resultMtx;
    result.bl_alpha = this->bl_alpha;
    return result;
}

BinaryLayer BinaryLayer::reshape(uint new_rows, uint new_cols) {
    BinaryMatrix resultMtx = this->bl_binMtx->reshape(new_rows, new_cols);
    BinaryLayer result = BinaryLayer(resultMtx.width(), resultMtx.height());
    *result.bl_binMtx = resultMtx;
    result.bl_alpha = this->bl_alpha;
    return result;
}
