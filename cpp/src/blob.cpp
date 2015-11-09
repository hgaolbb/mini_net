/*!
*  Copyright (c) 2015 by hgaolbb
* \file blob.cpp
* \brief all layers implement
*/

#include "../include/blob.hpp"

namespace mini_net {

Blob operator+(Blob& A, const double num) {
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] + num;
    }
    return out;
}
Blob operator+(const double num, Blob& A) {
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] + num;
    }
    return out;
}
Blob operator+(Blob& A, Blob& B) {
    vector<int> sz_A = A.size();
    vector<int> sz_B = B.size();
    for (int i = 0; i < 4; ++i) {
        assert(sz_A[i] == sz_B[i]);
    }
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] + B[i];
    }
    return out;
}
Blob operator-(Blob& A, const double num) {
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] - num;
    }
    return out;
}
Blob operator-(const double num, Blob& A) {
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = num - A[i] ;
    }
    return out;
}
Blob operator-(Blob& A, Blob& B) {
    vector<int> sz_A = A.size();
    vector<int> sz_B = B.size();
    for (int i = 0; i < 4; ++i) {
        assert(sz_A[i] == sz_B[i]);
    }
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] - B[i];
    }
    return out; 
}
Blob operator*(Blob& A, const double num) {
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] * num;
    }
    return out;
}
Blob operator*(const double num, Blob& A) {
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] * num;
    }
    return out;
}
Blob operator*(Blob& A, Blob& B) {
    vector<int> sz_A = A.size();
    vector<int> sz_B = B.size();
    for (int i = 0; i < 4; ++i) {
        assert(sz_A[i] == sz_B[i]);
    }
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] % B[i];
    }
    return out;
}
Blob operator/(Blob& A, const double num) {
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] / num;
    }
    return out;
}
Blob operator/(const double num, Blob& A) {
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = num / A[i];
    }
    return out;
}
Blob operator/(Blob& A, Blob& B) {
    vector<int> sz_A = A.size();
    vector<int> sz_B = B.size();
    for (int i = 0; i < 4; ++i) {
        assert(sz_A[i] == sz_B[i]);
    }
    Blob out(A.size());
    int N = A.get_N();
    for (int i = 0; i < N; ++i) {
        out[i] = A[i] / B[i];
    }
    return out;
}

// convertion
void mat2Blob(mat& mA, shared_ptr<Blob>& out, int c, int h, int w) {
    int n = mA.n_rows;
    assert(mA.n_cols == c*h*w);

    mA = mA.t();
    if (out) {
        out.reset();
    }
    out.reset(new Blob(n, c, h, w));
    for (int i = 0; i < n; ++i) {
        (*out)[i] = cube(mA.colptr(i), h, w, c);
    }
    return;
}

void mat2Blob(mat& mA, shared_ptr<Blob>& out, const vector<int>& sz) {
    int n = mA.n_rows;
    int c = sz[1];
    int h = sz[2];
    int w = sz[3];
    assert(mA.n_cols == c*h*w);

    mA = mA.t();
    if (out) {
        out.reset();
    }
    out.reset(new Blob(n, c, h, w));
    for (int i = 0; i < n; ++i) {
        (*out)[i] = cube(mA.colptr(i), h, w, c);
    }
    return;
}
void mat2Blob(mat& mA, Blob** out, int c, int h, int w) {}
void mat2Blob(mat& mA, Blob** out, const vector<int>& sz) {}

// += -= *= /=
Blob& Blob::operator+=(const double num) {
    for (int i=0; i<N_; ++i) {
        data_[i] = data_[i] + num;
    }
    return *this;
}
Blob& Blob::operator-=(const double num) {
    for (int i=0; i<N_; ++i) {
        data_[i] = data_[i] - num;
    }
    return *this;
}
Blob& Blob::operator*=(const double num) {
    for (int i=0; i<N_; ++i) {
        data_[i] = data_[i] * num;
    }
    return *this;
}

Blob& Blob::operator/=(const double num) {
    for (int i=0; i<N_; ++i) {
        data_[i] = data_[i] / num;
    }
    return *this;
}

//---Blob---
void Blob::setShape(vector<int>& shape) {
    N_ = shape[0];
    C_ = shape[1];
    H_ = shape[2];
    W_ = shape[3];
    data_ = vector<cube>(N_, cube(H_, W_, C_));
    return;
}
Blob::Blob(const int n, const int c, const int h, const int w, int type) :
        N_(n), C_(c), H_(h), W_(w) {
    _init(n, c, h, w, type);
    return;
}

