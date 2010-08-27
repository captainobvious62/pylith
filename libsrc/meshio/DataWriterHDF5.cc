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
// Copyright (c) 2010 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

#include <portinfo>

#include <petscmesh_viewers.hh> // USES HDF5Viewer
#include <petscmesh_formats.hh> // USES PCICE output

#include <cassert> // USES assert()
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error

// ----------------------------------------------------------------------
// Constructor
template<typename mesh_type, typename field_type>
pylith::meshio::DataWriterHDF5<mesh_type,field_type>::DataWriterHDF5(void) :
  _filename("output.h5"),
  _viewer(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
template<typename mesh_type, typename field_type>
pylith::meshio::DataWriterHDF5<mesh_type,field_type>::~DataWriterHDF5(void)
{ // destructor
  deallocate();
} // destructor  

// ----------------------------------------------------------------------
// Deallocate PETSc and local data structures.
template<typename mesh_type, typename field_type>
void
pylith::meshio::DataWriterHDF5<mesh_type, field_type>::deallocate(void)
{ // deallocate
  if (0 != _viewer)
    PetscViewerDestroy(_viewer);
  _viewer = 0;
} // deallocate
  
// ----------------------------------------------------------------------
// Copy constructor.
template<typename mesh_type, typename field_type>
pylith::meshio::DataWriterHDF5<mesh_type,field_type>::DataWriterHDF5(const DataWriterHDF5<mesh_type, field_type>& w) :
  DataWriter<mesh_type, field_type>(w),
  _filename(w._filename),
  _viewer(0)
{ // copy constructor
} // copy constructor

// ----------------------------------------------------------------------
// Prepare file for data at a new time step.
template<typename mesh_type, typename field_type>
void
pylith::meshio::DataWriterHDF5<mesh_type,field_type>::openTimeStep(const double t,
						       const mesh_type& mesh,
						       const char* label,
						       const int labelId)
{ // openTimeStep
  try {
    PetscErrorCode err = 0;
    
    const std::string& filename = _hdf5Filename(t);

    err = PetscViewerCreate(mesh.comm(), &_viewer);
    CHECK_PETSC_ERROR(err);
    err = PetscViewerSetType(_viewer, PETSCVIEWERHDF5);
    CHECK_PETSC_ERROR(err);
    err = PetscViewerFileSetName(_viewer, filename.c_str());
    CHECK_PETSC_ERROR(err);

    const ALE::Obj<typename mesh_type::SieveMesh>& sieveMesh = mesh.sieveMesh();
    const ALE::Obj<typename field_type::Mesh::RealSection>& coordinates = sieveMesh->getRealSection("coordinates");
    field_type coordField(coordinates);

    coordField.createVector();
    coordField.createScatter();
    coordField.scatterSectionToVector();
    err = VecView(coordField.vector(), _viewer);CHECK_PETSC_ERROR(err);
    Vec          elemVec;
    PetscInt     numElements, numCorners, *vertices;
    PetscScalar *tmpVertices;
    PetscTruth   columnMajor = PETSC_FALSE;

    ALE::PCICE::Builder::outputElementsLocal(sieveMesh, &numElements, &numCorners, &vertices, columnMajor);
    // Hack right now, move to HDF5 Section viewer
    err = PetscMalloc(sizeof(PetscScalar)*numElements*numCorners, &tmpVertices);CHECK_PETSC_ERROR(err);
    for(PetscInt i = 0; i < numElements*numCorners; ++i) {tmpVertices[i] = vertices[i];}
    err = VecCreateMPIWithArray(sieveMesh->comm(), numElements*numCorners, PETSC_DETERMINE, tmpVertices, &elemVec);CHECK_PETSC_ERROR(err);
    err = VecView(elemVec, _viewer);CHECK_PETSC_ERROR(err);
    err = VecDestroy(elemVec);CHECK_PETSC_ERROR(err);
    err = PetscFree(tmpVertices);CHECK_PETSC_ERROR(err);
    err = PetscFree(vertices);CHECK_PETSC_ERROR(err);
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error while preparing for writing data to HDF5 file "
	<< _filename << " at time " << t << ".\n" << err.what();
    throw std::runtime_error(msg.str());
  } catch (const ALE::Exception& err) {
    std::ostringstream msg;
    msg << "Error while preparing for writing data to HDF5 file "
	<< _filename << " at time " << t << ".\n" << err.msg();
    throw std::runtime_error(msg.str());
  } catch (...) { 
    std::ostringstream msg;
    msg << "Unknown error while preparing for writing data to HDF5 file "
	<< _filename << " at time " << t << ".\n";
    throw std::runtime_error(msg.str());
  } // try/catch
} // openTimeStep

// ----------------------------------------------------------------------
/// Cleanup after writing data for a time step.
template<typename mesh_type, typename field_type>
void
pylith::meshio::DataWriterHDF5<mesh_type,field_type>::closeTimeStep(void)
{ // closeTimeStep
  PetscViewerDestroy(_viewer); _viewer = 0;
} // closeTimeStep

// ----------------------------------------------------------------------
// Write field over vertices to file.
template<typename mesh_type, typename field_type>
void
pylith::meshio::DataWriterHDF5<mesh_type,field_type>::writeVertexField(
				            const double t,
					    const field_type& field,
					    const mesh_type& mesh)
{ // writeVertexField
  try {
    // We will try the simplest thing, using the embedded vector. If this is not
    // general enough, due to ordering, etc., we can construct an auxiliary vector.

    const PetscVec vector = field.vector();
    if (vector == PETSC_NULL) {
      field.createVector();
    }
    // TODO: Create scatter if necessary
    field.scatterSectionToVector();

    PetscErrorCode err = 0;
    err = VecView(vector, _viewer);
    CHECK_PETSC_ERROR(err);
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error while writing field '" << field.label() << "' at time " 
	<< t << " to HDF5 file '" << _filename << "'.\n" << err.what();
    throw std::runtime_error(msg.str());
  } catch (...) { 
    std::ostringstream msg;
    msg << "Error while writing field '" << field.label() << "' at time " 
	<< t << " to HDF5 file '" << _filename << "'.\n";
    throw std::runtime_error(msg.str());
  } // try/catch
} // writeVertexField

// ----------------------------------------------------------------------
// Write field over cells to file.
template<typename mesh_type, typename field_type>
void
pylith::meshio::DataWriterHDF5<mesh_type,field_type>::writeCellField(
				       const double t,
				       const field_type& field,
				       const char* label,
				       const int labelId)
{ // writeCellField
  try {
    // We will try the simplest thing, using the embedded vector. If this is not
    // general enough, due to ordering, etc., we can construct an auxiliary vector.

    const PetscVec vector = field.vector();
    if (vector == PETSC_NULL) {
      field.createVector();
    }
    // TODO: Create scatter if necessary
    field.scatterSectionToVector();

    PetscErrorCode err = 0;
    err = VecView(vector, _viewer);
    CHECK_PETSC_ERROR(err);
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error while writing field '" << field.label() << "' at time " 
	<< t << " to HDF5 file '" << _filename << "'.\n" << err.what();
    throw std::runtime_error(msg.str());
  } catch (...) { 
    std::ostringstream msg;
    msg << "Error while writing field '" << field.label() << "' at time " 
	<< t << " to HDF5 file '" << _filename << "'.\n";
    throw std::runtime_error(msg.str());
  } // try/catch
} // writeCellField

// ----------------------------------------------------------------------
// Generate filename for HDF5 file.
template<typename mesh_type, typename field_type>
std::string
pylith::meshio::DataWriterHDF5<mesh_type,field_type>::_hdf5Filename(const double t) const
{ // _hdf5Filename
  std::ostringstream filename;
  const int indexExt = _filename.find(".h5");
  const int numTimeSteps = DataWriter<mesh_type, field_type>::_numTimeSteps;
  if (0 == numTimeSteps)
    filename << std::string(_filename, 0, indexExt) << "_info.hdf5";

  return std::string(filename.str());
} // _hdf5Filename


// End of file 
