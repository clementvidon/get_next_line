
#           TODO

- Create a tester that doesnt use binary chars except for buffer 1 with cat,
  otherwise use different textfile with getline.

- Understand why does getline doesn't print binary file (some chars) exactly
  like get_next_line and replace `cat` with `getline` in `gnldiff.sh` to make it
  works with any buffer size.

- A tool that determine the most optimized `BUFFER_SIZE` value to use for a
  specific `get_next_line` use.

