/*
 * Copyright (C) 2014 uebb.tu-berlin.de.
 *
 * This file is part of daestruct
 *
 * daestruct is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * daestruct is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with daestruct. If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include "pendulumAnalysis.hpp"
#include "circuitAnalysis.hpp"

using namespace boost::unit_test;

using namespace daestruct::test;

test_suite*
init_unit_test_suite( int argc, char* argv[] ) {
  framework::master_test_suite().
        add( BOOST_TEST_CASE( &analyzePendulum ) );

  framework::master_test_suite().
        add( BOOST_TEST_CASE( &analyzeModelicaPendulum ) );

  framework::master_test_suite().
        add( BOOST_TEST_CASE( &analyzeCircuit1 ) );

  return 0;
}

