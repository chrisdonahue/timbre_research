#!/bin/bash
set -e
find . -name \*.sw* -type f -delete
find . -name \*~ -type f -delete
set +e
