/*
 * Copyright © 2014 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <xf86drm.h>

#include "i915_drm.h"
#include "i915_pciids.h"
#include "intel_device.h"

#ifdef HAVE_VALGRIND
#include <valgrind.h>
#include <memcheck.h>
#define VG(x) x
#else
#define VG(x)
#endif

#define VG_CLEAR(s) VG(memset(&s, 0, sizeof(s)))

#define DBG(...) do {					\
	if (bufmgr_gem->bufmgr.debug)			\
		fprintf(stderr, __VA_ARGS__);		\
} while (0)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

/*
 * The first few fields here have to match the layout of the publicly defined
 * struct drm_intel_device
 */
struct drm_intel_device_info {
	uint16_t gen, chip;
};

struct _drm_intel_device {
	struct drm_intel_device_info info;
	int fd;
};

static const struct drm_intel_device_info intel_i830_info = {
	.chip = DRM_INTEL_CHIP_I830,
	.gen = 2,
};
static const struct drm_intel_device_info intel_i845_info = {
	.chip = DRM_INTEL_CHIP_I845,
	.gen = 2,
};
static const struct drm_intel_device_info intel_i85x_info = {
	.chip = DRM_INTEL_CHIP_I85X,
	.gen = 2,
};
static const struct drm_intel_device_info intel_i865_info = {
	.chip = DRM_INTEL_CHIP_I865,
	.gen = 2,
};

static const struct drm_intel_device_info intel_i915_info = {
	.chip = DRM_INTEL_CHIP_I915,
	.gen = 3,
};
static const struct drm_intel_device_info intel_i945_info = {
	.chip = DRM_INTEL_CHIP_I945,
	.gen = 3,
};

static const struct drm_intel_device_info intel_g33_info = {
	.chip = DRM_INTEL_CHIP_G33,
	.gen = 3,
};
static const struct drm_intel_device_info intel_pineview_info = {
	.chip = DRM_INTEL_CHIP_PINEVIEW,
	.gen = 3,
};

static const struct drm_intel_device_info intel_i965_info = {
	.chip = DRM_INTEL_CHIP_I965,
	.gen = 4,
};

static const struct drm_intel_device_info intel_g4x_info = {
	.chip = DRM_INTEL_CHIP_IG4X,
	.gen = 4,
};

static const struct drm_intel_device_info intel_ironlake_info = {
	.chip = DRM_INTEL_CHIP_IRONLAKE,
	.gen = 5,
};

static const struct drm_intel_device_info intel_sandybridge_info = {
	.chip = DRM_INTEL_CHIP_SANDYBRIDGE,
	.gen = 6,
};

static const struct drm_intel_device_info intel_ivybridge_info = {
	.chip = DRM_INTEL_CHIP_IVYBRIDGE,
	.gen = 7,
};
static const struct drm_intel_device_info intel_valleyview_info = {
	.chip = DRM_INTEL_CHIP_VALLEYVIEW,
	.gen = 7,
};

static const struct drm_intel_device_info intel_haswell_info = {
	.chip = DRM_INTEL_CHIP_HASWELL,
	.gen = 7,
};

static const struct drm_intel_device_info intel_broadwell_info = {
	.chip = DRM_INTEL_CHIP_BROADWELL,
	.gen = 8,
};

static const struct drm_intel_device_info intel_cherryview_info = {
	.chip = DRM_INTEL_CHIP_CHERRYVIEW,
	.gen = 8,
};

/*
 * let's not introduce a dependency on libpciaccess just for the struct
 * pci_id_match definition...
 */
struct device_info_match {
	uint32_t vendor, device;
	uint32_t subvendor, subdevice;
	uint32_t class, class_mask;
	unsigned long info;
};

static const struct device_info_match intel_devices[] = {
	INTEL_I830_IDS(&intel_i830_info),
	INTEL_I845G_IDS(&intel_i830_info),
	INTEL_I85X_IDS(&intel_i85x_info),
	INTEL_I865G_IDS(&intel_i865_info),

	INTEL_I915G_IDS(&intel_i915_info),
	INTEL_I915GM_IDS(&intel_i915_info),
	INTEL_I945G_IDS(&intel_i945_info),
	INTEL_I945GM_IDS(&intel_i945_info),

	INTEL_G33_IDS(&intel_g33_info),
	INTEL_PINEVIEW_IDS(&intel_pineview_info),

	INTEL_I965G_IDS(&intel_i965_info),
	INTEL_I965GM_IDS(&intel_i965_info),

	INTEL_G45_IDS(&intel_g4x_info),
	INTEL_GM45_IDS(&intel_g4x_info),

	INTEL_IRONLAKE_D_IDS(&intel_ironlake_info),
	INTEL_IRONLAKE_M_IDS(&intel_ironlake_info),

	INTEL_SNB_D_IDS(&intel_sandybridge_info),
	INTEL_SNB_M_IDS(&intel_sandybridge_info),

	INTEL_IVB_D_IDS(&intel_ivybridge_info),
	INTEL_IVB_M_IDS(&intel_ivybridge_info),

	INTEL_HSW_D_IDS(&intel_haswell_info),
	INTEL_HSW_M_IDS(&intel_haswell_info),

	INTEL_VLV_D_IDS(&intel_valleyview_info),
	INTEL_VLV_M_IDS(&intel_valleyview_info),

	INTEL_BDW_D_IDS(&intel_broadwell_info),
	INTEL_BDW_M_IDS(&intel_broadwell_info),

	INTEL_CHV_IDS(&intel_cherryview_info),
};

/**
 * Get the PCI ID for the device.  This can be overridden by setting the
 * INTEL_DEVID_OVERRIDE environment variable to the desired ID.
 */
static int
drm_intel_device_get_pci_id(struct _drm_intel_device *device)
{
	int devid;
	struct drm_i915_getparam gp;
	int ret;

	if (geteuid() == getuid()) {
		char *devid_override;

		devid_override = getenv("INTEL_DEVID_OVERRIDE");
		if (devid_override) {
			device->fd = -1;
			return strtod(devid_override, NULL);
		}
	}

	VG_CLEAR(devid);
	VG_CLEAR(gp);
	gp.param = I915_PARAM_CHIPSET_ID;
	gp.value = &devid;
	ret = drmIoctl(device->fd, DRM_IOCTL_I915_GETPARAM, &gp);
	if (ret)
		return 0;

	return devid;
}

struct drm_intel_device *drm_intel_device_init(int fd)
{
	struct _drm_intel_device *device;
	unsigned int i, devid;

	device = calloc(1, sizeof(*device));
	if (device == NULL)
		return NULL;

	devid = drm_intel_device_get_pci_id(device);

	for (i = 0; i < ARRAY_SIZE(intel_devices); i++) {
		const struct device_info_match *entry = &intel_devices[i];

		if (devid != entry->device)
			continue;

		device->info = *(struct drm_intel_device_info *)entry->info;
		return (struct drm_intel_device *)device;
	}

	free(device);
	return NULL;
}
