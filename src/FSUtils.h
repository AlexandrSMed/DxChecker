#pragma once

#include <filesystem>
#include <string>

namespace TDW::FS {

    std::filesystem::path makeNewDocumentName(const std::wstring& name_prefix);

    void writeToFile(const std::wstring& data, const std::filesystem::path& filePath);
}
