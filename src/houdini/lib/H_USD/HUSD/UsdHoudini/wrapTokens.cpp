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
// GENERATED FILE.  DO NOT EDIT.
#include "./api.h"
#include BOOST_HEADER(python/class.hpp)
#include "./tokens.h"

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

// Helper to return a static token as a string.  We wrap tokens as Python
// strings and for some reason simply wrapping the token using def_readonly
// bypasses to-Python conversion, leading to the error that there's no
// Python type for the C++ TfToken type.  So we wrap this functor instead.
class _WrapStaticToken {
public:
    _WrapStaticToken(const TfToken* token) : _token(token) { }

    std::string operator()() const
    {
        return _token->GetString();
    }

private:
    const TfToken* _token;
};

template <typename T>
void
_AddToken(T& cls, const char* name, const TfToken& token)
{
    cls.add_static_property(name,
                            BOOST_NS::python::make_function(
                                _WrapStaticToken(&token),
                                BOOST_NS::python::return_value_policy<
                                    BOOST_NS::python::return_by_value>(),
                                BOOST_NS::mpl::vector1<std::string>()));
}

} // anonymous

void wrapUsdHoudiniTokens()
{
    BOOST_NS::python::class_<UsdHoudiniTokensType, BOOST_NS::noncopyable>
        cls("Tokens", BOOST_NS::python::no_init);
    _AddToken(cls, "houdiniBackgroundimage", UsdHoudiniTokens->houdiniBackgroundimage);
    _AddToken(cls, "houdiniClippingRange", UsdHoudiniTokens->houdiniClippingRange);
    _AddToken(cls, "houdiniEditable", UsdHoudiniTokens->houdiniEditable);
    _AddToken(cls, "houdiniForegroundimage", UsdHoudiniTokens->houdiniForegroundimage);
    _AddToken(cls, "houdiniGuidescale", UsdHoudiniTokens->houdiniGuidescale);
    _AddToken(cls, "houdiniInviewermenu", UsdHoudiniTokens->houdiniInviewermenu);
    _AddToken(cls, "houdiniProcedural", UsdHoudiniTokens->houdiniProcedural);
    _AddToken(cls, "houdiniProcedural_MultipleApplyTemplate_HoudiniActive", UsdHoudiniTokens->houdiniProcedural_MultipleApplyTemplate_HoudiniActive);
    _AddToken(cls, "houdiniProcedural_MultipleApplyTemplate_HoudiniAnimated", UsdHoudiniTokens->houdiniProcedural_MultipleApplyTemplate_HoudiniAnimated);
    _AddToken(cls, "houdiniProcedural_MultipleApplyTemplate_HoudiniPriority", UsdHoudiniTokens->houdiniProcedural_MultipleApplyTemplate_HoudiniPriority);
    _AddToken(cls, "houdiniProcedural_MultipleApplyTemplate_HoudiniProceduralArgs", UsdHoudiniTokens->houdiniProcedural_MultipleApplyTemplate_HoudiniProceduralArgs);
    _AddToken(cls, "houdiniProcedural_MultipleApplyTemplate_HoudiniProceduralPath", UsdHoudiniTokens->houdiniProcedural_MultipleApplyTemplate_HoudiniProceduralPath);
    _AddToken(cls, "houdiniProcedural_MultipleApplyTemplate_HoudiniProceduralType", UsdHoudiniTokens->houdiniProcedural_MultipleApplyTemplate_HoudiniProceduralType);
    _AddToken(cls, "houdiniSelectable", UsdHoudiniTokens->houdiniSelectable);
    _AddToken(cls, "HoudiniCameraPlateAPI", UsdHoudiniTokens->HoudiniCameraPlateAPI);
    _AddToken(cls, "HoudiniEditableAPI", UsdHoudiniTokens->HoudiniEditableAPI);
    _AddToken(cls, "HoudiniFieldAsset", UsdHoudiniTokens->HoudiniFieldAsset);
    _AddToken(cls, "HoudiniLayerInfo", UsdHoudiniTokens->HoudiniLayerInfo);
    _AddToken(cls, "HoudiniMetaCurves", UsdHoudiniTokens->HoudiniMetaCurves);
    _AddToken(cls, "HoudiniProceduralAPI", UsdHoudiniTokens->HoudiniProceduralAPI);
    _AddToken(cls, "HoudiniSelectableAPI", UsdHoudiniTokens->HoudiniSelectableAPI);
    _AddToken(cls, "HoudiniViewportGuideAPI", UsdHoudiniTokens->HoudiniViewportGuideAPI);
    _AddToken(cls, "HoudiniViewportLightAPI", UsdHoudiniTokens->HoudiniViewportLightAPI);
}
