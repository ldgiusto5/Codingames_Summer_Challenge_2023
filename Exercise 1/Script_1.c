#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>
#include <locale.h>
#include <ctype.h>


/**
 * The score corresponding to each mutant
 */
typedef struct doubleEntry {
  char* key;
  double value;
} doubleEntry;
typedef struct doubleEntryList {
  int length;
  doubleEntry* items;
} doubleEntryList;

/**
 * @param mutant_scores The score corresponding to each mutant
 * @param threshold The score threshold above which mutants should be ignored
 * @return 
 */
char* bestRemainingMutant(doubleEntryList mutant_scores, int threshold) {
  // Write your code here (THIS FUNCTION IS MY CODE, THE REST OF THE CODE IS PART OF THE STATEMENT)
  int i = 0;
  int score = 0;
  while (i < mutant_scores.length)
  {
    if((mutant_scores.items[i].value) < threshold)
    {
      if ((mutant_scores.items[i].value) > score)
      {
        score = mutant_scores.items[i].value;
      }
    }
    i++;
  }
  i = 0;
  while ((mutant_scores.items[i].value) != score)
  {
    i++;
  }
  return (mutant_scores.items[i].key);
}

/* Ignore and do not change the code below */

void trySolution(char* output) {
  struct json_object *output_json;
  output_json = json_object_new_string(output);
  printf("%s\n", json_object_to_json_string_ext(output_json, 0));
  json_object_put(output_json);
}

int main () {
  setlocale(LC_ALL, "en_US.UTF-8");
  char *line;
  size_t len = 0;

  line = NULL;
  getline(&line, &len, stdin);
  struct json_object *parsed_json0 = json_tokener_parse(line);
  free(line);
  doubleEntryList mutant_scores;

  doubleEntryList map = {json_object_object_length(parsed_json0), malloc((sizeof(double) + sizeof(char*)) * map.length)};

  int counter = 0;
  json_object_object_foreach(parsed_json0, key, value) {
    map.items[counter].key = key;
    map.items[counter].value = json_object_get_double(value);
    counter++;
  }
  mutant_scores = map;

  line = NULL;
  getline(&line, &len, stdin);
  struct json_object *parsed_json1 = json_tokener_parse(line);
  free(line);
  int threshold;
  threshold = json_object_get_int(parsed_json1);

  json_object_put(parsed_json1);
  char* output = bestRemainingMutant(mutant_scores, threshold);

  trySolution(output);
}
/* Ignore and do not change the code above */
