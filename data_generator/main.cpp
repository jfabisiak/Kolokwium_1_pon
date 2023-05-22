#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <algorithm>
#include <random>

using namespace std;

int main(int argc, char *argv[])
{
    // Settings strings
    string sett_option = "-s";
    
    // Settings values
    string sett_file = "";

    // Values read from file
    int xval  = 0;
    int yval  = 0;

    // parsing command line args
    for(int i=0; i<argc; ++i)
    {
        if(sett_option.compare(argv[i]) == 0) // setting file
        {
            sett_file = argv[i+1];
            if(filesystem::exists(sett_file)) // file exists, read settings
            {
                ifstream myfile(sett_file); // open file as an input stream
                std::string line;
                while( getline(myfile, line) ) // go through all lines
                {
                    if(line[0] == '#') continue; // skip comments
                    if(line.find_first_of('=') != string::npos) // consider only if there is a '='
                    {
                        istringstream is_line(line); // to use with getline
                        std::string key, value;
                        getline(is_line, key, '='); // first, get the key
                        getline(is_line, value, '='); // get the value
                        key.erase (remove (key.begin(), key.end(), ' '), key.end()); // get rid of whitespaces
                        if(key.compare("P") == 0) xval = stod(value); // string to double, whitespaces removed
                        else if(key.compare("N") == 0) yval = stod(value);
                        else { cout << key << " " << " with vaue " << value << " is not regcognized" << '\n'; }
                    }
                }
                myfile.close();
            }
            else cout << "Setting file " << sett_file << "does not exist, using defaults" << '\n';
	    if(xval>4)
	    {
		cout << "Too much parameters requested, using defaults" << '\n';
		xval=0;
	    }
	if(xval<0||yval<0)
	{
	cout << "Negative parameters number requested, resetting to defaults" << '\n';
		xval=0;
		yval=0;
	}
        }
    }

    // sum up the settings
    cout << "===== Starting data generation =====" << '\n';
    cout << "Parameters in set number:\t" << xval << '\n';
    cout << "Parameters sets generated:\t" << yval << '\n';

    // File to store to
    ofstream myfile; // open output stream
    myfile.open ("data.dat"); // file to store results
    myfile << "# Generating data\n"
           << "# Input: " << xval << " " << yval << '\n';
    myfile.flush();
	int c1=0;
	int c2=1;
	if(xval>0)
        myfile << "NAME ";
	if(xval>1)
	myfile <<  "A ";
	if(xval>2)
	myfile <<"B ";
	if(xval==4)
	myfile <<"N ";	
        myfile << '\n';
    for(int i=0;i<yval;i++)
	{
	if(i%20==0)
	c2++;
	if(i%10==0)
	c1++;
	if(xval>0)
        myfile << "set_" << i+1 << " ";
	if(xval>1)
	myfile << i%10+1 << " ";
	if(xval>2)
	myfile << c1 << " ";
	if(xval==4)
	myfile << c2 << " ";	
        myfile << '\n';
        
	}
        myfile.flush();
    cout << "Data generated Succesfully";

    // Tidy up
    myfile.close();
    return 0;
}
