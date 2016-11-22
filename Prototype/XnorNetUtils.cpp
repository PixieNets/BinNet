//
// Created by Zal on 11/21/16.
//

#include "XnorNetUtils.h"

#include <assert.h>

/**
 * Binarizes an input double-precision 2D data slice to a 2D binary matrix
 * @param data - a 2D matrix of size H x W
 * @return 2D binary matrix representation of input data slice
 */
BinaryMatrix* XnorNetUtils::centerDataMat(arma::mat data) {
    BinaryMatrix *ch = new BinaryMatrix(data.n_rows, data.n_cols);
    arma::mat centered_data = (data - mean(mean(data))) / stddev(stddev(data));
    int n_elems = data.n_rows * data.n_cols;
    for (int i = 0; i < n_elems; ++i) {
        ch->setValueAt(i, (centered_data(i) >= 0.0) ? BIT_ONE:BIT_ZERO);
    }
    return ch;
}

/**
 * Binarizes an input double-precision data matrix to a 3D binary matrix
 * @param data - a 3D matrix of size H X W X N
 * @return 3D binary matrix representation of input data
 */
BinaryTensor XnorNetUtils::normalizeData(arma::cube data) {

    BinaryTensor binMat = new BinaryLayer*[data.n_slices];
    for (int ch = 0; ch < data.n_slices; ++ch) {
        arma::mat centered_data = (data.slice(ch) - mean(mean(data.slice(ch)))) / stddev(stddev(data.slice(ch)));
        binMat[ch] = new BinaryLayer(data.n_cols, data.n_rows);
        binMat[ch]->binarizeMat(centered_data);
    }

    return binMat;
}