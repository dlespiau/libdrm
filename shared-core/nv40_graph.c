#include "drmP.h"
#include "drm.h"
#include "nouveau_drv.h"
#include "nouveau_drm.h"

/* The sizes are taken from the difference between the start of two
 * grctx addresses while running the nvidia driver.  Probably slightly
 * larger than they actually are, because of other objects being created
 * between the contexts
 */
#define NV40_GRCTX_SIZE (175*1024)
#define NV44_GRCTX_SIZE (25*1024)

/*TODO: deciper what each offset in the context represents. The below
 *      contexts are taken from dumps just after the 3D object is
 *      created.
 */
static void nv40_graph_context_init(drm_device_t *dev, struct mem_block *ctx)
{
	drm_nouveau_private_t *dev_priv = dev->dev_private;
	int i;

	/* Always has the "instance address" of itself at offset 0 */
	INSTANCE_WR(ctx, 0x00000/4, nouveau_chip_instance_get(dev, ctx));
	/* unknown */
	INSTANCE_WR(ctx, 0x00024/4, 0x0000ffff);
	INSTANCE_WR(ctx, 0x00028/4, 0x0000ffff);
	INSTANCE_WR(ctx, 0x00030/4, 0x00000001);
	INSTANCE_WR(ctx, 0x0011c/4, 0x20010001);
	INSTANCE_WR(ctx, 0x00120/4, 0x0f73ef00);
	INSTANCE_WR(ctx, 0x00128/4, 0x02008821);
	INSTANCE_WR(ctx, 0x0016c/4, 0x00000040);
	INSTANCE_WR(ctx, 0x00170/4, 0x00000040);
	INSTANCE_WR(ctx, 0x00174/4, 0x00000040);
	INSTANCE_WR(ctx, 0x0017c/4, 0x80000000);
	INSTANCE_WR(ctx, 0x00180/4, 0x80000000);
	INSTANCE_WR(ctx, 0x00184/4, 0x80000000);
	INSTANCE_WR(ctx, 0x00188/4, 0x80000000);
	INSTANCE_WR(ctx, 0x0018c/4, 0x80000000);
	INSTANCE_WR(ctx, 0x0019c/4, 0x00000040);
	INSTANCE_WR(ctx, 0x001a0/4, 0x80000000);
	INSTANCE_WR(ctx, 0x001b0/4, 0x80000000);
	INSTANCE_WR(ctx, 0x001c0/4, 0x80000000);
	INSTANCE_WR(ctx, 0x001d0/4, 0x0b0b0b0c);
	INSTANCE_WR(ctx, 0x00340/4, 0x00040000);
	INSTANCE_WR(ctx, 0x00350/4, 0x55555555);
	INSTANCE_WR(ctx, 0x00354/4, 0x55555555);
	INSTANCE_WR(ctx, 0x00358/4, 0x55555555);
	INSTANCE_WR(ctx, 0x0035c/4, 0x55555555);
	INSTANCE_WR(ctx, 0x00388/4, 0x00000008);
	INSTANCE_WR(ctx, 0x0039c/4, 0x00000010);
	INSTANCE_WR(ctx, 0x00480/4, 0x00000100);
	INSTANCE_WR(ctx, 0x00494/4, 0x00000111);
	INSTANCE_WR(ctx, 0x00498/4, 0x00080060);
	INSTANCE_WR(ctx, 0x004b4/4, 0x00000080);
	INSTANCE_WR(ctx, 0x004b8/4, 0xffff0000);
	INSTANCE_WR(ctx, 0x004bc/4, 0x00000001);
	INSTANCE_WR(ctx, 0x004d0/4, 0x46400000);
	INSTANCE_WR(ctx, 0x004ec/4, 0xffff0000);
	INSTANCE_WR(ctx, 0x004f8/4, 0x0fff0000);
	INSTANCE_WR(ctx, 0x004fc/4, 0x0fff0000);
	INSTANCE_WR(ctx, 0x00504/4, 0x00011100);
	for (i=0x00520; i<=0x0055c; i+=4)
		INSTANCE_WR(ctx, i/4, 0x07ff0000);
	INSTANCE_WR(ctx, 0x00568/4, 0x4b7fffff);
	INSTANCE_WR(ctx, 0x00594/4, 0x30201000);
	INSTANCE_WR(ctx, 0x00598/4, 0x70605040);
	INSTANCE_WR(ctx, 0x0059c/4, 0xb8a89888);
	INSTANCE_WR(ctx, 0x005a0/4, 0xf8e8d8c8);
	INSTANCE_WR(ctx, 0x005b4/4, 0x40100000);
	INSTANCE_WR(ctx, 0x005cc/4, 0x00000004);
	INSTANCE_WR(ctx, 0x005d8/4, 0x0000ffff);
	INSTANCE_WR(ctx, 0x0060c/4, 0x435185d6);
	INSTANCE_WR(ctx, 0x00610/4, 0x2155b699);
	INSTANCE_WR(ctx, 0x00614/4, 0xfedcba98);
	INSTANCE_WR(ctx, 0x00618/4, 0x00000098);
	INSTANCE_WR(ctx, 0x00628/4, 0xffffffff);
	INSTANCE_WR(ctx, 0x0062c/4, 0x00ff7000);
	INSTANCE_WR(ctx, 0x00630/4, 0x0000ffff);
	INSTANCE_WR(ctx, 0x00640/4, 0x00ff0000);
	INSTANCE_WR(ctx, 0x0067c/4, 0x00ffff00);
	/* 0x680-0x6BC - NV30_TCL_PRIMITIVE_3D_TX_ADDRESS_UNIT(0-15) */
	/* 0x6C0-0x6FC - NV30_TCL_PRIMITIVE_3D_TX_FORMAT_UNIT(0-15) */
	for (i=0x006C0; i<=0x006fc; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00018488);
	/* 0x700-0x73C - NV30_TCL_PRIMITIVE_3D_TX_WRAP_UNIT(0-15) */
	for (i=0x00700; i<=0x0073c; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00028202);
	/* 0x740-0x77C - NV30_TCL_PRIMITIVE_3D_TX_ENABLE_UNIT(0-15) */
	/* 0x780-0x7BC - NV30_TCL_PRIMITIVE_3D_TX_SWIZZLE_UNIT(0-15) */
	for (i=0x00780; i<=0x007bc; i+=4)
		INSTANCE_WR(ctx, i/4, 0x0000aae4);
	/* 0x7C0-0x7FC - NV30_TCL_PRIMITIVE_3D_TX_FILTER_UNIT(0-15) */
	for (i=0x007c0; i<=0x007fc; i+=4)
		INSTANCE_WR(ctx, i/4, 0x01012000);
	/* 0x800-0x83C - NV30_TCL_PRIMITIVE_3D_TX_XY_DIM_UNIT(0-15) */
	for (i=0x00800; i<=0x0083c; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00080008);
	/* 0x840-0x87C - NV30_TCL_PRIMITIVE_3D_TX_UNK07_UNIT(0-15) */
	/* 0x880-0x8BC - NV30_TCL_PRIMITIVE_3D_TX_DEPTH_UNIT(0-15) */
	for (i=0x00880; i<=0x008bc; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00100008);
	/* unknown */
	for (i=0x00910; i<=0x0091c; i+=4)
		INSTANCE_WR(ctx, i/4, 0x0001bc80);
	for (i=0x00920; i<=0x0092c; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00000202);
	for (i=0x00940; i<=0x0094c; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00000008);
	for (i=0x00960; i<=0x0096c; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00080008);
	INSTANCE_WR(ctx, 0x00980/4, 0x00000002);
	INSTANCE_WR(ctx, 0x009b4/4, 0x00000001);
	INSTANCE_WR(ctx, 0x009c0/4, 0x3e020200);
	INSTANCE_WR(ctx, 0x009c4/4, 0x00ffffff);
	INSTANCE_WR(ctx, 0x009c8/4, 0x60103f00);
	INSTANCE_WR(ctx, 0x009d4/4, 0x00020000);
	INSTANCE_WR(ctx, 0x00a08/4, 0x00008100);
	INSTANCE_WR(ctx, 0x00aac/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00af0/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00af8/4, 0x80800001);
	INSTANCE_WR(ctx, 0x00bcc/4, 0x00000005);
	INSTANCE_WR(ctx, 0x00bf8/4, 0x00005555);
	INSTANCE_WR(ctx, 0x00bfc/4, 0x00005555);
	INSTANCE_WR(ctx, 0x00c00/4, 0x00005555);
	INSTANCE_WR(ctx, 0x00c04/4, 0x00005555);
	INSTANCE_WR(ctx, 0x00c08/4, 0x00005555);
	INSTANCE_WR(ctx, 0x00c0c/4, 0x00005555);
	INSTANCE_WR(ctx, 0x00c44/4, 0x00000001);
	for (i=0x03008; i<=0x03080; i+=8)
		INSTANCE_WR(ctx, i/4, 0x3f800000);
	for (i=0x05288; i<=0x08570; i+=24)
		INSTANCE_WR(ctx, i/4, 0x00000001);
	for (i=0x08628; i<=0x08e18; i+=16)
		INSTANCE_WR(ctx, i/4, 0x3f800000);
	for (i=0x0bd28; i<=0x0f010; i+=24)
		INSTANCE_WR(ctx, i/4, 0x00000001);
	for (i=0x0f0c8; i<=0x0f8b8; i+=16)
		INSTANCE_WR(ctx, i/4, 0x3f800000);
	for (i=0x127c8; i<=0x15ab0; i+=24)
		INSTANCE_WR(ctx, i/4, 0x00000001);
	for (i=0x15b68; i<=0x16358; i+=16)
		INSTANCE_WR(ctx, i/4, 0x3f800000);
	for (i=0x19268; i<=0x1c550; i+=24)
		INSTANCE_WR(ctx, i/4, 0x00000001);
	for (i=0x1c608; i<=0x1cdf8; i+=16)
		INSTANCE_WR(ctx, i/4, 0x3f800000);
	for (i=0x1fd08; i<=0x22ff0; i+=24)
		INSTANCE_WR(ctx, i/4, 0x00000001);
	for (i=0x230a8; i<=0x23898; i+=16)
		INSTANCE_WR(ctx, i/4, 0x3f800000);
	for (i=0x267a8; i<=0x29a90; i+=24)
		INSTANCE_WR(ctx, i/4, 0x00000001);
	for (i=0x29b48; i<=0x2a338; i+=16)
		INSTANCE_WR(ctx, i/4, 0x3f800000);
}

