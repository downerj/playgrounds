#/usr/bin/env bash

# Generate RSA keys.
# (Leave all options default by simply pressing Return.)
ssh-keygen

# Copy RSA keys to each client.
ssh-copy-id -i $A_USER@$A_HOST

# Install Homebrew.
/usr/bin/env bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
