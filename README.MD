# RFORTH Features

- support for +-*/<>, mod, and /mod
- similar terminal function to gforth: take one line of input, process, print, and accept more
- "bye" and "clear-stack" keywords
- integer variable assignment & use

# RFORTH Limitations

- no negative integers
    - token processing doesn't recognize negative numbers
    - map of variables has -1 as value for created but unassigned variables
- static capacity, currently 10