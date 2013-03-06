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
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

// DO NOT EDIT THIS FILE
// This file was generated from python application genmaxwellqpqsisotropic3dtimedep.

#include "GenMaxwellQpQsIsotropic3DTimeDepData.hh"

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_dimension = 3;

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_numLocs = 2;

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_numProperties = 15;

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_numStateVars = 27;

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_numDBProperties = 15;

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_numDBStateVars = 27;

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_numPropsQuadPt = 15;

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_numVarsQuadPt = 27;

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_lengthScale =   1.00000000e+03;

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_timeScale =   1.00000000e+00;

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_pressureScale =   2.25000000e+10;

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_densityScale =   2.25000000e+04;

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_dtStableImplicit =   8.88888889e+05;

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_dtStableExplicit =   1.92450090e-01;

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_numPropertyValues[] = {
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
};

const int pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_numStateVarValues[] = {
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
};

const char* pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_dbPropertyValues[] = {
"density",
"vs",
"vp",
"shear-ratio-1",
"shear-ratio-2",
"shear-ratio-3",
"shear-viscosity-1",
"shear-viscosity-2",
"shear-viscosity-3",
"bulk-ratio-1",
"bulk-ratio-2",
"bulk-ratio-3",
"bulk-viscosity-1",
"bulk-viscosity-2",
"bulk-viscosity-3",
};

