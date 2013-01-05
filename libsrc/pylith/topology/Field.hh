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

/**
 * @file libsrc/topology/Field.hh
 *
 * @brief Vector field over the vertices or cells of a finite-element
 * mesh.
 */

#if !defined(pylith_topology_field_hh)
#define pylith_topology_field_hh

// Include directives ---------------------------------------------------
#include "FieldBase.hh" // ISA FieldBase

#include "pylith/utils/arrayfwd.hh" // HASA int_array
#include "pylith/utils/petscfwd.h" // HASA PetscVec

#include <petscdmmesh.hh>

#include <map> // USES std::map
#include <string> // USES std::string

// Field ----------------------------------------------------------------
/** @brief Vector field over the vertices or cells of a finite-element
 * mesh.
 *
 * Extends Sieve real general section by adding metadata.
 */
template<typename mesh_type,
	 typename section_type>
class pylith::topology::Field : public FieldBase
{ // Field
  friend class TestFieldMesh; // unit testing
  friend class TestFieldSubMesh; // unit testing

// PUBLIC TYPEDEFS //////////////////////////////////////////////////////
public:

  // Convenience typedefs
  typedef mesh_type Mesh;

  typedef ALE::ISieveVisitor::RestrictVisitor<section_type> RestrictVisitor;
  typedef ALE::ISieveVisitor::UpdateAddVisitor<section_type> UpdateAddVisitor;
  typedef ALE::ISieveVisitor::UpdateAllVisitor<section_type> UpdateAllVisitor;

// PRIVATE TYPEDEFS /////////////////////////////////////////////////////
private:

  // Convenience typedefs
  typedef typename mesh_type::SieveMesh SieveMesh;
  typedef typename SieveMesh::label_sequence label_sequence;
  typedef typename section_type::chart_type chart_type;

// PUBLIC MEMBERS ///////////////////////////////////////////////////////
public :

  /** Default constructor.
   *
   * @param mesh Finite-element mesh.
   */
  Field(const mesh_type& mesh);

  /** Constructor with mesh, DM, and metadata
   *
   * @param mesh Finite-element mesh.
   */
  Field(const mesh_type& mesh, DM dm, const Metadata& metadata);

  /** Constructor with mesh, section, and metadata.
   *
   * @param mesh Finite-element mesh.
   */
  Field(const mesh_type& mesh,
	const ALE::Obj<section_type>& section,
	const Metadata& metadata);


  Field(const Field& src, const int fields[], int numFields);

  /// Destructor.
  ~Field(void);

  /// Deallocate PETSc and local data structures.
  void deallocate(void);
  
  /** Get Sieve section.
   *
   * @returns Sieve section.
   */
  const ALE::Obj<section_type>& section(void) const;
  
  /** Get DMPlex section.
   *
   * @returns DMPlex section.
   */
  void dmSection(PetscSection *s, Vec *v) const;
  
  /** Get PetscSection.
   *
   * @returns PetscSection.
   */
  PetscSection petscSection() const;

  /** Get local Vec.
   *
   * @returns local Vec.
   */
  Vec localVector() const;

  /** Get global Vec.
   *
   * @returns global Vec.
   */
  Vec globalVector() const;

  /** Get mesh associated with field.
   *
   * @returns Finite-element mesh.
   */
  const mesh_type& mesh(void) const;

  /** Get DM associated with field.
   *
   * @returns DM
   */
  DM dmMesh(void) const;

  /** Set label for field.
   *
   * @param value Label for field.
   */
  void label(const char* value);

  /** Get label for field.
   *
   * @returns Label for field.
   */
  const char* label(void) const;

  /** Set vector field type
   *
   * @param value Type of vector field.
   */
  void vectorFieldType(const VectorFieldEnum value);

  /** Set vector field type
   *
   * @param name Field name
   * @param value Type of vector field.
   */
  void vectorFieldType(const std::string& name, const VectorFieldEnum value);

  /** Get vector field type
   *
   * @returns Type of vector field.
   */
  VectorFieldEnum vectorFieldType(void) const;

  /** Set scale for dimensionalizing field.
   *
   * @param value Scale associated with field.
   */
  void scale(const PylithScalar value);

  /** Set scale for dimensionalizing field.
   *
   * @param name Field name
   * @param value Scale associated with field.
   */
  void scale(const std::string& name, const PylithScalar value);

  /** Get scale for dimensionalizing field.
   *
   * @returns Scale associated with field.
   */
  PylithScalar scale(void) const;

  /** Set flag indicating whether it is okay to dimensionalize field.
   *
   * @param value True if it is okay to dimensionalize field.
   */
  void addDimensionOkay(const bool value);

