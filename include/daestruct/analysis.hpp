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
#ifndef DAE_ANALYSIS_HPP
#define DAE_ANALYSIS_HPP

#include <vector>
#include <functional>
#include <boost/variant.hpp>

#include <daestruct/sigma_matrix.hpp>

namespace daestruct {
  namespace analysis {

    using namespace std;

    void solveByFixedPoint(const std::vector<int>& assignment,  
			   const sigma_matrix& sigma,
			   std::vector<int>& c, std::vector<int>& d);

    struct InflatedMap {
      /* public variables and non-component equations */
      std::vector<int> cols;
      std::vector<int> rows;
      
      /* component-private variables and component-equations */
      std::vector<int> component_cols;
      std::vector<int> component_rows;
    };

    struct AnalysisResult {
      std::vector<int> row_assignment;
      std::vector<int> col_assignment;
      
      std::vector<int> c;
      std::vector<int> d;

      InflatedMap inflated;

      int extracted_equation(int eq, int k) const ;

      int extracted_variable(int var, int k) const;
    };

    /**
     * A compressible sub-component S = ((P U Q) U X, D, d, {M_q})
     * Q = {0 .. q - 1}
     * P = {0 .. p - 1}
     * X = {0 .. p}
     */
    struct compressible {
      int p;
      int q;

      //TODO: replace this with a better suited matrix, 
      //every row from p+1 .. p+q will be full in the end
      sigma_matrix sigma; //represents D and d as well

      /* M_q in the form of row-assignments */
      std::vector<std::vector<int>> M;

      /* cost of the M_q assignments */
      std::vector<int> cost;

      compressible(int pub_v, int pri_v) : p(pri_v), q(pub_v), sigma(p+q) {}

      /**
       * Seal this sub-component (i.e. afterwards set_*_incidence is a no-op)
       */
      void seal();

      /**
       * Set the incidence in this sub component
       * j is interpreted as a private variable
       * Note: i < p + 1 !
       */
      void set_private_incidence(int i, int j, int val);

      /**
       * Set the incidence in this sub component
       * j is interpreted as a private variable
       * Note: i < p + 1 !
       */
      void set_public_incidence(int i, int j, int val);
    };

    struct compressible_instance {
      int q; /* offset of the first public variable in the compressed matrix */
      int s; /* the surrogat equation */    
      compressible* c;

      compressible_instance(int qv, int se, compressible* comp) : q(qv), s(se), c(comp) {}

      void insert_incidence(sigma_matrix& sigma) const;
    };

    struct compression {
      int variables() const;

      std::vector<compressible_instance> instances;
    };

    struct InputProblem {
      long dimension;
      sigma_matrix sigma;
  
      InputProblem(long d) : dimension(d), sigma(d) {}

      AnalysisResult pryceAlgorithm() const;
    
      AnalysisResult pryceCompressed(const compression& c) const;
    };
  }
}

#endif
