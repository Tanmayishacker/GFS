#pragma once
#include <openssl/sha.h>
#include <commanInclude.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>

std::string hashBySHA1(std::string& str)
{
    unsigned char hash[SHA_DIGEST_LENGTH]; // SHA_DIGEST_LENGTH is 20 for SHA-1
    SHA1(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);

    return ss.str();
}

std::string compressDataBoost(const std::string& uncompressedData) {
    std::ostringstream compressedDataStream;
    boost::iostreams::filtering_streambuf<boost::iostreams::output> filter;

    // Add zlib compressor to the filter chain
    filter.push(boost::iostreams::zlib_compressor());
    filter.push(compressedDataStream);

    // Write data through the filter to compress
    std::istringstream dataStream(uncompressedData);
    boost::iostreams::copy(dataStream, filter);

    // Return the compressed data as a string
    return compressedDataStream.str();
}

std::string decompressDataBoost(const std::string& compressedData) {
    
    std::string decompressedData;

    try {
        // Create a filtering streambuf for decompression
        boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
        std::istringstream compressedStream(compressedData);
        std::ostringstream decompressedStream;

        // Add zlib decompressor
        in.push(boost::iostreams::zlib_decompressor());
        in.push(compressedStream);

        // Copy the decompressed data into the output stream
        boost::iostreams::copy(in, decompressedStream);

        // Retrieve decompressed data
        decompressedData = decompressedStream.str();
    }
    catch (const boost::iostreams::zlib_error& e) {
        std::cerr << "Error during decompression: " << e.what() << std::endl;
    }

    return decompressedData;
}