  /** Set flag indicating whether it is okay to dimensionalize field.
   *
   * @param value True if it is okay to dimensionalize field.
   */
  bool addDimensionOkay(void) const;

  /** Get spatial dimension of domain.
   *
   * @returns Spatial dimension of domain.
   */
  int spaceDim(void) const;

  /** Get the number of sieve points in the chart.
   *
   * @returns the chart size.
   */
  int chartSize(void) const;

  /** Get the number of degrees of freedom.
   *
   * @returns the number of degrees of freedom.
   */
  int sectionSize(void) const;

  /** Create sieve section.
   *
   * @note Don't forget to call label().
   */
  void newSection(void);

  /** Create sieve section and set chart and fiber dimesion for
   * sequence of points.
   *
   * @param points Points over which to define section.
   * @param dim Fiber dimension for section.
   *
   * @note Don't forget to call label(), especially if reusing a field.
   */
  void newSection(const ALE::Obj<label_sequence>& points,
		  const int fiberDim);

  /** Create sieve section and set chart and fiber dimesion for a list
   * of points.
   *
   * @param points Points over which to define section.
   * @param dim Fiber dimension for section.
   *
   * @note Don't forget to call label(), especially if reusing a field.
   */
  void newSection(const int_array& points,
		  const int fiberDim);

  /** Create sieve section and set chart and fiber dimesion.
   *
   * @param domain Type of points over which to define section.
   * @param dim Fiber dimension for section.
   * @param stratum Stratum depth (for vertices) and height (for cells).
   *
   * @note Don't forget to call label(), especially if reusing a field.
   */
  void newSection(const DomainEnum domain,
		  const int fiberDim,
		  const int stratum =0);

  /** Create section using src field as template with given fiber dimension.
   *
   * @param sec Field defining layout.
   * @param fiberDim Fiber dimension.
   *
   * @note Don't forget to call label(), especially if reusing a field.
   */
  void newSection(const Field& src,
		  const int fiberDim);

  /** Create section with same layout (fiber dimension and
   * constraints) as another section. This allows the layout data
   * structures to be reused across multiple fields, reducing memory
   * usage.
   *
   * @param sec Field defining layout.
   *
   * @note Don't forget to call label(), especially if reusing a field.
   */
  void cloneSection(const Field& src);

  void addField(const char *name, int numComponents);

  void setupFields();

  void updateDof(const char *name, const DomainEnum domain, const int fiberDim);

  /// Clear variables associated with section.
  void clear(void);

  /// Allocate field.
  void allocate(void);

  /// Zero section values (does not zero constrained values).
  void zero(void);

  /// Zero section values (including constrained values).
  void zeroAll(void);

  /// Complete section by assembling across processors.
  void complete(void);

  /** Copy field values and metadata.
   *
   * @param field Field to copy.
   */
  void copy(const Field& field);

  /** Copy field values.
   *
   * @param field Field to copy.
   */
  void copy(const ALE::Obj<section_type>& field);

  /** Copy field values.
   *
   * @param osection Field to copy.
   * @param field Section field or -1
   * @param component Section field component or -1
   * @param ovec Values to copy.
   */
  void copy(PetscSection osection, PetscInt field, PetscInt component, Vec ovec);

  /** Add two fields, storing the result in one of the fields.
   *
   * @param field Field to add.
   */
  Field& operator+=(const Field& field);

  /** Dimensionalize field. Throws runtime_error if field is not
   * allowed to be dimensionalized.
   */
  void dimensionalize(void) const;

  /** Print field to standard out.
   *
   * @param label Label for output.
   */
  void view(const char* label) const;

  /** Create PETSc vector scatter for field. This is used to transfer
   * information from the "global" PETSc vector view to the "local"
   * Sieve section view. The PETSc vector does not contain constrained
   * DOF. Use createScatterWithBC() to include the constrained DOF in
   * the PETSc vector.
   *
   * @param mesh Mesh associated with scatter.
   * @param context Label for context associated with vector.
   */
  template<typename scatter_mesh_type>
  void createScatter(const scatter_mesh_type& mesh,
		     const char* context ="");


  /** Create PETSc vector scatter for field. This is used to transfer
   * information from the "global" PETSc vector view to the "local"
   * Sieve section view. The PETSc vector does not contain constrained
   * DOF. Use createScatterWithBC() to include the constrained DOF in
   * the PETSc vector.
   *
   * @param mesh Mesh associated with scatter.
   * @param numbering Numbering used to select points in section.
   * @param context Label for context associated with vector.
   */
  template<typename scatter_mesh_type>
  void createScatter(const scatter_mesh_type& mesh,
		     const typename ALE::Obj<typename SieveMesh::numbering_type> numbering,
		     const char* context ="");

