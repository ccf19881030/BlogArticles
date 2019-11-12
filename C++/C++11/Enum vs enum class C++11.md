## [Enum vs enum class C++11](http://www.cplusplus.com/forum/general/147341/)
What is the difference between enum and enum class in C++11? I think it is about type safety, but I need a better explanation.

### Thanks in advance
* [http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html](http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html)

* [http://www.stroustrup.com/C++11FAQ.html#enum](http://www.stroustrup.com/C++11FAQ.html#enum)

### In C++11, we can specify the underlying integral type of the enum (enum-base defaults to int for scoped enum):
```cpp
enum colour : unsigned short{ RED, GREEN, BLUE }; // unscoped
enum class direction: unsigned short{ LEFT, RIGHT }; // scoped 
```
For unscoped enums, the enumerators are visible in the enclosing scope, and conversion to the underlying integer type is implicit.
For scoped enums, the enumerators are contained within the scope of the enum, and conversion to the underlying integer type is explicit.

### We can have our pick:
```cpp
enum colour { RED, GREEN, BLUE }; // unscoped enum

struct printer { enum state { BUSY, IDLE, OFFLINE }; }; // unscoped enum at class scope

enum class direction { LEFT, RIGHT }; // scoped enum

int main()
{
    colour clr_sky = BLUE ;
    printer::state curr_state = printer::BUSY ;
    direction next_move = direction::RIGHT ;

    int a = clr_sky ; // imlicit conversion
    int b = printer::OFFLINE ; // imlicit conversion
    int c = int( direction::LEFT ) ; // explicit conversion

    clr_sky = colour(a) ; // explicit conversion
    curr_state = printer::state(b) ; // explicit conversion
    next_move = direction(c) ; // explicit conversion
}
```
