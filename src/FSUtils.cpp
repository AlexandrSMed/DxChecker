#include "FSUtils.h"
#include <shlobj_core.h>
#include <comdef.h>

#include <chrono>
#include <sstream>
#include <fstream>
#include <system_error>

std::filesystem::path TDW::FS::makeNewDocumentName(const std::wstring& name_prefix) {
    PWSTR myDocumentsStr;
    auto getMyDocumentsResult = SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, nullptr, &myDocumentsStr);
    if(FAILED(getMyDocumentsResult)) {
        CoTaskMemFree(myDocumentsStr);
        throw std::system_error{
            getMyDocumentsResult, std::iostream_category(),
            _com_error{ getMyDocumentsResult }.ErrorMessage()
        };
    }

    namespace sfs = std::filesystem;
    const sfs::path myDocumentsPath{ myDocumentsStr, sfs::path::native_format };
    CoTaskMemFree(myDocumentsStr);

    namespace ch = std::chrono;
    const ch::milliseconds ms = ch::duration_cast<ch::milliseconds>(
        ch::system_clock::now().time_since_epoch()
    );
    std::wostringstream ws;
    ws << name_prefix << "_";
    ws << std::to_wstring(ms.count());
    ws << ".txt";
    return { myDocumentsPath / ws.str() };
}

void TDW::FS::writeToFile(const std::wstring& data, const std::filesystem::path& filePath) {
    std::wofstream ofs{ filePath };
    ofs << data;
    ofs.close();
}
