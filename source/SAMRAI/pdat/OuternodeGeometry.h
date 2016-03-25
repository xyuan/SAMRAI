/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   hier
 *
 ************************************************************************/

#ifndef included_pdat_OuternodeGeometry
#define included_pdat_OuternodeGeometry

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/pdat/NodeOverlap.h"
#include "SAMRAI/hier/Box.h"
#include "SAMRAI/hier/BoxGeometry.h"
#include "SAMRAI/hier/BoxOverlap.h"
#include "SAMRAI/hier/IntVector.h"
#include "SAMRAI/tbox/Pointer.h"

namespace SAMRAI {
namespace pdat {

class NodeGeometry;

/*!
 * Class OuternodeGeometry manages the mapping between the AMR index
 * and the outernode geometry index space.  It is a subclass of
 * hier::BoxGeometry and it computes intersections between outernode
 * box geometries and node or outernode box geometries for communication
 * operations.
 *
 * See header file for OuternodeData<DIM> class for a more detailed
 * description of the data layout.
 *
 * @see hier::BoxGeometry
 * @see pdat::NodeGeometry
 * @see pdat::NodeOverlap
 */

class OuternodeGeometry:public hier::BoxGeometry
{
public:
   /*!
    * The BoxOverlap implemenation for this geometry.
    */
   typedef NodeOverlap Overlap;

   /*!
    * @brief Construct an outernode geometry object given an AMR index
    * space box and ghost cell width.
    */
   explicit OuternodeGeometry(
      const hier::Box& box,
      const hier::IntVector& ghosts);

   /*!
    * @brief The virtual destructor does nothing interesting.
    */
   virtual ~OuternodeGeometry();

   /*!
    * @brief Compute the overlap in node-centered index space on the
    * boundaries of the source box geometry and the destination box geometry.
    */
   virtual tbox::Pointer<hier::BoxOverlap>
   calculateOverlap(
      const hier::BoxGeometry& dst_geometry,
      const hier::BoxGeometry& src_geometry,
      const hier::Box& src_mask,
      const hier::Box& fill_box,
      const bool overwrite_interior,
      const hier::Transformation& transformation,
      const bool retry,
      const hier::BoxContainer& dst_restrict_boxes = hier::BoxContainer()) const;

   /*!
    * @brief Set up a NodeOverlap object based on the given boxes and the
    * transformation.
    */
   virtual tbox::Pointer<hier::BoxOverlap>
   setUpOverlap(
      const hier::BoxContainer& boxes,
      const hier::Transformation& transformation) const;

   /*!
    * @brief Return the box for this outernode box geometry object.
    */
   const hier::Box&
   getBox() const;

   /*!
    * @brief Return the ghost cell width for this outernode box geometry object.
    */
   const hier::IntVector&
   getGhosts() const;

private:
   /*!
    * @brief
    * Compute the overlap
    * between the source and destination objects, where the source
    * has outernode geometry and the destination node geometry.
    */
   static tbox::Pointer<hier::BoxOverlap>
   doOverlap(
      const NodeGeometry& dst_geometry,
      const OuternodeGeometry& src_geometry,
      const hier::Box& src_mask,
      const hier::Box& fill_box,
      const bool overwrite_interior,
      const hier::Transformation& transformation,
      const hier::BoxContainer& dst_restrict_boxes);

   /*!
    * @brief
    * Compute the overlap
    * between the source and destination objects, where the source
    * has node geometry and the destination outernode geometry.
    */
   static tbox::Pointer<hier::BoxOverlap>
   doOverlap(
      const OuternodeGeometry& dst_geometry,
      const NodeGeometry& src_geometry,
      const hier::Box& src_mask,
      const hier::Box& fill_box,
      const bool overwrite_interior,
      const hier::Transformation& transformation,
      const hier::BoxContainer& dst_restrict_boxes);

   /*!
    * @brief
    * Compute the overlap
    * between the source and destination objects, where the source
    * has outernode geometry and the destination outernode geometry.
    */
   static tbox::Pointer<hier::BoxOverlap>
   doOverlap(
      const OuternodeGeometry& dst_geometry,
      const OuternodeGeometry& src_geometry,
      const hier::Box& src_mask,
      const hier::Box& fill_box,
      const bool overwrite_interior,
      const hier::Transformation& transformation,
      const hier::BoxContainer& dst_restrict_boxes);

   /*! Not implemented */
   OuternodeGeometry(
      const OuternodeGeometry&);
   /*! Not implemented */
   void
   operator = (
      const OuternodeGeometry&);

   hier::Box d_box;
   hier::IntVector d_ghosts;

};

}
}
#ifdef SAMRAI_INLINE
#include "SAMRAI/pdat/OuternodeGeometry.I"
#endif
#endif