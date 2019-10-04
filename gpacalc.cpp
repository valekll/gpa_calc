#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Course {
public:
  Course() {
    subject = "";
    crn = "";
    grade = "";
    gpa = 0.0;
    hours = 0.0;
  } //Course()

  Course(std::string s, std::string c, std::string g, double h) {
    subject = s;
    crn = c;
    grade = g;
    gpa = gradeToGpa(g);
    hours = h;
  } //Course()

  Course(const Course& c) {
    subject = c.subject;
    crn = c.crn;
    grade = c.grade;
    gpa = gradeToGpa(c.grade);
    hours = c.hours;
  } //Course();
  
  double gradeToGpa(std::string g) const {
    std::string grades[] = {"A", "A-", "B+", "B", "B-",
			    "C+", "C", "C-", "D", "F"};
    double gpas[] = {4.0, 3.7, 3.3, 3.0, 2.7,
		     2.3, 2.0, 1.7, 1.0, 0.0};
    for(int i{0}; i < 10; i++) {
      if(g == grades[i]) {
	return gpas[i];
      } //if
    } //for
    return 0;
  } //gradeToGpa()

  std::string getName() const {
    return subject + " " + crn;
  } //getName()

  std::string getGrade() {
    return grade;
  } //getGrade()

  double getGpa() {
    return gpa;
  } //getGpa()

  double getHours() {
    return hours;
  } //getHours()

  double getQualityPoints() {
    return gpa * hours;
  } //getQualityPoints()

  friend std::ostream& operator<<(std::ostream& os, const Course c) {
    os << c.subject << " " << c.crn << "\t" << c.grade << "\t" << c.hours;
    return os;
  } //operator<<()

  Course& operator=(const Course& c) {
    subject = c.subject;
    crn = c.crn;
    grade = c.grade;
    gpa = gradeToGpa(c.grade);
    hours = c.hours;
    return *this;
  } //operator=()

  bool operator==(const Course& c) const {
    if(subject != c.subject || crn != c.crn) {
      return false;
    } //if
    return true;
  } //operator==()
  
  bool operator!=(const Course& c) const {
    return !this->operator==(c);
  } //operator!=()
  
  bool operator>(const Course& c) const{
    if(getName() > c.getName()) {
      return true;
    } //if
    return false;
  } //operator>()
  
  bool operator<(const Course& c) const {
    if(getName() < c.getName()) {
      return true;
    } //if
    return false;
  } //operator<()
  
  bool operator>=(const Course& c) const {
    return !this->operator<(c);
  } //operator>=()
  
  bool operator<=(const Course& c) const {
    return !this->operator>(c);
  } //operator<=()
  
private:
  std::string subject;
  std::string crn;
  std::string grade;
  double gpa;
  double hours;
}; //Course

int merge(std::vector<Course>& arr, int s, int p, int f) {
  int comp{0};

  int x = p - s + 1;
  std::vector<Course> left(x);
  int y = f - p;
  std::vector<Course> right(y);

  for(int i{0}; i < x; i++) {
    left[i] = arr[s + i];
  } //for
  
  for(int i{0}; i < y; i++) {
    right[i] = arr[p + 1 + i];
  } //for

  int i{0}, j{0}, k{s};

  while(i < x && j < y) {
    if(left[i] < right[j]) {
      arr[k] = left[i];
      i++;
    } //if
    else {
      arr[k] = right[j];
      j++;
    } //else
    comp++;
    k++;
  } //while

  while(i < x) {
    arr[k] = left[i];
    i++;
    k++;
  } //while

  while(j < y) {
    arr[k] = right[j];
    j++;
    k++;
  } //while
  
  return comp;
} //merge()

int mergeSort(std::vector<Course>& arr, int s, int f) {
  int comp{0};
  
  if(s < f) {
    int p = (s + f - 1) / 2;

    comp += mergeSort(arr, s, p);
    comp += mergeSort(arr, p + 1, f);

    comp += merge(arr, s, p ,f);
  } //if
  
  return comp;
} //mergeSort()

int main(int argc, char* args[]) {

  double totalHours{0};
  double qualityPoints{0};
  
  std::vector<Course> courses(0);
  std::string s;
  std::string c;
  std::string g;
  double h;

  for(int i{1}; i < argc; i++) { //take input file and get Courses
    std::ifstream inf;
    inf.open(args[i]);
    
    while(true) {
      inf >> s;
      if(s == "end") {
	break;
      } //if
      inf >> c;
      inf >> g;
      inf >> h;
      totalHours += h;
      Course tmp(s, c, g, h);
      courses.push_back(tmp);
    } //while
  } //for
  
  mergeSort(courses, 0, courses.size() - 1);
  
  for(int i{0}; i < courses.size(); i++) {
    qualityPoints += courses[i].getQualityPoints();
    std::cout << courses[i] << std::endl;
  } //for

  std::cout << std::endl;
  std::cout << "Quality Points: " << qualityPoints << std::endl;
  std::cout << "Total Hours: " << totalHours << std::endl;
  if(totalHours != 0) {
    double gpa = qualityPoints / totalHours;
    std::cout << "GPA: " << gpa << std::endl;
  } //if

  std::cout << std::endl;
  return 0;
} //main()
