## [cplusplus网站的示例](http://www.cplusplus.com/reference/chrono/system_clock/now/)
* public static member function
<chrono>
std::chrono::system_clock::now
static time_point now() noexcept;
* Get current time
Returns the current time_point in the frame of the system_clock.

* Parameters
none

* Return value
The time_point representing the current time.
time_point is a member type, defined as an alias of time_point<system_clock>.

* Eaxmple
```cpp
// system_clock::now
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

int main ()
{
  using namespace std::chrono;

  duration<int,std::ratio<60*60*24> > one_day (1);

  system_clock::time_point today = system_clock::now();
  system_clock::time_point tomorrow = today + one_day;

  time_t tt;

  tt = system_clock::to_time_t ( today );
  std::cout << "today is: " << ctime(&tt);

  tt = system_clock::to_time_t ( tomorrow );
  std::cout << "tomorrow will be: " << ctime(&tt);

  return 0;
}
```

* Possible output:
```shell
today is: Wed May 30 12:25:03 2012
tomorrow will be: Thu May 31 12:25:03 2012
```
## [cppreference网站的示例](https://en.cppreference.com/w/cpp/chrono/system_clock/now)
### 1、Example
```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
 
volatile int sink;
int main()
{
    for (auto size = 1ull; size < 1000000000ull; size *= 100) {
        // record start time
        auto start = std::chrono::system_clock::now();
        // do some work
        std::vector<int> v(size, 42);
        sink = std::accumulate(v.begin(), v.end(), 0u); // make sure it's a side effect
        // record end time
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end-start;
        std::cout << "Time to fill and iterate a vector of " 
                  << size << " ints : " << diff.count() << " s\n";
    }
}

### 2、Possible output:
```shell
Time to fill and iterate a vector of 1 ints : 2.43e-07 s
Time to fill and iterate a vector of 100 ints : 4.1e-07 s
Time to fill and iterate a vector of 10000 ints : 2.519e-05 s
Time to fill and iterate a vector of 1000000 ints : 0.00207669 s
Time to fill and iterate a vector of 100000000 ints : 0.423087 s
```
