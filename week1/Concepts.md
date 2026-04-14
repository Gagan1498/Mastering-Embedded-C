# Week 1 — C Foundations

---

## Code Written

| File | What it does |
|---|---|
| `week1/day1.c` | Print addresses of stack, heap and global variables, swap 2 numbers (with/without 3rd variable, using XOR) |
| `week1/day2.c` | Print min and max for `uint8_t` and `int8_t` |
| `week1/day3.c` | Palindrome number |
| `week1/day4.c` | Operators and type casting |
| `week1/day5.c` | Mini project involving type casting, suffix, pointer and stuct |

---

### Pointers

- `&` → get the address of a variable *(what is the address??)*
- `*` → go to that address and get the value *(go to that address and get value!!)*
- `*` is also called the **dereference operator**

**Example:**
```c
int n = 50;
int *p = &n;
printf("%i", *p);  // prints 50
```

> **Why does `*p` print 50 and not the address of n?**
> The 2nd line tells the compiler that `p` is a pointer variable which *points to* an address.
> So when `*p` is used, the compiler knows to dereference — go to the address `p` holds and get the value there.

| Syntax | Meaning |
|---|---|
| `int *p = &n` | `*` here means "p is a pointer variable" — declaration only |
| `*p` anywhere else | dereference — go to the address p holds and get the value |

---

### Memory Regions

| Region | Also called | What lives here | When |
|---|---|---|---|
| Stack | SMA (Static Memory Allocation) | Local variables (initialized + uninitialized) | present at Compile time |
| Heap | DMA (Dynamic Memory Allocation) | `malloc`, `calloc`, `realloc` variables | present at Runtime |
| Data segment | Global segment | Initialized global variables | Entire program |
| BSS | — | Uninitialized global variables (zeroed by OS) | Entire program |

> **Memory leak warning:** When you `malloc` a variable, the pointer lives on the stack but the actual data lives on the heap. If you don't call `free()`, the stack destroys the pointer but the heap memory stays allocated and wasted forever.

---

### Quick Rules

- Use `%p` for printing addresses
- Use `%zu` for `sizeof()` — because `sizeof` returns `size_t` which is unsigned
- Use suffixes to define literal types: `3.3f` (float), `3u` (unsigned), `3l` (long), `3hu` (unsigned uint16_t)

---

### Bit Shifting

```c
1 << 7  // moves 1 from bit 0 (Imp: 1 is already at bit 0) to bit 7 (8th position) → equals 2^7 = 128
1 << 8  // equals 2^8 = 256
```

> Shifting left by n positions = multiplying by 2^n. Faster than `pow()` and works without floating point — important for embedded systems.

---

### Signed vs Unsigned

`uint8_t 255 → int8_t` = -1, not 1. Bits don't change, interpretation does.

**Ranges:**
- `uint8_t` → 0 to 255 (all 8 bits for value, no sign bit)
- `int8_t` → -128 to 127 (1 bit for sign, 7 bits for value)

**Two's complement** — how C represents negative numbers:
1. Flip all bits
2. Add 1

```
+1  = 0000 0001
-1  = 1111 1111  (flip → 1111 1110, add 1 → 1111 1111)
-2  = 1111 1110
-128= 1000 0000
```

**Overflow behavior:**
```c
uint8_t x = 255; x++;  // wraps to 0
int8_t  y = 127; y++;  // wraps to -128 (sign bit flips)
```

---

### Signed and unsigned arithamatics

The lesson here is **integer promotion** — any arithmetic in C happens at minimum in int width. uint8_t and int8_t get promoted to int before any operation.

---

### Signed vs Unsigned Comparison Bug

When you mix signed and unsigned, **C silently converts signed to unsigned:**

```c
int8_t  a = -1;  // binary: 1111 1111
uint8_t b = 1;   // binary: 0000 0001

if (a < b)
    printf("a is less\n");  // WRONG — never prints
else
    printf("b is less\n");  // this prints — because -1 becomes 255 unsigned
```

> `-1` as unsigned = 255 (for `uint8_t`) or 4,294,967,295 (for `unsigned int`). Always cast explicitly when comparing signed and unsigned.

**Implicit comparision conversion rules:**
- `signed vs unsigned` → signed gets converted to unsigned
- `smaller type vs bigger type` → smaller gets converted to bigger

---

### Type Casting

```c
int a = 5;
int b = 2;
float result1 = a / b;         // = 2.0 (integer division first, then converted to float)
float result2 = (float)a / b;  // = 2.5 (a cast to float before dividing)
```

> Always cast *before* the operation, not after — otherwise integer division already happened.

---

### Logical vs Bitwise Operators

```c
int p = 5;  // 0101
int q = 3;  // 0011

p && q  // = 1  logical AND: (is p non-zero) AND (q non-zero)?
p & q   // = 1  bitwise AND: bit by bit → 0101 & 0011 = 0001
p || q  // = 1  logical OR:  (is p non-zero) OR (q non-zero?)
```

> **Logical operators** (`&&`, `||`) return 1 or 0 — they only care if values are true/false.
> **Bitwise operators** (`&`, `|`, `^`) operate on each individual bit.

---

### Increment Operator

```c
i++  // i = i + 1, value of i itself changes
```

---

## Interview Questions
- What is the difference between stack and heap?
- What does `*` mean in a declaration vs anywhere else?
- What happens when you compare a signed and unsigned value in C?
- What is two's complement and why does C use it instead of sign-magnitude?
- What does `uint8_t x = 255; x++` give you and why?
- What happens when you swap a variable with itself using XOR?

---