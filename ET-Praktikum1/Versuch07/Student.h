//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXVI
//////////////////////////////////////////////////////////////////////////////

#ifndef STUDENT_H_
#define STUDENT_H_

#include <ostream>
#include <string>

/**
 * @brief Speichert die Daten eines Studenten.
 */
class Student
{
public:
    Student();
    Student(unsigned int matNr, std::string name, std::string geburtstag, std::string address);
    unsigned int getMatNr() const;
    std::string getName() const;
    std::string getGeburtstag() const;
    std::string getAdresse() const;
    void ausgabe(std::ostream& ausgabe) const;
    bool operator<(const Student& andererStudent) const;
    bool operator>(const Student& andererStudent) const;
    bool operator==(const Student& andererStudent) const;
private:
    unsigned int matNr;
    std::string name;
    std::string geburtstag;
    std::string adresse;
};

std::ostream& operator<<(std::ostream& ausgabe, const Student& student);

#endif
