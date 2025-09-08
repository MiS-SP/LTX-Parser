#ifndef __GNUC__
#pragma once
#endif
#ifndef __XR_FILE_SYSTEM_PLATFORM_H__
#define __XR_FILE_SYSTEM_PLATFORM_H__

#include "xr_file_system.h"
#include "xr_reader.h"
#include <fstream>
#include <memory>
#include <string>

namespace xray_re
{

#ifdef _WIN32
#include <windows.h>
    class xr_mmap_reader : public xr_reader
    {
    public:
        xr_mmap_reader(HANDLE h, HANDLE h_mmap, const void *data, size_t size);
        virtual ~xr_mmap_reader();

    private:
        HANDLE m_h;
        HANDLE m_h_mmap;
    };
#else
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
    class xr_mmap_reader : public xr_reader
    {
    public:
        xr_mmap_reader(int fd, const void *data, size_t size);
        virtual ~xr_mmap_reader();

    private:
        int m_fd;
    };
#endif

    class xr_file_writer : public xr_writer
    {
    public:
        xr_file_writer(const std::string &path);
        virtual ~xr_file_writer();

        virtual void w_raw(const void *src, size_t src_size) override;
        virtual void seek(size_t pos) override;
        virtual size_t tell() override;
        virtual bool is_open() const;

    private:
        std::ofstream m_file;
        std::string m_path;
    };

} // end of namespace xray_re

#endif