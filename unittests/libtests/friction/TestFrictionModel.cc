// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestFrictionModel.hh" // Implementation of class methods

#include "data/StaticFrictionData.hh" // USES StaticFrictionData

#include "pylith/topology/SubMesh.hh" // USES SubMesh
#include "pylith/topology/Field.hh" // USES Field
#include "pylith/meshio/MeshIOAscii.hh" // USES MeshIOAscii
#include "pylith/friction/StaticFriction.hh" // USES StaticFriction
#include "pylith/feassemble/Quadrature.hh" // USES Quadrature
#include "pylith/feassemble/GeometryTri2D.hh" // USES GeometryTri2D

#include "pylith/utils/array.hh" // USES double_array

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleIOAscii.hh" // USES SimpleIOAscii
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/units/Nondimensional.hh" // USES Nondimensional

#include <cstring> // USES memcpy()

//#define PRECOMPUTE_GEOMETRY

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( pylith::friction::TestFrictionModel );

// ----------------------------------------------------------------------
typedef pylith::topology::Mesh::SieveSubMesh SieveSubMesh;
typedef pylith::topology::Mesh::RealSection RealSection;

// ----------------------------------------------------------------------
// Test label()
void
pylith::friction::TestFrictionModel::testLabel(void)
{ // testLabel
  const std::string& label = "the database";
  StaticFriction friction;
  friction.label(label.c_str());
  
  CPPUNIT_ASSERT_EQUAL(label, std::string(friction.label()));
} // testLabel
    
// ----------------------------------------------------------------------
// Test timestep()
void
pylith::friction::TestFrictionModel::testTimeStep(void) 
{ // testTimeStep
  const double dt = 2.0;
  StaticFriction friction;
  friction.timeStep(dt);
  
  CPPUNIT_ASSERT_EQUAL(dt, friction.timeStep());
} // testTimeStep

// ----------------------------------------------------------------------
// Test dbProperties()
void
pylith::friction::TestFrictionModel::testDBProperties(void)
{ // testDBProperties
  const std::string& label = "my_database";
  spatialdata::spatialdb::SimpleDB db;
  db.label(label.c_str());
  
  StaticFriction friction;
  friction.dbProperties(&db);
  
  CPPUNIT_ASSERT(0 != friction._dbProperties);
  CPPUNIT_ASSERT_EQUAL(label, std::string(friction._dbProperties->label()));
} // testDBProperties

// ----------------------------------------------------------------------
// Test dbStateVars()
void
pylith::friction::TestFrictionModel::testDBStateVars(void)
{ // testDBStateVars
  const std::string& label = "my_database";
  spatialdata::spatialdb::SimpleDB db;
  db.label(label.c_str());
  
  StaticFriction friction;
  friction.dbInitialState(&db);
  
  CPPUNIT_ASSERT(0 != friction._dbInitialState);
  CPPUNIT_ASSERT_EQUAL(label, std::string(friction._dbInitialState->label()));
} // testDBStateVars

// ----------------------------------------------------------------------
// Test normalizer()
void
pylith::friction::TestFrictionModel::testNormalizer(void)
{ // testNormalizer
  spatialdata::units::Nondimensional normalizer;
  const double lengthScale = 2.0;
  normalizer.lengthScale(lengthScale);

  StaticFriction friction;
  friction.normalizer(normalizer);
  
  CPPUNIT_ASSERT(0 != friction._normalizer);
  CPPUNIT_ASSERT_EQUAL(lengthScale, friction._normalizer->lengthScale());
} // testNormalizer

// ----------------------------------------------------------------------
// Test initialize()
void
pylith::friction::TestFrictionModel::testInitialize(void)
{ // testInitialize
  topology::Mesh mesh;
  StaticFriction friction;
  StaticFrictionData data;
  _initialize(&mesh, &friction, &data);

#if 1
  CPPUNIT_ASSERT(false);
#else
  // :TODO: ADD STUFF HERE
  // Test propertiesVertex with mesh

  // Test cell arrays
  size_t size = data.numLocs*data.numPropsVertex;
  CPPUNIT_ASSERT_EQUAL(size, friction._propertiesVertex.size());

  size = data.numLocs*data.numVarsVertex;
  CPPUNIT_ASSERT_EQUAL(size, friction._stateVarsVertex.size());

  size = data.numLocs;
  CPPUNIT_ASSERT_EQUAL(size, material._frictionVertex.size());
#endif
} // testInitialize

