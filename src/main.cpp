#include "DXUtils.h"
#include "FSUtils.h"
#include <iostream>
#include <exception>

bool shouldWriteToFile() {
    std::cout << "Do you want to save the report into a file? (y/n): ";
    constexpr auto retryMessage = "Plese type 'y' or 'n': ";
    while(true) {
        std::string answer;
        std::cin >> answer;
        if(answer.size() != 1) {
            std::cout << retryMessage;
            continue;
        }
        switch(answer[0]) {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                std::cout << retryMessage;
                continue;
        }
    }
}

int main() {
    try {
        using namespace TDW;

        auto result = Utils::supportedDXVersions();
        if(result.empty()) {
            throw std::runtime_error{ "Adapter list is empty!" };
        }
        auto reportData = Utils::printSupportedDXVersions(result);
        if(shouldWriteToFile()) {
            const auto documentName = FS::makeNewDocumentName(L"DxCheck_Report");
            FS::writeToFile(reportData, documentName);
            std::wcout << "The report is written to " << documentName.native() << std::endl;
        }
    } catch(const std::exception& exception) {
        std::wcerr << exception.what();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
