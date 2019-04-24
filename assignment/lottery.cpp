/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "lottery.h"
#include <string.h>
#include <stdlib.h>

static FILE* stream;
static char separator;
static int digits[TIP_SIZE];

bool init_lottery(const char *csv_file, char csv_separator)
{
  stream = fopen(csv_file, "r");

  if (stream == 0)
  {
    return false;
  }

  for (int i = 0; i < TIP_SIZE; i++)
  {
    digits[i] = 0;
  }

  separator = csv_separator;
  return true;
}

bool get_tip(int tip_number, int tip[TIP_SIZE])
{
  if (tip_number < 0 || tip_number >= 44)
  {
      return false;
  }

  int index = 0;
  char line[MAX_LINE_LEN];

  while ( fgets(line, MAX_LINE_LEN, stream) != 0)
  {
      if (index == tip_number)
        {
          if(line == 0)
          {
            return 0;
          }

          index = 0;
          char seperatorTemp[2];
          seperatorTemp[0] = separator;
          seperatorTemp[1] = '\0';
          char* pLine = strtok(line, seperatorTemp);

          while(pLine != 0)
          {
              pLine = strtok(0, seperatorTemp);

              if (pLine == 0)
              {
                break;
              }
              if (atoi(pLine) > 0 && atoi(pLine) <= 45)
              {
                tip[index] = atoi(pLine);
              }
              index++;
          }

          rewind(stream);
          return true;
        }

        index++;

    }

  return false;
}

bool set_drawing(int drawing_numbers[TIP_SIZE])
{
  for (int i = 0; i < TIP_SIZE; i++)
  {
    if (drawing_numbers[i] <= 0 || drawing_numbers[i] > 45)
    {
      return false;
    }
    else
    {
      digits[i] = drawing_numbers[i];
    }
  }
  return true;
}

bool isEmpty(int numbers[]);

int get_tip_result(int tip_number)
{
  if (tip_number < 0 || tip_number >= 44)
  {
    return -2;
  }
  if (isEmpty(digits))
  {
    return -1;
  }

  int tip[TIP_SIZE];
  int result = 0;
  get_tip(tip_number,tip);

  for (int i = 0; i < TIP_SIZE; i++)
  {
    for (int j = 0; j < TIP_SIZE; j++)
    {
      if (digits[i] == tip[j])
      {
        result++;
      }
    }
  }
  return result;
}

bool isEmpty(int numbers[])
{
    for (int i = 0; i < TIP_SIZE; ++i)
    {
        if (numbers[i] != 0) return false;
    }

    return true;
}

int get_right_tips_count(int right_digits_count)
{
  if (right_digits_count < 0 || right_digits_count > TIP_SIZE || isEmpty(digits))
  {
      return -1;
  }
  int count = 0;
  int temp = 0;
  for (int i = 0; i < 44; ++i)
  {
      temp = get_tip_result(i);

      if (temp == right_digits_count)
      {
        count++;
      }
  }
  return count;

}
