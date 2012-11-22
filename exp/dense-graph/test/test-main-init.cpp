#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE Suites
#include <boost/test/unit_test.hpp>

int add(int i, int j)
{
    return i + j;
}

BOOST_AUTO_TEST_SUITE(Math)

BOOST_AUTO_TEST_CASE(universeInOrder)
{
    BOOST_CHECK(add(2, 2) == 4);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Physics)

BOOST_AUTO_TEST_CASE(specialTheory)
{
    int e = 32;
    int m = 2;
    int c = 4;

    BOOST_CHECK(e == m * c * c);
}

BOOST_AUTO_TEST_SUITE_END()

//#define TESTING
//#include "../src/main-init.cpp"
//#undef main
//
//#define BOOST_TEST_MODULE const_string test
//#include <boost/test/unit_test.hpp>
//
//
//
//
//
//
//BOOST_AUTO_TEST_SUITE(VariantsSuite)
//BOOST_AUTO_TEST_CASE( constructors_test ) {
//  BOOST_CHECK_EQUAL( 0, 0 );
//}
//
//BOOST_AUTO_TEST_SUITE_END()
