# cpool - Memory pool based allocator implementation in C
### Principle:
- Divides memory block to sequence of "linked list" nodes;
- For initialization has special context strucure with pointer to memory block, it's size and node region size
- Has implemented memory alignment for better access and less fragmentation (may return in case of offset mismatch)
### The project is built and tested only for Windows x64 using MSVC toolset!