static void nv44_graph_context_init(drm_device_t *dev, struct mem_block *ctx)
{
	drm_nouveau_private_t *dev_priv = dev->dev_private;
	int i;

	INSTANCE_WR(ctx, 0x00000/4, nouveau_chip_instance_get(dev, ctx));
	INSTANCE_WR(ctx, 0x00024/4, 0x0000ffff);
	INSTANCE_WR(ctx, 0x00028/4, 0x0000ffff);
	INSTANCE_WR(ctx, 0x00030/4, 0x00000001);
	INSTANCE_WR(ctx, 0x0011c/4, 0x20010001);
	INSTANCE_WR(ctx, 0x00120/4, 0x0f73ef00);
	INSTANCE_WR(ctx, 0x00128/4, 0x02008821);
	INSTANCE_WR(ctx, 0x00158/4, 0x00000001);
	INSTANCE_WR(ctx, 0x0015c/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00160/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00164/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00168/4, 0x00000001);
	INSTANCE_WR(ctx, 0x0016c/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00170/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00174/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00178/4, 0x00000040);
	INSTANCE_WR(ctx, 0x0017c/4, 0x00000040);
	INSTANCE_WR(ctx, 0x00180/4, 0x00000040);
	INSTANCE_WR(ctx, 0x00188/4, 0x00000040);
	INSTANCE_WR(ctx, 0x001d0/4, 0x0b0b0b0c);
	INSTANCE_WR(ctx, 0x00340/4, 0x00040000);
	INSTANCE_WR(ctx, 0x00350/4, 0x55555555);
	INSTANCE_WR(ctx, 0x00354/4, 0x55555555);
	INSTANCE_WR(ctx, 0x00358/4, 0x55555555);
	INSTANCE_WR(ctx, 0x0035c/4, 0x55555555);
	INSTANCE_WR(ctx, 0x00388/4, 0x00000008);
	INSTANCE_WR(ctx, 0x0039c/4, 0x00001010);
	INSTANCE_WR(ctx, 0x003cc/4, 0x00000111);
	INSTANCE_WR(ctx, 0x003d0/4, 0x00080060);
	INSTANCE_WR(ctx, 0x003ec/4, 0x00000080);
	INSTANCE_WR(ctx, 0x003f0/4, 0xffff0000);
	INSTANCE_WR(ctx, 0x003f4/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00408/4, 0x46400000);
	INSTANCE_WR(ctx, 0x00418/4, 0xffff0000);
	INSTANCE_WR(ctx, 0x00424/4, 0x0fff0000);
	INSTANCE_WR(ctx, 0x00428/4, 0x0fff0000);
	INSTANCE_WR(ctx, 0x00430/4, 0x00011100);
	for (i=0x0044c; i<=0x00488; i+=4)
		INSTANCE_WR(ctx, i/4, 0x07ff0000);
	INSTANCE_WR(ctx, 0x00494/4, 0x4b7fffff);
	INSTANCE_WR(ctx, 0x004bc/4, 0x30201000);
	INSTANCE_WR(ctx, 0x004c0/4, 0x70605040);
	INSTANCE_WR(ctx, 0x004c4/4, 0xb8a89888);
	INSTANCE_WR(ctx, 0x004c8/4, 0xf8e8d8c8);
	INSTANCE_WR(ctx, 0x004dc/4, 0x40100000);
	INSTANCE_WR(ctx, 0x004f8/4, 0x0000ffff);
	INSTANCE_WR(ctx, 0x0052c/4, 0x435185d6);
	INSTANCE_WR(ctx, 0x00530/4, 0x2155b699);
	INSTANCE_WR(ctx, 0x00534/4, 0xfedcba98);
	INSTANCE_WR(ctx, 0x00538/4, 0x00000098);
	INSTANCE_WR(ctx, 0x00548/4, 0xffffffff);
	INSTANCE_WR(ctx, 0x0054c/4, 0x00ff7000);
	INSTANCE_WR(ctx, 0x00550/4, 0x0000ffff);
	INSTANCE_WR(ctx, 0x0055c/4, 0x00ff0000);
	INSTANCE_WR(ctx, 0x00594/4, 0x00ffff00);
	for (i=0x005d8; i<=0x00614; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00018488);
	for (i=0x00618; i<=0x00654; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00028202);
	for (i=0x00698; i<=0x006d4; i+=4)
		INSTANCE_WR(ctx, i/4, 0x0000aae4);
	for (i=0x006d8; i<=0x00714; i+=4)
		INSTANCE_WR(ctx, i/4, 0x01012000);
	for (i=0x00718; i<=0x00754; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00080008);
	for (i=0x00798; i<=0x007d4; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00100008);
	for (i=0x00828; i<=0x00834; i+=4)
		INSTANCE_WR(ctx, i/4, 0x0001bc80);
	for (i=0x00838; i<=0x00844; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00000202);
	for (i=0x00858; i<=0x00864; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00000008);
	for (i=0x00878; i<=0x00884; i+=4)
		INSTANCE_WR(ctx, i/4, 0x00080008);
	INSTANCE_WR(ctx, 0x00898/4, 0x00000002);
	INSTANCE_WR(ctx, 0x008cc/4, 0x00000020);
	INSTANCE_WR(ctx, 0x008d0/4, 0x030c30c3);
	INSTANCE_WR(ctx, 0x008d4/4, 0x00011001);
	INSTANCE_WR(ctx, 0x008e0/4, 0x3e020200);
	INSTANCE_WR(ctx, 0x008e4/4, 0x00ffffff);
	INSTANCE_WR(ctx, 0x008e8/4, 0x0c103f00);
	INSTANCE_WR(ctx, 0x008f4/4, 0x00040000);
	INSTANCE_WR(ctx, 0x0092c/4, 0x00008100);
	INSTANCE_WR(ctx, 0x009b8/4, 0x00000001);
	INSTANCE_WR(ctx, 0x009fc/4, 0x00001001);
	INSTANCE_WR(ctx, 0x00a04/4, 0x00000003);
	INSTANCE_WR(ctx, 0x00a08/4, 0x00888001);
	INSTANCE_WR(ctx, 0x00a6c/4, 0x00000005);
	INSTANCE_WR(ctx, 0x00a78/4, 0x0000ffff);
	INSTANCE_WR(ctx, 0x00a94/4, 0x00005555);
	INSTANCE_WR(ctx, 0x00a98/4, 0x00000001);
	INSTANCE_WR(ctx, 0x00aa4/4, 0x00000001);
	for (i=0x01668; i<=0x016e0; i+=8)
		INSTANCE_WR(ctx, i/4, 0x3f800000);
	for (i=0x03428; i<=0x05618; i+=24)
		INSTANCE_WR(ctx, i/4, 0x00000001);
	for (i=0x05628; i<=0x05a18; i+=16)
		INSTANCE_WR(ctx, i/4, 0x3f800000);
}

