/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <aidl/vendor/lineage/touch/BnTouchscreenGesture.h>

#include <map>

namespace {
struct GestureInfo {
    int32_t keycode;
    const char* name;
    const char* path;
    const char* enable;
    const char* disable;
};

constexpr GestureInfo kGestureNodes[] = {
        {0x2c2,
         "Single Tap",
         "/sys/class/touchscreen/primary/single_tap_enabled",
         "1", "0"},
};
}  // anonymous namespace

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

class TouchscreenGesture : public BnTouchscreenGesture {
  public:
    ndk::ScopedAStatus getSupportedGestures(std::vector<Gesture>* _aidl_return) override;
    ndk::ScopedAStatus setGestureEnabled(const Gesture& gesture, bool enabled) override;

   private:
    std::map<int32_t, GestureInfo> kGestureInfoMap;
};

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
