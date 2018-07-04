// EVMC: Ethereum Client-VM Connector API.
// Copyright 2018 Pawel Bylica.
// Licensed under the MIT License. See the LICENSE file.

#include <evmc/loader.h>

#include <gtest/gtest.h>

TEST(loader, nonexistent)
{
    evmc_loader_error_code ec;
    auto x = evmc_load("nonexistent", &ec);
    EXPECT_EQ(ec, EVMC_ERRC_CANNOT_OPEN);
    EXPECT_EQ(x, nullptr);

    x = evmc_load("nonexistent", nullptr);
    EXPECT_EQ(x, nullptr);
}

TEST(loader, longpath)
{
    std::vector<char> path(5000, 'a');
    *path.rbegin() = 0;

    evmc_loader_error_code ec;
    auto x = evmc_load(path.data(), &ec);
    EXPECT_EQ(ec, EVMC_ERRC_INVALID_ARGUMENT);
    EXPECT_EQ(x, nullptr);

    x = evmc_load(path.data(), nullptr);
    EXPECT_EQ(x, nullptr);
}

TEST(loader, not_so)
{
    auto path = "unittests/empty.file";

    evmc_loader_error_code ec;
    auto x = evmc_load(path, &ec);
    EXPECT_EQ(ec, EVMC_ERRC_CANNOT_OPEN);
    EXPECT_EQ(x, nullptr);

    x = evmc_load(path, nullptr);
    EXPECT_EQ(x, nullptr);
}

TEST(loader, null_path)
{
    evmc_loader_error_code ec;
    auto x = evmc_load(nullptr, &ec);
    EXPECT_EQ(ec, EVMC_ERRC_INVALID_ARGUMENT);
    EXPECT_EQ(x, nullptr);

    x = evmc_load(nullptr, nullptr);
    EXPECT_EQ(x, nullptr);
}

TEST(loader, empty_path)
{
    evmc_loader_error_code ec;
    auto x = evmc_load("", &ec);
    EXPECT_EQ(ec, EVMC_ERRC_INVALID_ARGUMENT);
    EXPECT_EQ(x, nullptr);

    x = evmc_load("", nullptr);
    EXPECT_EQ(x, nullptr);
}

TEST(loader, aaa)
{
    evmc_loader_error_code ec;
    auto x = (uintptr_t)evmc_load("unittests/libaaa.so", &ec);
    EXPECT_EQ(ec, EVMC_ERRC_SUCCESS);
    EXPECT_EQ(x, 0xaaa);

    x = (uintptr_t)evmc_load("unittests/libaaa.so", nullptr);
    EXPECT_EQ(x, 0xaaa);
}

TEST(loader, eee1)
{
    auto path = "unittests/libeee1.so";

    evmc_loader_error_code ec;
    auto x = evmc_load(path, &ec);
    EXPECT_EQ(ec, EVMC_ERRC_SYMBOL_NOT_FOUND);
    EXPECT_EQ(x, nullptr);

    x = evmc_load(path, nullptr);
    EXPECT_EQ(x, nullptr);
}

TEST(loader, eee2)
{
    auto path = "unittests/eee2.so";

    evmc_loader_error_code ec;
    auto x = evmc_load(path, &ec);
    EXPECT_EQ(ec, EVMC_ERRC_SYMBOL_NOT_FOUND);
    EXPECT_EQ(x, nullptr);

    x = evmc_load(path, nullptr);
    EXPECT_EQ(x, nullptr);
}

TEST(loader, eee3)
{
    auto path = "unittests/libeee3";

    evmc_loader_error_code ec;
    auto x = evmc_load(path, &ec);
    EXPECT_EQ(ec, EVMC_ERRC_SYMBOL_NOT_FOUND);
    EXPECT_EQ(x, nullptr);

    x = evmc_load(path, nullptr);
    EXPECT_EQ(x, nullptr);
}

TEST(loader, eee4)
{
    auto path = "unittests/eee4";

    evmc_loader_error_code ec;
    auto x = evmc_load(path, &ec);
    EXPECT_EQ(ec, EVMC_ERRC_SYMBOL_NOT_FOUND);
    EXPECT_EQ(x, nullptr);

    x = evmc_load(path, nullptr);
    EXPECT_EQ(x, nullptr);
}