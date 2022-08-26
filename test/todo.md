
#           TODO

- Create a tester that doesn't use binary chars except for `BUFFER_SIZE` 1 with
  `cat`, otherwise use different text file with `getline`.

- Understand why does `getline` doesn't print multi bytes exactly like
  `get_next_line` and replace `cat` with `getline` in `gnldiff.sh` to make it
  works with arbitrary `BUFFER_SIZE`.

- A tool that determine the most optimized `BUFFER_SIZE` value to use for a
  specific `get_next_line` use.

