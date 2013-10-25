#include<iostream>
#include<string>

using namespace std;

class Person
{
private: 
  int age;
  string name;

public:
  string universityRegistered;

  bool is_above_18(int age)
  {
    if (age > 18)
      return true;
  }

  bool is_under_40(int age)
  {
    if(age<40)
      return true;
  }

    Person(string name, int age, string unversityRegistered)//constructor
    {
        this->name = name;
        this->age = age;
        this->universityRegistered = universityRegistered;
    }

};

class Team
{
private:
  string name;
  string belong_to_university;

public:
  person* member[4];
  int captain_member_index;

  bool have_4_members(Person* member[])
  {
    if(*member[0] && *member[1] && *member[2] && *member[3])
      return true;
  }

  float average_age(person* member[])
  {
    float averageAge = 0;
    if (have_4_members(member))
      {
        for (int i=0; i<4; i++)
          averageAge += member[i] -> age; // member->age
        average /= 4;
      }
    return averageAge;
  }

  Team join_member(Person *member)
  {
      for (int i=0; i<4;)
      {
          if(*(this-> member[i]))
              i++;
          else
              this->member[i] = member;
      }
  }

  Team(string name, string belong_to_university) //constructor
  {
      this->name = name;
      this->belong_to_university = belong_to_university;
  }
};