const char* pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_dbStateVarValues[] = {
"total-strain-xx",
"total-strain-yy",
"total-strain-zz",
"total-strain-xy",
"total-strain-yz",
"total-strain-xz",
"viscousdeviatoric-strain-1-xx",
"viscousdeviatoric-strain-1-yy",
"viscousdeviatoric-strain-1-zz",
"viscousdeviatoric-strain-1-xy",
"viscousdeviatoric-strain-1-yz",
"viscousdeviatoric-strain-1-xz",
"viscousdeviatoric-strain-2-xx",
"viscousdeviatoric-strain-2-yy",
"viscousdeviatoric-strain-2-zz",
"viscousdeviatoric-strain-2-xy",
"viscousdeviatoric-strain-2-yz",
"viscousdeviatoric-strain-2-xz",
"viscousdeviatoric-strain-3-xx",
"viscousdeviatoric-strain-3-yy",
"viscousdeviatoric-strain-3-zz",
"viscousdeviatoric-strain-3-xy",
"viscousdeviatoric-strain-3-yz",
"viscousdeviatoric-strain-3-xz",
"viscous-mean-strain-1",
"viscous-mean-strain-2",
"viscous-mean-strain-3",
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_dbProperties[] = {
  2.50000000e+03,
  3.00000000e+03,
  5.19615242e+03,
  5.00000000e-01,
  1.00000000e-01,
  2.00000000e-01,
  1.00000000e+18,
  1.00000000e+17,
  1.00000000e+19,
  4.00000000e-01,
  3.00000000e-01,
  1.00000000e-01,
  2.00000000e+18,
  2.00000000e+17,
  2.00000000e+19,
  2.00000000e+03,
  1.20000000e+03,
  2.07846097e+03,
  2.00000000e-01,
  2.00000000e-01,
  2.00000000e-01,
  1.00000000e+18,
  1.00000000e+19,
  1.00000000e+20,
  2.00000000e-01,
  2.00000000e-01,
  2.00000000e-01,
  1.00000000e+18,
  1.00000000e+19,
  1.00000000e+20,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_dbStateVars[] = {
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_properties[] = {
  2.50000000e+03,
  2.25000000e+10,
  3.75000000e+10,
  5.00000000e-01,
  1.00000000e-01,
  2.00000000e-01,
  4.44444444e+07,
  4.44444444e+06,
  4.44444444e+08,
  4.00000000e-01,
  3.00000000e-01,
  1.00000000e-01,
  1.33333333e+08,
  1.77777778e+07,
  5.33333333e+09,
  2.00000000e+03,
  2.88000000e+09,
  4.80000000e+09,
  2.00000000e-01,
  2.00000000e-01,
  2.00000000e-01,
  3.47222222e+08,
  3.47222222e+09,
  3.47222222e+10,
  2.00000000e-01,
  2.00000000e-01,
  2.00000000e-01,
  1.04166667e+09,
  1.04166667e+10,
  1.04166667e+11,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_stateVars[] = {
  1.10000000e-04,
  2.20000000e-04,
  3.30000000e-04,
  4.40000000e-04,
  5.50000000e-04,
  6.60000000e-04,
 -1.10000000e-04,
  0.00000000e+00,
  1.10000000e-04,
  4.40000000e-04,
  5.50000000e-04,
  6.60000000e-04,
 -1.10000000e-04,
  0.00000000e+00,
  1.10000000e-04,
  4.40000000e-04,
  5.50000000e-04,
  6.60000000e-04,
 -1.10000000e-04,
  0.00000000e+00,
  1.10000000e-04,
  4.40000000e-04,
  5.50000000e-04,
  6.60000000e-04,
  0.00000000e+00,
  0.00000000e+00,
  2.30000000e-04,
  1.20000000e-04,
  2.30000000e-04,
  3.40000000e-04,
  4.50000000e-04,
  5.60000000e-04,
  6.70000000e-04,
 -1.10000000e-04,
 -2.71050543e-20,
  1.10000000e-04,
  4.50000000e-04,
  5.60000000e-04,
  6.70000000e-04,
 -1.10000000e-04,
 -2.71050543e-20,
  1.10000000e-04,
  4.50000000e-04,
  5.60000000e-04,
  6.70000000e-04,
 -1.10000000e-04,
 -2.71050543e-20,
  1.10000000e-04,
  4.50000000e-04,
  5.60000000e-04,
  6.70000000e-04,
  0.00000000e+00,
  0.00000000e+00,
  2.30000000e-04,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_propertiesNondim[] = {
  1.11111111e-01,
  1.00000000e+00,
  1.66666667e+00,
  5.00000000e-01,
  1.00000000e-01,
  2.00000000e-01,
  4.44444444e+07,
  4.44444444e+06,
  4.44444444e+08,
  4.00000000e-01,
  3.00000000e-01,
  1.00000000e-01,
  1.33333333e+08,
  1.77777778e+07,
  5.33333333e+09,
  8.88888889e-02,
  1.28000000e-01,
  2.13333333e-01,
  2.00000000e-01,
  2.00000000e-01,
  2.00000000e-01,
  3.47222222e+08,
  3.47222222e+09,
  3.47222222e+10,
  2.00000000e-01,
  2.00000000e-01,
  2.00000000e-01,
  1.04166667e+09,
  1.04166667e+10,
  1.04166667e+11,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_stateVarsNondim[] = {
  1.10000000e-04,
  2.20000000e-04,
  3.30000000e-04,
  4.40000000e-04,
  5.50000000e-04,
  6.60000000e-04,
 -1.10000000e-04,
  0.00000000e+00,
  1.10000000e-04,
  4.40000000e-04,
  5.50000000e-04,
  6.60000000e-04,
 -1.10000000e-04,
  0.00000000e+00,
  1.10000000e-04,
  4.40000000e-04,
  5.50000000e-04,
  6.60000000e-04,
 -1.10000000e-04,
  0.00000000e+00,
  1.10000000e-04,
  4.40000000e-04,
  5.50000000e-04,
  6.60000000e-04,
  0.00000000e+00,
  0.00000000e+00,
  2.30000000e-04,
  1.20000000e-04,
  2.30000000e-04,
  3.40000000e-04,
  4.50000000e-04,
  5.60000000e-04,
  6.70000000e-04,
 -1.10000000e-04,
 -2.71050543e-20,
  1.10000000e-04,
  4.50000000e-04,
  5.60000000e-04,
  6.70000000e-04,
 -1.10000000e-04,
 -2.71050543e-20,
  1.10000000e-04,
  4.50000000e-04,
  5.60000000e-04,
  6.70000000e-04,
 -1.10000000e-04,
 -2.71050543e-20,
  1.10000000e-04,
  4.50000000e-04,
  5.60000000e-04,
  6.70000000e-04,
  0.00000000e+00,
  0.00000000e+00,
  2.30000000e-04,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_density[] = {
  2.50000000e+03,
  2.00000000e+03,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_strain[] = {
  1.10000000e-04,
  2.20000000e-04,
  3.30000000e-04,
  4.40000000e-04,
  5.50000000e-04,
  6.60000000e-04,
  1.20000000e-04,
  2.30000000e-04,
  3.40000000e-04,
  4.50000000e-04,
  5.60000000e-04,
  6.70000000e-04,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_stress[] = {
  1.52472941e+07,
  3.08460297e+07,
  4.64447653e+07,
  6.24149423e+07,
  7.80136779e+07,
  9.36124135e+07,
  2.53395863e+06,
  4.68879364e+06,
  6.84362865e+06,
  8.86514321e+06,
  1.10199782e+07,
  1.31748132e+07,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_elasticConsts[] = {
  6.73240927e+10,
  2.24764147e+10,
  2.24764147e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  2.24764147e+10,
  6.73240927e+10,
  2.24764147e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  2.24764147e+10,
  2.24764147e+10,
  6.73240927e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  4.48476780e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  4.48476780e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  4.48476780e+10,
  8.63965224e+09,
  2.88002044e+09,
  2.88002044e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  2.88002044e+09,
  8.63965224e+09,
  2.88002044e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  2.88002044e+09,
  2.88002044e+09,
  8.63965224e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  5.75963179e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  5.75963179e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  5.75963179e+09,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_initialStress[] = {
  2.10000000e+04,
  2.20000000e+04,
  2.30000000e+04,
  2.40000000e+04,
  2.50000000e+04,
  2.60000000e+04,
  5.10000000e+04,
  5.20000000e+04,
  5.30000000e+04,
  5.40000000e+04,
  5.50000000e+04,
  5.60000000e+04,
};

const PylithScalar pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_initialStrain[] = {
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
};

const PylithScalar* pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::_stateVarsUpdated = 0;

pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::GenMaxwellQpQsIsotropic3DTimeDepData(void)
{ // constructor
  dimension = _dimension;
  numLocs = _numLocs;
  numProperties = _numProperties;
  numStateVars = _numStateVars;
  numDBProperties = _numDBProperties;
  numDBStateVars = _numDBStateVars;
  numPropsQuadPt = _numPropsQuadPt;
  numVarsQuadPt = _numVarsQuadPt;
  lengthScale = _lengthScale;
  timeScale = _timeScale;
  pressureScale = _pressureScale;
  densityScale = _densityScale;
  dtStableImplicit = _dtStableImplicit;
  dtStableExplicit = _dtStableExplicit;
  numPropertyValues = const_cast<int*>(_numPropertyValues);
  numStateVarValues = const_cast<int*>(_numStateVarValues);
  dbPropertyValues = const_cast<char**>(_dbPropertyValues);
  dbStateVarValues = const_cast<char**>(_dbStateVarValues);
  dbProperties = const_cast<PylithScalar*>(_dbProperties);
  dbStateVars = const_cast<PylithScalar*>(_dbStateVars);
  properties = const_cast<PylithScalar*>(_properties);
  stateVars = const_cast<PylithScalar*>(_stateVars);
  propertiesNondim = const_cast<PylithScalar*>(_propertiesNondim);
  stateVarsNondim = const_cast<PylithScalar*>(_stateVarsNondim);
  density = const_cast<PylithScalar*>(_density);
  strain = const_cast<PylithScalar*>(_strain);
  stress = const_cast<PylithScalar*>(_stress);
  elasticConsts = const_cast<PylithScalar*>(_elasticConsts);
  initialStress = const_cast<PylithScalar*>(_initialStress);
  initialStrain = const_cast<PylithScalar*>(_initialStrain);
  stateVarsUpdated = const_cast<PylithScalar*>(_stateVarsUpdated);
} // constructor

pylith::materials::GenMaxwellQpQsIsotropic3DTimeDepData::~GenMaxwellQpQsIsotropic3DTimeDepData(void)
{}


// End of file
