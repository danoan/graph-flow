#! /usr/bin/env bash

USER=root vncserver
update-alternatives --set x-terminal-emulator /usr/bin/xfce4-terminal.wrapper
