# Week 4 — Strings & Structs

---

## Code Written

| File | What it does |
|---|---|
| `week4/day16.c` | `my_strlen` — manual string length via pointer traversal, no `string.h` calls |
| `week4/day17.c` | Practice snippets — safe `strncpy`/`snprintf` truncation handling, manual string split using `strchr` + in-place `'\0'` overwrite |

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

## Day 17 — Buffer Safety

### Core Concepts

| Concept | Summary |
|---|---|
| Out-of-bounds `strcpy` | `strcpy` doesn't know or check the destination's declared size — it writes straight through into adjacent memory regardless. On a typical OS, this usually does NOT crash (it overwrites other valid stack data silently); it only crashes if it happens to hit an unmapped page. |
| Embedded relevance | Bare-metal targets have no MMU/page protection at all — this kind of overflow can never segfault. It always silently corrupts whatever's next in RAM. |
| Off-by-one buffer rule | To store N actual characters, the array needs `N + 1` bytes total (N for content, 1 for the `'\0'` terminator). `char dst[5]` can NOT safely hold `"hello"` (5 chars) — it needs `dst[6]`. |
| `strncpy` doesn't guarantee termination | If `src` is longer than the limit passed, `strncpy` stops after copying exactly that many bytes — it never writes a terminator in that case. Treating the result as a string (e.g. `printf("%s", ...)`) is unsafe; it reads past the buffer hunting for a stray `\0`. |
| Safe `strncpy` idiom | `strncpy(dst, src, sizeof(dst) - 1); dst[sizeof(dst) - 1] = '\0';` — always reserve one byte and terminate manually. Use `sizeof(dst) - 1` rather than a hardcoded number so it stays correct if the buffer size changes. |
| `snprintf` return value | Returns the number of characters that *would have been written* if the buffer were big enough — not the number actually written. Use `if (n >= (int)sizeof(dst))` to detect truncation. A negative return means an encoding/format error. |
| `snprintf` vs `strncpy` | Both prevent overflow. `snprintf` additionally guarantees null-termination and tells you if truncation happened. `strncpy` truncates silently with zero feedback. |
| Manual string splitting | `strchr(buf, delim_char)` finds the delimiter. Overwriting that byte with `'\0'` splits the buffer into two independent C-strings in place — no copying, no allocation. A second pointer set to `delim + 1` picks up the remainder. |

### Code Patterns

```c
// Safe strncpy
strncpy(dst, src, sizeof(dst) - 1);
dst[sizeof(dst) - 1] = '\0';

// Truncation-aware snprintf
int n = snprintf(dst, sizeof(dst), "%s", src);
if (n >= (int)sizeof(dst)) {
    // truncation happened
}

// In-place string split
char buf[] = "SET:25";
char *delim = strchr(buf, ':');
*delim = '\0';
char *cmd = buf;        // "SET"
char *val = delim + 1;  // "25"
```

---

## Interview Questions

**Day 16**
- Where do string literals live in memory, and why does writing through a `char *` pointing at one crash while reading doesn't?
- Why is `char arr[] = "hello"` safe to modify but `char *p = "hello"` is not?
- Why is `arr++` illegal but `p++` legal, even though both support `[]` indexing?
- Why does `*s++;` as a standalone statement still correctly advance the pointer, even though the dereferenced value is discarded?
- What does `strcmp`'s return value actually guarantee, and what shouldn't you assume about it?

**Day 17**
- Why doesn't an out-of-bounds `strcpy` necessarily crash on a typical OS, and why does it *always* silently corrupt on bare-metal embedded targets?
- What's the off-by-one buffer sizing rule, and why is `char dst[5]` insufficient to hold `"hello"`?
- Why doesn't `strncpy` guarantee a null-terminated string, and what's the safe idiom to fix that?
- What does `snprintf`'s return value actually represent, and how do you use it to detect truncation?
- How do you split a string into two separate C-strings in place, without copying or allocating new memory?

---