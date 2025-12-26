#!/usr/bin/env bash

set -e

mkdir -p external

git submodule add https://github.com/tplgy/cppcodec external/cppcodec
git submodule add https://github.com/nlohmann/json external/nlohmann
