//
// Created by doom on 01/02/18
//

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
    logging::Logger _log{"test", logging::Info};
    _log(logging::Info) << "This is an info" << std::endl;
    _log(logging::Warning) << "This is a warning" << std::endl;
    releaseCerr();

    std::string line;
    std::getline(ss, line);
    line = line.substr(line.find_first_of(':') + 2); //Skip to the message
    ASSERT_EQ(line, "This is an info");

    std::getline(ss, line);
    line = line.substr(line.find_first_of(':') + 2);
    ASSERT_EQ(line, "This is a warning");
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
