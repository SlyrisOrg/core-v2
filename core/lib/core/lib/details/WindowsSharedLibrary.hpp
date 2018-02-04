//
// Created by doom on 11/10/17.
//

#ifndef CORE_LIB_WINDOWSSHAREDLIBRARY_HPP
#define CORE_LIB_WINDOWSSHAREDLIBRARY_HPP

#ifndef CORE_LIB_SHAREDLIBRARY_HPP
# error "do not include this file directly: use #include <lib/SharedLibrary.hpp> instead"
#endif

#include <windows.h>
#include <experimental/filesystem>
#include <core/lib/Exceptions.hpp>
#include <core/lib/details/LoadingMode.hpp>

namespace fs = std::experimental::filesystem;

namespace lib::details
{
    class SharedLibraryImplementation
    {
    protected:
        using Handle = HMODULE;

        SharedLibraryImplementation() noexcept = default;

        ~SharedLibraryImplementation() noexcept
        {
        }

        SharedLibraryImplementation(SharedLibraryImplementation &&other) noexcept : _handle(other._handle)
        {
            other._handle = nullptr;
        }

        SharedLibraryImplementation &operator=(SharedLibraryImplementation &&other) noexcept
        {
            std::swap(_handle, other._handle);
            return *this;
        }

    private:
        static void _addExtensionIfNeeded(fs::path &path) noexcept
        {
            if (!path.has_extension()) {
                path += fs::path(".dll");
            }
        }

    protected:
        void load(fs::path path, LoadingMode mode) noexcept
        {
            /** Unload the library if previously loaded */
            unload();

            _addExtensionIfNeeded(path);
            _handle = LoadLibrary(path.string().c_str());
        }

        void unload() noexcept
        {
            if (isLoaded()) {
                FreeLibrary(_handle);
                _handle = nullptr;
            }
        }

        bool isLoaded() const noexcept
        {
            return _handle != nullptr;
        }

        Handle handle() noexcept
        {
            return _handle;
        }

        bool hasSymbol(const std::string &name) const
        {
            return getRawSymbol(name) != nullptr;
        }

        void *getRawSymbol(const std::string &name) const
        {
            if (!isLoaded()) {
                throw LibraryNotLoaded();
            }
            return reinterpret_cast<void *>(GetProcAddress(_handle, name.c_str()));
        }

        std::string getLastError() const noexcept
        {
            return "error code " + std::to_string(GetLastError());
        }

    private:
        Handle _handle{nullptr};
    };
}

#endif //CORE_LIB_WINDOWSSHAREDLIBRARY_HPP
