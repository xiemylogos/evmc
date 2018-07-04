/* EVMC: Ethereum Client-VM Connector API.
 * Copyright 2018 Pawel Bylica.
 * Licensed under the MIT License. See the LICENSE file.
 */

#include <evmc/loader.h>

#include <dlfcn.h>
#include <stdint.h>
#include <string.h>

#include <stdio.h>

#define PATH_MAX_LENGHT 4095

#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

typedef struct evmc_instance* (*evmc_create_fn)();

struct evmc_instance* evmc_load(const char* filename, enum evmc_loader_error_code* error_code)
{
    enum evmc_loader_error_code ec = EVMC_ERRC_SUCCESS;
    struct evmc_instance* instance = NULL;

    if (!filename)
    {
        ec = EVMC_ERRC_INVALID_ARGUMENT;
        goto exit;
    }

    const size_t length = strlen(filename);
    if (length == 0 || length > PATH_MAX_LENGHT)
    {
        ec = EVMC_ERRC_INVALID_ARGUMENT;
        goto exit;
    }

    void* handle = dlopen(filename, RTLD_LAZY);
    if (!handle)
    {
        ec = EVMC_ERRC_CANNOT_OPEN;
        goto exit;
    }

    const char prefix[] = "evmc_create_";
    const size_t prefix_length = strlen(prefix);
    char name[sizeof(prefix) + PATH_MAX_LENGHT];
    strcpy(name, prefix);

    printf("1: %s\n", name);

    const char* name_pos = strrchr(filename, '/');
    // FIXME: Add test without /.
    name_pos += 1;

    printf("2: %s\n", name_pos);

    const char lib_prefix[] = "lib";
    const size_t lib_prefix_length = strlen(lib_prefix);
    if (strncmp(name_pos, lib_prefix, lib_prefix_length) == 0)
        name_pos += lib_prefix_length;

    printf("3: %s\n", name_pos);

    strncpy(name + prefix_length, name_pos, PATH_MAX_LENGHT);

    char* ext_pos = strrchr(name, '.');
    if (ext_pos)
        *ext_pos = 0;

    printf("4: %s\n", name);

    const void* symbol = dlsym(handle, name);
    if (!symbol)
    {
        dlclose(handle);
        ec = EVMC_ERRC_SYMBOL_NOT_FOUND;
        goto exit;
    }

    evmc_create_fn create_fn = (evmc_create_fn)(uintptr_t)symbol;
    instance = create_fn();

exit:
    if (error_code)
        *error_code = ec;
    return instance;
}
