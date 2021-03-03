#! /bin/bash
# generate documentation
doxygen
git add .
# This will prompt for a commit message
git commit
# Push master
git push
# Now push _site to gh-pages
git subtree push --prefix doc/doxy/html origin gh-pages