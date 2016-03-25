//
// File:        $URL: file:///usr/casc/samrai/repository/SAMRAI/tags/v-2-2-0/examples/mblkcomm/FaceMultiblockTest.h $
// Package:     SAMRAI tests
// Copyright:   (c) 1997-2007 Lawrence Livermore National Security, LLC
// Revision:    $LastChangedRevision: 1704 $
// Modified:    $LastChangedDate: 2007-11-13 16:32:40 -0800 (Tue, 13 Nov 2007) $
// Description: AMR communication tests for edge-centered patch data
//

#ifndef included_FaceMultiblockTest
#define included_FaceMultiblockTest

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif

#ifndef included_tbox_Array
#include "tbox/Array.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_pdat_FaceData
#include "FaceData.h"
#endif
#ifndef included_pdat_FaceDoubleConstantRefine
#include "FaceDoubleConstantRefine.h"
#endif
#ifndef included_tbox_Database
#include "tbox/Database.h"
#endif
#ifndef included_hier_IntVector
#include "IntVector.h"
#endif
#ifndef included_hier_Patch
#include "Patch.h"
#endif
#ifndef included_hier_PatchMultiblockTestStrategy
#include "PatchMultiblockTestStrategy.h"
#endif
#ifndef included_tbox_Pointer
#include "Pointer.h"
#endif
#ifndef included_geom_BlockGridGeometry
#include "BlockGridGeometry.h"
#endif
#ifndef included_hier_Variable
#include "Variable.h"
#endif

using namespace SAMRAI;

/**
 * Class FaceMultiblockTest provides routines to test communication operations
 * for edge-centered patch data on an AMR patch hierarchy.
 *
 * See PatchMultiblockTestStrategy header file comments for variable and
 * refinement input data description.
 */

class FaceMultiblockTest : public PatchMultiblockTestStrategy
{
public:
  /**
   * The constructor initializes variable data arrays to zero length.
   */
   FaceMultiblockTest(const string& object_name,
                tbox::Pointer<tbox::Database> main_input_db,
                bool do_refine,
                bool do_coarsen,
                const string& refine_option);

   /**
    * Virtual destructor for FaceMultiblockTest.
    */
   virtual ~FaceMultiblockTest();

   /**
    * User-supplied boundary conditions.  Note that we do not implement
    * user-defined coarsen and refine operations.
    */
   void setPhysicalBoundaryConditions(
      hier::Patch<NDIM>& patch,
      const double time,
      const hier::IntVector<NDIM>& gcw_to_fill) const;

   void fillSingularityBoundaryConditions(
      hier::Patch<NDIM>& patch,
      tbox::List<xfer::MultiblockRefineSchedule<NDIM>::SingularityPatch>&
         sing_patches,
      const hier::Box<NDIM>& fill_box,
      const hier::BoundaryBox<NDIM>& boundary_box);

   /**
    * This function is called from the MultiblockTester constructor.  Its
    * purpose is to register variables used in the patch data test
    * and appropriate communication parameters (ghost cell widths,
    * coarsen/refine operations) with the MultiblockTester object, which
    * manages the variable storage.
    */
   void registerVariables(MultiblockTester* commtest);

   /**
    * Function for setting data on new patch in hierarchy.
    *
    * @param src_or_dst Flag set to 's' for source or 'd' for destination
    *        to indicate variables to set data for.
    */
   virtual void initializeDataOnPatch(
      hier::Patch<NDIM>& patch,
      const tbox::Pointer<hier::PatchHierarchy<NDIM> > hierarchy,
      int level_number,
      int block_number,
      char src_or_dst);

   /**
    * Function for tagging cells on each patch to refine.
    */
   void tagCellsToRefine(
      hier::Patch<NDIM>& patch,
      const tbox::Pointer<hier::PatchHierarchy<NDIM> > hierarchy,
      int level_number,
      int tag_index);
   
   /**
    * Function for checking results of communication operations.
    */
   bool verifyResults(
      hier::Patch<NDIM>& patch,
      const tbox::Pointer<hier::MultiblockPatchHierarchy<NDIM> > hierarchy,
      int level_number,
      int block_number);

   ///
   void postprocessRefine(hier::Patch<NDIM>& fine,
                          const hier::Patch<NDIM>& coarse,
                          const tbox::Pointer<hier::VariableContext>& context,
                          const hier::Box<NDIM>& fine_box,
                          const hier::IntVector<NDIM>& ratio) const;

private:
   /**
    * Function for reading test data from input file.
    */
   void readTestInput(tbox::Pointer<tbox::Database> db);

   /*
    * Object string identifier for error reporting
    */
   string d_object_name;

   /*
    * Data members specific to this edge data test.
    */
   tbox::Array< tbox::Pointer< hier::GridGeometry<NDIM> > >
   d_skel_grid_geometry;

   string d_refine_option;
   int d_finest_level_number;

   tbox::Array< tbox::Pointer< hier::Variable<NDIM> > > d_variables;

};

#endif