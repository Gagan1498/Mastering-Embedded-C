# Week 2 — Bitwise operators

---

## Code Written

| File | What it does |
|---|---|
| `week2/day6.c` | Using bitwise operators and typedef and enums |
| `week2/day7.c` | Using bitwise operators and typedef and enums |

---

### Bitwise Operator

- **XOR operator** - Differentiator operator. If the numbers are different, give 1 (if difference between numbers, give 1 as output).
- **Shift operator**:

`x << n` = `x * 2^n`
`x >> n` = `x / 2^n` (for unsigned)

### Masking, Setting and Toggling bits:
- SET with OR
- CLEAR with AND NOT
- TOGGLE with XOR

```
uint8_t reg = 0b00000000;

// SET bit 3 (make it 1)
reg = reg | (1 << 3);    // reg |= (1 << 3);

// CLEAR bit 3 (make it 0)
reg = reg & ~(1 << 3);   // reg &= ~(1 << 3);

// TOGGLE bit 3 (flip it)
reg = reg ^ (1 << 3);    // reg ^= (1 << 3);
```
---

### Typedef
- Provides a new name for an existing type. for ex:
`Pattern` = `typedef <existing type> <new name>;`

```
typedef unsigned int uint;

unsigned int x = 5;  // original
uint x = 5;          // same thing, shorter name
```
Here, instead of writing `unsigned int x` = `5`, I can just write `uint x` = `5`

Example 2:
```
struct sensor{
    int raw_value;
    float temperature;
};
struct sensor s; //without typedef
```

```
typedef struct sensor{
    int raw_value;
    float temperature;
}Sen;
Sen s; //with typedef
```

For struct:
```
typedef struct sensor { ... } Sensor;
//      ^^^^^^^^^^^^^^^^^^^^  ^^^^^
//      existing type          new name
```

Example 3:
Similarly for enum:
Without typedef
```
enum STATE { IDLE, RUNNING, ERROR };
enum STATE s = IDLE;  // have to write enum every time
```

With typedef:
```
typedef enum { IDLE, RUNNING, ERROR } STATE;
STATE s = IDLE;  
```

---

### Enum
- A way to define a set of named integer constants that are **logically related***
```
typedef enum {
    IDLE,     //0
    RUNNING,  //1
    ERROR     //2
} DeviceState;
```
Under the hood these are just integers — `IDLE=0`, `RUNNING=1`, `ERROR=2`. But you work with meaningful names instead of raw numbers.

- It auto increments as shown above.

**Decleration**
- DeviceState state = IDLE;

**Advantage of using enums over `#define`**
- Groups related constants:
```
// #define — scattered, no relationship visible
#define IDLE    0
#define RUNNING 1
#define ERROR   2
#define NORTH   0   // same value, different context, no way to tell apart
#define EAST    1

// enum — grouped, relationship is clear
typedef enum { IDLE, RUNNING, ERROR } DeviceState;
typedef enum { NORTH, EAST, SOUTH, WEST } Direction;
```
- Debugger shows names not numbers
- Type safety — compiler can warn you
```
DeviceState state = IDLE;
Direction   dir   = NORTH;

state = dir;   // compiler warning — mixing types
               // with #define this silently works, both are just ints
```
- Switch completeness warning
```
switch(state) {
    case IDLE:    break;
    case RUNNING: break;
    // forgot ERROR
}
// compiler warns: enumeration value ERROR not handled
// #define gives you nothing
```

---

## Interview Questions
- Why use enum over define?

---