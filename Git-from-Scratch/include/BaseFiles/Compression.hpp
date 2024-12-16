#pragma once
#include <zlib.h>
#include <vector>
#include <stdexcept>
#include <openssl/sha.h>
#include "commanInclude.hpp"

std::string hashBySHA1(std::string& str)
{
    unsigned char hash[SHA_DIGEST_LENGTH]; // SHA_DIGEST_LENGTH is 20 for SHA-1
    SHA1(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);

    return ss.str();
}

std::string compressDataZlib(const std::string& str) {
    z_stream deflateStream{};
    deflateStream.zalloc = Z_NULL;
    deflateStream.zfree = Z_NULL;
    deflateStream.opaque = Z_NULL;

    deflateStream.avail_in = static_cast<unsigned int>(str.size());
    deflateStream.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(str.data()));

    if (deflateInit(&deflateStream, Z_BEST_COMPRESSION) != Z_OK) {
        throw std::runtime_error("Failed to initialize zlib for compression");
    }

    std::vector<char> outBuffer;
    const size_t bufferSize = 32768;
    std::vector<char> tempBuffer(bufferSize);

    int deflateStatus;
    do {
        deflateStream.avail_out = bufferSize;
        deflateStream.next_out = reinterpret_cast<Bytef*>(tempBuffer.data());

        deflateStatus = deflate(&deflateStream, Z_FINISH);

        if (deflateStatus == Z_STREAM_ERROR) {
            deflateEnd(&deflateStream);
            throw std::runtime_error("Error during compression with deflate()");
        }

        outBuffer.insert(outBuffer.end(), tempBuffer.data(), tempBuffer.data() + bufferSize - deflateStream.avail_out);
    } while (deflateStatus != Z_STREAM_END);

    deflateEnd(&deflateStream);
    return std::string(outBuffer.begin(), outBuffer.end());
}

std::string decompressDataZlib(const std::string& binaryStr) {
    z_stream inflateStream{};
    inflateStream.zalloc = Z_NULL;
    inflateStream.zfree = Z_NULL;
    inflateStream.opaque = Z_NULL;

    inflateStream.avail_in = static_cast<unsigned int>(binaryStr.size());
    inflateStream.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(binaryStr.data()));

    if (inflateInit(&inflateStream) != Z_OK) {
        throw std::runtime_error("Failed to initialize zlib for decompression");
    }

    std::vector<char> outBuffer;
    const size_t bufferSize = 32768;
    std::vector<char> tempBuffer(bufferSize);

    int inflateStatus;
    do {
        inflateStream.avail_out = bufferSize;
        inflateStream.next_out = reinterpret_cast<Bytef*>(tempBuffer.data());

        inflateStatus = inflate(&inflateStream, Z_NO_FLUSH);

        if (inflateStatus == Z_STREAM_ERROR || inflateStatus == Z_DATA_ERROR || inflateStatus == Z_MEM_ERROR) {
            inflateEnd(&inflateStream);
            throw std::runtime_error("Error during decompression");
        }

        outBuffer.insert(outBuffer.end(), tempBuffer.data(), tempBuffer.data() + bufferSize - inflateStream.avail_out);
    } while (inflateStatus != Z_STREAM_END);

    inflateEnd(&inflateStream);
    return std::string(outBuffer.begin(), outBuffer.end());
}