// ----------------------------------------------------------------------
// Test retrievePropsAndVars().
void
pylith::friction::TestFrictionModel::testRetrievePropsAndVars(void)
{ // testRetrievePropsAndVars
  topology::Mesh mesh;
  StaticFriction friction;
  StaticFrictionData data;
  _initialize(&mesh, &friction, &data);

#if 1
  CPPUNIT_ASSERT(false);
#else
  // ADD STUFF HERE

  friction.retrievePropsAndVars(vertex);

  const double tolerance = 1.0e-06;
  const int numVarsVertex = data.numVarsVertex;

  // Test vertex arrays
  const double* propertiesE = data.properties;
  CPPUNIT_ASSERT(0 != propertiesE);
  const double_array& properties = material._propertiesCell;
  size_t size = data.numLocs*data.numPropsVertex;
  CPPUNIT_ASSERT_EQUAL(size, properties.size());
  for (size_t i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, properties[i]/propertiesE[i],
				 tolerance);

  const double* stateVarsE = data.stateVars;
  CPPUNIT_ASSERT( (0 < numVarsVertex && 0 != stateVarsE) ||
		  (0 == numVarsVertex && 0 == stateVarsE) );
  const double_array& stateVars = material._stateVarsCell;
  size = data.numLocs*numVarsVertex;
  CPPUNIT_ASSERT_EQUAL(size, stateVars.size());
  for (size_t i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, stateVars[i]/stateVarsE[i],
				 tolerance);
#endif
} // testRetrievePropsAndVars

// ----------------------------------------------------------------------
// Test calcFriction()
void
pylith::friction::TestFrictionModel::testCalcFriction(void)
{ // testCalcFriction
  topology::Mesh mesh;
  StaticFriction friction;
  StaticFrictionData data;
  _initialize(&mesh, &friction, &data);

#if 1
  CPPUNIT_ASSERT(false);
#else

  friction.retrievePropsAndVars(vertex);
  const double_array& friction = friction.calcFriction();

  const double* densityE = data.friction;
  CPPUNIT_ASSERT(0 != frictionE);
  const size_t size = numVertexs;
  CPPUNIT_ASSERT_EQUAL(size, density.size());
  const double tolerance = 1.0e-06;
  for (size_t i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, density[i]/densityE[i], tolerance);
#endif
} // testCalcFriction
    
// ----------------------------------------------------------------------
// Test updateStateVars()
void
pylith::friction::TestFrictionModel::testUpdateStateVars(void)
{ // testUpdateStateVars
  std::cout << "\n\nWARNING!! WARNING!! WARNING!!\n"
    "Need to implement using material with state variables.\n\n";
} // testUpdateStateVars

// ----------------------------------------------------------------------
// Setup testing data.
void
pylith::friction::TestFrictionModel::setUp(void)
{ // setUp
  _friction = 0;
  _data = 0;
} // setUp

// ----------------------------------------------------------------------
// Tear down testing data.
void
pylith::friction::TestFrictionModel::tearDown(void)
{ // tearDown
  delete _friction; _friction = 0;
  delete _data; _data = 0;
} // tearDown

// ----------------------------------------------------------------------
// Test _dbToProperties().
void
pylith::friction::TestFrictionModel::testDBToProperties(void)
{ // testDBToProperties
  CPPUNIT_ASSERT(0 != _friction);
  CPPUNIT_ASSERT(0 != _data);
  
  const int numLocs = _data->numLocs;
  const int numDBProperties = _data->numDBProperties;
  double_array dbValues(numDBProperties);

  const int propertiesSize = _data->numPropsVertex;
  double_array properties(propertiesSize);

  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    for (int i=0; i < numDBProperties; ++i)
      dbValues[i] = _data->dbProperties[iLoc*numDBProperties+i];

    _friction->_dbToProperties(&properties[0], dbValues);
    
    const double* const propertiesE = &_data->properties[iLoc*propertiesSize];
    const double tolerance = 1.0e-06;
    for (int i=0; i < propertiesSize; ++i) {
      if (fabs(propertiesE[i]) > tolerance)
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 
				     properties[i]/propertiesE[i],
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(propertiesE[i], properties[i],
				     tolerance);
    } // for
  } // for
} // testDBToProperties

