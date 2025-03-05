#ifndef SFF2_STREAMINTERFACEIMPL_H
#define SFF2_STREAMINTERFACEIMPL_H

#include "SFF2_StreamInterface.h"
#include <fstream>

class SFF2_StreamInterfaceImpl : public SFF2_StreamInterface {
public:
    SFF2_StreamInterfaceImpl() : fileStream(nullptr) {}
    ~SFF2_StreamInterfaceImpl() { Close(); }

    int Open(const char* filename) override {
        fileStream = new std::ifstream(filename, std::ios::binary);
        return fileStream->is_open() ? 0 : -1;
    }

    int ReadU8(SFF8_u& value) override {
        return Read(reinterpret_cast<char*>(&value), sizeof(SFF8_u));
    }

    int ReadU16(SFF16_u& value) override {
        return Read(reinterpret_cast<char*>(&value), sizeof(SFF16_u));
    }

    int ReadU32(SFF32_u& value) override {
        return Read(reinterpret_cast<char*>(&value), sizeof(SFF32_u));
    }

    int ReadS16(SFF16_s& value) override {
        return Read(reinterpret_cast<char*>(&value), sizeof(SFF16_s));
    }

    int Read(char* buffer, size_t size) override {
        if (!fileStream || !fileStream->is_open()) return -1;
        fileStream->read(buffer, size);
        return (size_t) fileStream->gcount() == size ? 0 : -1;
    }

    int Seek(size_t position) override {
        if (!fileStream || !fileStream->is_open()) return -1;
        fileStream->seekg(position);
        return fileStream->good() ? 0 : -1;
    }

    void Close() override {
        if (fileStream) {
            fileStream->close();
            delete fileStream;
            fileStream = nullptr;
        }
    }

    bool is_open() override {
        return fileStream && fileStream->is_open();
    }

private:
    std::ifstream* fileStream;
};

#endif // SFF2_STREAMINTERFACEIMPL_H