//
// Created by Esha Uboweja on 12/4/16.
//

#include "BinaryTensor3D.h"

using namespace bd;

BinaryTensor3D::BinaryTensor3D(uint rows, uint cols, uint channels, uint8 value) {

}

BinaryTensor3D::BinaryTensor3D(uint rows, uint cols, uint channels, bool randomized, uint n) {

}

BinaryTensor3D::BinaryTensor3D(arma::ucube tensor) {
    this->bt3_rows = (uint) tensor.n_rows;
    this->bt3_cols = (uint) tensor.n_cols;
    this->bt3_channels = (uint) tensor.n_slices;
    uint n_elems = this->bt3_rows * this->bt3_cols * this->bt3_channels;

    this->bt3_tensor.reserve(this->bt3_channels);
    for (uint ch = 0; ch < this->bt3_channels; ++ch) {
        this->bt3_tensor.emplace_back(new BinaryLayer(tensor.slice(ch)));
    }
    this->bt3_alpha = arma::accu(arma::abs(tensor)) / (double) n_elems;
}

BinaryTensor3D::BinaryTensor3D(const BinaryTensor3D &tensor) {

}

BinaryTensor3D::~BinaryTensor3D() {

}

BinaryLayer BinaryTensor3D::im2col(uint block_width, uint block_height, uint padding, uint stride) {
    BinaryLayer result(0,0);
    return result;
}