int
nv40_graph_context_create(drm_device_t *dev, int channel)
{
	drm_nouveau_private_t *dev_priv =
		(drm_nouveau_private_t *)dev->dev_private;
	struct nouveau_fifo *chan = &dev_priv->fifos[channel];
	unsigned int ctx_size;
	int i;

	if (dev_priv->card_type == NV_40)
		ctx_size = NV40_GRCTX_SIZE;
	else
		ctx_size = NV44_GRCTX_SIZE;

	/* Alloc and clear RAMIN to store the context */
	chan->ramin_grctx = nouveau_instmem_alloc(dev, ctx_size, 4);
	if (!chan->ramin_grctx)
		return DRM_ERR(ENOMEM);
	for (i=0; i<ctx_size; i+=4)
		INSTANCE_WR(chan->ramin_grctx, i/4, 0x00000000);

	/* Initialise default context values */
	if (dev_priv->card_type == NV_40)
		nv40_graph_context_init(dev, chan->ramin_grctx);
	else
		nv44_graph_context_init(dev, chan->ramin_grctx);

	return 0;
}

/* Save current context (from PGRAPH) into the channel's context
 *XXX: fails sometimes, not sure why..
 */
void
nv40_graph_context_save_current(drm_device_t *dev)
{
	drm_nouveau_private_t *dev_priv =
		(drm_nouveau_private_t *)dev->dev_private;
	uint32_t instance;
	int i;

	NV_WRITE(NV_PGRAPH_FIFO, 0);

	instance = NV_READ(0x40032C) & 0xFFFFF;
	if (!instance) {
		NV_WRITE(NV_PGRAPH_FIFO, 1);
		return;
	}

	NV_WRITE(0x400784, instance);
	NV_WRITE(0x400310, NV_READ(0x400310) | 0x20);
	NV_WRITE(0x400304, 1);
	/* just in case, we don't want to spin in-kernel forever */
	for (i=0; i<1000; i++) {
		if (NV_READ(0x40030C) == 0)
			break;
	}
	if (i==1000) {
		DRM_ERROR("failed to save current grctx to ramin\n");
		DRM_ERROR("instance = 0x%08x\n", NV_READ(0x40032C));
		DRM_ERROR("0x40030C = 0x%08x\n", NV_READ(0x40030C));
		NV_WRITE(NV_PGRAPH_FIFO, 1);
		return;
	}

	NV_WRITE(NV_PGRAPH_FIFO, 1);
}

