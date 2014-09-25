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

#ifndef __INTEL_DEVICE_H__
#define __INTEL_DEVICE_H__

#include <stdint.h>
#include <stdbool.h>

/* This is not an exhaustive list, but enough for our purposes */
enum drm_intel_chip {

	/* gen 2 */
	DRM_INTEL_CHIP_I830,
	DRM_INTEL_CHIP_I845,
	DRM_INTEL_CHIP_I85X,
	DRM_INTEL_CHIP_I865,

	/* gen 3 */
	DRM_INTEL_CHIP_I915,
	DRM_INTEL_CHIP_I945,
	DRM_INTEL_CHIP_G33,
	DRM_INTEL_CHIP_PINEVIEW,

	/* gen 4 */
	DRM_INTEL_CHIP_I965,
	DRM_INTEL_CHIP_IG4X,

	/* gen 5 */
	DRM_INTEL_CHIP_IRONLAKE,

	/* gen 6 */
	DRM_INTEL_CHIP_SANDYBRIDGE,

	/* gen 7 */
	DRM_INTEL_CHIP_IVYBRIDGE,
	DRM_INTEL_CHIP_HASWELL,
	DRM_INTEL_CHIP_VALLEYVIEW,

	/* gen 8 */
	DRM_INTEL_CHIP_BROADWELL,
	DRM_INTEL_CHIP_CHERRYVIEW,

	/* gen 9 */
	DRM_INTEL_CHIP_SKYLAKE,
};

/*
 * Note that this structure definition doesn't actually hold the internal
 * fields of the real struct drm_intel_device device allocated by
 * drm_intel_device_init(). This is to allow direct access to widely used
 * fields like ->gen without having to go through a function call.
 *
 * This means that this structure shouldn't statically or stack allocated.
 */
struct drm_intel_device {
	uint16_t chip, gen;
};

/*
 * Allocate a drm_intel_device object from:
 * - a PCI devid or,
 * - an opened DRM file descriptor
 *
 * The version taking a fd is the preferred one as it allows run-time support
 * from the kernel.
 *
 * The returned object has to be freed with drm_intel_device_free(). When being
 * instantiated with a file descriptor, the object does not take ownership of
 * the fd and so _free() will not close that fd.
 */
struct drm_intel_device *drm_intel_device_new(int fd);
struct drm_intel_device *drm_intel_device_new_from_devid(uint16_t devid);
void drm_intel_device_free(struct drm_intel_device *dev);

/* Retrieve the PCI device id */
uint16_t drm_intel_device_get_devid(struct drm_intel_device *dev);

#endif /* __INTEL_DEVICE_H__ */
