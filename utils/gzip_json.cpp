#include "gzip_json.hpp"

json readGzippedJson(const std::vector<unsigned char>& data) {
    constexpr size_t CHUNK = 16384;

    z_stream strm{};
    strm.next_in  = const_cast<Bytef*>(data.data());
    strm.avail_in = static_cast<uInt>(data.size());

    if (inflateInit2(&strm, 15 + 32) != Z_OK) {
        throw std::runtime_error("inflateInit2 failed");
    }

    unsigned char out[CHUNK];
    std::ostringstream decompressed;
    int ret;

    do {
        strm.avail_out = CHUNK;
        strm.next_out  = out;

        ret = inflate(&strm, Z_NO_FLUSH);

        if (ret == Z_STREAM_ERROR ||
            ret == Z_DATA_ERROR ||
            ret == Z_MEM_ERROR) {
            inflateEnd(&strm);
            throw std::runtime_error("gzip decompression failed");
        }

        decompressed.write(
            reinterpret_cast<char*>(out),
            CHUNK - strm.avail_out
        );

    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);

    return json::parse(decompressed.str());
}
