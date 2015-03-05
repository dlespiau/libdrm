/*
 * Copyright © 2015 Intel Corporation
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

#ifndef __INTEL_DEVICE_PRIV_H__
#define __INTEL_DEVICE_PRIV_H__

#include "intel_device.h"

/*
 * Shorthand defines. These are not namespaced and shouldn't be in a public
 * header, hence a _priv.h one for internal use.
 */
#define IS_CHIP(dev, id)	((dev)->chip == DRM_INTEL_CHIP_ ## id)
#define IS_GEN2(dev)		((dev)->gen == 2)
#define IS_GEN3(dev)		((dev)->gen == 3)
#define IS_GEN4(dev)		((dev)->gen == 4)
#define IS_GEN5(dev)		((dev)->gen == 5)
#define IS_GEN6(dev)		((dev)->gen == 6)
#define IS_GEN7(dev)		((dev)->gen == 7)
#define IS_GEN8(dev)		((dev)->gen == 8)
#define IS_GEN9(dev)		((dev)->gen == 9)

#endif /* __INTEL_DEVICE_PRIV_H__ */
