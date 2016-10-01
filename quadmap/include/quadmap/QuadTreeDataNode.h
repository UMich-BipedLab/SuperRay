/*
 * OctoMap - An Efficient Probabilistic 3D Mapping Framework Based on Octrees
 * http://octomap.github.com/
 *
 * Copyright (c) 2009-2013, K.M. Wurm and A. Hornung, University of Freiburg
 * All rights reserved.
 * License: New BSD
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of Freiburg nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef QUADMAP_QUADTREE_DATA_NODE_H
#define QUADMAP_QUADTREE_DATA_NODE_H

#include "quadmap_types.h"
#include "assert.h"

namespace quadmap {

	class AbstractQuadTreeNode {


	};

	// forward declaration for friend in QuadTreeDataNode
	template<typename NODE, typename I> class QuadTreeBaseImpl;

	/**
	 * Basic node in the QuadTree that can hold arbitrary data of type T in value.
	 * This is the base class for nodes used in an QuadTree. The used implementation
	 * for occupancy mapping is in QuadTreeNode.#
	 * \tparam T data to be stored in the node (e.g. a float for probabilities)
	 *
	 * Note: If you derive a class (directly or indirectly) from QuadTreeDataNode,
	 * you have to implement (at least) the following functions to avoid slicing
	 * errors and memory-related bugs:
	 * createChild(), getChild(), getChild() const, expandNode()
	 * See ColorQuadTreeNode in ColorQuadTree.h for an example.
	 */
	template<typename T> class QuadTreeDataNode : public AbstractQuadTreeNode {
		template<typename NODE, typename I>
		friend class QuadTreeBaseImpl;

	public:

		QuadTreeDataNode();
		QuadTreeDataNode(T initVal);

		/// Copy constructor, performs a recursive deep-copy of all children 
		/// including node data in "value"
		QuadTreeDataNode(const QuadTreeDataNode& rhs);

		/// Delete only own members. 
		/// QuadTree maintains tree structure and must have deleted children already
		~QuadTreeDataNode();

		/// Copy the payload (data in "value") from rhs into this node
		/// Opposed to copy ctor, this does not clone the children as well
		void copyData(const QuadTreeDataNode& from);

		/// Equals operator, compares if the stored value is identical
		bool operator==(const QuadTreeDataNode& rhs) const;





		// -- children  ----------------------------------

		/// Test whether the i-th child exists. 
		/// @deprecated Replaced by tree->nodeChildExists(...)
		/// \return true if the i-th child exists
		QUADMAP_DEPRECATED(bool childExists(unsigned int i) const);

		/// @deprecated Replaced by tree->nodeHasChildren(...)
		/// \return true if the node has at least one child
		QUADMAP_DEPRECATED(bool hasChildren() const);

		/// @return value stored in the node
		T getValue() const{ return value; };
		/// sets value to be stored in the node
		void setValue(T v) { value = v; };

		// file IO:

		/// Read node payload (data only) from binary stream
		std::istream& readData(std::istream &s);

		/// Write node payload (data only) to binary stream
		std::ostream& writeData(std::ostream &s) const;


		/// Make the templated data type available from the outside
		typedef T DataType;


	protected:
		void allocChildren();

		/// pointer to array of children, may be NULL
		/// @note The tree class manages this pointer, the array, and the memory for it!
		/// The children of a node are always enforced to be the same type as the node
		AbstractQuadTreeNode** children;
		/// stored data (payload)
		T value;

	};


} // end namespace

#include "quadmap/QuadTreeDataNode.hxx"

#endif
