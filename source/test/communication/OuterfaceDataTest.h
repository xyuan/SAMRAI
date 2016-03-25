/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   AMR communication tests for outerface-centered patch data
 *
 ************************************************************************/

#ifndef included_OuterfaceDataTest
#define included_OuterfaceDataTest

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/tbox/Array.h"
#include "SAMRAI/hier/BoundaryBox.h"
#include "SAMRAI/hier/Box.h"
#include "SAMRAI/geom/CartesianGridGeometry.h"
#include "SAMRAI/geom/CartesianPatchGeometry.h"
#include "SAMRAI/pdat/CellIndex.h"
#include "SAMRAI/pdat/FaceData.h"
#include "SAMRAI/pdat/OuterfaceData.h"
#include "SAMRAI/tbox/Database.h"
#include "SAMRAI/hier/IntVector.h"
#include "SAMRAI/hier/Patch.h"
#include "PatchDataTestStrategy.h"
#include "SAMRAI/tbox/Pointer.h"
#ifndef included_String
#include <string>
using namespace std;
#define included_String
#endif
#include "SAMRAI/hier/Variable.h"

namespace SAMRAI {

class CommTester;

/**
 * Class OuterfaceDataTest provides routines to test communication operations
 * for outerface-centered patch data on an AMR patch hierarchy.
 *
 * Required input keys and data types for test:
 *
 *   NONE...
 *
 * See PatchDataTestStrategy header file comments for variable and
 * refinement input data description.  Additionally, there are two
 * optional input parameters for each face variable.  These are:
 *
 *
 *
 *
 *
 *    - \b  use_fine_value_at_interface   which values to use at coarse-
 *                                          fine interface (default = TRUE)
 *
 *
 *
 *
 *
 */

class OuterfaceDataTest:public PatchDataTestStrategy
{
public:
   /**
    * The constructor initializes variable data arrays to zero length.
    */
   OuterfaceDataTest(
      const std::string& object_name,
      const tbox::Dimension& dim,
      tbox::Pointer<tbox::Database> main_input_db,
      bool do_refine,
      bool do_coarsen,
      const std::string& refine_option);

   /**
    * Virtual destructor for OuterfaceDataTest.
    */
   ~OuterfaceDataTest();

   /**
    * User-supplied boundary conditions.  Note that we do not implement
    * user-defined coarsen and refine operations.
    */
   virtual void
   setPhysicalBoundaryConditions(
      const hier::Patch& patch,
      const double time,
      const hier::IntVector& gcw) const;

   /**
    * This function is called from the CommTester constructor.  Its
    * purpose is to register variables used in the patch data test
    * and appropriate communication parameters (ghost cell widths,
    * coarsen/refine operations) with the CommTester object, which
    * manages the variable storage.
    */
   void
   registerVariables(
      CommTester* commtest);

   /**
    * Function for setting data on new patch in hierarchy.
    *
    * @param src_or_dst Flag set to 's' for source or 'd' for destination
    *        to indicate variables to set data for.
    */
   virtual void
   initializeDataOnPatch(
      const hier::Patch& patch,
      const tbox::Pointer<hier::PatchHierarchy> hierarchy,
      int level_number,
      char src_or_dst);

   /**
    * Function for checking results of communication operations.
    */
   bool
   verifyResults(
      const hier::Patch& patch,
      const tbox::Pointer<hier::PatchHierarchy> hierarchy,
      int level_number);

private:
   /*
    * Function for reading test data from input file.
    */
   void
   readTestInput(
      tbox::Pointer<tbox::Database> db);

   void
   setLinearData(
      tbox::Pointer<pdat::FaceData<double> > data,
      const hier::Box& box,
      const hier::Patch& patch) const;

   void
   setLinearData(
      tbox::Pointer<pdat::OuterfaceData<double> > data,
      const hier::Box& box,
      const hier::Patch& patch) const;

   void
   checkPatchInteriorData(
      const tbox::Pointer<pdat::OuterfaceData<double> >& data,
      const hier::Box& interior,
      const tbox::Pointer<geom::CartesianPatchGeometry>& pgeom) const;

   const tbox::Dimension d_dim;

   /*
    * Object std::string identifier for error reporting
    */
   std::string d_object_name;

   /*
    * Data members specific to this outerface data test.
    */
   tbox::Pointer<geom::CartesianGridGeometry> d_cart_grid_geometry;

   tbox::Array<bool> d_use_fine_value_at_interface;

   double d_Acoef;
   double d_Bcoef;
   double d_Ccoef;
   double d_Dcoef;

   bool d_do_refine;
   bool d_do_coarsen;
   std::string d_refine_option;
   int d_finest_level_number;

   tbox::Array<tbox::Pointer<hier::Variable> > d_variables_src;
   tbox::Array<tbox::Pointer<hier::Variable> > d_variables_dst;

};

}
#endif