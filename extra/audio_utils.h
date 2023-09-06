#include <cstdio>
#include <cstdlib>

class PCMReader {
public:
    explicit PCMReader(const char *filepath) {
        _file = fopen(filepath, "rb");
        if (nullptr == _file) {
            printf("==> open file %s error.\n", filepath);
            abort();
        }
    }

    long sample_size_in_16bit() {
        if (_file == nullptr)
            return 0;
        fseek(_file, 0, SEEK_END);
        long len = ftell(_file);
        len /= sizeof(short);
        rewind(_file);
        return len;
    }

    size_t read_bytes(void *to, size_t size) {
        if (nullptr == _file) {
            printf("==> file empty!");
            abort();
        }
        size_t readsize = fread(to, sizeof(char), size, _file);
        if (readsize != size) {
            printf("read size err!\n");
            abort();
        }
        return readsize;
    }

    ~PCMReader() {
        if (nullptr != _file) {
            fclose(_file);
            _file = nullptr;
        }
    }

private:
    FILE *_file = nullptr;

};

class PCMWriter {
public:
    explicit PCMWriter(const char *filepath) {
        _file = fopen(filepath, "wb");
        if (nullptr == _file) {
            printf("==> open file %s error.\n", filepath);
            abort();
        }

    }

    void write_bytes(void *src, size_t size) {
        if (nullptr == _file) {
            printf("==> file empty!");
            abort();
        }
        fwrite(src, sizeof(char), size, _file);
    }

    ~PCMWriter() {
        if (nullptr != _file) {
            fclose(_file);
            _file = nullptr;
        }
    }

private:
    FILE *_file = nullptr;

};
