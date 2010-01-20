#!/bin/sh

echo -en "`date`\n\t$1\n\n`cat CHANGELOG 2>/dev/null`" > CHANGELOG