/* Restore the context for a specific channel into PGRAPH
 * XXX: fails sometimes.. not sure why
 */
void
nv40_graph_context_restore(drm_device_t *dev, int channel)
{
	drm_nouveau_private_t *dev_priv =
		(drm_nouveau_private_t *)dev->dev_private;
	struct nouveau_fifo *chan = &dev_priv->fifos[channel];
	uint32_t instance;
	int i;

	instance = nouveau_chip_instance_get(dev, chan->ramin_grctx);

	NV_WRITE(NV_PGRAPH_FIFO, 0);
	NV_WRITE(0x400784, instance);
	NV_WRITE(0x400310, NV_READ(0x400310) | 0x40);
	NV_WRITE(0x400304, 1);
	/* just in case, we don't want to spin in-kernel forever */
	for (i=0; i<1000; i++) {
		if (NV_READ(0x40030C) == 0)
			break;
	}
	if (i==1000) {
		DRM_ERROR("failed to restore grctx for ch%d to PGRAPH\n",
				channel);
		DRM_ERROR("instance = 0x%08x\n", instance);
		DRM_ERROR("0x40030C = 0x%08x\n", NV_READ(0x40030C));
		NV_WRITE(NV_PGRAPH_FIFO, 1);
		return;
	}


	/* 0x40032C, no idea of it's exact function.  Could simply be a
	 * record of the currently active PGRAPH context.  It's currently
	 * unknown as to what bit 24 does.  The nv ddx has it set, so we will
	 * set it here too.
	 */
	NV_WRITE(0x40032C, instance | 0x01000000);
	/* 0x32E0 records the instance address of the active FIFO's PGRAPH
	 * context.  If at any time this doesn't match 0x40032C, you will
	 * recieve PGRAPH_INTR_CONTEXT_SWITCH
	 */
	NV_WRITE(NV40_PFIFO_GRCTX_INSTANCE, instance);
	NV_WRITE(NV_PGRAPH_FIFO, 1);
}

