#! /bin/bash

if [[ $# -ne "1" ]]; then
  echo "Invalid arguments passed: $*"
  echo "Usage: submission.sh \$userName"
  exit 1
fi

LAB_NO=3

USER=$1
git add -A 
git commit -m "$USER - Auto-commit for submission: `date`"
git archive -o $USER-lab${LAB_NO}asn.zip --format zip --prefix $USER/ HEAD
