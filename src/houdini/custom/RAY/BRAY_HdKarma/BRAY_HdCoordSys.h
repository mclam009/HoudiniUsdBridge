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
 *      Side Effects Software Inc.
 *      123 Front Street West, Suite 1401
 *      Toronto, Ontario
 *      Canada   M5J 2M2
 *      416-504-9876
 *
 */

#ifndef __BRAY_HdCoordSys__
#define __BRAY_HdCoordSys__

#include <pxr/pxr.h>
#include <pxr/imaging/hd/coordSys.h>
#include <BRAY/BRAY_Interface.h>

PXR_NAMESPACE_OPEN_SCOPE

class BRAY_HdCoordSys final : public HdCoordSys
{
public:
    BRAY_HdCoordSys(const SdfPath &id);
    ~BRAY_HdCoordSys() override;

    void	        Finalize(HdRenderParam *renderParam) override final;
    void	        Sync(HdSceneDelegate *sceneDelegate,
				HdRenderParam *renderParam,
				HdDirtyBits *dirtyBits) override final;
    HdDirtyBits	        GetInitialDirtyBitsMask() const override final;
private:
    BRAY::CoordSysPtr   myCoordSys;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