/* Some voodoo that makes context switching work without the binary driver
 * initialising the card first.
 *
 * My best guess is that this describes to the GPU how to save/restore the
 * context between RAMIN and PGRAPH.  But, this is just a hunch.. no actual
 * evidence as of yet.. Though, it should be easily testable.
 *
 * If that hunch is correct, it's likely that this differs between cards.  At
 * least NV44 has a different grctx layout than NV40 does.
 *
 * mmio-trace dumps from other nv4x cards very welcome :)
 */
static uint32_t nv40_ctx_voodoo[] = {
	0x00400889, 0x00200000, 0x0060000a, 0x00200000, 0x00300000, 0x00800001,
	0x00700009, 0x0060000e, 0x00400d64, 0x00400d05, 0x00408f65, 0x00409406,
	0x0040a268, 0x00200000, 0x0060000a, 0x00700000, 0x00106000, 0x00700080,
	0x004014e6, 0x007000a0, 0x00401a84, 0x00700082, 0x00600001, 0x00500061,
	0x00600002, 0x00401b68, 0x00500060, 0x00200001, 0x0060000a, 0x0011814d,
	0x00110158, 0x00105401, 0x0020003a, 0x00100051, 0x001040c5, 0x0010c1c4,
	0x001041c9, 0x0010c1dc, 0x00110205, 0x0011420a, 0x00114210, 0x00110216,
	0x0012421b, 0x00120270, 0x001242c0, 0x00200040, 0x00100280, 0x00128100,
	0x00128120, 0x00128143, 0x0011415f, 0x0010815c, 0x0010c140, 0x00104029,
	0x00110400, 0x00104d10, 0x00500060, 0x00403b87, 0x0060000d, 0x004076e6,
	0x002000f0, 0x0060000a, 0x00200045, 0x00100620, 0x00108668, 0x0011466b,
	0x00120682, 0x0011068b, 0x00168691, 0x0010c6ae, 0x001206b4, 0x0020002a,
	0x001006c4, 0x001246f0, 0x002000c0, 0x00100700, 0x0010c3d7, 0x001043e1,
	0x00500060, 0x00405600, 0x00405684, 0x00600003, 0x00500067, 0x00600008,
	0x00500060, 0x00700082, 0x0020026c, 0x0060000a, 0x00104800, 0x00104901,
	0x00120920, 0x00200035, 0x00100940, 0x00148a00, 0x00104a14, 0x00200038,
	0x00100b00, 0x00138d00, 0x00104e00, 0x0012d600, 0x00105c00, 0x00104f06,
	0x0020031a, 0x0060000a, 0x00300000, 0x00200680, 0x00406c00, 0x00200684,
	0x00800001, 0x00200b62, 0x0060000a, 0x0020a0b0, 0x0040728a, 0x00201b68,
	0x00800041, 0x00407684, 0x00203e60, 0x00800002, 0x00408700, 0x00600006,
	0x00700003, 0x004080e6, 0x00700080, 0x0020031a, 0x0060000a, 0x00200004,
	0x00800001, 0x00700000, 0x00200000, 0x0060000a, 0x00106002, 0x0040a284,
	0x00700002, 0x00600004, 0x0040a268, 0x00700000, 0x00200000, 0x0060000a,
	0x00106002, 0x00700080, 0x00400a84, 0x00700002, 0x00400a68, 0x00500060,
	0x00600007, 0x00409388, 0x0060000f, 0x00000000, 0x00500060, 0x00200000,
	0x0060000a, 0x00700000, 0x00106001, 0x00700083, 0x00910880, 0x00901ffe,
	0x00940400, 0x00200020, 0x0060000b, 0x00500069, 0x0060000c, 0x00401b68,
	0x0040a406, 0x0040a505, 0x00600009, 0x00700005, 0x00700006, 0x0060000e,
	~0
};

