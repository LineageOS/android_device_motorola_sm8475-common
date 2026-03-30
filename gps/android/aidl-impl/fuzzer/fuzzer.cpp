/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */
#include <aidl/android/hardware/gnss/IGnss.h>
#include "Gnss.h"

#include <fuzzbinder/libbinder_ndk_driver.h>
#include <fuzzer/FuzzedDataProvider.h>

using ::android::hardware::gnss::aidl::implementation::Gnss;

std::shared_ptr<Gnss> service;

extern "C" int LLVMFuzzerInitialize(int* argc, char*** argv) {
    service = ndk::SharedRefBase::make<Gnss>();
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if ( service == nullptr || service->asBinder() == nullptr ) {
        return 0;
    }

    FuzzedDataProvider provider(data, size);
    android::fuzzService(service->asBinder().get(), std::move(provider));

    return 0;
}
