#include "SFF2File.h"
#include "SFF2_StreamInterfaceImpl.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "SFF8_u:" << sizeof(SFF8_u) * 8 << std::endl;
    std::cout << "SFF16_u:" << sizeof(SFF16_u) * 8 << std::endl;
    std::cout << "SFF32_u:" << sizeof(SFF32_u) * 8 << std::endl;
    std::cout << "SFF16_s:" << sizeof(SFF16_s) * 8 << std::endl << std::endl;

    SFF2_StreamInterface* streamInterface = new SFF2_StreamInterfaceImpl();
    if (argc > 1) {
        if (streamInterface->Open(argv[1]) != 0) {
            std::cerr << "Failed to open file." << std::endl;
            delete streamInterface;
            return -1;
        }
    } else
        if (streamInterface->Open("test.sff") != 0) {
            std::cerr << "Failed to open file." << std::endl;
            delete streamInterface;
            return -1;
        }

    SFF2File sff2File(streamInterface);
    SFF2_Header* header = sff2File.GetHeader();
    if (header) {
        std::cout << "Header loaded successfully." << std::endl;
        std::cout << "Signature: " << header->getSignature() << std::endl;
        std::cout << "Version: " << header->getVersion() << std::endl;
        std::cout << "CompatVersion: " << header->getCompatVersion() << std::endl;
        std::cout << "Num_Sprite: " << header->getNumSpr() << std::endl;
        std::cout << "Num_Pal: " << header->getNumPal() << std::endl;
        std::cout << "LDataOfs: " << header->getLDataOfs() << std::endl;
        std::cout << "LDataLen: " << header->getLDataLen() << std::endl;
        std::cout << "TDataOfs: " << header->getTDataOfs() << std::endl;
        std::cout << "TDataLen: " << header->getTDataLen() << std::endl;
    } else {
        std::cout << "Failed to load header." << std::endl;
    }

    sff2File.GetSpriteIndex(1, 0);

    streamInterface->Close();
    delete streamInterface;
    return 0;
}