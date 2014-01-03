
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace std;
const int MAXFILENAME = 100;
struct Length
{
    int minutes;                            // #minuten  (0..)
    int seconds;                            // #seconden (0..59)
};

struct Track
{
    string artist;                          // naam van uitvoerende artiest
    string cd;                              // titel van cd
    int    year;                            // jaar van uitgave
    int    track;                            // nummer van track
    string title;                           // titel van track
    string tags;                            // tags van track
    Length time;                            // lengte van track
    string country;                         // land van artiest
};

struct TrackDisplay
{
    bool showArtist;                        // toont artist als true
    bool showAlbum;                            // toont cd titel als true
    bool showYear;                            // toont year als true
    bool showTrack;                            // toont track nr als true
    bool showTitle;                            // toont track titel als true
    bool showTags;                          // toont tags als true
    bool showLength;                        // toont track lengte als true
    bool showCountry;                       // toont country als true
};

bool match (string sub, string source)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    Resultaat is true alleen als sub een letterlijke (case-sensitive) deelstring is van source.
*/
    return source.find(sub) != string::npos ;
}

ostream& operator<< (ostream& out, const Length lengte)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    de waarde van lengte is getoond via out in de vorm: minuten, ':', seconden (tenminste 2 digits)
*/
    out << lengte.minutes << ':' << lengte.seconds;
    return out;
}

istream& operator>> (istream& in, Length& lengte)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    de waarde van lengte is ingelezen uit in: eerst minuten, daarna ':', daarna seconden.
*/
    char token;
    in >> lengte.minutes >> token >> lengte.seconds;
    return in;
}

Length operator+ (const Length& a, const Length& b)
{// Preconditie:
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*  Postconditie:
    Resultaat is de som van a en b.
*/
    Length sum = a;
    sum.minutes += b.minutes;
    sum.seconds += b.seconds;
    return sum;
}

void show_track (Track lied,TrackDisplay lt)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    alleen die members van lied zijn getoond waarvan de corresponderende member in lt de waarde true heeft.
*/
    if (lt.showArtist)
        cout << "Artist: "<< lied.artist << endl;
    if (lt.showAlbum)
        cout << "Album: "<< lied.cd << endl;
    if (lt.showYear)
        cout << "Year: "<< lied.year << endl;
    if (lt.showTrack)
        cout << "Track: "<< lied.track << endl;
    if (lt.showTitle)
        cout << "Title: "<< lied.title << endl;
    if (lt.showTags)
        cout << "Tags: "<< lied.tags << endl;
    if (lt.showLength)
       cout << "Time: "<< lied.time << endl;
    if (lt.showCountry)
       cout << "Country: "<< lied.country << endl;
}

bool open_dbfile (ifstream& infile)
{
    // Preconditie:
     assert (!infile.is_open()) ;
/*  Postconditie:
    File wordt geopend als hij nog niet open is.
*/
    infile.open ("Nummers.txt");
    return infile.is_open ( ) ;
}

istream& operator>> (istream& in, Track& track)
{// Preconditie:
   assert (true) ;
/*  Postconditie:
    De inhoud van de eerstvolgende 8 regels uit infile zijn gelezen en omgezet naar de corresponderende members in track.
    De daaropvolgende (lege) regel uit infile is ook gelezen.
*/
    char a;
    in.get(a);
    while (a != '\n')
    {
        track.artist += a;
        in.get(a);
    }
    in.get(a);
    while (a != '\n')
    {
        track.cd += a;
        in.get(a);
    }
    in >> track.year;
    in >> track.track;
    in.get(a);
    in.get(a);
    while (a != '\n')
    {
        track.title += a;
        in.get(a);
    }
    in.get(a);
    while (a != '\n')
    {
        track.tags += a;
        in.get(a);
    }
    in >> track.time;
    in.get(a);
    in.get(a);
    while (a != '\n')
    {
        track.country += a;
        in.get(a);
    }
    in.get(a);
    return in;
}

const int MAX_NR_OF_TRACKS = 5000;
typedef Track MusicdB [MAX_NR_OF_TRACKS];
MusicdB MusicDB;

