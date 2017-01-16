#!/usr/bin/env bash

## https://www.codeux.com/textual/
## https://github.com/Codeux-Software/Textual
## rss: https://github.com/Codeux-Software/Textual/releases.atom

## create the signing identity:
## https://oddsocks.io/Textual/
## http://www.sysrage.net/guides/mac-os-x/compiling-textual-irc-client-with-xcode


# stop on errors and echo shell commands as they are executed
set -e
set -v


SIGNING_IDENTITY='Alex Scherbanov'


git clone https://github.com/Codeux-Software/Textual.git Textual
cd Textual
git submodule update --init --recursive
sed -i -e "s/Mac Developer/$SIGNING_IDENTITY/g"                                             Resources/Build\ Configurations/Code\ Signing\ Identity.xcconfig
sed -i -e 's/DEVELOPMENT_TEAM = .*/DEVELOPMENT_TEAM = /g'                                   Resources/Build\ Configurations/Code\ Signing\ Identity.xcconfig
sed -i -e 's/PROVISIONING_PROFILE_SPECIFIER = .*/PROVISIONING_PROFILE_SPECIFIER = /g'       Resources/Build\ Configurations/Code\ Signing\ Identity.xcconfig
sed -i -e 's/TEXTUAL_BUILT_WITH_LICENSE_MANAGER=1/TEXTUAL_BUILT_WITH_LICENSE_MANAGER=0/'    Resources/Build\ Configurations/Shared\ Standard\ Release\ Configuration.xcconfig
xcodebuild -scheme 'Textual (Standard Release)' build
open -R Build\ Results/Release/Textual.app      # reveal in Finder


