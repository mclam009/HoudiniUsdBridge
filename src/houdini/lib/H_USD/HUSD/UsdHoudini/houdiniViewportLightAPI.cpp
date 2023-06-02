//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "./houdiniViewportLightAPI.h"
#include "pxr/usd/usd/schemaRegistry.h"
#include "pxr/usd/usd/typed.h"
#include "pxr/usd/usd/tokens.h"

#include "pxr/usd/sdf/types.h"
#include "pxr/usd/sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
// NOTE: IF THIS LINE IS DIFFERENT FROM THE CODE IN GITHUB, MAKE SURE WE USE
// TF_REGISTRY_FUNCTION_WITH_TAG, JUST NOT TF_REGISTRY_FUNCTION.
// THIS IS TO FIX A VS2019 BUILD ISSUE (SEE r352600, r366226).
TF_REGISTRY_FUNCTION_WITH_TAG(TfType, schemaClass_UsdHoudinihoudiniViewportLightAPI)
{
    TfType::Define<UsdHoudinihoudiniViewportLightAPI,
        TfType::Bases< UsdAPISchemaBase > >();
    
}

// PLEASE DO NOT UNDO THIS CHANGE (moving of the line below)
// This fixes clang unused variable warnings
/* virtual */
UsdHoudinihoudiniViewportLightAPI::~UsdHoudinihoudiniViewportLightAPI()
{
}

/* static */
UsdHoudinihoudiniViewportLightAPI
UsdHoudinihoudiniViewportLightAPI::Get(const UsdStagePtr &stage, const SdfPath &path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdHoudinihoudiniViewportLightAPI();
    }
    return UsdHoudinihoudiniViewportLightAPI(stage->GetPrimAtPath(path));
}


/* virtual */
UsdSchemaKind UsdHoudinihoudiniViewportLightAPI::_GetSchemaKind() const {
    return UsdHoudinihoudiniViewportLightAPI::schemaKind;
}

/* virtual */
UsdSchemaKind UsdHoudinihoudiniViewportLightAPI::_GetSchemaType() const {
    return UsdHoudinihoudiniViewportLightAPI::schemaType;
}

/* static */
UsdHoudinihoudiniViewportLightAPI
UsdHoudinihoudiniViewportLightAPI::Apply(const UsdPrim &prim)
{
    if (prim.ApplyAPI<UsdHoudinihoudiniViewportLightAPI>()) {
        return UsdHoudinihoudiniViewportLightAPI(prim);
    }
    return UsdHoudinihoudiniViewportLightAPI();
}

/* static */
const TfType &
UsdHoudinihoudiniViewportLightAPI::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<UsdHoudinihoudiniViewportLightAPI>();
    return tfType;
}

/* static */
bool 
UsdHoudinihoudiniViewportLightAPI::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType &
UsdHoudinihoudiniViewportLightAPI::_GetTfType() const
{
    return _GetStaticTfType();
}

UsdAttribute
UsdHoudinihoudiniViewportLightAPI::GetHoudiniClippingRangeAttr() const
{
    return GetPrim().GetAttribute(UsdHoudiniTokens->houdiniClippingRange);
}

UsdAttribute
UsdHoudinihoudiniViewportLightAPI::CreateHoudiniClippingRangeAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdHoudiniTokens->houdiniClippingRange,
                       SdfValueTypeNames->Float2,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

namespace {
static inline TfTokenVector
_ConcatenateAttributeNames(const TfTokenVector& left,const TfTokenVector& right)
{
    TfTokenVector result;
    result.reserve(left.size() + right.size());
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}
}

/*static*/
const TfTokenVector&
UsdHoudinihoudiniViewportLightAPI::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames = {
        UsdHoudiniTokens->houdiniClippingRange,
    };
    static TfTokenVector allNames =
        _ConcatenateAttributeNames(
            UsdAPISchemaBase::GetSchemaAttributeNames(true),
            localNames);

    if (includeInherited)
        return allNames;
    else
        return localNames;
}

PXR_NAMESPACE_CLOSE_SCOPE

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
//
// Just remember to wrap code in the appropriate delimiters:
// 'PXR_NAMESPACE_OPEN_SCOPE', 'PXR_NAMESPACE_CLOSE_SCOPE'.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--