// ----------------------------------------------------------------------
// Test _nondimProperties().
void
pylith::friction::TestFrictionModel::testNonDimProperties(void)
{ // testNonDimProperties
  CPPUNIT_ASSERT(0 != _friction);
  CPPUNIT_ASSERT(0 != _data);
  
  const int numLocs = _data->numLocs;
  const int propertiesSize = _data->numPropsVertex;
  double_array propertiesNondim(propertiesSize);
  double_array properties(propertiesSize);

  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    for (int i=0; i < propertiesSize; ++i)
      properties[i] = _data->properties[iLoc*propertiesSize+i];
    _friction->_nondimProperties(&properties[0], properties.size());
    
    const double* const propertiesNondimE =
      &_data->propertiesNondim[iLoc*propertiesSize];
    CPPUNIT_ASSERT(0 != propertiesNondimE);

    const double tolerance = 1.0e-06;
    for (int i=0; i < propertiesSize; ++i) {
      if (fabs(propertiesNondimE[i]) > tolerance)
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 
				     properties[i]/propertiesNondimE[i],
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(propertiesNondimE[i], properties[i],
				     tolerance);
    } // for
  } // for
} // testNonDimProperties

// ----------------------------------------------------------------------
// Test _dimProperties().
void
pylith::friction::TestFrictionModel::testDimProperties(void)
{ // testDimProperties
  CPPUNIT_ASSERT(0 != _friction);
  CPPUNIT_ASSERT(0 != _data);
  
  const int numLocs = _data->numLocs;
  const int propertiesSize = _data->numPropsVertex;
  double_array properties(propertiesSize);

  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    for (int i=0; i < propertiesSize; ++i)
      properties[i] = _data->propertiesNondim[iLoc*propertiesSize+i];
    _friction->_dimProperties(&properties[0], properties.size());
    
    const double* const propertiesE =
      &_data->properties[iLoc*propertiesSize];
    CPPUNIT_ASSERT(0 != propertiesE);

    const double tolerance = 1.0e-06;
    for (int i=0; i < propertiesSize; ++i) {
      if (fabs(propertiesE[i]) > tolerance)
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 
				     properties[i]/propertiesE[i],
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(propertiesE[i], properties[i],
				     tolerance);
    } // for
  } // for
} // testDimProperties

// ----------------------------------------------------------------------
// Test _dbToStateVars().
void
pylith::friction::TestFrictionModel::testDBToStateVars(void)
{ // testDBToStateVars
  CPPUNIT_ASSERT(0 != _friction);
  CPPUNIT_ASSERT(0 != _data);
  
  const int numLocs = _data->numLocs;
  const int numDBStateVars = _data->numDBStateVars;
  double_array dbValues(numDBStateVars);

  const int stateVarsSize = _data->numVarsVertex;
  double_array stateVars(stateVarsSize);

  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    for (int i=0; i < numDBStateVars; ++i)
      dbValues[i] = _data->dbStateVars[iLoc*numDBStateVars+i];

    _friction->_dbToStateVars(&stateVars[0], dbValues);
    
    const double* const stateVarsE = 
      (stateVarsSize > 0) ? &_data->stateVars[iLoc*stateVarsSize] : 0;
    CPPUNIT_ASSERT( (0 < stateVarsSize && 0 != stateVarsE) ||
		    (0 == stateVarsSize && 0 == stateVarsE) );
    const double tolerance = 1.0e-06;
    for (int i=0; i < stateVarsSize; ++i) {
      if (fabs(stateVarsE[i]) > tolerance)
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 
				     stateVars[i]/stateVarsE[i],
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(stateVarsE[i], stateVars[i],
				     tolerance);
    } // for
  } // for
} // testDBToStateVars

// ----------------------------------------------------------------------
// Test _nondimStateVars().
void
pylith::friction::TestFrictionModel::testNonDimStateVars(void)
{ // testNonDimStateVars
  CPPUNIT_ASSERT(0 != _friction);
  CPPUNIT_ASSERT(0 != _data);
  
  const int numLocs = _data->numLocs;
  const int stateVarsSize = _data->numVarsVertex;
  double_array stateVars(stateVarsSize);

  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    for (int i=0; i < stateVarsSize; ++i)
      stateVars[i] = _data->dbStateVars[iLoc*stateVarsSize+i];
    _friction->_nondimStateVars(&stateVars[0], stateVars.size());
    
    const double* const stateVarsNondimE =
      (stateVarsSize > 0) ? &_data->stateVarsNondim[iLoc*stateVarsSize] : 0;
    CPPUNIT_ASSERT( (0 < stateVarsSize && 0 != stateVarsNondimE) ||
		    (0 == stateVarsSize && 0 == stateVarsNondimE) );

    const double tolerance = 1.0e-06;
    for (int i=0; i < stateVarsSize; ++i) {
      if (fabs(stateVarsNondimE[i]) > tolerance)
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 
				     stateVars[i]/stateVarsNondimE[i],
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(stateVarsNondimE[i], stateVars[i],
				     tolerance);
    } // for
  } // for
} // testNonDimStateVars