int
nv40_graph_init(drm_device_t *dev)
{
	drm_nouveau_private_t *dev_priv =
		(drm_nouveau_private_t *)dev->dev_private;
	uint32_t *ctx_voodoo;
	uint32_t pg0220_inst;
	int i, chipset;

	chipset = (NV_READ(NV_PMC_BOOT_0) & 0x0ff00000) >> 20;
	DRM_DEBUG("chipset (from PMC_BOOT_0): NV0x%02X\n", chipset);
	switch (chipset) {
	case 0x40:
		ctx_voodoo = nv40_ctx_voodoo;
		break;
	default:
		DRM_ERROR("Unknown ctx_voodoo for chipset 0x%02x\n", chipset);
		ctx_voodoo = NULL;
		break;
	}

	/* Load the context voodoo onto the card */
	if (ctx_voodoo) {
		DRM_DEBUG("Loading context-switch voodoo\n");
		i = 0;

		NV_WRITE(0x400324, 0);
		while (ctx_voodoo[i] != ~0) {
			NV_WRITE(0x400328, ctx_voodoo[i]);
			i++;
		}
	}	

	/* No context present currently */
	NV_WRITE(0x40032C, 0x00000000);

	/* No idea what this is for.. */
	dev_priv->fb_obj = nouveau_dma_object_create(dev,
			0, nouveau_mem_fb_amount(dev),
			NV_DMA_ACCESS_RW, NV_DMA_TARGET_VIDMEM);
	pg0220_inst = nouveau_chip_instance_get(dev,
			dev_priv->fb_obj->instance);
	NV_WRITE(NV_PGRAPH_NV40_UNK220, pg0220_inst);

	return 0;
}
