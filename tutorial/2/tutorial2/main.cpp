#include <iostream>
//#include "class.h"
#include <string>

using namespace std;

class Person
{
private:
  string name;

public:
  int age;
  string universityRegistered;

  bool is_above_18(int age)
  {
    if (age > 18)
      return true;
  }

  bool is_under_40(int age)
  {
    if(age < 40)
      return true;
  }

  void graduate()
  {
      universityRegistered = "graduated";
  }

    Person(string name, int age, string universityRegistered)//constructor
    {
        this->name = name;
        this->age = age;
        this->universityRegistered = universityRegistered;
    }

};

class Team
{
private:
  string belong_to_university;

public:
    string name;
  Person* member[4];
  int captain_member_index;

  bool have_4_members()
  {
    if((member[0]) && (member[1]) && (member[2]) && (member[3]))
      return true;
    else
        cout << "the number of members in your team is not 4!" << endl;
  }

  float average_age()
  {
    float averageAge = 0;
    if (have_4_members())
      {
        for (int i=0; i<4; i++)
          averageAge += (member[i])->age; // member->age
        averageAge /= 4;
      }
        return averageAge;
  }

  bool valid_average_age()
  {
      if (average_age() < 25)
          return true;
      else
          return false;

  }

  Team(string name, string belong_to_university) //constructor
  {
      this->name = name;
      this->belong_to_university = belong_to_university;
  }
};


void join_member(Team& team, Person& member)
{
    for (int i=0; i<4;)
    {
        if(team.member[i])
            i++;
        else
            *team.member[i] = member;
    }
}

bool team_valid(Team team)
{
    if(team.valid_average_age())
        return true;
    else
        return false;
}

int main()
{
    Team imperial("Imperial","Imperial College");
    Person ivor("Ivor Bigbrain", 20, "Imperial College");
    Person prezza("Prezza Buzza", 18, "Imperial College");
    Person ivonna("Ivonna Singh", 25, "Imperial College");
    Person yuman("Yuman Google", 32, "Imperial College");

    join_member(imperial, ivor);
    join_member(imperial, prezza);
    join_member(imperial, ivonna);
    join_member(imperial, yuman);

    prezza.graduate();

    if (team_valid(imperial))
        cout << imperial.name << ": you have a qualified team!" << endl;
    else
        cout << imperial.name << ": your team is not qualified!" << endl;

   // return 0;
}
