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
                "debug",
                "info",
                "warning",
                "error",
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

#ifdef LOGGER_THREAD_SAFE
        std::mutex &mutex() noexcept
        {
            return _mutex;
        }
#endif

    private:
        std::unordered_map<std::string, Level> _levels;

#ifdef LOGGER_THREAD_SAFE
        std::mutex _mutex;
#endif
    };

    template <typename Logger>
    class LoggerBase
    {
    public:
        class Handle
        {
        private:
            auto _getTime() const noexcept
            {
                auto n = std::chrono::system_clock::now().time_since_epoch();
                return std::chrono::duration_cast<std::chrono::milliseconds>(n).count();
            }

            std::string_view _getLevel(Level lvl) const noexcept
            {
                static const std::string_view tab[] = {
                    "debug",
                    "info",
                    "warning",
                    "error",
                };
                return tab[lvl];
            }

            utils::Color _getLevelColor(Level lvl) const noexcept
            {
                static const utils::Color tab[] = {
                    utils::White,
                    utils::White,
                    utils::Yellow,
                    utils::LightRed,
                };
                return tab[lvl];
            }

        public:
            explicit Handle(const Logger &logger, Level lvl) noexcept :
                _logger(logger), _shouldLog(lvl >= _logger.level())
            {
#ifndef LOGGER_DISABLE_ALL
                if (_shouldLog) {
                    _oss << _getTime() << " ";
                    _oss << utils::Color::Cyan << "[" << _logger.name() << "] ";
                    _oss << _getLevelColor(lvl) << _getLevel(lvl) << utils::ResetColor::Reset << ": ";
                }
#endif
            }

            ~Handle() noexcept
            {
                _logger.log(_oss.str());
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
            const Logger &_logger;
            bool _shouldLog;
            std::ostringstream _oss;
        };
    };

    class Logger : public LoggerBase<Logger>
    {
    public:
        explicit Logger(const std::string &name, Level defaultLvl = Warning) noexcept :
            _name(name), _lvl(LoggerConfManager::get().getLevel(name))
        {
            if (_lvl == Unknown)
                _lvl = defaultLvl;
        }

    public:
        void log(const std::string &str) const noexcept
        {
#ifdef LOGGER_THREAD_SAFE
            std::scoped_lock<std::mutex> lock{LoggerConfManager::get().mutex()};
#endif
            std::cerr << str;
        }

        void setLevel(Level lvl) noexcept
        {
            _lvl = lvl;
        }

        Level level() const noexcept
        {
            return _lvl;
        }

        const std::string &name() const noexcept
        {
            return _name;
        }

        Handle operator()(Level lvl) const noexcept
        {
            return Handle(*this, lvl);
        }

    protected:
        std::string _name;
        Level _lvl;
    };
};

#endif //CORE_LOG_LOGGER_HPP
