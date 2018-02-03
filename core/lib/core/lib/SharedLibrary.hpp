//
// Created by doom on 11/10/17.
//

#ifndef CORE_LIB_SHAREDLIBRARY_HPP
#define CORE_LIB_SHAREDLIBRARY_HPP

#include <core/config/PlatformConfig.hpp>

#ifdef USING_WINDOWS
#include <core/lib/details/WindowsSharedLibrary.hpp>
#else
#include <core/lib/details/PosixSharedLibrary.hpp>
#endif

namespace lib
{
    class SharedLibrary : private details::SharedLibraryImplementation
    {
        using Impl = details::SharedLibraryImplementation;

    public:
        SharedLibrary() noexcept = default;

        SharedLibrary(const fs::path &path, LoadingMode mode = LoadingMode::Default) noexcept
        {
            load(path, mode);
        }

        ~SharedLibrary() noexcept
        {
            unload();
        }

        void unload() noexcept
        {
            Impl::unload();
        }

        void load(const fs::path &path, LoadingMode mode = LoadingMode::Default) noexcept
        {
            Impl::load(path, mode);
        }

        Impl::Handle handle() noexcept
        {
            return Impl::handle();
        }

        bool isLoaded() const noexcept
        {
            return Impl::isLoaded();
        }

        bool operator!() const noexcept
        {
            return !isLoaded();
        }

        operator bool() const noexcept
        {
            return isLoaded();
        }

        bool hasSymbol(const std::string &name) const noexcept
        {
            return Impl::hasSymbol(name);
        }

        void *getSymbol(const std::string &name) const
        {
            void *ret = Impl::getRawSymbol(name);

            if (!ret) {
                throw SymbolNotFound(Impl::getLastError());
            }
            return ret;
        }

        template <typename T, std::enable_if_t<std::is_member_pointer_v<T> || std::is_reference_v<T>, bool> = true>
        T get(const std::string &name) const
        {
            return (T)getSymbol(name);
        }

        template <typename T, std::enable_if_t<!std::is_member_pointer_v<T> && !std::is_reference_v<T>, bool> = true>
        T &get(const std::string &name) const
        {
            return *(T *)getSymbol(name);
        }
    };
}

#endif //CORE_LIB_SHAREDLIBRARY_HPP
