/*
 * Assembly annotation compatibility for kexec_mod.
 *
 * ENTRY()/ENDPROC() no longer assemble on recent arm64 kernels (5.10+), which
 * use the SYM_*() annotations (available since 4.15). Map them back to the
 * old macros on kernels that lack them.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef KEXEC_MOD_COMPAT_ASM_H
#define KEXEC_MOD_COMPAT_ASM_H

#include <linux/linkage.h>

#ifndef SYM_FUNC_START
#define SYM_FUNC_START(name)	ENTRY(name)
#define SYM_FUNC_END(name)	ENDPROC(name)
#define SYM_CODE_START(name)	ENTRY(name)
#define SYM_CODE_END(name)	ENDPROC(name)
#endif

#endif /* KEXEC_MOD_COMPAT_ASM_H */
