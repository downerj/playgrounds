#!/bin/false

# Get the current branch.
alias GitBr="git branch | grep '\\*' | cut -d\  -f2"

# Add and commit all changes.
alias GitAll="git add --all && git commit"

# Push up the current branch.
alias GitPush="git push origin \$(GitBr)"

# Pull down the current branch (fetch and merge).
alias GitPull="git pull origin \$(GitBr)"

# Fetch the current branch.
alias GitFetch="git fetch origin \$(GitBr)"

