# Contributing

## Table of contents

 * [Committing](#committing)
    * [When to commit?](#when-to-commit)
    * [What sort of message should I use?](#what-sort-of-commit-message-should-i-use)
    * [Other Types](#other-types)
 * [Code Style](#code-style)
    * [Brackets](#brackets)
    * [Distinction between related code](#distinction-between-related-code)

## Committing

### When to commit?

Whenever you commit make sure your commit is related to one feature or change, don't commit multiple unrelated things at once.
You don't **have** to commit every 5 minutes, only commit whenever you've got a working code base with a finished feature.

### What sort of commit message should I use?

If you're committing a new feature or change something existing to act differently use the following syntax:
```
feat(subject): Added new method of destroying children
```

If your commit is related to fixing an issue:
```
fix(subject): Fixed issue related to children multiplying endlessly

Closes #1337 <-- mention a related issue to automatically close it when making this commit
```

#### Other Types

Aside from `feat` and `fix`, you can also use the following types `build`, `docs`, `style`, `refactor` and `test` whenever you deem these more useful in the context.

## Code Style

1. Be consistent
2. Use 4 spaces for tab indentation, don't ever use HARD tabs

### Brackets

```cpp
for (int i = 1; i < 5; i++)
{
  //code here;
}
```

### Distinction between related code

Create a clear line of separation between lines, don't just put everything right next each other.

How not to do it:
```cpp
void foo() {
  int x = fribbery;
  y.attack(frabbet(x));
  z.attack(frobbet(x));
  bejooger[0].scramboozle(y);
  bejooger[1].scramboozle(y);
  bejooger[2].scramboozle(z);
  bejooger[3].scramboozle(z);
  if (curdleblogpod.getAlive() <= 5) {
    //Yikes! 
  }
}
```

How you should do it:
```cpp
void foo() {

  //Start the attack on the fribs.
  int x = fribbery;
  y.attack(frabbet(x));
  z.attack(frobbet(x));
  
  //Now send the bejoogers out...
  bejooger[0].scramboozle(y);
  bejooger[1].scramboozle(y);
  bejooger[2].scramboozle(z);
  bejooger[3].scramboozle(z);

  //Make sure the curdleblogs are still alive.
  if (curdleblogpod.getAlive() <= 5) {
    //Yikes! 
  }
}
```
