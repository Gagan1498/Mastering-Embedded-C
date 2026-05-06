# Week 3 — Pointers Deep Dive

---

## Code Written

| File | What it does |
|---|---|
| `week3/day1.c` | Traverses an int array using pointer arithmetic, prints value and address with `%p`. Demonstrates array decay on function call. |
| `week3/day2.c` | Pointers and functions — add_ten, swap, update_pointer, reset_buffer exercises. |
| `week3/day3.c` | const pointers — scale_readings (int *) and print_sensor (const int *) with in-place modification pattern. |

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
| `sizeof` length trick | `sizeof(arr) / sizeof(int)` gives element count. Only works on the actual array, not a pointer to it. |
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

## Day 2 — Pointers & Functions

### Core Concepts

| Concept | Summary |
|---|---|
| Pass by value | C always passes copies. Modifying a parameter inside a function does NOT affect the caller's variable. |
| Pass by address | Pass `&a` and accept `int *` to modify the caller's variable. The function writes through the pointer to the original memory. |
| The universal rule | If you want a function to modify a variable, pass its address. Doesn't matter if it's an `int`, `float`, or a pointer — same rule every time. |
| `sizeof` breaks inside functions | An array decays to a pointer when passed to a function. `sizeof(ptr) / sizeof(int)` = `8 / 4` = 2 always. Pass `len` as a separate parameter. |
| Double pointer | `int **pp` — a pointer to a pointer. Use when a function needs to modify a pointer itself (e.g. malloc inside a function). |
| Modifying through pointer vs modifying pointer | `buf[i] = 0` writes to the memory `buf` points to — affects original. `buf = NULL` only changes the local copy of the pointer — does NOT affect caller. |

### Swap Without Temp

```c
// Arithmetic swap
*a = *a + *b;
*b = *a - *b;
*a = *a - *b;

// XOR swap
*a = *a ^ *b;
*b = *a ^ *b;
*a = *a ^ *b;
```
⚠️ Both break if `a` and `b` point to the same address.

### Double Pointer Pattern

```c
void update_pointer(int **p) {
    *p = malloc(sizeof(int));
    **p = 99;
}
int main() {
    int *data = NULL;
    update_pointer(&data);  // pass address of the pointer itself
    printf("%d\n", *data);  // 99
}
```

---

## Day 3 — const Pointers

### Three Forms — Read Right to Left

| Declaration | Meaning | Can change `*p`? | Can move `p`? |
|---|---|---|---|
| `const int *p` | pointer to a const int | ❌ No | ✅ Yes |
| `int * const p` | const pointer to an int | ✅ Yes | ❌ No |
| `const int * const p` | const pointer to a const int | ❌ No | ❌ No |

**Right-to-left reading trick:** Start at `p`, read right to left. `const` before `*` locks the value. `const` after `*` locks the pointer.

### In-place Modification Pattern

```c
void scale_readings(int *data, int len, int factor) {
    for (int i = 0; i < len; i++)
        data[i] *= factor;
}

void print_sensor(const int *data, int len) {
    for (int i = 0; i < len; i++)
        printf("index %d: %d\n", i, data[i]);
}
```

- `scale_readings` takes `int *` — needs to modify values in place
- `print_sensor` takes `const int *` — promises not to modify, read only
- No return value needed — `scale_readings` modifies the original array directly through the pointer
- This is the standard embedded pattern: pass a buffer in, function fills/modifies it, use it after

### Embedded Use Cases

| Use case | Form |
|---|---|
| Hardware register at fixed address (read-only) | `const volatile uint32_t * const` |
| String literals / lookup tables in flash | `const char *` |
| Function that should not modify caller's buffer | `const int *` parameter |


---


## Interview Questions

**Day 1**
- A pointer is incremented by 1. How many bytes does it actually move, and how does the compiler know?
- What is the difference between `arr` and `&arr`? Do they hold the same address?
- What does `(char *)&x` on an `int` give you, and what does `p[0]` return on a little endian machine?
- Why is `int (*p)[5]` different from `int *p[5]`?
- What format specifier do you use to print a pointer, and what cast is required?
- How do you detect at runtime whether a machine is little endian or big endian?

**Day 2**
- Why doesn't modifying a parameter inside a function affect the caller?
- When would you need an `int **` parameter instead of `int *`?
- Why does `sizeof(buf) / sizeof(int)` not give the array length inside a function?
- What is the difference between `buf[i] = 0` and `buf = NULL` inside a function — which one affects the caller?
- Why do arithmetic and XOR swap break when both pointers point to the same address?

**Day 3**
- What is the difference between `const int *p` and `int * const p`?
- Which form would you use for a function parameter that should not modify the caller's array?
- Which form would you use for a pointer to a hardware register at a fixed address?

---