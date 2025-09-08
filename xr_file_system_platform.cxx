#include "xr_file_system_platform.h"
#include <filesystem>

using namespace xray_re;
namespace fs = std::filesystem;

#ifdef _WIN32

xr_mmap_reader::xr_mmap_reader(HANDLE h, HANDLE h_mmap, const void *data, size_t size) : m_h(h), m_h_mmap(h_mmap)
{
    m_next = m_p = m_data = static_cast<const uint8_t *>(data);
    m_end = m_data + size;
}

xr_mmap_reader::~xr_mmap_reader()
{
    UnmapViewOfFile(const_cast<uint8_t *>(m_data));
    CloseHandle(m_h_mmap);
    CloseHandle(m_h);
}

#else

xr_mmap_reader::xr_mmap_reader(int fd, const void *data, size_t size) : m_fd(fd)
{
    m_next = m_p = m_data = static_cast<const uint8_t *>(data);
    m_end = m_data + size;
}

xr_mmap_reader::~xr_mmap_reader()
{
    if (m_data)
    {
        munmap(const_cast<void *>(static_cast<const void *>(m_data)), size());
        m_data = nullptr;
    }
    if (m_fd != -1)
    {
        close(m_fd);
        m_fd = -1;
    }
}

#endif

xr_file_writer::xr_file_writer(const std::string &path) : m_path(path)
{
    m_file.open(path, std::ios::binary | std::ios::out);
}

xr_file_writer::~xr_file_writer()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

void xr_file_writer::w_raw(const void *src, size_t src_size)
{
    if (m_file.is_open())
    {
        m_file.write(static_cast<const char *>(src), src_size);
    }
}

void xr_file_writer::seek(size_t pos)
{
    if (m_file.is_open())
    {
        m_file.seekp(static_cast<std::streamoff>(pos));
    }
}

size_t xr_file_writer::tell()
{
    return m_file.is_open() ? static_cast<size_t>(m_file.tellp()) : 0;
}

bool xr_file_writer::is_open() const
{
    return m_file.is_open();
}