// ----------------------------------------------------------------------
// Test _dimStateVars().
void
pylith::friction::TestFrictionModel::testDimStateVars(void)
{ // testDimStateVars
  CPPUNIT_ASSERT(0 != _friction);
  CPPUNIT_ASSERT(0 != _data);
  
  const int numLocs = _data->numLocs;
  const int stateVarsSize = _data->numVarsVertex;
  double_array stateVars(stateVarsSize);

  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    for (int i=0; i < stateVarsSize; ++i)
      stateVars[i] = _data->stateVarsNondim[iLoc*stateVarsSize+i];
    _friction->_dimStateVars(&stateVars[0], stateVars.size());
    
    const double* const stateVarsE =
      (stateVarsSize > 0) ? &_data->stateVars[iLoc*stateVarsSize] : 0;
    CPPUNIT_ASSERT( (0 < stateVarsSize && 0 != stateVarsE) ||
		    (0 == stateVarsSize && 0 == stateVarsE) );

    const double tolerance = 1.0e-06;
    for (int i=0; i < stateVarsSize; ++i) {
      if (fabs(stateVarsE[i]) > tolerance)
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 
				     stateVars[i]/stateVarsE[i],
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(stateVarsE[i], stateVars[i],
				     tolerance);
    } // for
  } // for
} // testDimStateVars

// ----------------------------------------------------------------------
// Test _calcFriction()
void
pylith::friction::TestFrictionModel::test_calcFriction(void)
{ // _testCalcFriction
  CPPUNIT_ASSERT(0 != _friction);
  CPPUNIT_ASSERT(0 != _data);

  const int numLocs = _data->numLocs;
  const int numPropsVertex = _data->numPropsVertex;
  const int numVarsVertex = _data->numVarsVertex;
  
  double_array properties(numPropsVertex);
  double_array stateVars(numVarsVertex);

  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    for (int i=0; i < numPropsVertex; ++i)
      properties[i] = _data->properties[iLoc*numPropsVertex+i];
    for (int i=0; i < numVarsVertex; ++i)
      stateVars[i] = _data->stateVars[iLoc*numVarsVertex+i];
    const double slip = _data->slip[iLoc];
    const double slipRate = _data->slipRate[iLoc];
    const double normalTraction = _data->normalTraction[iLoc];

    const double friction = _friction->_calcFriction(
					slip, slipRate, normalTraction,
					&properties[0], properties.size(),
					&stateVars[0], stateVars.size());
    
    const double frictionE = _data->friction[iLoc];
    
    const double tolerance = 1.0e-06;
    if (0.0 != frictionE)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, friction/frictionE, tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(frictionE, friction, tolerance);
  } // for
} // _testCalcFriction

// ----------------------------------------------------------------------
// Test _updateStateVars()
void
pylith::friction::TestFrictionModel::test_updateStateVars(void)
{ // test_updateStateVars
  CPPUNIT_ASSERT(0 != _friction);
  CPPUNIT_ASSERT(0 != _data);

  const bool computeStateVars = true;

  const int numLocs = _data->numLocs;
  const int numPropsVertex = _data->numPropsVertex;
  const int numVarsVertex = _data->numVarsVertex;
  
  double_array properties(numPropsVertex);
  double_array stateVars(numVarsVertex);

  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    for (int i=0; i < numPropsVertex; ++i)
      properties[i] = _data->properties[iLoc*numPropsVertex+i];
    for (int i=0; i < numVarsVertex; ++i)
      stateVars[i] = _data->stateVars[iLoc*numVarsVertex+i];

    _friction->_updateStateVars(&stateVars[0], stateVars.size(),
				&properties[0], properties.size());
    
    const double* stateVarsE = 
      (numVarsVertex > 0) ? &_data->stateVarsUpdated[iLoc*numVarsVertex] : 0;
    CPPUNIT_ASSERT( (0 < numVarsVertex && 0 != stateVarsE) ||
		    (0 == numVarsVertex && 0 == stateVarsE) );

    const double tolerance = 1.0e-06;
    for (int i=0; i < numVarsVertex; ++i)
      if (0.0 != stateVarsE[i])
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, stateVars[i]/stateVarsE[i], 
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(stateVarsE[i], stateVars[i],
				     tolerance);
  } // for
} // test_updateStateVars

