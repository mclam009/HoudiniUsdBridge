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

#ifndef __HUSD_PropertyHandle_h__
#define __HUSD_PropertyHandle_h__

#include "HUSD_API.h"
#include "HUSD_ObjectHandle.h"
#include "HUSD_PrimHandle.h"

class PI_EditScriptedParm;

// These defines specify node parameter sparte data tags that are used to
// describe how a parameter should be translated into a USD attribute.
#define HUSD_PROPERTY_VALUETYPE			"usdvaluetype"
#define HUSD_PROPERTY_VALUETYPE_RELATIONSHIP	"relationship"
#define HUSD_PROPERTY_VALUETYPE_XFORM		"xform"
#define HUSD_PROPERTY_VALUETYPE_RAMP		"ramp"
#define HUSD_PROPERTY_VALUE_ORDERED		"usdvalueordered"
#define HUSD_PROPERTY_APISCHEMA			"usdapischema"
#define HUSD_PROPERTY_VALUENAME		        "usdvaluename"
#define HUSD_PROPERTY_RAMPCOUNTNAME		"usdrampcountname"
#define HUSD_PROPERTY_RAMPBASISNAME		"usdrampbasisname"
#define HUSD_PROPERTY_RAMPBASISISARRAY		"usdrampbasisisarray"
#define HUSD_PROPERTY_RAMPBASISSUFFIX		"_basis"
#define HUSD_PROPERTY_RAMPPOSNAME		"usdrampposname"
#define HUSD_PROPERTY_RAMPPOSSUFFIX		"_pos"
#define HUSD_PROPERTY_CONTROLPARM		"usdcontrolparm"
#define HUSD_PROPERTY_XFORM_PARM_PREFIX		"xformparmprefix"
#define HUSD_PROPERTY_ISCUSTOM			"usdiscustomattrib"

// These defines are used as custom data keys on the value attribute of the
// ramp attribute trio, to tie everything together.
#define HUSD_PROPERTY_RAMPVALUEATTR_KEY         "rampvalueattr"
#define HUSD_PROPERTY_RAMPCOUNTATTR_KEY         "rampcountattr"
#define HUSD_PROPERTY_RAMPBASISATTR_KEY         "rampbasisattr"
#define HUSD_PROPERTY_RAMPBASISISARRAY_KEY      "rampbasisisarray"
#define HUSD_PROPERTY_RAMPPOSATTR_KEY           "rampposattr"

// This class is a standalone wrapper around a specific property in a USD
// stage wrapped in an HUSD_DataHandle. It's purpose is to serve as the data
// accessor for tree nodes in the Scene Graph Tree. It should not be used for
// any other purpose, as it is extremely inefficient. Each function call locks
// the HUSD_DataHandle, queries its information, then unlocks it again. This
// is a matter of convenience for the calling pattern of the scene graph tree.
// Because it is inefficient the scene graph tree caches any information that
// comes out of this object.
//
// Anyone else tempted to use this object should use HUSD_Info instead.
class HUSD_API HUSD_PropertyHandle : public HUSD_ObjectHandle
{
public:
				 HUSD_PropertyHandle();
				 HUSD_PropertyHandle(
					const HUSD_PrimHandle &prim_handle,
					const UT_StringRef &property_name);
                                ~HUSD_PropertyHandle() override;

    const HUSD_DataHandle	        &dataHandle() const override
					 { return myPrimHandle.dataHandle(); }
    const HUSD_ConstOverridesPtr        &overrides() const override
					 { return myPrimHandle.overrides(); }
    const HUSD_PrimHandle		&primHandle() const
					 { return myPrimHandle; }

    UT_StringHolder		 getSourceSchema() const;
    UT_StringHolder		 getTypeDescription() const;
    bool			 isCustom() const;
    bool			 isXformOp() const;

    void			 createScriptedParms(
					UT_Array<PI_EditScriptedParm *> &parms,
					const UT_StringRef &custom_name,
					bool prepend_control_parm,
					bool prefix_xform_parms) const;

private:
    void			 createScriptedControlParm(
					UT_Array<PI_EditScriptedParm *> &parms,
					const UT_StringHolder &propbasename,
                                        const UT_StringRef &usdvaluetype) const;

    HUSD_PrimHandle		 myPrimHandle;
};

#endif

