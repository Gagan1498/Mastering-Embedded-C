# Week 4 — Strings & Structs

---

## Code Written

| File | What it does |
|---|---|
| `week4/day16.c` | `my_strlen` — manual string length via pointer traversal, no `string.h` calls |

---

## Day 16 — Strings as Char Arrays

### Core Concepts

| Concept | Summary |
|---|---|
| String literal storage | Literals like `"hello"` live in a read-only segment (`.rodata`, often folded into the text segment) — separate from stack, heap, BSS, and the writable data segment. |
| `char arr[] = "hello"` | Array gets its own writable copy on the stack — the literal's bytes are copied in as an initializer. Modifying `arr[0]` is safe. |
| `char *p = "hello"` | `p` points directly at the literal in read-only memory — no copy. Reading `p[0]` works (reads are allowed on read-only pages). Writing `p[0] = 'H'` triggers a hardware page-protection fault → segfault. |
| Real distinction | Not "pointer vs array" syntax — both compile to identical indexing. It's about ownership: does the variable have its own writable storage, or does it just point at someone else's read-only data? |
| `const char *p` vs `p++` | `p` itself is a normal mutable pointer (just points to const data). `p++` is legal — moves `p` to the next char. Only `*p = ...` (writing through it) is blocked. |
| `arr++` — illegal | `arr` isn't a pointer *variable* holding an address you can change; it IS the storage. It decays to a pointer *value* only transiently in expressions — there's no assignable identity to increment. Compiler error: "lvalue required." |
| `*s++` precedence | Postfix `++` binds tighter than `*`, so it's `*(s++)`. `s++` evaluates to the *old* address and, as a side effect, advances `s`. The outer `*` dereferences that old address — but if the result isn't used (e.g. standalone statement), that read is dead work. The loop still advances `s` correctly, but `s++;` alone does the same job without the wasted dereference. The `*` only earns its place when you use the read, e.g. `*dst++ = *src++;`. |

### string.h Basics

| Function | Summary |
|---|---|
| `strlen(s)` | Length excluding the null terminator. |
| `strcpy(dst, src)` | Copies including `\0`. No bounds checking — overflows `dst` silently if `src` is longer. |
| `strcat(dst, src)` | Appends `src` onto `dst`. Also no bounds checking. |
| `strcmp(a, b)` | Returns `0` if equal. Otherwise sign indicates lexical order (negative = `a` < `b`) — don't rely on the magnitude, only the sign/zero. |

### Code Pattern

```c
int my_strlen(const char *s) {
    int count = 0;
    while (*s != '\0') {
        count++;
        s++;
    }
    return count;
}
```

---

## Interview Questions

**Day 16**
- Where do string literals live in memory, and why does writing through a `char *` pointing at one crash while reading doesn't?
- Why is `char arr[] = "hello"` safe to modify but `char *p = "hello"` is not?
- Why is `arr++` illegal but `p++` legal, even though both support `[]` indexing?
- Why does `*s++;` as a standalone statement still correctly advance the pointer, even though the dereferenced value is discarded?
- What does `strcmp`'s return value actually guarantee, and what shouldn't you assume about it?

---