#	$OpenBSD$

PROG=	c99
MAN=	c89.1 c99.1 c11.1 c17.1
LINKS=	${BINDIR}/c99 ${BINDIR}/c89
LINKS+=	${BINDIR}/c99 ${BINDIR}/c11
LINKS+=	${BINDIR}/c99 ${BINDIR}/c17

.include <bsd.prog.mk>
