# Contrib

### Commit convention

**Don't overthink it, we can edit the final commit message if it doesn't describe the changes correctly!**

Types:
- feat: The new feature you're adding to a particular application
- fix: To fix a bug
- style: Feature and updates related to styling
- refactor: Refactoring a specific section of the codebase
- test: Everything related to testing
- docs: Everything related to documentation
- chore: Regular code maintenance

A scope is a phrase describing parts of the code affected by the changes. For example "(userservice)"

Body (optional) can provide additional contextual information. For breaking changes the body MUST start with "BREAKING CHANGE".

Footer (optional) is used to reference issues affected by the code changes. For example "Fixes #13". Can also be used to indicate breaking changes by starting with "BREAKING CHANGE".
#### Structure


```
<type>(scope): <description>

[optional body]

[optional footer]
```

#### Examples
- `feat(order): add purchase order button`
- `docs(readme): document coding conventions`


# C++ Coding Standards
## Naming Style

Avoid Hun-garian notation. 
This means, we never want to use variable names that contain the type.

| Entities | Naming | Preview |
| ----------- | ----------- | ---------- |
| NameSpaces | snake_case | namespace `ex_namespace` |
| Classes and Structs | snake_case | Class `ex_class` |
| Enums | UpperCamelCase | Enum `ExEnum` |
| Enum Members | ALL_UPPER | ExNum::`NONE`; ExNum::`FIRST_HALF`; ...
| Global Variables| g_snake_case | bool `g_running` |
| Macros | ALL_UPPER | #define `USE_OPENGL` |
| Template Parameter | UpperCamelCase | template<`typename T`> |
| Parameters | snake_case | ex_method(int `number`) |
| Local Variables | snake_case | int `number{}` |
| Member Variables | m_snake_case | int `m_number` |
| Member Methods | snake_case | void `ex_method`(int param1, int param2); |

<br><br><br>

## Formatting Style
### **Indents**
prefer Tabs for indents

### **Braces**  

With `if` statements and `for` loops we drop the brackets if it only has to execute 1 line of code or if it calls a method
```c++
if (true)
    execute_method();

int num;
if (true)
    num += 5;

for (;;)
    execute_method();

for (;;)
    num += 5;
```


Example for namespaces, classes, etc...
```c++
namespace ex_namesspace
{
    class ex_class
    {
    public:
        ex_class()
        {
        }

        void ex_method();

        int GetNum() const 
        {
            return m_num;
        }
    private:
        int m_num;
    }
}

ex_namesspace::ex_class::ex_method()
{
    auto lambda = []()
    {
        int x = 0;
        return x;
    };

    switch (expression)
    {
    case 0:
    {
        // do stuff
        break;
    }
    case 1:
    {
        // do stuff
        break;
    }
    }
    
    do
    {
        // do stuff
    } while (true);
}
```
### **Regarding if statements**  

Prefer default initialized variables that will be set in an if
	
Bad example:
```c++
int value;
if(true)
{
    value = 1;
}
else
{
    value = 2
}
```
Instead, we prefer this:
```c++
int value{2};
if(true)
{
    value = 1;
}
```


Prefer using guarding `if` statements for readability

Bad Example:
```c++ 
void method()
{
    bool val1 = true;
    bool val2 = false;
    bool val3 = true;

    if(val1)
    {
        if(val2)
        {
        }
        else 
        {
            if(val3)
            {
                // code part
                // where tf are we at
            }
        }
    }
}
```

Guarded if Example:
```c++
void method()
{
    bool val1 = true;
    bool val2 = false;
    bool val3 = true;

    if(!val1)
        return;

    if (val2)
        return;

    if (!val3)
        return;

    // here comes the code part
}
```

### **Member variables in classes**

1. Separate every variable to a single line
2. Initialize all member variables
3. Use the same order of initialization as in the header file
4. Order data types from big to low 

```c++
// Header File
class ex_class
{
public:
    ex_class();

private:
    float m_Length;
    int m_Number;
    bool m_Enabled;
}

// Cpp File
ex_class::ex_class() :
  m_Length{ 1.f },
  m_Number{ 5 },
  m_Enabled { true }
{

}
```

### use of auto
1. Not for numeric types: `int, bool, char, float, ...`
2. When methods return a value
3. Only when r-value type is evident
4. Prefer using `auto&` to avoid copies
```c++
// 1.
int a{ 0 };        
float b{ 0.5f };
// 2.
const auto& data = exClass->GetData();
// 3.
auto timer = new TimerClass();
```
    
### using keyword

 - **Never use `using namespace std`!** 
 - Never use `using namespace` in a header file. This can mess with code that includes the header file wich contains `using namespace`.
 - Never use `using namespace` before any `#include`s. This can mess with the meaning of code in someone else's header.
 - Use `using` instead of typedef! Modernized c++
```c++
// bad example
typedef int my_int;

// good example
using my_float = float;
```
 - Prefer specified using over namespace using.
```c++
// bad example
using namepace std::chrono;
	
// good examples
using std::chrono::high_resolution_clock;
using std::chrono::duration;
```

Nested Namespaces  
Example:
```c++
// bad example
namespace a
{
	namespace b {}
}

// good example
namespace a::b {}
```

### overriding methods
1. Use `virtual` in Base classes
2. Use `virtual` and `override` in Derived classes
3. Use `virtual` and `= 0` for an abstract(instantiable) class
4. Always make destructors `virtual`