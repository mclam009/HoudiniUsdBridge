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
 *      Calvin Gu
 *	Side Effects Software Inc.
 *	123 Front Street West, Suite 1401
 *	Toronto, Ontario
 *      Canada   M5J 2M2
 *	416-504-9876
 *
 */

#ifndef __HUSD_SetAttributes_h__
#define __HUSD_SetAttributes_h__

#include "HUSD_API.h"
#include "HUSD_DataHandle.h"
#include "HUSD_TimeCode.h"
#include <UT/UT_StringHolder.h>

class UT_Options;
class HUSD_FindPrims;

class HUSD_API HUSD_SetAttributes
{
public:
			 HUSD_SetAttributes(HUSD_AutoWriteLock &lock);
			~HUSD_SetAttributes();

    /// @{ Create an attribute or primvar on a primitive.
    bool		 addAttribute(const UT_StringRef &primpath,
				const UT_StringRef &attrname,
				const UT_StringRef &type,
				bool custom = true) const;

    bool		 addPrimvar(const UT_StringRef &primpath,
				const UT_StringRef &primvarname,
				const UT_StringRef &interpolation,
				const UT_StringRef &type) const;
    /// @}

    /// @{ Set an attribute or primvar value on a primitive.
    template<typename UtValueType>
    bool		 setAttribute(const UT_StringRef &primpath,
				const UT_StringRef &attrname,
				const UtValueType &value,
				const HUSD_TimeCode &timecode,
				const UT_StringRef &valueType =
				    UT_StringHolder::theEmptyString,
				bool custom = true,
                                bool clear_existing = true) const;

    template<typename UtValueType>
    bool		 setPrimvar(const UT_StringRef &primpath,
				const UT_StringRef &primvarname,
				const UT_StringRef &interpolation,
				const UtValueType &value,
				const HUSD_TimeCode &timecode,
				const UT_StringRef &valueType =
				    UT_StringHolder::theEmptyString,
                                int elementsize = 1,
                                bool clear_existing = true) const;
    /// @}


    /// @{ Set an attribute or primvar value on a primitive,
    /// but accept the *subclasses* of the UT_Array. 
    template<typename UtValueType>
    bool		 setAttributeArray(const UT_StringRef &primpath,
				const UT_StringRef &attrname,
				const UT_Array<UtValueType> &value,
				const HUSD_TimeCode &timecode,
				const UT_StringRef &valueType =
                                    UT_StringHolder::theEmptyString,
				bool custom = true,
                                bool clear_existing = true) const
			 { return setAttribute(primpath, attrname,
				 value, timecode, valueType,
                                 custom, clear_existing); }

    template<typename UtValueType>
    bool		 setPrimvarArray(const UT_StringRef &primpath,
				const UT_StringRef &primvarname,
				const UT_StringRef &interpolation,
				const UT_Array<UtValueType> &value,
				const HUSD_TimeCode &timecode,
				const UT_StringRef &valueType =
                                    UT_StringHolder::theEmptyString,
                                int elementsize = 1,
                                bool clear_existing = true) const
			 { return setPrimvar(primpath, primvarname,
				 interpolation, value, timecode,
                                 valueType, elementsize, clear_existing); }
    /// @}

    /// @{ Set attributes for every entry in a UT_Options object.
    bool		 setAttributes(const UT_StringRef &primpath,
				const UT_Options &options,
                                const HUSD_TimeCode &timecode,
				const UT_StringRef &attrnamespace =
                                    UT_StringHolder::theEmptyString,
                                bool clear_existing = true) const;
    /// @}

    /// @{ Blocks an attribute or primvar.
    bool		 blockAttribute(const UT_StringRef &primpath,
				const UT_StringRef &attrname) const;
    bool		 blockPrimvar(const UT_StringRef &primpath,
				const UT_StringRef &primvarname) const;
    bool		 blockPrimvarIndices(const UT_StringRef &primpath,
				const UT_StringRef &primvarname) const;
    /// @}
  
    /// @{ Disconnects an input attribute from its source.
    bool		disconnect(const UT_StringRef &primpath,
				const UT_StringRef &attrname) const;
    bool		disconnectIfConnected(const UT_StringRef &primpath,
				const UT_StringRef &attrname) const;
    bool		isConnected(const UT_StringRef &primpath,
				const UT_StringRef &attrname) const;
    /// @}
   

    /// Sets primvar's indices, making it an indexed primvar.
    bool		 setPrimvarIndices( const UT_StringRef &primpath,
				const UT_StringRef &primvar_name,
				const UT_ExintArray &indices,
				const HUSD_TimeCode &timecode) const;

    /// @{ Returns effective time code at which the value should be set.
    /// Eg, if attribute has time samples and the given time code is default,
    /// it needs to be "promoted" to time code for the specific frame/time.
    /// Otherwise, setting value at default time will not take effect, if
    /// there is already a value at that specific frame/time.
    /// This ensures that getAttribute() returns the same value as set here.
    HUSD_TimeCode	 getAttribEffectiveTimeCode(
				const UT_StringRef &primpath,
				const UT_StringRef &attribname,
				const HUSD_TimeCode &timecode) const;
    HUSD_TimeCode	 getPrimvarEffectiveTimeCode(
				const UT_StringRef &primpath,
				const UT_StringRef &primvarname,
				const HUSD_TimeCode &timecode) const;
    HUSD_TimeCode	 getPrimvarIndicesEffectiveTimeCode(
				const UT_StringRef &primpath,
				const UT_StringRef &primvarname,
				const HUSD_TimeCode &timecode) const;
    /// @}

    /// Copies an attribute from one primitive to another. This method will
    /// copy all values and time samples, ensure matching data types, etc.
    bool                 copyProperty(
                                const UT_StringRef &srcprimpath,
                                const UT_StringRef &srcpropertyname,
                                const HUSD_FindPrims &finddestprims,
                                const UT_StringRef &destpropertyname,
                                bool copymetadata,
                                bool blocksource);

private:
    HUSD_AutoWriteLock	&myWriteLock;
};

#endif
