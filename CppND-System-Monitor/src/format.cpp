#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long int totalSecs)
{
  char buffer[10];
  // int day = floor(totalSecs / 86400);
  // int rem = totalSecs % 86400;
  int hours = totalSecs / 3600;
  int rem = totalSecs % 3600;
  int mins = rem / 60;
  int secs = rem % 60;

  for (int i = 0; i < 10; i++) {
    buffer[i] = 0;
  }
  sprintf(buffer,"%02d:%02d:%02d", hours, mins, secs);

  return string(buffer);
}