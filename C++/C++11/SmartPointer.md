# 智能指针 unique_ptr、shared_ptr、weak_ptr的用法示例
可以参考Youtube视频：[SMART POINTERS in C++ (std::unique_ptr, std::shared_ptr, std::weak_ptr)](https://www.youtube.com/watch?v=UOB7-B2MfwA)
C++代码示例如下：
```cpp
#include <iostream>
#include <memory>

class Entity
{
public:
	Entity()
	{
		std::cout << "Create Entity!" << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print()
	{
		std::cout << "hello Entity in Print() call" << std::endl;
	}
};


// SMART POINTERS in C++ (std::unique_ptr, std::shared_ptr, std::weak_ptr)
// https://www.youtube.com/watch?v=UOB7-B2MfwA
int main()
{
	{
		std::cout << "------------------------ Scope unique_ptr 001 --------------------" << std::endl;

		// unique_ptr 测试
		// std::unique_ptr<Entity> entity(new Entity()); // ok
		// std::unique_ptr<Entity> entity = new Entity(); // no 注意：unique_ptr 不能copy
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		// std::unique_ptr<Entity> entity02 = entity; // not ok  unique_ptr指针包装的实体不能被赋值，或者拷贝
		entity->Print();

		std::cout << "------------------------ End Scope unique_ptr 001 --------------------" << std::endl;
	}


	{
		std::cout << "------------------------ Scope shared_ptr 001 --------------------" << std::endl;

		// shared_ptr测试，注意：shared_ptr是基于引用计数机制的
		std::shared_ptr<Entity> sharedEntity1;
		{
			std::cout << "------------------------ Scope shared_ptr 002 --------------------" << std::endl;

			std::shared_ptr<Entity> sharedEntity0 = std::make_shared<Entity>();
			std::cout << "reference count: " << sharedEntity0.use_count() << std::endl; // 1
			sharedEntity1 = sharedEntity0; // // 注意：此处将shared_ptr的指针sharedEntity0，赋值给shared_ptr的指针sharedEntity1，sharedEntity0的引用计数会加1
			std::cout << "reference count: " << sharedEntity0.use_count() << std::endl; // 2
			
			std::cout << "------------------------ End Scope shared_ptr 002 --------------------" << std::endl;
		}

		std::cout << "reference count: " << sharedEntity1.use_count() << std::endl; // 1

		std::cout << "------------------------ End Scope shared_ptr 001 --------------------" << std::endl;
	}

	{
		std::cout << "------------------------ Scope weak_ptr and  shared_ptr 001 --------------------" << std::endl;

		// weak_ptr测试，注意：shared_ptr是基于引用计数机制的
		std::weak_ptr<Entity> weakEntity1;
		{
			std::cout << "------------------------ Scope weak_ptr and  shared_ptr 002 --------------------" << std::endl;

			std::shared_ptr<Entity> sharedEntity0 = std::make_shared<Entity>();
			std::cout << "reference count: " << sharedEntity0.use_count() << std::endl; // 1
			weakEntity1 = sharedEntity0; // 注意：此处将shared_ptr的指针sharedEntity0，赋值给weak_ptr的指针weakEntity1，sharedEntity0的引用计数并不会增加
			std::cout << "reference count: " << sharedEntity0.use_count() << std::endl; // 1

			std::cout << "------------------------ End Scope weak_ptr and  shared_ptr 002 --------------------" << std::endl;
		}

		std::cout << "reference count: " << weakEntity1.use_count() << std::endl; // 0

		std::cout << "------------------------ End Scope weak_ptr and  shared_ptr 001 --------------------" << std::endl;
	}


	std::cin.get();

	return 0;
}
```

执行结果如下：
```
------------------------ Scope unique_ptr 001 --------------------
Create Entity!
hello Entity in Print() call
------------------------ End Scope unique_ptr 001 --------------------
Destroyed Entity!
------------------------ Scope shared_ptr 001 --------------------
------------------------ Scope shared_ptr 002 --------------------
Create Entity!
reference count: 1
reference count: 2
------------------------ End Scope shared_ptr 002 --------------------
reference count: 1
------------------------ End Scope shared_ptr 001 --------------------
Destroyed Entity!
------------------------ Scope weak_ptr and  shared_ptr 001 --------------------
------------------------ Scope weak_ptr and  shared_ptr 002 --------------------
Create Entity!
reference count: 1
reference count: 1
------------------------ End Scope weak_ptr and  shared_ptr 002 --------------------
Destroyed Entity!
reference count: 0
------------------------ End Scope weak_ptr and  shared_ptr 001 --------------------
```
![image](https://github.com/ccf19881030/BlogArticles/assets/5925259/934a1fbb-4788-4b64-b3c4-a7202d5a7453)
