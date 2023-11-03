/* This code is part of the CPISync project developed at Boston
 * University. Please see the README for use and references.
 *
 * @author Novak Boškov <boskov@bu.edu>
 *
 * Created on April, 2020.
 */

#include "Compact2DBitArrayTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Compact2DBitArrayTest);

Compact2DBitArrayTest::Compact2DBitArrayTest() = default;

Compact2DBitArrayTest::~Compact2DBitArrayTest() = default;

void Compact2DBitArrayTest::setUp() {}

void Compact2DBitArrayTest::tearDown() {}

inline void _setEntries(Compact2DBitArray& arr, vector<size_t>& content) {
    size_t zz = 0;
    for (size_t ii=0; ii<arr.getRows(); ii++)
        for (size_t jj=0; jj<arr.getColumns(); jj++)
            arr.setEntry(ii, jj, content.at(zz++));
}

inline vector<size_t> _getEntries(Compact2DBitArray& arr) {
    vector<size_t> ret;
    for (size_t ii=0; ii<arr.getRows(); ii++)
        for (size_t jj=0; jj<arr.getColumns(); jj++)
            ret.push_back(arr.getEntry(ii, jj));

    return ret;
}

inline void _assert_vectors_equal(vector<size_t>& a, vector<size_t>& b) {
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Different lengths of compared vectors",
                                 a.size(), b.size());

    for (size_t xx=0; xx<a.size(); xx++)
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Differ at index " + toStr(xx),
                                     a.at(xx), b.at(xx));
}

/**
 * Generate count numbers in range from 0 to max using logistic map
 */
inline vector<size_t> _gen_range(size_t max, size_t count) {
    vector<size_t> ret;
    float x_i= .3; // logistic map initial x
    for (size_t ii=0; ii<count; ii++) {
        x_i = 3.8 * x_i * (1 - x_i); // logistic map
        // scale by 1e9 to support max being 2^32 ~ 4e9
        ret.push_back(int(x_i * 1e9) % max);
    }

    return ret;
}

inline void _test_various_columns_rows(size_t fSize) {
    for (size_t bSize=MIN_COLUMNS_TESTED; bSize<=MAX_COLUMNS_TESTED; bSize++)
        for (size_t rows=MIN_ROWS_TESTED; rows<=MAX_ROWS_TESTED; rows++) {
            auto a = Compact2DBitArray(fSize, bSize, rows);

            vector<size_t> toAdd = _gen_range((1LU << fSize) - 1, bSize * rows);
            _setEntries(a, toAdd);
            auto added = _getEntries(a);

            _assert_vectors_equal(toAdd, added);
        }
}

void Compact2DBitArrayTest::readWriteTest() {
    for (size_t f=MIN_F_SIZE_TESTED; f<=MAX_F_SIZE_TESTED; f++)
        _test_various_columns_rows(f);
}
