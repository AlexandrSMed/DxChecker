#pragma once

#include "GPUDescriptor.h"
#include <unordered_map>
#include <string>
#include <d3d11.h>
#include <dxgi.h>


namespace TDW::Utils {
    bool operator==(const LUID& lhs, const LUID& rhs);

    struct AdapterDescHash {
        inline size_t operator()(const DXGI_ADAPTER_DESC& ad) const {
            const auto luid = ad.AdapterLuid;
            return std::hash<LONG>()(luid.HighPart | luid.LowPart);
        }
    };

    struct AdapterDescEqualTo {
        inline bool operator()(const DXGI_ADAPTER_DESC& lhs, const DXGI_ADAPTER_DESC& rhs) const {
            const auto lLuid = lhs.AdapterLuid;
            const auto rLuid = rhs.AdapterLuid;
            return lLuid == rLuid;
        }
    };

    using adapter_desc_feature_map = std::unordered_map<DXGI_ADAPTER_DESC, D3D_FEATURE_LEVEL, AdapterDescHash, AdapterDescEqualTo>;

    adapter_desc_feature_map supportedDXVersions();
    std::wstring printSupportedDXVersions(const adapter_desc_feature_map& supportedVersions);
}