// ----------------------------------------------------------------------
// Setup nondimensionalization.
void
pylith::friction::TestFrictionModel::setupNormalizer(void)
{ // setupNormalizer
  spatialdata::units::Nondimensional normalizer;
  normalizer.lengthScale(_data->lengthScale);
  normalizer.pressureScale(_data->pressureScale);
  normalizer.timeScale(_data->timeScale);
  normalizer.densityScale(_data->densityScale);
  _friction->normalizer(normalizer);
} // setupNormalizer

// ----------------------------------------------------------------------
// Setup mesh and material.
void
pylith::friction::TestFrictionModel::_initialize(
					  topology::Mesh* mesh,
					  StaticFriction* friction,
					  const StaticFrictionData* data)
{ // _initialize
  CPPUNIT_ASSERT(0 != mesh);
  CPPUNIT_ASSERT(0 != friction);
  CPPUNIT_ASSERT(0 != data);

#if 0
  meshio::MeshIOAscii iohandler;
  iohandler.filename("data/line3.mesh");
  iohandler.read(mesh);

  // Set up coordinates
  spatialdata::geocoords::CSCart cs;
  spatialdata::units::Nondimensional normalizer;
  cs.setSpaceDim(mesh->dimension());
  cs.initialize();
  mesh->coordsys(&cs);
  mesh->nondimensionalize(normalizer);

  // Setup quadrature
  feassemble::Quadrature<topology::Mesh> quadrature;
  feassemble::GeometryLine1D geometry;
  quadrature.refGeometry(&geometry);
  const int cellDim = 1;
  const int numCorners = 3;
  const int numQuadPts = 2;
  const int spaceDim = 1;
  const double basis[] = { 0.455, -0.122, 0.667, -0.122, 0.455, 0.667 };
  const double basisDeriv[] = { 
    -1.07735027e+00,
    -7.73502692e-02,
    1.15470054e+00,
    7.73502692e-02,
    1.07735027e+00,
    -1.15470054e+00,
  };
  const double quadPtsRef[] = { -0.577350269, 0.577350269 };
  const double quadWts[] = { 1.0, 1.0  };
  quadrature.initialize(basis, numQuadPts, numCorners,
			basisDeriv, numQuadPts, numCorners, cellDim,
			quadPtsRef, numQuadPts, cellDim,
			quadWts, numQuadPts,
			spaceDim);


  // Get cells associated with material
  const int materialId = 24;
  const ALE::Obj<SieveMesh>& sieveMesh = mesh->sieveMesh();
  assert(!sieveMesh.isNull());
  const ALE::Obj<SieveMesh::label_sequence>& cells = 
    sieveMesh->getLabelStratum("material-id", materialId);

  // Compute geometry for cells
  quadrature.initializeGeometry();
#if defined(PRECOMPUTE_GEOMETRY)
  quadrature.computeGeometry(*mesh, cells);
#endif

  spatialdata::spatialdb::SimpleDB db;
  spatialdata::spatialdb::SimpleIOAscii dbIO;
  dbIO.filename("data/matinitialize.spatialdb");
  db.ioHandler(&dbIO);
  db.queryType(spatialdata::spatialdb::SimpleDB::NEAREST);
  
  spatialdata::spatialdb::SimpleDB dbStress;
  spatialdata::spatialdb::SimpleIOAscii dbIOStress;
  dbIOStress.filename("data/matstress.spatialdb");
  dbStress.ioHandler(&dbIOStress);
  dbStress.queryType(spatialdata::spatialdb::SimpleDB::NEAREST);
  
  spatialdata::spatialdb::SimpleDB dbStrain;
  spatialdata::spatialdb::SimpleIOAscii dbIOStrain;
  dbIOStrain.filename("data/matstrain.spatialdb");
  dbStrain.ioHandler(&dbIOStrain);
  dbStrain.queryType(spatialdata::spatialdb::SimpleDB::NEAREST);
  
  material->dbProperties(&db);
  material->id(materialId);
  material->label("my_friction");
  material->normalizer(normalizer);
  material->dbInitialStress(&dbStress);
  material->dbInitialStrain(&dbStrain);
  
  material->initialize(*mesh, &quadrature);
#endif
} // _initialize


// End of file 
