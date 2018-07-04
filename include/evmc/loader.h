/* EVMC: Ethereum Client-VM Connector API.
 * Copyright 2018 Pawel Bylica.
 * Licensed under the MIT License. See the LICENSE file.
 */

#pragma once

#if __cplusplus
extern "C" {
#endif

enum evmc_loader_error_code
{
    EVMC_ERRC_SUCCESS = 0,
    EVMC_ERRC_CANNOT_OPEN,
    EVMC_ERRC_SYMBOL_NOT_FOUND,
    EVMC_ERRC_INVALID_ARGUMENT,
};

struct evmc_instance* evmc_load(const char* filename, enum evmc_loader_error_code* error_code);

#if __cplusplus
}
#endif