void read_database()
{
    ifstream infile;
    if (!open_dbfile(infile))
        cout << "File could not be opened.";
    else
    {
            Track track;
            for(int nr =1; nr <= MAX_NR_OF_TRACKS; nr++)
            {
                infile >> track;
                show_track(track, {false, false, false, false,true,false, false, false });
                cout << nr << endl;
                if (infile >> track.artist == NULL)
                {
                    cout << "Total tracks counted: " << nr;
                    break;
                }
                track.artist = ""; track.cd = ""; track.title = ""; track.tags = ""; track.country = "";
            }
    }
}

enum Command {track = 1, artist, cd, cdsA, cds, timing, stop};

Command string_to_enum (char Option [MAXFILENAME])
{
    //Precondition:
    assert(true);
    /*Postcondition:
    De input zorgt er voor dat je de juiste optie kiest.
    */
    if(strcmp(Option, "track") == 0)
        return track;
    if(strcmp(Option, "artist") == 0)
        return artist;
    if(strcmp(Option, "cd") == 0)
        return cd;
    if(strcmp(Option, "cds") == 0)
        return cdsA;
    if(strcmp(Option, "#cds") == 0)
        return cds;
    if(strcmp(Option, "time") == 0)
        return timing;
    if(strcmp(Option, "stop")==0)
        return stop;
}

void comparison(char searchtrack[MAXFILENAME])
{
    //Precondition:
    assert(MAXFILENAME>0);
    /*Postcondition:
    Displays all tracks whos name matches the search-term, will also show the number of tracks found.
    */
    int counter = 0;
    TrackDisplay TD={true,true,true,true,true,true,true,true};
    for(int i = 0 ;i < MAX_NR_OF_TRACKS; i++)
    {
        if(match(searchtrack, MusicDB[i].title))
        {
            show_track(MusicDB[i], TD);
            counter ++;
        }
    }
    cout<<"Number of tracks found: "<< counter <<endl;
}


void optionTrack()
{
    //Precondition:
    assert(true);
    /*Postcondition:
    Hier wordt de zoekterm voor void comparison gegeven.
    */
    bool finished=false;
    int counter = 0;
    char searchtrack[MAXFILENAME];
    cin.get(); //Picks up space.
    while(!finished && counter < MAXFILENAME)
    {
        searchtrack[counter]= cin.get();
        if(searchtrack[counter]=='\n')
        {
            searchtrack[counter]='\0';
            finished = true;
        }
        counter++;
    }
    comparison(searchtrack);
}

void optionArtist()
{
    //Precondition:
    assert(true);
    /*Postcondition:
    Zoekt alle artiesten met naam gelijk aan de zoekopdracht en laat zien hoeveel er gevonden zijn
    */
    char searchArtist[MAXFILENAME];
    bool finished = false;
    int counter;
    string compareArtist[MAXFILENAME];
    int counter2 = 0;
    cin.get();
    while (!finished && counter < MAXFILENAME)
    {
        searchArtist[counter] = cin.get();
        if (searchArtist[counter] == '\n')
        {
            searchArtist[counter] = '\0';
            finished = true;
        }
        counter++;
    }

    for (int i = 0; i < MAX_NR_OF_TRACKS; i++)
    {
        if (match(searchArtist, MusicDB[i].artist))
        {
            bool knownartist = false;
            for (int ka = 0; ka < MAXFILENAME; ka++)
            {
                if (match(MusicDB[i].artist, compareArtist[ka]))
                {
                    knownartist = true;
                    break;
                }
            }
            if (!knownartist)
            {
                cout<<"Artist: "<<MusicDB[i].artist<<endl;
                compareArtist[counter2]=MusicDB[i].artist;
                counter2++;
            }
        }
    }
    cout<<"The number of artists is "<<counter2<<endl;
}

