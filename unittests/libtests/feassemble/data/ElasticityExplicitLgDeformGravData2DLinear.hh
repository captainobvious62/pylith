// -*- C++ -*-
//
// ======================================================================
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

// DO NOT EDIT THIS FILE
// This file was generated from python application elasticitylgdeformexplicitapp.

#if !defined(pylith_feassemble_elasticityexplicitlgdeformgravdata2dlinear_hh)
#define pylith_feassemble_elasticityexplicitlgdeformgravdata2dlinear_hh

#include "ElasticityExplicitData.hh"

namespace pylith {
  namespace feassemble {
     class ElasticityExplicitLgDeformGravData2DLinear;
  } // pylith
} // feassemble

class pylith::feassemble::ElasticityExplicitLgDeformGravData2DLinear : public ElasticityExplicitData
{

public: 

  /// Constructor
  ElasticityExplicitLgDeformGravData2DLinear(void);

  /// Destructor
  ~ElasticityExplicitLgDeformGravData2DLinear(void);

private:

  static const int _spaceDim;

  static const int _cellDim;

  static const int _numVertices;

  static const int _numCells;

  static const int _numBasis;

  static const int _numQuadPts;

  static const char* _matType;

  static const char* _matDBFilename;

  static const int _matId;

  static const char* _matLabel;

  static const PylithScalar _dt;

  static const PylithScalar _dtStableExplicit;

  static const PylithScalar _gravityVec[];

  static const PylithScalar _vertices[];

  static const int _cells[];

  static const PylithScalar _verticesRef[];

  static const PylithScalar _quadPts[];

  static const PylithScalar _quadWts[];

  static const PylithScalar _basis[];

  static const PylithScalar _basisDerivRef[];

  static const PylithScalar _fieldTIncr[];

  static const PylithScalar _fieldT[];

  static const PylithScalar _fieldTmdt[];

  static const PylithScalar _valsResidual[];

  static const PylithScalar _valsJacobian[];

};

#endif // pylith_feassemble_elasticityexplicitlgdeformgravdata2dlinear_hh

// End of file
