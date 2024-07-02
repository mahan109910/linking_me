#include "person.h"

Person::Person(const std::string &id, const std::string &phone, const std::string &email, const std::string &firstName, const std::string &lastName)
    : Account_ID(id), Phone_number(phone), Email(email), First_name(firstName), Last_name(lastName)
{
}
