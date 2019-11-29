#include "query.pb.h"

#include <string>
#include <cassert>
#include <iostream>
using namespace std;

//typedef muduo::Query T;

using namespace ::google::protobuf;

typedef std::shared_ptr<google::protobuf::Message> MessagePtr;

// createMessage(const std::string& typeName)返回的是动态创建的对象的指针，调用方有责任释放它，不然会出现内存泄漏
google::protobuf::Message* createMessage(const std::string& typeName)
{
	google::protobuf::Message* message = NULL;
	const google::protobuf::Descriptor* descriptor = 
		google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
	if (descriptor)
	{
		const google::protobuf::Message* prototype =
			google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
		if (prototype)
		{
			message = prototype->New();
		}
	}
	return message;
}


void testQuery()
{
	muduo::Query query;
	query.set_id(1);
	query.set_questioner("Cao Chufeng");
	query.set_question("Running?");

	muduo::Answer answer;
	answer.set_id(1);
	answer.set_questioner("Cao Chufeng");
	answer.set_answerer("blog.csdn.net/ccf19881030");
	answer.add_solution("Jump!");
	answer.add_solution("Win!");
}

int main(int argc, char* argv[])
{
	std::string type_name = muduo::Query::descriptor()->full_name();
	std::cout << type_name << std::endl;

	const ::google::protobuf::Descriptor* descriptor = ::google::protobuf::DescriptorPool::generated_pool()
		->FindMessageTypeByName(type_name);
	assert(descriptor == muduo::Query::descriptor());
	cout << "FindMessageTypeByName() = " << descriptor << endl;
	cout << "muduo::Query::descriptor() = " << muduo::Query::descriptor() << endl;
	cout << endl;

	const ::google::protobuf::Message* prototype = ::google::protobuf::MessageFactory::generated_factory()
						->GetPrototype(descriptor);
	assert(prototype == &muduo::Query::default_instance());
	cout << "GetPrototype() = " << prototype << endl;
	cout << "&muduo::Query::default_instance() = " << &muduo::Query::default_instance() << endl;
	cout << endl;

	muduo::Query* new_obj = dynamic_cast<muduo::Query*>(prototype->New());
	assert(new_obj != NULL);
	assert(new_obj != prototype);
	assert(typeid(*new_obj) == typeid(muduo::Query::default_instance()));
	cout << "prototype->New() = " << new_obj << endl;
	cout << endl;
	delete new_obj;

	google::protobuf::Message* newQuery = createMessage("muduo.Query");
	assert(newQuery != NULL);
	assert(typeid(*newQuery) == typeid(muduo::Query::default_instance()));
	cout << "createMessage(\"muduo.Query\") = " << newQuery << endl;

	testQuery();

	getchar();
	
	return 0;
}
