/*
 * Symbol lookup helper for kexec_mod.
 *
 * kallsyms_lookup_name() stopped being exported to modules in Linux 5.7.
 * On those kernels, resolve its address through a temporary kprobe, which
 * requires CONFIG_KPROBES in the host kernel.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef KEXEC_MOD_KSYM_H
#define KEXEC_MOD_KSYM_H

#include <linux/version.h>
#include <linux/kallsyms.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,7,0)

#include <linux/kprobes.h>

static unsigned long (*kexec_kallsyms_lookup_name_ptr)(const char *);

static inline unsigned long kexec_kallsyms_lookup_name(const char *name)
{
	if (!kexec_kallsyms_lookup_name_ptr) {
		struct kprobe kp = { .symbol_name = "kallsyms_lookup_name" };

		if (register_kprobe(&kp) < 0)
			return 0;
		kexec_kallsyms_lookup_name_ptr = (void *)kp.addr;
		unregister_kprobe(&kp);
	}
	return kexec_kallsyms_lookup_name_ptr(name);
}

#else

#define kexec_kallsyms_lookup_name kallsyms_lookup_name

#endif

#endif /* KEXEC_MOD_KSYM_H */
