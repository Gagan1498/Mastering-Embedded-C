# Week 3 — Pointers Deep Dive

---

## Code Written

| File | What it does |
|---|---|
| `week3/day1.c` | Traverses an int array using pointer arithmetic, prints value and address with `%p`. Demonstrates array decay on function call. |

---

## Day 1 — Pointer Arithmetic & Arrays

### Core Concepts

| Concept | Summary |
|---|---|
| Pointer arithmetic scaling | `p + 2` on an `int *` moves `2 * sizeof(int)` = 8 bytes, not 2 bytes. Compiler uses the declared type to scale. |
| Type info is compile-time only | At runtime a pointer holds only an address. No type, no size metadata. `int *` and `char *` are identical in memory — just addresses. |
| Array decay | `arr` in an expression decays to `&arr[0]` — a pointer to the first element. It is NOT the value at index 0. |
| `arr[i]` == `*(arr + i)` | These are identical. The compiler treats them the same way. |
| `%p` for addresses | Use `%p` with a `(void *)` cast to print pointers. `%x` truncates on 64-bit systems. |
| `sizeof` length trick | `sizeof(arr) / sizeof(int)` gives element count. |
| `&arr` vs `arr` | Both hold the same numeric address. But `arr` decays to `int *` (arithmetic moves 4 bytes), while `&arr` is `int (*)[5]` (arithmetic moves 20 bytes — one full array). |
| Pointer to array syntax | `int (*p)[5]` — parentheses needed because `[]` binds tighter than `*`. Without them, `int *p[5]` is an array of 5 pointers. |

### Endianness & Byte-level Casting

| Concept | Summary |
|---|---|
| `(char *)` cast | Reinterprets a multi-byte value one byte at a time. Lets you inspect raw memory. |
| Little endian | LSB stored at lowest address. `0x12345678` stored as `78 56 34 12` in memory. `p[0]` gives `0x78`. |
| Detecting endianness | `int x = 1; char *p = (char *)&x; if (p[0] == 1)` → little endian. |
| Embedded relevance | When casting register values to `uint8_t *`, byte order depends on hardware. ARM Cortex-M is little endian by default. Getting this wrong causes silent register parsing bugs. |

---

## Interview Questions

- A pointer is incremented by 1. How many bytes does it actually move, and how does the compiler know?
- What is the difference between `arr` and `&arr`? Do they hold the same address?
- What does `(char *)&x` on an `int` give you, and what does `p[0]` return on a little endian machine?
- Why is `int (*p)[5]` different from `int *p[5]`?
- What format specifier do you use to print a pointer, and what cast is required?
- How do you detect at runtime whether a machine is little endian or big endian?

---
