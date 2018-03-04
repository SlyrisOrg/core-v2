//
// Created by doom on 12/09/17.
//

#ifndef CORE_LOG_LOGGER_HPP
#define CORE_LOG_LOGGER_HPP

#include <string>
#include <string_view>
#ifdef LOGGER_THREAD_SAFE
#include <mutex>
#endif
#include <unordered_map>
#include <chrono>
#include <core/utils/Utils.hpp>

/**
 * This logger utility can be configured at runtime through the environment
 * using the LOGGER_CONFIG variable like below.
 *
 * LOGGER_CONFIG="<logger_name>[:<level>],<logger_name>[:<level>]"
 *
 * Example:
 * LOGGER_CONFIG="awesomelogger,otherlogger:debug"
 */

namespace logging
{
    enum Level
    {
        Unknown = -1,
        Debug,
        Info,
        Warning,
        Error,
        Silent,
    };

    namespace details
    {
        static inline auto getTime() noexcept
        {
            auto n = std::chrono::system_clock::now().time_since_epoch();
            return std::chrono::duration_cast<std::chrono::milliseconds>(n).count();
        }

        static inline std::string_view getLevelString(Level lvl) noexcept
        {
            static const std::string_view tab[] = {
                "debug",
                "info",
                "warning",
                "error",
            };
            return tab[lvl];
        }

        static inline utils::Color getLevelColor(Level lvl) noexcept
        {
            static const utils::Color tab[] = {
                utils::White,
                utils::White,
                utils::Yellow,
                utils::LightRed,
            };
            return tab[lvl];
        }
    }

    class LoggerConfManager : public utils::Singleton<LoggerConfManager>
    {
    public:
        LoggerConfManager() noexcept
        {
            const char *var = std::getenv("LOGGER_CONFIG");

            if (var)
                _parseConfig(var);
        }

        ~LoggerConfManager() noexcept = default;

    private:
        static Level _stringToLevel(std::string_view v) noexcept
        {
            static const std::array<std::string_view, 4> arr = {
                {
                    "debug",
                    "info",
                    "warning",
                    "error",
                }
            };

            for (size_t i = 0; i < arr.size(); ++i) {
                if (arr[i] == v)
                    return static_cast<Level>(i);
            }
            return Unknown;
        }

        void _parseConfig(const std::string &var) noexcept
        {
            size_t start = 0;
            size_t end = var.find(',');

            while (start < end) {
                std::string_view view(var.c_str() + start,
                                      end == std::string::npos ? var.length() - start : end - start);

                size_t pos = view.find(':');
                if (pos != std::string_view::npos) {
                    _levels.emplace(std::make_pair(std::string(view.substr(0, pos)),
                                                   _stringToLevel(view.substr(pos + 1, view.length() - pos - 1))));
                }
                start = end == std::string::npos ? end : end + 1;
                end = var.find(',', start);
            }
        }

    public:
        Level getLevel(const std::string &name) const noexcept
        {
            auto it = _levels.find(name);

            if (it != _levels.end()) {
                return it->second;
            }
            return Level::Unknown;
        }

    private:
        std::unordered_map<std::string, Level> _levels;
    };

    template <typename Logger>
    class LoggerBase
    {
    public:
        class Handle
        {
        public:
            explicit Handle(Logger &logger, Level lvl) noexcept : _logger(logger), _shouldLog(lvl >= _logger.level())
            {
            }

            Handle(const Handle &other) noexcept : _logger(other._logger), _shouldLog(other._shouldLog)
            {
            }

            ~Handle() noexcept
            {
#ifndef LOGGER_DISABLE_ALL
                _logger.log(_oss.str());
#endif
            }

            template <typename T>
            Handle &operator<<(T &&t) noexcept
            {
#ifndef LOGGER_DISABLE_ALL
                if (_shouldLog) {
                    _oss << std::forward<T>(t);
                }
#endif
                return *this;
            }

            using CerrT = decltype(std::cerr);
            using EndlT = CerrT &(*)(CerrT &);

            Handle &operator<<(EndlT manip) noexcept
            {
#ifndef LOGGER_DISABLE_ALL
                if (_shouldLog) {
                    manip(_oss);
                }
#endif
                return *this;
            }

        private:
            Logger &_logger;
            bool _shouldLog;
            std::ostringstream _oss;
        };

        explicit LoggerBase(Level lvl) : _lvl(lvl)
        {
        }

        void setLevel(Level lvl) noexcept
        {
            _lvl = lvl;
        }

        Level level() const noexcept
        {
            return _lvl;
        }

    protected:
        Level _lvl;
    };

    class Logger : public LoggerBase<Logger>
    {
    public:
        explicit Logger(const std::string &name, Level defaultLvl = Warning) noexcept :
            LoggerBase(LoggerConfManager::get().getLevel(name)), _name(name)
        {
            if (_lvl == Unknown)
                _lvl = defaultLvl;
        }

    public:
        void log(const std::string &str) const noexcept
        {
#ifdef LOGGER_THREAD_SAFE
            std::scoped_lock<std::mutex> lock{Logger::_mutex()};
#endif
            std::cerr << str;
        }

        const std::string &name() const noexcept
        {
            return _name;
        }

        Handle operator()(Level lvl) noexcept
        {
            Handle ret(*this, lvl);

#ifndef LOGGER_DISABLE_ALL
            if (lvl >= _lvl) {
                ret << details::getTime() << " ";
                ret << utils::Color::Cyan << "[" << _name << "] ";
                ret << details::getLevelColor(lvl) << details::getLevelString(lvl) << utils::ResetColor::Reset << ": ";
            }
#endif
            return ret;
        }

    protected:
        const std::string _name;

#ifdef LOGGER_THREAD_SAFE
        //MSVC lacks support for inline variables
        static std::mutex &_mutex() noexcept
        {
            static std::mutex mutex;
            return mutex;
        }
#endif
    };
};

#endif //CORE_LOG_LOGGER_HPP
