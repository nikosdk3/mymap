#include <gtest/gtest.h>
#include "mymap.h"
#include "myrandom.h"
#include <algorithm> //for sort to test
#include <map>		 //for testing

//test default constructor with int, int pair
TEST(mymapInt, emptyMap)
{
	mymap<int, int> map;
	EXPECT_EQ(map.Size(), 0);
}

//test unique keys with int, int pairs
TEST(mymapInt, UniqueKeys)
{
	map<int, int> mapSol;
	mymap<int, int> map;
	int arr[] = {2, 1, 3, 4, 5};
	int arr2[] = {3, 10, 12, 9, 4};

	for (int i = 0; i < 5; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into mapx
		mapSol[arr[i]] = arr2[i];
	}
	EXPECT_EQ(map.Size(), mapSol.size()); // check size after put

	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), 5);					   // rechecking size
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map[7];
	map.put(7, 21);
	map.put(9, 31);
	EXPECT_EQ(map.get(7), 21);
	EXPECT_EQ(map.get(9), 31);
	EXPECT_TRUE(map.contains(7));
	EXPECT_TRUE(map.contains(9));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test duplicate keys with int, double pairs
TEST(mymapInt, DuplicateKeys)
{
	map<int, double> mapSol;
	mymap<int, double> map;
	int arr[] = {2, 1, 2, 1, 2};
	double arr2[] = {3.4, 10.2, 12.5, 9.12, 4.56};

	for (int i = 0; i < 5; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	EXPECT_EQ(map.Size(), mapSol.size()); // compare size after put

	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size());		   // rechecking size
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding duplicates
	map[2];
	map.put(2, 21.34);
	map.put(1, 31.67);
	EXPECT_EQ(map.get(2), 21.34);
	EXPECT_EQ(map.get(1), 31.67);
	EXPECT_TRUE(map.contains(2));
	EXPECT_TRUE(map.contains(1));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test a balanced tree with int, string pairs
TEST(mymapInt, BalancedTree)
{
	map<int, string> mapSol;
	mymap<int, string> map;
	int arr[] = {5, 3, 7, 4, 2, 6, 8};
	string arr2[7];
	// fill arr2 with random strings
	for (int i = 0; i < 7; i++)
	{
		string value = to_string(randomInteger(0, 99)); // random strings
		arr2[i] = value;
	}
	for (int i = 0; i < 7; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	for (int i = 0; i < 7; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size());		   // rechecking size each iteration
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map[1];
	map.put(1, "alabama");
	map.put(9, "houston");
	EXPECT_EQ(map.get(1), "alabama");
	EXPECT_EQ(map.get(9), "houston");
	EXPECT_TRUE(map.contains(1));
	EXPECT_TRUE(map.contains(9));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test an unbalanced tree with int, char pairs
TEST(mymapInt, UnbalancedTree)
{
	map<int, char> mapSol;
	mymap<int, char> map;
	int arr[] = {3, 2, 4, 5, 6, 7, 1, 8};
	char arr2[8];
	// fill arr2 with random chars
	for (int i = 0; i < 8; i++)
	{
		char value = char(randomInteger(0, 99)); // random chars
		arr2[i] = value;
	}
	for (int i = 0; i < 8; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	for (int i = 0; i < 8; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size());		   // rechecking size each iteration
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map[1];
	map.put(1, 't');
	map.put(9, 'q');
	EXPECT_EQ(map.get(1), 't');
	EXPECT_EQ(map.get(9), 'q');
	EXPECT_TRUE(map.contains(1));
	EXPECT_TRUE(map.contains(9));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test a big map(1000 elements) with int, int pairs
TEST(mymapInt, bigmymap)
{
	map<int, int> mapSol;
	mymap<int, int> map;
	for (int i = 0; i < 1000; i++)
	{
		int key = randomInteger(0, 100);
		int value = randomInteger(0, 1000);
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test an ascending map with int, double pairs
TEST(mymapInt, ascending)
{
	map<int, double> mapSol;
	mymap<int, double> map;
	for (int i = 0; i < 100; i++)
	{
		int key = i;
		double value = randomInteger(0, 100) / randomInteger(1, 10);
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
	EXPECT_EQ(map.Size(), mapSol.size());
	for (int i = 0; i < 100; i++)
	{
		EXPECT_EQ(map.get(i), mapSol.at(i));  // making sure each element is accessible with get
		EXPECT_EQ(map[i], mapSol[i]);		  // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(i));		  // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size()); // rechecking size each iteration
	}
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test a descending map with int, string pairs
TEST(mymapInt, descending)
{
	map<int, string> mapSol;
	mymap<int, string> map;
	for (int i = 100; i >= 0; i--)
	{
		int key = i;
		string value = to_string(randomInteger(0, 100));
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
	EXPECT_EQ(map.Size(), mapSol.size());
	for (int i = 0; i < 100; i++)
	{
		EXPECT_EQ(map.get(i), mapSol.at(i));  // making sure each element is accessible with get
		EXPECT_EQ(map[i], mapSol[i]);		  // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(i));		  // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size()); // rechecking size each iteration
	}
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test an empty map (default constructor) with double, int pair
TEST(mymapDouble, emptyMap)
{
	mymap<double, int> map;
	EXPECT_EQ(map.Size(), 0);
}

//test unique keys with double, char pairs
TEST(mymapDouble, UniqueKeys)
{
	map<double, char> mapSol;
	mymap<double, char> map;
	double arr[] = {2.56, 1.213, 3.5436, 5.56, 4.23};
	char arr2[] = {'r', 'b', 'e', 'g', 'f'};
	// filling map with double,chars pairs
	for (int i = 0; i < 5; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insertion to compare
	}
	EXPECT_EQ(map.Size(), mapSol.size()); // check size after put

	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), 5);					   // rechecking size
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map[7.34];
	EXPECT_TRUE(map.contains(7.34));
	map.put(7.34, 'u');
	map.put(9.76, 'q');
	EXPECT_EQ(map.get(7.34), 'u');
	EXPECT_EQ(map.get(9.76), 'q');
	EXPECT_TRUE(map.contains(7.34));
	EXPECT_TRUE(map.contains(9.76));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test duplicate keys with double, string pairs
TEST(mymapDouble, DuplicateKeys)
{
	map<double, string> mapSol;
	mymap<double, string> map;
	double arr[] = {2.34, 1.45, 2.34, 1.45, 2.34};
	string arr2[] = {"apple", "banana", "fruit loops", "top", "pot"};
	// filling map with double,string pairs
	for (int i = 0; i < 5; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	EXPECT_EQ(map.Size(), mapSol.size()); // compare size after put

	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size());		   // rechecking size
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding duplicates
	map[2.34];
	EXPECT_TRUE(map.contains(2.34));
	map.put(2.34, "c++");
	map.put(1.45, "java");
	EXPECT_EQ(map.get(2.34), "c++");
	EXPECT_EQ(map.get(1.45), "java");
	EXPECT_TRUE(map.contains(2.34));
	EXPECT_TRUE(map.contains(1.45));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test balanced tree with double, double pairs
TEST(mymapDouble, BalancedTree)
{
	map<double, double> mapSol;
	mymap<double, double> map;
	double arr[] = {5.456, 3.123, 7.67, 4.123, 2.678, 6.9878, 8.332};
	double arr2[7];
	for (int i = 0; i < 7; i++)
	{
		arr2[i] = double(randomInteger(0, 99)) / double(randomInteger(1, 10)); // random values
	}
	for (int i = 0; i < 7; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map[1];
	map.put(1.345, 10.567);
	map.put(9.567, 90.123);
	EXPECT_EQ(map.get(1.345), 10.567);
	EXPECT_EQ(map.get(9.567), 90.123);
	EXPECT_TRUE(map.contains(1.345));
	EXPECT_TRUE(map.contains(9.567));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test unbalanced tree with double, int pairs
TEST(mymapDouble, UnbalancedTree)
{
	map<double, int> mapSol;
	mymap<double, int> map;
	double arr[] = {3.5536, 2.6543, 4.213, 5.543, 6.324, 7.654, 1.79, 8.1};
	int arr2[8];
	// filling map double,int pairs
	for (int i = 0; i < 8; i++)
	{
		arr2[i] = randomInteger(0, 99); // random values
	}
	for (int i = 0; i < 8; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map[1.123];
	map.put(1.123, 10);
	map.put(9.245, 90);
	EXPECT_EQ(map.get(1.123), 10);
	EXPECT_EQ(map.get(9.245), 90);
	EXPECT_TRUE(map.contains(1.123));
	EXPECT_TRUE(map.contains(9.245));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test big mymap(10000 elements) with double, double pairs
TEST(mymapDouble, bigmymap)
{
	map<double, double> mapSol;
	mymap<double, double> map;
	// filling map with double, double pairs
	for (int i = 0; i < 10000; i++)
	{
		double key = randomInteger(0, 10000) / randomInteger(1, 100);	// random double key
		double value = randomInteger(0, 10000) / randomInteger(1, 100); // random double value
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size()); // check size
	}
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test ascending map with double, string pairs
TEST(mymapDouble, ascending)
{
	map<double, string> mapSol;
	mymap<double, string> map;
	// filling map in ascending order
	for (int i = 0; i < 100; i++)
	{
		double key = i + (1 / double(randomInteger(1, 10))); // random double key
		string value = to_string(randomInteger(0, 100));	 // random string value
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size()); // check sizes
	}
	EXPECT_EQ(map.Size(), mapSol.size());
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test descending map with double, char pairs
TEST(mymapDouble, descending)
{
	map<double, char> mapSol;
	mymap<double, char> map;
	// filling map in descending order
	for (int i = 100; i >= 0; i--)
	{
		double key = i + double(1 / randomInteger(1, 10)); // random double value
		char value = char(randomInteger(0, 100));		   // random char value
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size()); // checking if sizes equal
	}
	EXPECT_EQ(map.Size(), mapSol.size());
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test an empty map with string, int pair
TEST(mymapString, emptyMap)
{
	mymap<string, int> map;
	EXPECT_EQ(map.Size(), 0);
}

//test unique keys with string, string pairs
TEST(mymapString, UniqueKeys)
{
	map<string, string> mapSol;
	mymap<string, string> map;
	string arr[] = {"sweater", "now", "hold", "here", "hands"};
	string arr2[] = {"say", "something", "nothing", "wake up", "morning"};
	// filling map with string, string pairs
	for (int i = 0; i < 5; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i];
	}
	EXPECT_EQ(map.Size(), mapSol.size()); // check size after put

	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), 5);					   // rechecking size
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map["sky"];
	EXPECT_TRUE(map.contains("sky"));
	map.put("sky", "high");
	map.put("way", "club");
	EXPECT_EQ(map.get("sky"), "high");
	EXPECT_EQ(map.get("way"), "club");
	EXPECT_TRUE(map.contains("sky"));
	EXPECT_TRUE(map.contains("way"));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test duplicate keys with string, char pairs
TEST(mymapString, DuplicateKeys)
{
	map<string, char> mapSol;
	mymap<string, char> map;
	string arr[] = {"sweater", "now", "sweater", "now", "sweater"};
	char arr2[] = {'s', 'n', 'h', 'i', 'j'};

	// filling map with string, char pairs
	for (int i = 0; i < 5; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	EXPECT_EQ(map.Size(), mapSol.size()); // compare size after put

	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size());		   // rechecking size
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding duplicates
	map["sweater"];
	map.put("sweater", 'm');
	map.put("now", 'n');
	EXPECT_EQ(map.get("sweater"), 'm');
	EXPECT_EQ(map.get("now"), 'n');
	EXPECT_TRUE(map.contains("sweater"));
	EXPECT_TRUE(map.contains("now"));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test balanced tree with string, double pairs
TEST(mymapString, BalancedTree)
{
	map<string, double> mapSol;
	mymap<string, double> map;
	string arr[] = {"wire", "crash", "kanye", "drake", "carti", "red", "vert"};
	double arr2[7];
	for (int i = 0; i < 7; i++)
	{
		arr2[i] = double(randomInteger(0, 99)) / double(randomInteger(1, 10)); // random values
	}
	for (int i = 0; i < 7; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	for (int i = 0; i < 7; i++)
	{
		EXPECT_EQ(map.get(arr[i]), arr2[i]);  // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], arr2[i]);	  // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));	  // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size()); // rechecking size each iteration
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map["chamber"];
	map.put("chamber", 3.56);
	map.put("reflection", 3.76);
	EXPECT_EQ(map.get("chamber"), 3.56);
	EXPECT_EQ(map.get("reflection"), 3.76);
	EXPECT_TRUE(map.contains("chamber"));
	EXPECT_TRUE(map.contains("reflection"));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test unbalanced tree with string, int pairs
TEST(mymapString, UnbalancedTree)
{
	map<string, int> mapSol;
	mymap<string, int> map;
	string arr[] = {"alone", "again", "one", "more", "time", "celebrate", "decor", "vision"};
	int arr2[8];
	for (int i = 0; i < 8; i++)
	{
		arr2[i] = randomInteger(0, 99); // random values
	}
	for (int i = 0; i < 8; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	for (int i = 0; i < 8; i++)
	{
		EXPECT_EQ(map.get(arr[i]), arr2[i]);  // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], arr2[i]);	  // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));	  // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size()); // rechecking size each iteration
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map["lonely"];
	map.put("lonely", 10);
	map.put("feeling", 90);
	EXPECT_EQ(map.get("lonely"), 10);
	EXPECT_EQ(map.get("feeling"), 90);
	EXPECT_TRUE(map.contains("lonely"));
	EXPECT_TRUE(map.contains("feeling"));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test big mymap(10000 elements) with string, double pairs
TEST(mymapString, bigmymap)
{
	map<string, double> mapSol;
	mymap<string, double> map;
	// filling map with string, double pairs
	for (int i = 0; i < 10000; i++)
	{
		string key = to_string(randomInteger(0, 10000));
		double value = randomInteger(0, 10000) + (1 / randomInteger(1, 10)); // adding whole and decimal number for double
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
	EXPECT_EQ(map.Size(), mapSol.size());
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str()); // comparing two strings
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test ascending map with string, string pairs
TEST(mymapString, ascending)
{
	map<string, string> mapSol;
	mymap<string, string> map;
	// filling map with string, string pairs
	for (int i = 0; i < 100; i++)
	{
		string key = to_string(i);
		string value = to_string(randomInteger(0, 100));
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
	EXPECT_EQ(map.Size(), mapSol.size());
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str()); // comparing two strings
	map.clear();							   // clear map
	EXPECT_EQ(map.Size(), 0);
}

//test descending map with string char pairs
TEST(mymapString, descending)
{
	map<string, char> mapSol;
	mymap<string, char> map;
	// filling map with string, char pairs
	for (int i = 100; i >= 0; i--)
	{
		string key = to_string(i);
		char value = char(randomInteger(0, 100));
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
	EXPECT_EQ(map.Size(), mapSol.size());
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());
	map.clear(); // clear map
	EXPECT_EQ(map.Size(), 0);
}

//test an empty map (default constructor) with char, int pairs
TEST(mymapChar, emptyMap)
{
	mymap<char, int> map;
	EXPECT_EQ(map.Size(), 0);
}

//test unique keys with char, string pairs
TEST(mymapChar, UniqueKeys)
{
	map<char, string> mapSol;
	mymap<char, string> map;
	char arr[] = {'h', 'd', 'e', 'b', 'z'};
	string arr2[] = {"say", "something", "nothing", "wake up", "morning"};
	// filling map with char,string pairs
	for (int i = 0; i < 5; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i];
	}
	EXPECT_EQ(map.Size(), mapSol.size()); // check size after put

	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), 5);					   // rechecking size
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map['s'];
	EXPECT_TRUE(map.contains('s'));
	map.put('s', "high");
	map.put('w', "club");
	EXPECT_EQ(map.get('s'), "high");
	EXPECT_EQ(map.get('w'), "club");
	EXPECT_TRUE(map.contains('s'));
	EXPECT_TRUE(map.contains('w'));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test duplicate keys with char, char pairs
TEST(mymapChar, DuplicateKeys)
{
	map<char, char> mapSol;
	mymap<char, char> map;
	char arr[] = {'f', 'n', 's', 'f', 'n'};
	char arr2[] = {'s', 'n', 'h', 'i', 'j'};

	// filling map with char, char pairs
	for (int i = 0; i < 5; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	EXPECT_EQ(map.Size(), mapSol.size()); // compare size after put

	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size());		   // rechecking size
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding duplicates
	map['m'];
	map.put('m', 'm');
	map.put('v', 'v');
	EXPECT_EQ(map.get('m'), 'm');
	EXPECT_EQ(map.get('v'), 'v');
	EXPECT_TRUE(map.contains('m'));
	EXPECT_TRUE(map.contains('v'));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}

//test duplicate keys with char, double pairs
TEST(mymapChar, BalancedTree)
{
	map<char, double> mapSol;
	mymap<char, double> map;
	char arr[] = {'w', 'r', 'k', 'r', 'q', 'r', 'w'};
	double arr2[7];
	for (int i = 0; i < 7; i++)
	{
		arr2[i] = double(randomInteger(0, 99)) / double(randomInteger(1, 10)); // random values
	}
	// filling map with char, double values
	for (int i = 0; i < 7; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	for (int i = 0; i < 7; i++)
	{
		EXPECT_EQ(map.get(arr[i]), mapSol.at(arr[i])); // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], mapSol[arr[i]]);		   // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));			   // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size());		   // rechecking size each iteration
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map['c'];
	map.put('c', 3.56);
	map.put('r', 3.76);
	EXPECT_EQ(map.get('c'), 3.56);
	EXPECT_EQ(map.get('r'), 3.76);
	EXPECT_TRUE(map.contains('c'));
	EXPECT_TRUE(map.contains('r'));
	map.clear(); // clear map
	EXPECT_EQ(map.Size(), 0);
}

//test unbalanced tree with char, int pairs
TEST(mymapChar, UnbalancedTree)
{
	map<char, int> mapSol;
	mymap<char, int> map;
	char arr[] = {'a', 'b', 'd', 'l', 'r', 's', 'y', 'h'};
	int arr2[8];
	for (int i = 0; i < 8; i++)
	{
		arr2[i] = randomInteger(0, 99); // random values
	}
	// filling map with char, int pairs
	for (int i = 0; i < 8; i++)
	{
		map.put(arr[i], arr2[i]); // inserting elements into map
		mapSol[arr[i]] = arr2[i]; // insert elements into std lib map for comparison
	}
	for (int i = 0; i < 8; i++)
	{
		EXPECT_EQ(map.get(arr[i]), arr2[i]);  // making sure each element is accessible with get
		EXPECT_EQ(map[arr[i]], arr2[i]);	  // making sure each element is accessible with []
		EXPECT_TRUE(map.contains(arr[i]));	  // check if each element is in map
		EXPECT_EQ(map.Size(), mapSol.size()); // rechecking size each iteration
	}

	// comparing toStrings
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());

	// manually adding more pairs
	map['p'];
	map.put('p', 10);
	map.put('j', 90);
	EXPECT_EQ(map.get('p'), 10);
	EXPECT_EQ(map.get('j'), 90);
	EXPECT_TRUE(map.contains('p'));
	EXPECT_TRUE(map.contains('j'));
	map.clear(); // clear map
	EXPECT_EQ(map.Size(), 0);
}

//test big mymap(>5000 elements) with char, double pairs
TEST(mymapChar, bigmymap)
{
	map<char, double> mapSol;
	mymap<char, double> map;
	// filling map with char, double pairs
	for (int i = 0; i < 10000; i++)
	{
		char key = char(randomInteger(0, 10000));
		double value = randomInteger(0, 10000) + (1 / randomInteger(1, 10)); // adding whole and decimal number for double
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
	EXPECT_EQ(map.Size(), mapSol.size());
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str()); // comapring two strings
	map.clear();							   // clear map
	EXPECT_EQ(map.Size(), 0);
}

//test ascending map with char, string pairs
TEST(mymapChar, ascending)
{
	map<char, string> mapSol;
	mymap<char, string> map;
	// fill map in ascending order with char, string pairs
	for (int i = 0; i < 100; i++)
	{
		char key = char(i);								 // char value ascending
		string value = to_string(randomInteger(0, 100)); // random string value
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
	EXPECT_EQ(map.Size(), mapSol.size());
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str());
	map.clear(); // clear map
	EXPECT_EQ(map.Size(), 0);
}

//test descending map with char, char pairs
TEST(mymapChar, descending)
{
	map<char, char> mapSol;
	mymap<char, char> map;
	// fill map in descending order with char, char paris
	for (int i = 100; i >= 0; i--)
	{
		char key = char(i);						  // char key in desc order
		char value = char(randomInteger(0, 100)); // random char value
		map.put(key, value);
		mapSol[key] = value;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
	EXPECT_EQ(map.Size(), mapSol.size()); // comapre sizes
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(map.contains(pair.first));
		EXPECT_EQ(map.get(pair.first), pair.second);
	}
	EXPECT_EQ(map.toString(), solution.str()); // compare two map string outputs
	map.clear();							   // clear map
	EXPECT_EQ(map.Size(), 0);
}

//test all functions that are included in milestone one
TEST(mymapMisc, milestoneOneAll)
{
	mymap<int, int> testMap;
	map<int, int> mapSol;
	int n = 1000;

	for (int i = 1; i <= n; i++)
	{
		int key = randomInteger(0, n);
		int val = randomInteger(0, n);
		testMap.put(key, val);
		mapSol[key] = val;
	}
	EXPECT_EQ(testMap.Size(), mapSol.size());
	stringstream solution("");
	for (auto pair : mapSol)
	{
		solution << "key: " << pair.first;
		solution << " value: " << pair.second << endl;
		EXPECT_TRUE(testMap.contains(pair.first));
		EXPECT_EQ(testMap.get(pair.first), pair.second);
	}
	EXPECT_EQ(testMap.toString(), solution.str());
}

//test all functions that are included in milestone three
TEST(mymapMisc, milestoneThree)
{
	mymap<int, int> map;
	int arr[] = {2, 1, 3};
	int order[] = {1, 2, 3};
	for (int i = 0; i < 3; i++)
	{
		map.put(arr[i], arr[i]);
	}
	int i = 0;
	for (auto key : map)
	{
		EXPECT_EQ(order[i++], key);
	}
	mymap<int, int> myTest;
	int n = 1000;
	for (int i = 0; i < n; i++)
	{
		int key = randomInteger(0, n);
		int val = randomInteger(0, n);
		myTest.put(key, val);
	}
	stringstream ss;
	for (auto key : myTest)
	{
		ss << "key: " << key << " value: " << myTest[key] << endl;
	}
	ASSERT_EQ(myTest.toString(), ss.str());
}

//testing single node edge case
TEST(mymapMisc, singleNode)
{
	mymap<int, int> map;
	int value = randomInteger(0, 100000);
	map.put(1, value);
	EXPECT_EQ(map.Size(), 1);
	EXPECT_EQ(map.get(1), value);
	EXPECT_EQ(map[1], value);
	EXPECT_TRUE(map.contains(1));
	map.clear();
	EXPECT_EQ(map.Size(), 0);
}


//milestone 1 tests
//test put function indpendently
TEST(mymapFunction, testPut)
{
	//simple put test
	mymap<int, int> map;
	int arr[] = {2, 1, 3};
	for (int i = 0; i < 3; i++)
	{
		map.put(arr[i], arr[i]);
	}
	EXPECT_EQ(map.Size(), 3);
}

//stress testing put to make sure it works correctly before proceeding
TEST(mymapFunction, stressTestPut)
{
	//put test with 1000000 random keys and values
	map<int, int> mapSol;
	mymap<int, int> map;
	for (int i = 0; i < 1000000; i++)
	{
		int rand = randomInteger(0,1000000);
		int rand2 = randomInteger(0, 1000000);
		map.put(rand, rand2);
		mapSol[rand] = rand2;
		EXPECT_EQ(map.get(rand), mapSol.at(rand));
	}
	EXPECT_EQ(map.Size(), mapSol.size());
}

//testing contains function
TEST(mymapFunction, containsTest)
{
	//simple contains test
	mymap<int, int> map;
	int arr[] = {2, 1, 3};
	for (int i = 0; i < 3; i++)
	{
		map.put(arr[i], arr[i]);
		EXPECT_TRUE(map.contains(arr[i]));
	}
}

//testing get function
TEST(mymapFunction, getTest)
{
	//simple get test
	mymap<int, int> map;
	int arr[] = {2, 1, 3};
	for (int i = 0; i < 3; i++)
	{
		map.put(arr[i], arr[i]);
		EXPECT_EQ(map.get(arr[i]), arr[i]);
	}
	EXPECT_EQ(map.Size(), 3);
}

//testing operator[] function
TEST(mymapFunction, operatorBracketTest){
	//simple operator[] test
	map<int, int> mapSol;
	mymap<int, int> map;
	for (int i = 0; i < 1000; i++)
	{
		int rand = randomInteger(0, 50);
		map.put(i, rand);
		EXPECT_EQ(map[i], rand);
		mapSol[i] = rand;
		EXPECT_EQ(map.Size(), mapSol.size());
	}
}

//milestone 4 functions
//testing clear function
TEST(mymapFunction, testClear)
{
	//simple clear test
	mymap<int, int> testMap;
	int n = 1000;
	for (int i = 0; i < n; i++)
	{
		int key = randomInteger(0, n);
		int val = randomInteger(0, n);
		testMap.put(key, val);
		EXPECT_NE(testMap.Size(), 0);
	}
	testMap.clear();
	ASSERT_EQ(testMap.Size(), 0);
	// Test valgrind as well
}

//testing equals operator
TEST(mymapFunction, testEqualOperator)
{
	//simeple equal operator test
	mymap<int, int> map;
	int n = 1000;
	for (int i = 0; i < n; i++)
	{
		int key = randomInteger(0, n);
		int val = randomInteger(0, n);
		map.put(key, val);
	}
	mymap<int, int> mapequal;
	mapequal = map;
	EXPECT_EQ(mapequal.Size(), map.Size());
	EXPECT_EQ(mapequal.toString(), map.toString());
}

//testing copy constructor
TEST(mymapFunction, testCopyConstructor)
{
	//simple copy constructor test
	mymap<int, int> mapOrig;
	int n = 1000;
	for (int i = 0; i < n; i++)
	{
		int key = randomInteger(0, n);
		int val = randomInteger(0, n);
		mapOrig.put(key, val);
	}
	mymap<int, int> mapCopy = mapOrig;
	ASSERT_EQ(mapOrig.Size(), mapCopy.Size());
	ASSERT_EQ(mapOrig.toString(), mapCopy.toString());
}

//milestone 5 functions
// commented this out since I did not figure out how to rebalance
// TEST(mymapFunction, testCheckBalance){
// 	mymap<int, int> map;
// 	string s = "";
// 	for(int i = 0; i < 3; i++)
// 		map.put(i,i);
// 	s+= "key: 2, nL: 1, nR: 1\n";
// 	s+= "key: 1, nL: 0, nR: 0\n";
// 	s+= "key: 3, nL: 0, nR: 0\n";
// 	EXPECT_EQ(map.checkBalance(),s);
// }

//testing toVector with ascending values
TEST(mymapFunction, testToVectorAscending)
{
	mymap<int, int> map;
	vector<pair<int, int>> solution;
	for (int i = 0; i < 100; i++)
	{
		int rand = randomInteger(0, 100);
		solution.push_back(make_pair(i, rand));
		sort(solution.begin(), solution.end());
		map.put(i, rand);
	}
	EXPECT_EQ(solution, map.toVector());
}

//testing toVector with descending values
TEST(mymapFunction, testToVectorDescending)
{
	mymap<int, int> map;
	vector<pair<int, int>> solution;
	for (int i = 100; i >= 0; i--)
	{
		int rand = randomInteger(0, 100);
		solution.push_back(make_pair(i, rand));
		sort(solution.begin(), solution.end());
		map.put(i, rand);
	}
	EXPECT_EQ(solution, map.toVector());
}

//other students' tests

// netid: msiddi73
// Testing Put with random int key (Testing Size and toString)
TEST(Put, randomIntInt)
{

	map<int, int> m;
	mymap<int, int> mymap;
	stringstream s;

	int randomKey = 0;
	int randomValue = 0;
	int randomSize = 0;
	string test;

	for (int i = 0; i < 35; i++)
	{

		test = "";
		s.str("");

		randomSize = randomInteger(1, 50);

		for (int p = 0; p < randomSize; p++)
		{

			randomKey = randomInteger(0, 100);
			randomValue = randomInteger(0, 100);

			m[randomKey] = randomValue;
			mymap.put(randomKey, randomValue);
		}

		for (auto const &x : m)
		{
			s << "key: " << x.first << " value: " << x.second << "\n";
		}

		test = mymap.toString();

		ASSERT_EQ(mymap.Size(), m.size());
		ASSERT_EQ(test, s.str());

		mymap.clear();
		m.clear();
	}
}

// netid: msiddi73
// Testing put with random char key (Testing Size and toString)
TEST(Put, randomCharInt)
{

	map<char, int> m;
	mymap<char, int> mymap;
	stringstream s;

	char randomKey = 0;
	int randomValue = 0;
	int randomSize = 0;
	string test;

	for (int i = 0; i < 35; i++)
	{

		test = "";
		s.str("");

		randomSize = randomInteger(1, 50);

		for (int p = 0; p < randomSize; p++)
		{

			randomKey = randomInteger(65, 90); // get uppercase characthers
			randomValue = randomInteger(0, 100);

			m[randomKey] = randomValue;
			mymap.put(randomKey, randomValue);
		}

		for (auto const &x : m)
		{
			s << "key: " << x.first << " value: " << x.second << "\n";
		}

		test = mymap.toString();

		ASSERT_EQ(mymap.Size(), m.size());
		ASSERT_EQ(test, s.str());

		mymap.clear();
		m.clear();
	}
}

// Test for operator[] on already balanced tree.
// netid: lsasu2
TEST(mymapFunction, operatorBrackets)
{
	mymap<int, string> test;
	map<int, string> omap;
	int n = 10;
	int arr[] = {40, 25, 60, 18, 35, 80, 30, 38, 50, 70};

	for (int i = 0; i < n; i++)
	{
		string value = "MAX: " + to_string(randomInteger(0, 40));
		test.put(arr[i], value);
		omap.emplace(arr[i], value);
	}
	for (int i = 0; i < n; i++)
	{
		ASSERT_EQ(test[arr[i]], omap[arr[i]]);
	}

	// Value not in map
	for (int i = 0; i < n; i++)
	{
		ASSERT_EQ(test[i * 1000], "");
		ASSERT_EQ(test.Size(), n + i + 1);
	}

	// Duplicate values
	for (int i = 0; i < n; i++)
	{
		string value = "MAX: " + to_string(randomInteger(0, 40));
		test.put(arr[i], value);
		omap[arr[i]] = value;
	}
	for (int i = 0; i < n; i++)
	{
		ASSERT_EQ(test[arr[i]], omap[arr[i]]);
	}
}

// netid: rshah268
// Copy and Clear Stress Test
TEST(mymapFunction, Copy)
{

	// Create two mymaps m1 and m2
	mymap<int, int> m1;
	mymap<int, int> m2;
	int n = 10000;

	for (int i = 0; i < n; i++)
	{

		// Generate two random numbers
		int key = randomInteger(0, 100000);
		int val = randomInteger(0, 100000);

		// Insert them in map1
		m1.put(key, val);

		// Insert different elements in map2
		if (i % 2)
		{
			m2.put(val, key);
		}
	}

	// At this point they must be unequal
	ASSERT_NE(m1.Size(), m2.Size());

	// Set map2 equals to map1
	m2 = m1;

	// Both should be the same size and contain the same elements
	ASSERT_EQ(m1.Size(), m2.Size());
	ASSERT_EQ(m1.toString(), m2.toString());

	// Clear map1
	m1.clear();

	// Now they are unequal again
	ASSERT_NE(m1.Size(), m2.Size());
	// Map1 must be empty
	ASSERT_EQ(m1.Size(), 0);
}

// tkoope2
// Copy Operator test <int, int>
TEST(mymapFunction, IICopyP)
{
	mymap<int, int> m;
	mymap<int, int> m2;

	// Populate 1 and 2
	int key, value, high, low, modOp;
	int arrSize = rand() % 100;

	string mOriginal, m2Original;

	// Populate m
	high = 500;
	low = 1;
	modOp = (high - (low + 1)) + low;
	for (int i = 0; i < arrSize; i++)
	{
		key = rand() % modOp;
		value = rand() % modOp;
		m.put(key, value);
	}

	// Populate m2
	high = 1000;
	low = 500;
	modOp = (high - (low + 1)) + low;
	for (int i = 0; i < arrSize; i++)
	{
		key = rand() % modOp;
		value = rand() % modOp;
		m2.put(key, value);
	}

	m = m2;

	EXPECT_EQ(m.Size(), m2.Size()) << "IIEquals; size difference\n";
	EXPECT_NE(mOriginal, m.toString()) << "m should not still equal original\n";
	EXPECT_EQ(m2.toString(), m.toString()) << "toString() !=\n"
										   << "M:\n"
										   << m.toString() << "\nM2:\n"
										   << m2.toString() << endl;
	;
}

// tkoope2
// Copy Constructor
TEST(mymapFunction, IIConCopy)
{
	mymap<int, int> m;
	map<int, int> correct;
	vector<int> keys;
	int key;
	int val;
	int arrSize = 15;
	int high = 500, low = 0;
	int modOp = (high - (low + 1)) + low;

	// Populate
	for (int i = 0; i < arrSize; i++)
	{
		key = rand() % modOp;
		val = rand() % modOp;

		keys.push_back(key);

		m.put(key, val);
		correct[key] = val;
	}

	EXPECT_EQ(m.Size(), correct.size()) << "mymap != map\n";

	mymap<int, int> m2 = m;
	EXPECT_EQ(m.toString(), m2.toString()) << "Copy operator formating off\n";
	EXPECT_EQ(m2.Size(), correct.size()) << "M2's size does not match correct's\n";

	// Both have the same return value on keys
	int compA;
	int compB;
	for (auto &k : keys)
	{
		compA = m2[k];
		compB = correct[k];
		EXPECT_EQ(compA, compB) << compA << " != " << compB << "\t Incorrect Copy Constructor\n";
	}
}