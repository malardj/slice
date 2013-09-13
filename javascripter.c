//
// Object: This program attempts to make mechanized email snooping more difficult on a massive level
// by automated tools.
//
// This code is not intended to prevent anyone in particular from reading the original message which may
// be legal according to some court order but to force the reader to either execute a javascript from a
// trusted source or to unscramble the body of the message.
//
// How it works: massive text searches that work by replacing text with keyword signatures depend on
// being able to quickly identify and extract keywords in the message text. That harvesting of keywords
// is made harder if the text is broken at irregular random intervals unrelated to word boundaries and those
// frangments are scrambled inside the message body. The program translates the original message into
// javascript that produces the original message when it is run. There is no encryption and no exchange of
// passwords.
//
// What is the impact of having to run javascript? First one needs to trust the sender or scan the script
// for possible malware, then there is the computational costs. Loading the web page for the sample input
// takes over 1 milliseconds on my laptop, so 1% of all of the 294 billion emails that were exchanged per day
// in April 2010 would take 817 hours to just load into a browser.
//
// Limitations: There are many. This program only accept ASCII input and no HTML input. The program could be
// made more robust in many ways and the array of strings could be replaced by a spagetthi of function calls.
//
// This software is distributed for illustration purposes only under the Apache V2 License.
//
// Copyright Joel M. Malard September 12, 2013
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <string>
#include <ctime>
#include <vector>

#define BSIZE 4
#define LAMBDA (1.0/BSIZE)

/* based on : www.hscripts.com/tutorials/javascript/types.php */

using namespace std;

double unif(int i)
{
    if ( i== 0 ) {
        srand((unsigned)time(0));
    }
    return ((double) rand())/((double)RAND_MAX+1);
}

main(int argc, char ** argv)
{
    /* Read cin into a string */
    string myemail;

    if ( getline(cin,myemail) ) {
        string aline;
        while ( getline(cin,aline) ) {
            myemail += "<br>" + aline;
        }
    }

    /* slice the message at random intervals */
    int mylen = myemail.length();
    int myseg = (mylen<BSIZE) ? 1 : (mylen+1)/BSIZE;

    vector<string> myshorts;
    vector<string> testme;
    vector<int> mystarts;

    double u = -log(unif(0))/LAMBDA;
    int iu = (u<1.0) ? 1 : (int)u;
    int idx = 0, jdx = 0;;
    while ( idx < mylen ) {
        myshorts.push_back(myemail.substr(idx,iu));
        testme.push_back(myemail.substr(idx,iu));
        mystarts.push_back(jdx++);
        idx += iu;
        u = -log(unif(1))/LAMBDA;
        iu = (u<1.0) ? 1 : (int)u;
    }

    /* Scramble the message */
    int myl = myshorts.size();
    for ( int ix=0; ix<myl; ix++ ) {
        double ju = unif(1);
        int jx = ix + (myl-1-ix)*ju;
        swap(myshorts[ix],myshorts[jx]);
        swap(mystarts[ix],mystarts[jx]);
    }

    int *invert = new int[myl];
    for ( int ix=0; ix<myl; ix++ ) {
        invert[mystarts[ix]] = ix;
    }

    /* print javascript header */
    cout << "<html>\n";
    cout << "<head></head>\n";
    cout << "<body>\n\n";
    cout << "<script language=javascript>\n";
    cout << "alert(\"Email received: run Javascript?\");" << endl;


#if defined TIME_ME
    // cout << "var Start = new Date().getTime();" << endl;
#endif

    /* create normal variable */
    cout << "var myshorts = new Array();" << endl;

    /* print scrambled email text */
    for ( int i=0; i<myshorts.size(); i++ ) {
        cout << "myshorts[" << i << "] = \"" << myshorts[i] << "\";" << endl;
    }
    for ( int i=0; i<myshorts.size(); i++ ) {
        cout << "document.write(myshorts[" << invert[i] << "]);" << endl;
    }

#if defined TIME_ME
    cout << "var End = new Date().getTime();" << endl;
    cout << "var Time = End-Start;" << endl;
    cout << "alert(\"Execution time: \" + Time);" << endl;
#endif

    /* print javascript footer */
    cout << "</script>\n";
    cout << "</body>\n";
    cout << "</html>\n";

    /* clean up */
    delete[] invert;

    return 0;
}