void optionCD()
{
   //Precondition:
    assert(true);
    /*Postcondition:
    Laat alle cd's zien die voldoen aan de zoekterm.
    */
    char searchCD[MAXFILENAME];
    bool finished=false;
    int counter = 0;
    string compareCD[MAXFILENAME];
    int counter2=0;
    cin.get();
    TrackDisplay TD={true,true,true,false,false,false,false,false};

    while(!finished && counter < MAXFILENAME)
    {
        searchCD[counter]= cin.get();
        if(searchCD[counter]=='\n')
        {
            searchCD[counter]='\0';
            finished = true;
        }
        counter++;
    }

    for(int i = 0 ;i < MAX_NR_OF_TRACKS; i++)
    {
        if(match(searchCD, MusicDB[i].cd))
        {
            bool knownCD = false;
            for(int kcd = 0; kcd < MAXFILENAME; kcd++)
            {
                if(match(MusicDB[i].cd, compareCD[kcd]))
                {
                    knownCD = true;
                    break;
                }
            }
            if(!knownCD)
            {
                show_track(MusicDB[i], TD);
                compareCD[counter2]=MusicDB[i].cd;
                counter2++;
            }
        }
    }
    cout<<"The number of CDS: "<<counter2<<endl;
}

void optionCDArtist()
{
    //Precondition:
    assert(true);
    /*Postcondition:
    Laat alle cd's van een artiest zien en het aantal cd's van deze artiest.
    */
    char searchCD[MAXFILENAME];
    bool finished=false;
    int counter = 0;
    string CDarray[MAX_NR_OF_TRACKS];
    int counter2=0;
    TrackDisplay TD={true,true,true,false,false,false,false,false};
    cin.get();

    while(!finished && counter < MAXFILENAME)
    {
        searchCD[counter]= cin.get();
        if(searchCD[counter]=='\n')
        {
            searchCD[counter]='\0';
            finished = true;
        }
        counter++;
    }
    for(int i = 0 ;i < MAX_NR_OF_TRACKS; i++)
    {
        if(match(searchCD, MusicDB[i].artist))
        {
            bool finished = false;
            for(int k = 0; k < MAX_NR_OF_TRACKS; k++)
            {
                if(match(MusicDB[i].cd, CDarray[k]))
                {
                    finished = true;
                    break;
                }

            }
                if(!finished)
                {
                    show_track(MusicDB[i], TD);
                    CDarray[counter2]=MusicDB[i].cd;
                    counter2++;
                }
        }
    }
    cout<<"The number of CDs: "<<counter2<<endl;
}

void optionCDS()
{
    //Precondition:
    assert(true);
    /*Postcondition:
    Zoekt alle cd's en laat het aantal nummers op een cd zien.
    */
    string searchCD [MAX_NR_OF_TRACKS];
    int counter = 0 ;
    for(int i = 0 ;i < MAX_NR_OF_TRACKS; i++)
    {
        bool finished = false;
        for(int k = 0; k < MAX_NR_OF_TRACKS; k++)
        {
            if(match(MusicDB[i].cd, searchCD[k]))
            {
                finished = true;
                break;
            }
        }
        if(!finished)
        {
            searchCD[counter]=MusicDB[i].cd;
            counter++;
        }
    }
    cout<<"The total number of CDs: "<<counter<<endl;
}

void optionTime()
{
    //Precondition:
    assert(true);
    /*Totale muziektijd wordt berekend en weergegeven.. */
    Length temp;
    temp.minutes=0;
    temp.seconds=0;
    for(int i = 0; i < MAX_NR_OF_TRACKS; i++)
    {
        temp=temp+MusicDB[i].time;
    }
    cout<<temp<<endl;
}

void commands()
{
    bool finished = false;
    char option[MAXFILENAME];

    while(!finished)
    {
        cout<<'\n'<<"Please enter a valid command: ";
        cin>>option;
        switch(string_to_enum(option))
        {
        case track:optionTrack(); break;
        case artist:optionArtist(); break;
        case cd: optionCD();break;
        case cdsA:optionCDArtist(); break;
        case cds: optionCDS(); break;
        case timing: optionTime(); break;
        case stop: finished = true; break;
        default: cout<<"Invalid command, please try again!"<<endl; break;
        }
        cin.clear();
    }
}

int main()
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    De muziekdatabase "Nummers.txt" is (indien aanwezig en correct geformateerd) ingelezen.
    De gebruiker is in staat geweest database queries te stellen en heeft de antwoorden op deze
    queries gezien.
*/
    read_database();
    commands();
    return 0;
}

