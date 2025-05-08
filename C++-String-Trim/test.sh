#!/usr/bin/env bash

print_lines() {
  while IFS= read -r line
  do
    echo "$line\\n"
  done <<< "$1"
}

read -r -d '' src_str << EOF
This is a test message.
       Spaces.           
  More space.	After a tab.		
Hello.	
EOF

dest_str=$(echo -e "$src_str" | bin/trim)

echo -e "[Source string]\n"
print_lines "$src_str"
echo -e "\n[Destination string]\n"
print_lines "$dest_str"