Blob::Blob(const vector<int>& shape, int type) :
        N_(shape[0]), C_(shape[1]), H_(shape[2]), W_(shape[3]) {
    _init(N_, C_, H_, W_, type);
    return;
}

cube& Blob::operator[] (int i) {
    return data_[i];
}
Blob& Blob::operator= (double num) {
    assert(!data_.empty());
    for (int i = 0; i < N_; ++i) {
        (*this)[i].fill(num);
    }
    return *this;
}

vector<int> Blob::size() {
    vector<int> shape{ N_, C_, H_, W_ };
    return shape;   
}

vector<cube>& Blob::get_data() {
    return data_;
}

mat Blob::reshape() {
    cube dst;
    for (int i = 0; i < N_; ++i) {
        dst = join_slices(dst, data_[i]);
    }
    //return arma::reshape(vectorise(dst), N_, C_*H_*W_);
    return arma::reshape(vectorise(dst), C_*H_*W_, N_).t();
}

double Blob::sum() {
    assert(!data_.empty());
    double ans = 0;
    for (int i = 0; i < N_; ++i) {
        ans += accu(data_[i]);
    }
    return ans;
}

double Blob::numElement() {
    return N_ * C_ * H_ * W_;
}

Blob Blob::max(double val) {
    assert(!data_.empty());
    Blob out(*this);
    for (int i = 0; i < N_; ++i) {
        out[i].transform([val](double e) {return e > val ? e : val;});
    }
    return out;
}

void Blob::maxIn(double val) {
    assert(!data_.empty());
    for (int i = 0; i < N_; ++i) {
        (*this)[i].transform([val](double e) {return e > val ? e : val;});
    }
    return;
}

/*! element wise operation, change data_, if e = e < val ? 1 : 0; */
void Blob::smallerIn(double val) {
    assert(!data_.empty());
    for (int i = 0; i < N_; ++i) {
        (*this)[i].transform([val](double e) {return e < val ? 1 : 0;});
    }
    return;
}

/*! element wise operation, change data_, if e = e > val ? 1 : 0; */
void Blob::biggerIn(double val) {
    assert(!data_.empty());
    for (int i = 0; i < N_; ++i) {
        (*this)[i].transform([val](double e) {return e > val ? 1 : 0;});
    }
    return;
}

Blob Blob::abs() {
    assert(!data_.empty());
    Blob out(*this);
    for (int i = 0; i < N_; ++i) {
        out[i].transform([](double e) {return fabs(e);});
    }
    return out;
}

double Blob::maxVal() {
    assert(!data_.empty());
    double ans = data_[0].max();
    for (int i = 1; i < N_; ++i) {
        double tmp = data_[i].max();
        ans = std::max(ans, tmp);
    }
    return ans;
}

Blob Blob::pad(int p, double val) {
    assert(!data_.empty());
    Blob out(N_, C_, H_ + p*2, W_ + p*2);
    out = val;

    for (int n = 0; n < N_; ++n) {
        for (int c = 0; c < C_; ++c) {
            for (int h = 0; h < H_; ++h) {
                for (int w = 0; w < W_; ++w) {
                    out[n](p+h, p+w, c) = (*this)[n](h, w, c);
                }
            }
        }
    }
    return out;
}

Blob Blob::dePad(int p) {
    assert(!data_.empty());
    Blob out(N_, C_, H_ - p*2, W_ - p*2);

    for (int n = 0; n < N_; ++n) {
        //out[n] = (*this)[n](span(p, H_-p), span(p, W_-p), span::all);
        for (int c = 0; c < C_; ++c) {
            for (int h = p; h < H_-p; ++h) {
                for (int w = p; w < W_-p; ++w) {
                    out[n](h-p, w-p, c) = (*this)[n](h, w, c);
                }
            }
        }
    }
    return out;
}

void Blob::print(std::string s) {
    assert(!data_.empty());
    cout << s << endl;
    for (int i = 0; i < N_; ++i) {
        printf("N = %d\n", i);
        (*this)[i].print();
    }
    return;
}

void Blob::_init(int n, int c, int h, int w, int type) {
    if (type == TONES) {
        data_ = vector<cube>(n, cube(h, w, c, fill::ones));
        return;
    }
    if (type == TZEROS) {
        data_ = vector<cube>(n, cube(h, w, c, fill::zeros));
        return;
    }
    if (type == TDEFAULT) {
        data_ = vector<cube>(n, cube(h, w, c));
        return;
    }
    for (int i = 0; i < n; ++i) {
        cube tmp;
        if (type == TRANDU) tmp = randu<cube>(h, w, c);
        if (type == TRANDN) tmp = randn<cube>(h, w, c);
        data_.push_back(tmp);
    }
    return;
}

} // namespace mini_net
