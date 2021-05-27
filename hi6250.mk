#
# Copyright (C) 2021 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

## Common Path
COMMON_PATH := device/huawei/hi6250-common

# Graphics
PRODUCT_PACKAGES += \
￼    libion

# Init
PRODUCT_PACKAGES += \
    fstab.hi6250 \
    init.audio.rc \
    init.balong_modem.rc \
    init.connectivity.bcm43455.rc \
    init.connectivity.gps.rc \
    init.connectivity.hi1102.rc \
    init.connectivity.rc \
    init.device.rc \
    init.extmodem.rc \
    init.hi6250.rc \
    init.hisi.rc \
    init.ko.rc \
    init.manufacture.rc \
    init.performance.rc \
    init.platform.rc \
    init.post-fs-data.rc \
    init.protocol.rc \
    init.recovery.hi6250.rc \
    init.tee.rc \
    ueventd.hi6250.rc

# Media
PRODUCT_COPY_FILES += \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_telephony.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_telephony.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_video.xml
