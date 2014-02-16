#!/bin/bash

if [[ $EUID -ne 0 ]]; then
  echo "Not root... re-running with sudo"
  sleep 2
  sudo bash $0 "$@"
else
  make domserver judgehost install-domserver install-judgehost
fi
