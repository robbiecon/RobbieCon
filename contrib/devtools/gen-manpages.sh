#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

ROBBIECOND=${ROBBIECOND:-$SRCDIR/robbiecond}
ROBBIECONCLI=${ROBBIECONCLI:-$SRCDIR/robbiecon-cli}
ROBBIECONTX=${ROBBIECONTX:-$SRCDIR/robbiecon-tx}
ROBBIECONQT=${ROBBIECONQT:-$SRCDIR/qt/robbiecon-qt}

[ ! -x $ROBBIECOND ] && echo "$ROBBIECOND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
ROBVER=($($ROBBIECONCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for robbiecond if --version-string is not set,
# but has different outcomes for robbiecon-qt and robbiecon-cli.
echo "[COPYRIGHT]" > footer.h2m
$ROBBIECOND --version | sed -n '1!p' >> footer.h2m

for cmd in $ROBBIECOND $ROBBIECONCLI $ROBBIECONTX $ROBBIECONQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${ROBVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${ROBVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
