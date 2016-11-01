#! /bin/bash

if [[ $# -ne "1" ]]; then
  echo "Invalid arguments passed: $*"
  echo "Usage: submission.sh \$userName"
  exit 1
fi

git archive -o $1-lab3asn.zip --format zip --prefix $1/ HEAD
