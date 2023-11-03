/* This code is part of the CPISync project developed at Boston
 * University. Please see the README for use and references.
 *
 * @author Novak Boškov <boskov@bu.edu>
 *
 * Created on Mar, 2020.
 */

#ifndef CPISYNCLIB_CUCKOOSYNCTEST_H
#define CPISYNCLIB_CUCKOOSYNCTEST_H

#include <cppunit/extensions/HelperMacros.h>

class CuckooSyncTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CuckooSyncTest);
    CPPUNIT_TEST(setReconcileTest);
    CPPUNIT_TEST(testAddDelElement);
    CPPUNIT_TEST_SUITE_END();
 public:
    CuckooSyncTest();
    ~CuckooSyncTest() override;
    void setUp() override;
    void tearDown() override;

    void setReconcileTest();
    void testAddDelElement();
};

#endif // CPISYNCLIB_CUCKOOSYNCTEST_H
