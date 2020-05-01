// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <string>
#include <memory>

#include "Property\Property.h"

using Int32 = signed __int32;
using Real32 = float;

class Person
{
public:
    Person()
    {
        Age = m_age;

        PreserveAge = m_age;

        ProxyAge.getStorage().BindGetFunc(std::bind(&Person::getAge, this));
        ProxyAge.getStorage().BindSetFunc(std::bind(&Person::setAge, this, std::placeholders::_1));
    }

    ~Person() = default;

    const Int32& getAge() const
    {
        return m_age;
    }

    void setAge(Int32 age)
    {
        m_age = age;
    }

    Property<Int32> Age;
    PreserveProperty<Int32> PreserveAge;
    ProxyProperty<Int32> ProxyAge;

private:
    Int32 m_age = 10;
};

////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
Int32 main()
{
    Int32 age = 0;
    Person person;

#pragma region Property �׽�Ʈ
    person.Age = 99;
    age = person.Age;
    
    printf("<Property �׽�Ʈ>\n");
    printf("age: %d\n", age);
    printf("person.getAge(): %d\n", person.getAge());
    printf("person.Age.get(): %d\n\n", person.Age.get());
#pragma endregion

#pragma region PreserveProperty �׽�Ʈ
    person.PreserveAge = 200;
    age = person.PreserveAge;

    printf("<PreserveProperty �׽�Ʈ>\n");
    printf("age: %d\n", age);
    printf("person.getAge(): %d\n", person.getAge());
    printf("person.Age.get(): %d\n\n", person.PreserveAge.get());
#pragma endregion

#pragma region ProxyProperty �׽�Ʈ
    person.ProxyAge = 555;
    age = person.ProxyAge;

    printf("<ProxyProperty �׽�Ʈ>\n");
    printf("age: %d\n", age);
    printf("person.getAge(): %d\n", person.getAge());
    printf("person.Age.get(): %d\n\n", person.ProxyAge.get());
#pragma endregion

	return 0;
}