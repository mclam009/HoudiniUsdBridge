/*
 * Copyright 2019 Side Effects Software Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Produced by:
 *	Side Effects Software Inc.
 *	123 Front Street West, Suite 1401
 *	Toronto, Ontario
 *      Canada   M5J 2M2
 *	416-504-9876
 *
 */

#ifndef __HUSD_FindPrims_h__
#define __HUSD_FindPrims_h__

#include "HUSD_API.h"
#include "HUSD_DataHandle.h"
#include "HUSD_Utils.h"
#include <OP/OP_ItemId.h>
#include <UT/UT_BoundingBox.h>
#include <UT/UT_StringMap.h>
#include <UT/UT_StringArray.h>
#include <UT/UT_UniquePtr.h>
#include <UT/UT_VectorTypes.h>
#include <SYS/SYS_Types.h>
#include <pxr/pxr.h>

PXR_NAMESPACE_OPEN_SCOPE
class XUSD_PathPattern;
PXR_NAMESPACE_CLOSE_SCOPE

class HUSD_PathSet;
class HUSD_TimeCode;
template <typename T> class UT_Array;

class HUSD_API HUSD_FindPrims : public UT_NonCopyable
{
public:
			 HUSD_FindPrims(HUSD_AutoAnyLock &lock,
				 HUSD_PrimTraversalDemands demands =
				    HUSD_TRAVERSAL_DEFAULT_DEMANDS,
				 bool find_point_instancer_ids = false);
			 // Simple constructors when you just want to operate
			 // on one or an array of primitives and you know the
			 // paths.
			 HUSD_FindPrims(HUSD_AutoAnyLock &lock,
				 const UT_StringRef &primpath,
				 HUSD_PrimTraversalDemands demands =
				    HUSD_TRAVERSAL_DEFAULT_DEMANDS);
			 HUSD_FindPrims(HUSD_AutoAnyLock &lock,
				 const UT_StringArray &primpaths,
				 HUSD_PrimTraversalDemands demands =
				    HUSD_TRAVERSAL_DEFAULT_DEMANDS);
			 HUSD_FindPrims(HUSD_AutoAnyLock &lock,
				 const HUSD_PathSet &primpaths,
				 HUSD_PrimTraversalDemands demands =
				    HUSD_TRAVERSAL_DEFAULT_DEMANDS);
			~HUSD_FindPrims();

    enum BBoxContainment {
	BBOX_FULLY_INSIDE,
	BBOX_FULLY_OUTSIDE,
	BBOX_PARTIALLY_INSIDE,
	BBOX_PARTIALLY_OUTSIDE
    };

    const HUSD_PathSet	&getExpandedPathSet() const;
    const HUSD_PathSet	&getCollectionAwarePathSet() const;
    const HUSD_PathSet	&getExcludedPathSet(bool skipdescendants) const;
    const HUSD_PathSet	&getMissingExplicitPathSet() const;
    const HUSD_PathSet	&getExpandedOrMissingExplicitPathSet() const;

    void		 setTraversalDemands(HUSD_PrimTraversalDemands demands);
    HUSD_PrimTraversalDemands traversalDemands() const;
    void                 setAssumeWildcardsAroundPlainTokens(bool assume);
    bool                 assumeWildcardsAroundPlainTokens() const;
    void                 setTrackMissingExplicitPrimitives(bool track_missing);
    bool                 trackMissingExplicitPrimitives() const;
    void                 setWarnMissingExplicitPrimitives(bool warn_missing);
    bool                 warnMissingExplicitPrimitives() const;
    void                 setCaseSensitive(bool casesensitive);
    bool                 caseSensitive() const;

    // Add a specific set of primitive paths or collection paths to our data.
    bool		 addPaths(const HUSD_PathSet &paths);
    // Evaluate the supplied pattern and add the resulting primitives and
    // collections to our data.
    bool		 addPattern(const UT_StringRef &pattern,
				int nodeid,
				const HUSD_TimeCode &timecode);
    bool		 addPrimitiveType(const UT_StringRef &primtype);
    bool		 addPrimitiveKind(const UT_StringRef &primkind);
    bool		 addPrimitivePurpose(const UT_StringRef &primpurpose);
    bool		 addVexpression(const UT_StringRef &vexpression,
				int nodeid,
				const HUSD_TimeCode &timecode) const;
    bool		 addBoundingBox(const UT_BoundingBox &bbox,
				const HUSD_TimeCode &t,
				const UT_StringArray &purposes,
				BBoxContainment containment);
    bool		 addDescendants();
    bool		 addAncestors();

    const UT_StringMap<UT_Array<int64>>
                        &getPointInstancerIds() const;
    bool		 getExcludedPointInstancerIds(
				UT_StringMap<UT_Array<int64>> &excludedids,
				const HUSD_TimeCode &timecode) const;

    bool		 getIsEmpty() const;
    bool		 getFindPointInstancerIds() const;
    bool		 getIsTimeVarying() const;
    bool		 allowInstanceProxies() const;

    /// Generally speaking, HUSD_FindPrims will never return the
    /// HoudiniLayerInfo prim. But there are some circumstances where we
    /// may wish to allow it.
    void                 setAllowHoudiniLayerInfo(bool allow);
    bool                 allowHoudiniLayerInfo() const;

    /// Returns a collection path, if only a single collection was added.
    /// Returns an empty string, if primitive target consists of more than 
    /// a single collection.
    UT_StringHolder	 getSingleCollectionPath() const;

    /// Returns the path to the most nested primitive that is the shared
    /// root primitive of every primitive in our expanded set. If the shared
    /// root prim is the absolute root, we return an empty string.
    UT_StringHolder      getSharedRootPrim() const;

    /// Return a string describing the last error generated by a failed
    /// call to this object's methods.
    const UT_StringHolder &getLastError() const
			 { return myLastError; }

private:
    bool		 addPattern(const PXR_NS::XUSD_PathPattern &pattern,
                                int nodeid);

    class husd_FindPrimsPrivate;

    UT_UniquePtr<husd_FindPrimsPrivate>	 myPrivate;
    HUSD_AutoAnyLock			&myAnyLock;
    HUSD_PrimTraversalDemands		 myDemands;
    UT_StringHolder			 myLastError;
    bool				 myFindPointInstancerIds;
    bool				 myAssumeWildcardsAroundPlainTokens;
    bool                                 myTrackMissingExplicitPrimitives;
    bool                                 myWarnMissingExplicitPrimitives;
    bool				 myCaseSensitive;
};

#endif

