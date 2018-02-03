//
// Created by doom on 11/10/17.
//

#ifndef CORE_LIB_POSIXSHAREDLIBRARY_HPP
#define CORE_LIB_POSIXSHAREDLIBRARY_HPP

#ifndef CORE_LIB_SHAREDLIBRARY_HPP
# error "do not include this file directly: use #include <lib/SharedLibrary.hpp> instead"
#endif

#include <dlfcn.h>
#include <experimental/filesystem>
#include <core/lib/Exceptions.hpp>
#include <core/lib/details/LoadingMode.hpp>

namespace fs = std::experimental::filesystem;

namespace lib::details
{
    class SharedLibraryImplementation
    {
    protected:
        using Handle = void *;

        SharedLibraryImplementation() = default;

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
        static void __addPrefix(fs::path &path) noexcept
        {
            std::string fileName = path.filename().string();
            if (fileName.compare("lib") != 0) {
                fileName.insert(0, "lib");
                path.replace_filename(fs::path(fileName));
            }
        }

        static void __addExtensionIfNeeded(fs::path &path) noexcept
        {
            if (!path.has_extension()) {
#ifdef USING_OSX
                path += fs::path(".dylib");
#else
                path += fs::path(".so");
#endif
            }
        }

        static LoadingMode __applyDefaultMode(LoadingMode mode) noexcept
        {
            if (!(mode & RTLDNow)) {
                mode = mode | RTLDLazy;
            }
            return mode;
        }

    protected:
        void load(fs::path path, LoadingMode mode) noexcept
        {
            /** Unload the library if previously loaded */
            unload();

            if (!path.has_parent_path()) {
                /** Path is of form 'file', so we transform it into './file' */
                path = fs::path("./") / path;
            }
            if (!(mode & DontAddPrefix)) {
                __addPrefix(path);
            }
            mode &= ~DontAddPrefix;
            __addExtensionIfNeeded(path);
            mode = __applyDefaultMode(mode);
            _handle = dlopen(path.c_str(), mode);
        }

        void unload() noexcept
        {
            if (isLoaded()) {
                dlclose(_handle);
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
            return dlsym(_handle, name.c_str());;
        }

        std::string getLastError() const noexcept
        {
            const char *err = dlerror();
            return std::string(err ? err : "");
        }

    private:
        Handle _handle{nullptr};
    };
}

#endif //CORE_LIB_POSIXSHAREDLIBRARY_HPP
