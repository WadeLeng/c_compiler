#ifndef TABLE_H
#define TABLE_H

#include <string>
#define ACTION_INDEX_LENGTH 29
#define GOTO_INDEX_LENGTH 29
#define ACTION_TABLE_LENGTH 118
#define ACTION_TABLE_WIDTH 29
#define GOTO_TABLE_LENGTH 118
#define GOTO_TABLE_WIDTH 29
#define COPY_TOTAL_LENGTH 6844
#define COPY_TABLE_WIDTH 58

using namespace std;

class Table
{
public:
	Table();
	string action_index[ACTION_INDEX_LENGTH];
	string goto_index[GOTO_INDEX_LENGTH];
	string action_table[ACTION_TABLE_LENGTH][ACTION_TABLE_WIDTH];
	string goto_table[GOTO_TABLE_LENGTH][GOTO_TABLE_WIDTH];
};

#endif
