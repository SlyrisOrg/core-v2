//
// Created by doom on 01/02/18
//

#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <core/log/Logger.hpp>

static std::streambuf *cerrBufBackup;

static void captureCerr(std::ostream &replacement) noexcept
{
    cerrBufBackup = std::cerr.rdbuf();
    std::cerr.rdbuf(replacement.rdbuf());
}

static void releaseCerr() noexcept
{
    std::cerr.rdbuf(cerrBufBackup);
}

TEST(Logging, Basic)
{
    std::stringstream ss;

    captureCerr(ss);
    const logging::Logger _log{"test", logging::Info};
    _log(logging::Info) << "This is an info" << std::endl;
    _log(logging::Warning) << "This is a warning" << std::endl;
    _log(logging::Info) << std::boolalpha << true << std::endl;
    releaseCerr();

    std::string line;
    std::getline(ss, line);
    line = line.substr(line.find_first_of(':') + 2); //Skip to the message
    ASSERT_EQ(line, "This is an info");

    std::getline(ss, line);
    line = line.substr(line.find_first_of(':') + 2);
    ASSERT_EQ(line, "This is a warning");

    std::getline(ss, line);
    line = line.substr(line.find_first_of(':') + 2);
    ASSERT_EQ(line, "true");
}

TEST(Logging, Level)
{
    std::stringstream ss;

    captureCerr(ss);
    logging::Logger _log{"test", logging::Info};
    _log(logging::Debug) << "This won't get printed" << std::endl;
    _log(logging::Info) << "But this will" << std::endl;
    _log.setLevel(logging::Debug);
    _log(logging::Info) << "And this too" << std::endl;
    releaseCerr();

    std::string line;
    std::getline(ss, line);
    line = line.substr(line.find_first_of(':') + 2);
    ASSERT_EQ(line, "But this will");

    std::getline(ss, line);
    line = line.substr(line.find_first_of(':') + 2);
    ASSERT_EQ(line, "And this too");
}

namespace
{
    class FileLogger : public logging::LoggerBase<FileLogger>
    {
    public:
        explicit FileLogger(const std::string &name, const std::string &fileName,
                            logging::Level defaultLvl = logging::Debug) noexcept :
            LoggerBase(defaultLvl), _name(name), _ofs(fileName)
        {
        }

        void flush() noexcept
        {
            _ofs << std::flush;
        }

        void log(const std::string &str) noexcept
        {
            _ofs << str;
        }

        const std::string &name() const noexcept
        {
            return _name;
        }

        Handle operator()(logging::Level lvl) noexcept
        {
            Handle ret(*this, lvl);

            if (lvl >= _lvl) {
                ret << logging::details::getTime() << " ";
                ret << utils::Color::Cyan << "[" << _name << "] ";
                ret << logging::details::getLevelColor(lvl)
                    << logging::details::getLevelString(lvl)
                    << utils::ResetColor::Reset << ": ";
            }
            return ret;
        }

    protected:
        const std::string _name;
        std::ofstream _ofs;
    };
}

TEST(Logging, FileLogger)
{
    FileLogger filo("file", "file_logger-testfile.txt");

    filo(logging::Debug) << "Test test" << std::endl;

    filo.flush();

    std::ifstream ifs("file_logger-testfile.txt");

    std::string line;
    std::getline(ifs, line);
    line = line.substr(line.find_first_of(':') + 2);
    ASSERT_EQ(line, "Test test");
    std::remove("file_logger-testfile.txt");
}
