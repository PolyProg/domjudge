#!/bin/bash

if [[ $EUID -ne 0 ]]; then
  echo "Not root... re-running with sudo"
  sleep 2
  sudo bash $0 "$@"
else
  make dist
  ./configure
  bash inst.sh
  sql/dj-setup-database -u root -r install || (echo "Database already installed... skipping" && sleep 2)
  cp misc/domjudge.conf /etc/apache2/conf-available/domjudge.conf && \
  (cd /etc/apache2/conf-enabled && ln -sf ../conf-available/domjudge.conf) && \
  service apache2 restart
fi
