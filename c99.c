/*
 * Copyright (c) 2024 Brian Callahan <bcallah@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <err.h>
#include <unistd.h>

#define ARG_MAX	4096

int
main(int argc, char *argv[])
{
	char *av[ARG_MAX + 1], s[9] = { '-', 's', 't', 'd', '=', 'c' };
	int ac;

	if (pledge("exec", NULL) == -1)
		err(1, "pledge");

	av[0] = "/usr/bin/cc";
	for (ac = 1; ac < argc; ++ac) {
		if (ac > ARG_MAX - 2)
			errx(1, "too many arguments");
		av[ac] = argv[ac];
	}

	av[ac] = argv[0];
	while (*argv[0]) {
		if (*argv[0]++ == '/')
			av[ac] = argv[0];
	}
	s[6] = av[ac][1], s[7] = av[ac][2], s[8] = '\0';
	av[ac++] = s;
	av[ac] = NULL;

	return execve(av[0], av, NULL);
}