  /** Create PETSc vector scatter for field. This is used to transfer
   * information from the "global" PETSc vector view to the "local"
   * Sieve section view. The PETSc vector includes constrained
   * DOF. Use createScatter() if constrained DOF should be omitted
   * from the PETSc vector.
   *
   * @param mesh Mesh associated with scatter.
   * @param context Label for context associated with vector.
   */
  template<typename scatter_mesh_type>
  void createScatterWithBC(const scatter_mesh_type& mesh,
			   const char* context ="");


  /** Create PETSc vector scatter for field. This is used to transfer
   * information from the "global" PETSc vector view to the "local"
   * Sieve section view. The PETSc vector includes constrained
   * DOF. Use createScatter() if constrained DOF should be omitted
   * from the PETSc vector.
   *
   * @param mesh Mesh associated with scatter.
   * @param labelName The name of the label defining the point set, or PETSC_NULL
   * @param labelValue The label stratum defining the point set
   * @param context Label for context associated with vector.
   */
  template<typename scatter_mesh_type>
  void createScatterWithBC(const scatter_mesh_type& mesh,
                           const std::string& labelName,
                           PetscInt labelValue,
                           const char* context ="");

  /** Get PETSc vector associated with field.
   *
   * @param context Label for context associated with vector.
   * @returns PETSc vector.
   */
  PetscVec vector(const char* context ="");

  /** Get PETSc vector associated with field.
   *
   * @param context Label for context associated with vector.
   * @returns PETSc vector.
   */
  const PetscVec vector(const char* context ="") const;

  /// Scatter section information across processors to update the
  /// PETSc vector view of the field.
  void scatterSectionToVector(const char* context ="") const;

  /** Scatter section information across processors to update the
   * PETSc vector view of the field.
   *
   * @param vector PETSc vector to update.
   */
  void scatterSectionToVector(const PetscVec vector,
			      const char* context ="") const;

  /// Scatter PETSc vector information across processors to update the
  /// Sieve section view of the field.
  void scatterVectorToSection(const char* context ="") const;

  /** Scatter section information across processors to update the
   * PETSc vector view of the field.
   *
   * @param vector PETSc vector used in update.
   */
  void scatterVectorToSection(const PetscVec vector,
			      const char* context ="") const;

  /// Setup split field with all entries set to a default space of 0.
  void splitDefault(void);

// PRIVATE STRUCTS //////////////////////////////////////////////////////
private :

  /// Data structures used in scattering to/from PETSc Vecs.
  struct ScatterInfo {
    DM dm; ///< PETSc DM defining the communication pattern
    PetscVec vector; ///< PETSc vector associated with field.
    // Deprecated
    PetscVecScatter scatter; ///< PETSc scatter associated with field.
    PetscVec scatterVec; ///< PETSC vector used in scattering.
  }; // ScatterInfo

// PRIVATE TYPEDEFS /////////////////////////////////////////////////////
private :

  typedef std::map<std::string, ScatterInfo> scatter_map_type;


// PRIVATE METHODS //////////////////////////////////////////////////////
private :

  /** Get fiber dimension associated with section (only works if fiber
   * dimension is uniform).
   *
   * Fiber dimension is determined from the first point on each
   * processor with the maximum value gathered across the processors.
   */
  int _getFiberDim(void);

  /** Get scatter for given context.
   *
   * @param context Context for scatter.
   * @param createOk If true, okay to create new scatter for
   * context, if false will throw std::runtime_error if scatter for
   * context doesn't already exist.
   */
  ScatterInfo& _getScatter(const char* context,
			   const bool createOk =false);

  /** Get scatter for given context.
   *
   * @param context Context for scatter.
   */
  const ScatterInfo& _getScatter(const char* context) const;

// PROTECTED TYPEDEFS ///////////////////////////////////////////////////
protected :

  typedef std::map< std::string, Metadata > map_type;

// PRIVATE MEMBERS //////////////////////////////////////////////////////
private :

  map_type _metadata;
  /* Old construction */
  const mesh_type& _mesh; ///< Mesh associated with section.
  ALE::Obj<section_type> _section; ///< Real section with data.
  scatter_map_type _scatters; ///< Collection of scatters.
  /* New construction */
  DM  _dm; /* Holds the PetscSection */
  Vec _globalVec;
  Vec _localVec;
  std::map<std::string, int> _tmpFields;

// NOT IMPLEMENTED //////////////////////////////////////////////////////
private :

  Field(const Field&); ///< Not implemented
  const Field& operator=(const Field&); ///< Not implemented

}; // Field

#include "Field.icc"
#include "Field.cc"

#endif // pylith_topology_field_hh


// End of file 
