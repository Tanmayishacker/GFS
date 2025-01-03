#pragma once
#include <openssl/sha.h>
#include <stdexcept>
#include <vector>
#include "commanInclude.hpp"
#include <zlib.h>

std::string hashBySHA1(const std::string& input) {
    // Create a buffer to hold the hash
    unsigned char hash[SHA_DIGEST_LENGTH];

    // Perform the SHA1 hash
    SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), hash);

    // Convert the hash to a hexadecimal string
    std::stringstream hexStream;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << (int)hash[i];
    }

    // Return the hash as a string
    return hexStream.str();
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